#include "lex.hpp"

lexer::CharStream::CharStream() {

}

lexer::CharStream::CharStream(std::stringstream stream) {
  this->stream = &stream;
}

std::string lexer::CharStream::getWhile(std::function<bool(char)> filter, size_t max_chars = 0) {
  size_t index = 0;

  #error todo
}

lexer::Lexer::Lexer(CharStream cs) {
  this->cs = cs;
}

