/* Q9: BNF -> YACC + Abstract Syntax Tree.
   BNF used (swap in the one from your sheet):
     stmt   ::= id = expr
     expr   ::= expr + term | expr - term | term
     term   ::= term * factor | term / factor | factor
     factor ::= ( expr ) | id | num
   Every rule builds a tree node: operator in the middle, operands as children. */
   
%{
typedef struct node { char label[32]; struct node *l, *r; } Node;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(); void yyerror(const char *s);

Node *mk(const char *label, Node *l, Node *r) {      // create one tree node
    Node *p = malloc(sizeof(Node));
    strcpy(p->label, label); p->l = l; p->r = r;
    return p;
}
void show(Node *p, int depth) {                      // print tree, children indented under parent
    if (!p) return;
    printf("%*s%s\n", depth * 4, "", p->label);
    show(p->l, depth + 1);
    show(p->r, depth + 1);
}
%}
%union { char *str; struct node *n; }
%token <str> ID NUM
%type  <n> stmt expr term factor
%%
input  : /* empty */ | input line ;
line   : '\n'
       | stmt '\n'            { printf("AST:\n"); show($1, 0); }
       | error '\n'           { yyerrok; } ;
stmt   : ID '=' expr          { $$ = mk("=", mk($1, 0, 0), $3); } ;
expr   : expr '+' term        { $$ = mk("+", $1, $3); }
       | expr '-' term        { $$ = mk("-", $1, $3); }
       | term                 { $$ = $1; } ;
term   : term '*' factor      { $$ = mk("*", $1, $3); }
       | term '/' factor      { $$ = mk("/", $1, $3); }
       | factor               { $$ = $1; } ;
factor : '(' expr ')'         { $$ = $2; }
       | ID                   { $$ = mk($1, 0, 0); }
       | NUM                  { $$ = mk($1, 0, 0); } ;
%%
void yyerror(const char *s) { printf("Syntax error\n"); }
int main() { printf("Enter statements like  x = a + b * 2  (Ctrl+D to quit):\n"); yyparse(); return 0; }
