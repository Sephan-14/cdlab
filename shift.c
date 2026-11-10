#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[200], tokens[100], stk[100];
int n = 0, top = -1;

void printStack() {
    for (int i = 0; i <= top; i++) {
        if (stk[i] == 'i')
            printf("id");
        else
            printf("%c", stk[i]);
    }
}

void printInput(int pos) {
    for (int i = pos; i < n; i++) {
        if (tokens[i] == 'i')
            printf("id");
        else
            printf("%c", tokens[i]);
    }
}

int precedence(char op) {
    if (op == '*') return 2;
    if (op == '+') return 1;
    return 0;
}

void reduce(int pos) {
    char lookahead = (pos < n) ? tokens[pos] : '\0';
    int changed = 1;

    while (changed) {
        changed = 0;
        // id -> E
        if (top >= 0 && stk[top] == 'i') {
            stk[top] = 'E';
            printf("\n");
            printStack();
            printf("\t");
            printInput(pos);
            printf("\tREDUCE id -> E\n");
            changed = 1;
        }
        // (E) -> E
        else if (top >= 2 &&
                 stk[top - 2] == '(' &&
                 stk[top - 1] == 'E' &&
                 stk[top] == ')') {
            top -= 2;
            stk[top] = 'E';

            printf("\n");
            printStack();
            printf("\t");
            printInput(pos);
            printf("\tREDUCE (E) -> E\n");
            changed = 1;
        }
        // E op E -> E, according to precedence
        else if (top >= 2 &&
                 stk[top - 2] == 'E' &&
                 (stk[top - 1] == '+' || stk[top - 1] == '*') &&
                 stk[top] == 'E') {

            char op = stk[top - 1];

            if (lookahead == '\0' || lookahead == ')' ||
                precedence(op) >= precedence(lookahead)) {

                top -= 2;
                stk[top] = 'E';

                printf("\n");
                printStack();
                printf("\t");
                printInput(pos);
                printf("\tREDUCE E%cE -> E\n", op);
                changed = 1;
            }
        }
    }
}

int main() {
    printf("Grammar:\n");
    printf("E -> E+E | E*E | (E) | id\n");

    printf("\nEnter expression: ");
    fgets(input, sizeof(input), stdin);

    // Convert input into tokens.
    // Each complete "id" is represented internally by 'i'.
    for (int i = 0; input[i] != '\0'; i++) {
        if (isspace((unsigned char)input[i]))
            continue;

        if (input[i] == 'i' && input[i + 1] == 'd') {
            tokens[n++] = 'i';
            i++;
        }
        else if (input[i] == '+' || input[i] == '*' ||
                 input[i] == '(' || input[i] == ')') {
            tokens[n++] = input[i];
        }
        else {
            printf("\nInvalid token in input.\n");
            return 1;
        }
    }

    printf("\nSTACK\t\tINPUT\t\tACTION\n");

    for (int i = 0; i < n; i++) {
        stk[++top] = tokens[i];

        printf("\n");
        printStack();
        printf("\t\t");
        printInput(i + 1);

        if (tokens[i] == 'i')
            printf("\t\tSHIFT id\n");
        else
            printf("\t\tSHIFT %c\n", tokens[i]);

        reduce(i + 1);
    }

    if (top == 0 && stk[0] == 'E')
        printf("\n\nString Accepted!\n");
    else
        printf("\n\nSyntax Error: String Rejected!\n");

    return 0;
}


/*The parser uses two main structures:
- Input (tokens): stores the tokens that still need to be processed.
- Stack (stk): stores the tokens that have already been shifted.
The parser performs two operations:
- SHIFT: Move the next input token onto the stack.
- REDUCE: Replace a matching pattern on the stack with the non-terminal E.

Step 1: Initialize
1. Read the input expression.
2. Remove whitespace.
3. Convert every id into a single internal symbol i.
4. Initialize the stack as empty (top = -1).
For example:
Input: id+id*id
Internal tokens: i+i*i
We use i internally to represent the complete id token.

Step 2: Shift operation
1. Read the next token from the input.
2. Push it onto the stack.
3. Print the current stack, remaining input, and SHIFT operation.
For example:
Stack: i
Input: +id*id
Action: SHIFT id

Step 3: Reduce id to E
Check whether the top of the stack contains i.
If it does:
id -> E
Replace i with E.
Example:
Before: i
After:  E

Step 4: Reduce parentheses
Check whether the top three stack symbols are:
(E)
If they are, replace all three symbols with E.
Example:
Before: (E)
After:  E
This allows nested expressions such as:
((id+id)*id)

Step 5: Reduce arithmetic expressions
Check whether the top three stack symbols match:
E + E
or
E * E
Before reducing, check the next input operator.
The rules are:
Stack pattern	Next input	Action
E+E	*	Do not reduce yet
E+E	+	Reduce
E*E	+	Reduce
E*E	*	Reduce
E+E or E*E	)	Reduce
E+E or E*E	End of input	Reduce
This is how the parser implements precedence and left associativity.

Step 6: Repeat reductions
After every SHIFT operation:
1. Check for id -> E.
2. Check for (E) -> E.
3. Check whether an arithmetic expression can be reduced.
4. Continue until no more reductions are possible.

Step 7: Check acceptance
After processing all input:
- If the stack contains exactly one symbol, E, accept the expression.
- Otherwise, reject it.*/