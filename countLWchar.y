
%{
#include <stdio.h>

int lines = 0;
int words = 0;
int characters = 0;
%}

%token NEWLINE SPACE WORD

%%
input:
      /* empty */
    | input NEWLINE {
          lines++;
          characters++;
      }
    | input SPACE {
          characters += yyleng;
      }
    | input WORD {
          words++;
          characters += yyleng;
      }
    ;
%%

int main()
{
    printf("Enter text (Ctrl+D to stop):\n");
    yyparse();

    printf("\nNumber of lines      : %d", lines);
    printf("\nNumber of words      : %d", words);
    printf("\nNumber of characters : %d\n", characters);

    return 0;
}

int yyerror(char *s)
{
    return 0;
}
