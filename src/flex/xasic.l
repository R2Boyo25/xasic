/* -*- mode: c -*- */

%top{
  extern char *location;
  #define _POSIX_C_SOURCE 200809L
  #include <string.h>
  #include <stdbool.h>
  #include "../parser/xasic.h"
}

%option yylineno bison-bridge bison-locations batch never-interactive noinput nounput noyywrap
%x INCLUDE

DIGIT    [0-9]
IDENT    [a-zA-Z][a-zA-Z0-9]*

%%

 /* Included files AND main files */
[:DIGIT:]+      yylval->num = atoi(yytext); return INT;
(?:"//"|"#").*  /* NOM (comments)*/
"/*"[\w\W]*"*/" /* multi-line comments */
[ \t\n]+        /* NOM */ (void)yylloc;
true|false      yylval->_bool = strcmp(yytext, "true") ? true : false; return BOOL;

"fn"            return FN;
"returning"     return RETURNING;
"do"            return DO;

[:IDENT:]       yylval->str = strdup(yytext); return IDENT;

 /* Only in main files. */
<INITIAL>[  ]*  /* a */

 /* Only in included files */
<INCLUDE>[  ]*  /* a */

.               return yytext[0];
