%{
#include <cstdlib>
#include "lex.hpp"
using namespace yy;

/*int yyFlexLexer::yywrap() { return 1; }*/
/*FILE* yyin;
FILE* yyout;*/
// reentrant
%}

%option c++ interactive noyywrap noyylineno nodefault

integer [0-9]+
float [0-9]+\.[0-9]+
string (["'])(?:[^\1\\]|\\.)*?\1

%%

{integer}   yylval->emplace<long long>(strtoll(yytext, nullptr, 10)); return Parser::token::INTEGER;
{float}     yylval->emplace<double>(strtod(yytext, nullptr)); return Parser::token::FLOAT;
{string}    yylval->emplace<std::string>(yytext); return Parser::token::STRING;

.           /* No action when no match. */
  