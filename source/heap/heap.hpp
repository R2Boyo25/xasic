#pragma once

#include <vector>
#include <map>
#include <string>
#include "../data/variable.hpp"

class Heap {
public:
  Heap();

  bool exists(std::string name);
  bool isLocal(std::string name);
  void enterScope(std::string name);
  void exitScope();
  void setGlobal(std::string name);
  std::vector<int> findReferences(std::string name);
  std::string getScope();
  std::vector<std::string> getGlobals();
  
  Variable get(std::string name);
  void set(std::string name, Variable value);
  void printHeap();
    
private:
  std::vector<std::string> heapins = {};
  std::map<std::string, Variable> heapmap = {};

  bool alreadyDefinedLocally(std::string name);
};

class VariableInstruction {
public:
  VariableInstruction();
  VariableInstruction(std::string instruction);
  std::string variable_name;
  std::string internal_name;
};

// v{ariable} varname internal_variable_name
// s{cope} scopename
// e{xitscope}
// TODO: g{lobal} varname
//   Tells heap that variable should be kept once scope is left.
