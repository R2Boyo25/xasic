#include "globals.hpp"
extern "C" {
#include "flex/xasic.h"
}

char* location = (char*) "stdin";

int main(int argc, char** argv) {
  argc--; argv++;

  if (argc > 0) {
    yyin = fopen(argv[0], "r");
    location = argv[0];
  } else {
    yyin = stdin;
  }
    
  yylex();
  
  return RETURNVALUE;
}
