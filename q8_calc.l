%{
#include "y.tab.h"
#include <stdlib.h>
%}
%option noyywrap
%%
[0-9]+(\.[0-9]+)?   { yylval = atof(yytext); return NUM; }
[ \t]               ;
\n                  return '\n';
.                   return yytext[0];
%%
