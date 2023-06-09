#pragma once

#include <variant>
#include <string>
#include <vector>
#include <tuple>

class Data;

typedef int   inttype;
typedef float decimaltype;

typedef std::variant<std::string, std::vector<Data>, inttype, decimaltype> datavariant;

// 1: string
// 2: vector of Data
// 3: integer
// 4: float

extern std::vector<std::string> namedtypes;

class Data {
public:
  datavariant data;
  uint type = -1;

  Data();
  Data(datavariant data);
  template <typename T> T get() {
    return std::get<T>(data);
  }
};
