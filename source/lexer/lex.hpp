#pragma once

#include <string>
#include <vector>

namespace lexer {
  enum TokenType {
    
  };

  struct Token {
    TokenType   type;
    std::string lexeme;
  };
  
  std::vector<Token> tokenize(std::string raw_text);
}
