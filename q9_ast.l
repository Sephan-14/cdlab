%{
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
%}
%option noyywrap
%%
[0-9]+                    { yylval.str = strdup(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*    { yylval.str = strdup(yytext); return ID; }
[ \t]                     ;
\n                        return '\n';
.                         return yytext[0];
%%
