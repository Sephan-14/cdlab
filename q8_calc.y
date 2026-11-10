/* Q8: Calculator. Precedence lines at the top handle BODMAS for us. */
%{
#include <stdio.h>
int yylex(); void yyerror(const char *s);
%}
%define api.value.type {double}
%token NUM
%left '+' '-'            /* lower precedence  */
%left '*' '/'            /* higher precedence */
%right UMINUS            /* unary minus, highest */
%%
input : /* empty */ | input line ;
line  : '\n'
      | expr '\n'          { printf("= %g\n", $1); }
      | error '\n'         { yyerrok; } ;
expr  : expr '+' expr      { $$ = $1 + $3; }
      | expr '-' expr      { $$ = $1 - $3; }
      | expr '*' expr      { $$ = $1 * $3; }
      | expr '/' expr      { if ($3 == 0) { yyerror("division by zero"); $$ = 0; } else $$ = $1 / $3; }
      | '-' expr %prec UMINUS { $$ = -$2; }
      | '(' expr ')'       { $$ = $2; }
      | NUM ;
%%
void yyerror(const char *s) { printf("Error: %s\n", s); }
int main() { printf("Enter expressions (Ctrl+D to quit):\n"); yyparse(); return 0; }
