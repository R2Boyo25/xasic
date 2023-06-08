#pragma once

#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <memory>

namespace lexer {
  class CharStream {
  public:
    CharStream();
    CharStream(std::stringstream stream);
    
    std::string getWhile(std::function<bool(char)> filter, size_t max_chars = 0);

    // #include <cctype>
    //   isalpha
    //   isupper
    //   islower
    //   isalnum
    //   isdigit
    //   isblank
    //   isspace
    //   iscntrl
    //   isprint
    //   isxdigit // hex
    //   ispunct
  private:
    std::stringstream *stream;
  };

  class Lexer {
  public:
    Lexer(CharStream cs);

  private:
    CharStream cs;
  };
}
