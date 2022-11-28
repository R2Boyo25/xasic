%skeleton "lalr1.cc"
%require "3.2"
%define api.parser.class {Parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define parse.error verbose
%locations
%parse-param {Scanner* scanner}

%code requires {
#include <FlexLexer.h>
#include "../flex/lex.hpp"
class Scanner;
int Scanner::lex(yy::Parser::semantic_type *yylval);
#include<map>
#include<list>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
/*#define ENUM_IDENTIFIERS(o) \
        o(undefined)
        o(function)
        o(parameter)
        o(variable)
#define o(n) n,
enum class id_type { ENUM_IDENTIFIERS(o) };
#undef o

struct identifier {
    id_type     type  = id_type::undefined;
    std::size_t index = 0;
    std::string name;
}*/

}//%code requires

%code {
    #define yylex(x) scanner->lex(x)
}

%token END 0
%token IDENTIFIER INTEGER FLOAT STRING
%token LET "let" DATA "data" READ "read" RESTORE "restore" DIM "dim"
%token MULT "*" ADD "+" DIV "/" SUB "-"
%token COMMA ","
%token COLONCOLON "::"

%left "+" "-"
%left "*" "/"

%start program

%% 

program: 
|        program line
;

line: INTEGER statement
|     IDENTIFIER statement
;

statement: variable_definition
|          IDENTIFIER expression_list
;

expression_list: expression_list "," expression
|                expression
;

variable_definition: "let" IDENTIFIER "::" IDENTIFIER "=" expression
|                    IDENTIFIER "::" IDENTIFIER "=" expression
;

expression: expression "*" expression
|           expression "+" expression
|           expression "/" expression
|           expression "-" expression
|           "(" expression ")"
|           data
;

data: IDENTIFIER
|     INTEGER
|     FLOAT
|     STRING
;
