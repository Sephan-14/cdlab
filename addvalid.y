
%{
#include <stdio.h>
%}

%token ID NUM INVALID

%%
statement:
    ID '=' ID '+' NUM
    ;
%%

int main()
{
    printf("Enter an expression: ");

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
