#pragma once

#include<vector>
#include<map>
#include<string>
#include"../data/variable.hpp"

class Heap {
    public:
        Heap();

        bool exists(std::string name);
        bool isLocal(std::string name);
        void enterScope(std::string name);
        void exitScope();
        std::vector<int> findReferences(std::string name);
        std::string getScope();
        
        Variable get(std::string name);
        void set(std::string name, Variable value);
        void printHeap();
    
    private:
        std::vector<std::string> heapins = {};
        std::map<std::string, Variable> heapmap = {};

        bool alreadyDefinedLocally(std::string name);
};

class RegexInstruction {
public:
  RegexInstruction();
  RegexInstruction(std::string instruction);
  std::string variable_name;
  std::string internal_name;
};

// var varname internal_variable_name
// scope scopename
// TODO: global varname
//   Tells heap that variable should be kept once scope is left.
