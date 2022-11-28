#include"variable.hpp"

Variable::Variable() {

};

Variable::Variable(std::string type, Data data, std::string edata) {
    this->type  = type;
    this->data  = data;
    this->edata = edata;
}

Variable Variable::clone() {
    return Variable(this->type, this->data, this->edata);
}