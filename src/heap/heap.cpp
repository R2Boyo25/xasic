#include "heap.hpp"
#include <random>
#include <iostream>
#include <algorithm>
#include <regex>

enum InstructionType {
  Var,
  Scope,
  ExitScope,
  Global
};

std::vector<std::regex> instructionRegexes = {
  std::regex("v (.+) (.+)"),
  std::regex("s (.+)"),
  std::regex("e"),
  std::regex("g (.+)")
};

std::string randstringchars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char randomCharacter() {
  return randstringchars[rand() % randstringchars.size()];
}

std::string randomString() {
  std::string str = "                                ";

  std::generate(str.begin(), str.end(), randomCharacter);

  return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

VariableInstruction::VariableInstruction() {
  this->variable_name = "";
  this->internal_name = "";
}

VariableInstruction::VariableInstruction(std::string instruction) {
  std::smatch variable_match;

  std::regex_match(instruction, variable_match, instructionRegexes[InstructionType::Var]);
  
  this->variable_name = variable_match[1].str();
  this->internal_name = variable_match[2].str();
}

Heap::Heap() {}

bool instructionIsName(std::string instruction, std::string name) {
  return VariableInstruction(instruction).variable_name == name;
}

bool Heap::exists(std::string name) {
  for (auto& i: this->heapins) {
    if (instructionIsName(i, name)) {
      return true;
    }
  }

  return false;
  //return this->heapmap.count(name) > 0;
}

InstructionType identifyInstruction(std::string instruction) {
  for (size_t i = 0; i < instructionRegexes.size(); i++) {
    std::regex re = instructionRegexes[i];
    if (std::regex_match(instruction, re)) {
      return static_cast<InstructionType>(i);
    }
  }

  throw "Unknown instruction \"" + instruction + "\"";
}

bool Heap::isLocal(std::string name) {
  if (!this->exists(name)) {
    return false;
  }

  std::string scope = "";

  for (auto& i : this->heapins) {
    switch (identifyInstruction(i)) {
    case InstructionType::Var: {
      if (VariableInstruction(i).variable_name == name) {
        if (scope != this->getScope()) {
          return false;
        }

        return true;
      }
      break;
    }
    case InstructionType::Scope: {
      std::smatch m;
      std::regex_match(i, m, instructionRegexes[InstructionType::Var]);
      scope = m[1].str();
      break;
    }
    default: ;
    }
  }

  return true;
}

std::vector<std::string> Heap::getGlobals() {
  std::vector<std::string> globals = {};
  
  for (long i = this->heapins.size() - 1; i >= 0; i--) {
    switch (identifyInstruction(this->heapins[i])) {
    case InstructionType::Global: {
      std::smatch m;
      std::regex_match(this->heapins[i], m, instructionRegexes[InstructionType::Global]);
      globals.push_back(m[1].str());
    }
    case InstructionType::Scope: {
      return globals;
      break;
    }
    default: ;
    }
  }

  return globals;
}

void Heap::enterScope(std::string name) {
  heapins.push_back("s " + name);
}

void Heap::exitScope() {
  if (this->getScope() == "") {
    return;
  }

  long scopebegin = 0;
  std::vector<std::string> globals = this->getGlobals();
  std::vector<std::string> preserved = {};

  for (long i = this->heapins.size() - 1; i >= 0; i--) {
    switch (identifyInstruction(this->heapins[i])) {
    case InstructionType::Scope: {
      scopebegin = i;
      break;
    }
    default: ;
    }
  }
  
  for (long i = this->heapins.size() - 1; i >= scopebegin - 1; i--) {
    switch (identifyInstruction(this->heapins[i])) {
    case InstructionType::Var: {
      VariableInstruction ins(heapins[i]);
	  
      std::string varname = ins.variable_name;

      bool isGlobal = false;
      
      for (long j = globals.size() - 1; j >= 0; j--) {
        if (ins.variable_name == globals[j]) {
          isGlobal = true;
        }
      }

      if (isGlobal) {
        preserved.push_back(this->heapins[i]);
      }

      if (this->isLocal(varname)) {
        this->heapmap.erase(ins.internal_name);
      }

      this->heapins.pop_back();
      break;
    }
      
    case InstructionType::Global: {
      this->heapins.pop_back();
      break;
    }
    default: ;
    }
  }

  for (long i = preserved.size() - 1; i >= 0; i--) {
    this->heapins.push_back(preserved[i]);
  }
}

std::vector<int> Heap::findReferences(std::string name) {
  std::vector<int> refindexes = {};
  
  if (!this->exists(name)) {
    return refindexes;
  }

  for (long i = this->heapins.size() - 1; i >= 0; i--) {
    switch (identifyInstruction(this->heapins[i])) {
    case InstructionType::Var: {
      if (VariableInstruction(heapins[i]).variable_name == name) {
        refindexes.push_back(i);
      }
      
      break;
    }
    default: ;
    }
  }

  return refindexes;
}

std::string Heap::getScope() {
  for (long i = this->heapins.size() - 1; i >= 0; i--) {
    switch (identifyInstruction(this->heapins[i])) {
    case InstructionType::Scope: {
      std::smatch m;
      std::regex_match(this->heapins[i], m, instructionRegexes[InstructionType::Scope]);
      
      return m[1].str();
    }
    default: ;
    }
  }

  return "";
}

Variable Heap::get(std::string name) {
  if (!this->exists(name)) {
    throw "Variable " + name + " is not defined";
  }

  std::string internal_name = "";
    
  for (auto& i : this->heapins) {
    switch (identifyInstruction(i)) {
    case InstructionType::Var: {
      VariableInstruction ins(i);
      
      if (ins.variable_name == name) {
        internal_name = ins.internal_name;
      }
      
      break;
    }
    default: ;
    }
  }

  return this->heapmap[internal_name];
}

void Heap::setGlobal(std::string name) {
  this->heapins.push_back("g " + name);
}

bool Heap::alreadyDefinedLocally(std::string name) {
  for (long i = this->heapins.size() - 1; i >= 0; i--) {
    switch (identifyInstruction(this->heapins[i])) {
    case InstructionType::Var: {
      std::string varname = VariableInstruction(heapins[i]).variable_name;

      if (varname == name) {
        return true;
      }
      
      break;
    }
    case InstructionType::Scope: {
      return false;
    }
    default: ;
    }
  }

  return false;
}

void Heap::set(std::string name, Variable value) {
  std::string internal_name = randomString();
  
  if (!this->alreadyDefinedLocally(name)) {
    this->heapins.push_back("v " + name + " " + internal_name);
  }

  this->heapmap[internal_name] = value;
}

void Heap::printHeap() {
  std::cout << "== heap dump ==" << std::endl;
  for (auto& i : this->heapins) {
    std::cout << i << std::endl;
  }
}
