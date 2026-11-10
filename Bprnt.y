
%{
#include <stdio.h>
%}

%token INVALID

%%
expression:
      /* empty */
    | expression '(' expression ')'
    ;
%%

int main()
{
    printf("Enter parentheses: ");

    if (yyparse() == 0)
        printf("Balanced parentheses\n");
    else
        printf("Not balanced\n");

    return 0;
}

int yyerror(char *s)
{
    return 0;
}
