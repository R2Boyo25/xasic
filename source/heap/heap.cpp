#include"heap.hpp"
#include<random>
#include<iostream>
#include<algorithm>
#include<regex>

std::string randstringchars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
std::regex variable_regex("var (.+) (.+)");

char randomCharacter() {
  return randstringchars[rand() % randstringchars.size()];
}

std::string randomString()
{
     std::string str = "                                ";

     std::generate(str.begin(), str.end(), randomCharacter);

     return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

RegexInstruction::RegexInstruction() {
  this->variable_name = "";
  this->internal_name = "";
}

RegexInstruction::RegexInstruction(std::string instruction) {
  std::smatch variable_match;

  std::regex_match(instruction, variable_match, variable_regex);
  
  this->variable_name = variable_match[1].str();
  this->internal_name = variable_match[2].str();
}

Heap::Heap() {};

bool instructionIsName(std::string instruction, std::string name) {
  return RegexInstruction(instruction).variable_name == name;
}

bool Heap::exists(std::string name) {
  for (auto& i: this->heapins) {
    if (instructionIsName(i, name)) {
      return true;
    }
  }

  return false;
  //return this->heapmap.count(name) > 0;
};

bool Heap::isLocal(std::string name) {
    if (!this->exists(name)) {
        return false;
    }

    std::string scope = "";

    for (auto& i : this->heapins) {
        if (i.find("scope") != std::string::npos) {
            scope = i.substr(i.find("scope") + 6, i.size()-1);
        }

        if (i.find("var") != std::string::npos) {
            if (i.find(name, i.find("var") + 3) != std::string::npos) {
                if (scope != this->getScope()) {
                    return false;
                }

		return true;
            }
        }
    }

    return true;
};

void Heap::enterScope(std::string name) {
    heapins.push_back("scope " + name);
};

void Heap::exitScope() {
    if (this->getScope() == "") {
        return;
    }

    int scopebegin = 0;

    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("scope") != std::string::npos) {
            scopebegin = i;
            break;
        }
    }

    for (int i=this->heapins.size()-1; i>=scopebegin-1; i--) {
        if (this->heapins[i].find("var") != std::string::npos) {
	  RegexInstruction ins(heapins[i]);
	  
	  std::string varname = ins.variable_name;

            if (this->isLocal(varname)) {
                this->heapmap.erase(ins.internal_name);
            }

            this->heapins.pop_back();
        }
    }
};

std::vector<int> Heap::findReferences(std::string name) {
    std::vector<int> refindexes = {};
    if (!this->exists(name)) {
        return refindexes;
    }

    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("var") != std::string::npos) {
	  if (RegexInstruction(heapins[i]).variable_name == name) {
                refindexes.push_back(i);
            }
        }
    }

    return refindexes;
};

std::string Heap::getScope() {
    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("scope") != std::string::npos) {
            return this->heapins[i].substr(this->heapins[i].find("scope") + 6, this->heapins[i].size()-1);
        }
    }

    return "";
};

Variable Heap::get(std::string name) {
    if (!this->exists(name)) {
        throw "Variable " + name + " is not defined";
    }

    std::string internal_name = "";
    
    for (auto& i : this->heapins) {
      if (i.find("var") != std::string::npos) {
	RegexInstruction ins(i);
	if (ins.variable_name == name) {
          internal_name = ins.internal_name;
	}
      }
    }

    return this->heapmap[internal_name];
};

bool Heap::alreadyDefinedLocally(std::string name) {
    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("var") != std::string::npos) {
	  std::string varname = RegexInstruction(heapins[i]).variable_name;

            if (varname == name) {
                return true;
            }
        }

        if (this->heapins[i].find("scope") != std::string::npos) {
            break;
        }
    }

    return false;
}

void Heap::set(std::string name, Variable value) {
  std::string internal_name = randomString();
  
    if (!this->alreadyDefinedLocally(name)) {
      this->heapins.push_back("var " + name + " " + internal_name);
    }

    this->heapmap[internal_name] = value;
};

void Heap::printHeap() {
    std::cout << "== heap dump ==" << std::endl;
    for (auto& i : this->heapins) {
      std::cout << i << std::endl;
    }
}
