/* comment block */

%{
#include <stdio.h>
#include<string.h>
%}
%option noyywrap

%%

.*seph.*    { printf("%s -> REJECTED\n", yytext); }
.+          { printf("%s -> ACCEPTED\n", yytext); }
\n          ;

%%

int main() { yylex(); return 0; }