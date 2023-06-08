#pragma once

#include <string>
#include "data.hpp"

class Variable {
    public:
        std::string type;
        Data data;
        std::string edata;

        Variable();
        Variable(std::string type, Data data, std::string edata = "");
        
        Variable clone();
};
