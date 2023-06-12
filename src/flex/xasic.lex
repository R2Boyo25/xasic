/* -*- mode: c -*- */

%{
  extern char *location;
  #include "../parser/y.tab.h"
%}

%option noyywrap yylineno bison-bridge

DIGIT    [0-9]
IDENT    [a-zA-Z][a-zA-Z0-9]*

%%

[:DIGIT:]+     yylval>num = atoi(yytext); return INTEGER;
(?:"//"|"#").* /* NOM (comments)*/
true | false   yylval->str = strdup(yytext); return BOOL;
[ \t\n]+       /* NOM */

[ ] /* .+             printf("%s:%d: That's a flippin' lexin' error there, bud. '%s'\n", location, yyget_lineno(), yytext); */
.+             printf("%s:%d: Lexing error at string '%s'\n", location, yyget_lineno(), yytext);
