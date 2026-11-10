/* Q7: valid variable = letter followed by any number of letters/digits */

%{
#include <stdio.h>
int yylex(); void yyerror(const char *s);
%}
%token LETTER DIGIT NL

%%

start : var NL        { printf("Valid variable\n"); return 0; } ;
var   : LETTER rest ;
rest  : LETTER rest | DIGIT rest | /* empty */ ;

%%

void yyerror(const char *s) { printf("Invalid variable\n"); }
int main() { printf("Enter a variable: "); yyparse(); return 0; }