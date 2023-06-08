#pragma once
#include <string>

namespace Token {
  class Token {
  public:
    Token(size_t line, size_t column, std::string content) : line(line), column(column), content(content) {};
    
    size_t line;
    size_t column;
    std::string content;
  };
}
