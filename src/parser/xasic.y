%{
#define YYPARSE_PARAM scanner
#define YYLEX_PARAM   scanner

#error test
%}

%locations
%define api.pure
%union {
    int   num;
    char* str;
    bool  _bool;
}

%token <str> STRING
%token <num> NUMBER
%token <bool> BOOL

%%

program: %empty;
