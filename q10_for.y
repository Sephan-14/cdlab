/* Q10: syntax check of C FOR statement:  for ( init ; cond ; incr ) body */

%{
#include <stdio.h>
int yylex(); void yyerror(const char *s);
%}
%token FOR ID NUM INC DEC RELOP
%left '+' '-'
%left '*' '/'

%%
start : stmt                       { printf("Valid FOR statement\n"); } ;
stmt  : FOR '(' init ';' cond ';' incr ')' body ;
init  : ID '=' expr | /* empty */ ;
cond  : expr RELOP expr | /* empty */ ;
incr  : ID INC | ID DEC | INC ID | DEC ID | ID '=' expr | /* empty */ ;
body  : ';'                        /* empty body      */
      | simple                     /* single statement */
      | stmt                       /* nested for       */
      | '{' list '}' ;             /* block            */
list  : list simple | list stmt | /* empty */ ;
simple: ID '=' expr ';' | ID INC ';' | ID DEC ';' ;
expr  : expr '+' expr | expr '-' expr | expr '*' expr | expr '/' expr
      | '(' expr ')' | ID | NUM ;
%%

void yyerror(const char *s) { printf("Invalid FOR statement\n"); }
int main() { printf("Enter a for statement (Ctrl+D when done):\n"); yyparse(); return 0; }
