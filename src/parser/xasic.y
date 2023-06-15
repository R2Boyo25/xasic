%{
  #define YYPARSE_PARAM scanner
  #define YYLEX_PARAM   scanner

  #include <stdio.h>
  #include "../flex/xasic.h"
  
  void yyerror(char* message) {
    printf("%s:%d: %s at '%s'", location, yyget_lineno(), message, yytext);
  }
%}

%locations
%define api.pure
%union {
    int   num;
    char  *str;
    bool  _bool;
}

%token <str>  IDENT
%token <num>  INT
%token <bool> BOOL
%token
    FN        "fn"
    RETURNING "returning"
    DO        "do"
    END       "end"
    SEMICOLON ";"
    ;

%%

program
    : YYEOF
    | line
    | program line
    ;

line
    : statement SEMICOLON
    | statement
    | expr SEMICOLON
    | expr
    | SEMICOLON
    ;

statement
    : declaration
    ;

declaration
    : fn_declaration
    ;

fn_declaration
    : FN IDENT '(' arglist ')' RETURNING IDENT
    ;


arglist
    : ident2
    : ident2 arglist
    ;

expr
    : '(' expr ')'
    | INT
    | BOOL
    ;

ident2: IDENT IDENT;
