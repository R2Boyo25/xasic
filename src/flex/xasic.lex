/* -*- mode: c; compile-command: "flex xasic.lex && gcc lex.yy.c" -*- */

%option noyywrap

DIGIT    [0-9]
IDENT    [a-zA-Z][a-zA-Z0-9]*

%%

(?:"//"|"#").* /* NOM (comments)*/
[ \t\n]+   /* NOM */

.+        printf("%d: That's a flippin' lexin' error there, bud. '%s'\n", yyget_lineno(), yytext);
