#include"data.hpp"

std::vector<std::string> namedtypes = {
    "string",
    "vector",
    "int",
    "float"
};

Data::Data() {

}

Data::Data(datavariant data) {
    this->data = data;
    this->type = data.index();
}

/*
template <typename T> T Data::get() {
    
}
*/