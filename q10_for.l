%{
#include "y.tab.h"
%}
%option noyywrap
%%
"for"                              return FOR;
[0-9]+                             return NUM;
[a-zA-Z_][a-zA-Z0-9_]*             return ID;
"++"                               return INC;
"--"                               return DEC;
"<="|">="|"=="|"!="|"<"|">"        return RELOP;
[ \t\n]                            ;
.                                  return yytext[0];
%%
