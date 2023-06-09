#include "globals.hpp"
extern "C" {
#include "flex/xasic.h"
}
  
int main(int argc, char** argv) {
  argc--; argv++;

  if (argc > 0) {
    yyin = fopen(argv[0], "r");
  } else {
    yyin = stdin;
  }
    
  yylex();
  
  return RETURNVALUE;
}
