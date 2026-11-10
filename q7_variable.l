%{
#include "y.tab.h"
%}
%option noyywrap

%%

[a-zA-Z]   return LETTER;
[0-9]      return DIGIT;
\n         return NL;
.          return yytext[0];     /* anything else -> syntax error */

%%
