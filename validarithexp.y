%{
#include <stdio.h>
%}

%token ID NUM INVALID

%left '+' '-'
%left '*' '/'

%%
input:
      expression
    ;

expression:
      expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | '(' expression ')'
    | ID
    | NUM
    ;
%%

int main()
{
    printf("Enter expression: ");

    if (yyparse() == 0)
        printf("Valid expression\n");
    else
        printf("Invalid expression\n");

    return 0;
}

int yyerror(char *s)
{
    return 0;
}
