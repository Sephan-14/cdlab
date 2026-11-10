#include <stdio.h>
#include <ctype.h>

char terminals[] = "i+*()$";

char table[6][6] = {
    //  i    +    *    (    )    $
    {  ' ', '>', '>', ' ', '>', '>' },
    {  '<', '>', '<', '<', '>', '>' },
    {  '<', '>', '>', '<', '>', '>' },
    {  '<', '<', '<', '<', '=', ' ' },
    {  ' ', '>', '>', ' ', '>', '>' },
    {  '<', '<', '<', '<', ' ', '=' }
};

// Find the index of a terminal
int getIndex(char ch) {
    int i;
    for (i = 0; i < 6; i++) {
        if (terminals[i] == ch) {
            return i;
        }
    }
    return -1;
}
// Find the rightmost terminal in the stack
int topTerminal(char stack[], int top) {
    int i;

    for (i = top; i >= 0; i--) {
        if (getIndex(stack[i]) != -1) {
            return i;
        }
    }
    return -1;
}
// Reduce according to grammar rules
int reduceHandle(char stack[], int *top) {

    // i -> N
    if (*top >= 1 && stack[*top] == 'i') {
        stack[*top] = 'N';
        return 1;
    }

    // (N) -> N
    if (*top >= 3 &&
        stack[*top - 2] == '(' &&
        stack[*top - 1] == 'N' &&
        stack[*top] == ')') {

        *top = *top - 2;
        stack[*top] = 'N';
        return 1;
    }
    // N+N -> N
    if (*top >= 3 &&
        stack[*top - 2] == 'N' &&
        stack[*top - 1] == '+' &&
        stack[*top] == 'N') {

        *top = *top - 2;
        stack[*top] = 'N';
        return 1;
    }
    // N*N -> N
    if (*top >= 3 &&
        stack[*top - 2] == 'N' &&
        stack[*top - 1] == '*' &&
        stack[*top] == 'N') {

        *top = *top - 2;
        stack[*top] = 'N';
        return 1;
    }

    return 0;
}
int main() {

    char stack[100];
    char input[100];
    char expression[100];

    int top = 0;
    int ptr = 0;
    int i, j = 0;
    int row, col;
    char relation;

    printf("Enter an arithmetic expression: ");

    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        printf("Invalid input\n");
        return 0;
    }
    // Convert operands into i
    for (i = 0; expression[i] != '\0'; i++) {

        if (isspace((unsigned char)expression[i])) {
            continue;
        }

        if (isalnum((unsigned char)expression[i])) {
            input[j++] = 'i';
        }
        else if (expression[i] == '+' ||
                 expression[i] == '*' ||
                 expression[i] == '(' ||
                 expression[i] == ')') {

            input[j++] = expression[i];
        }
        else {
            printf("Invalid character\n");
            return 0;
        }
    }

    // Add end marker
    input[j++] = '$';
    input[j] = '\0';

    // Initialize stack
    stack[top] = '$';
    stack[top + 1] = '\0';

    printf("\nSTACK\t\tINPUT\t\tACTION\n");

    while (1) {
        // Acceptance condition
        if (top == 1 &&
            stack[0] == '$' &&
            stack[1] == 'N' &&
            input[ptr] == '$') {

            printf("%s\t\t%s\t\tACCEPT\n",
                   stack, input + ptr);

            printf("\nString is ACCEPTED\n");
            break;
        }
        // Find topmost terminal
        row = topTerminal(stack, top);
        // Find current input terminal
        col = getIndex(input[ptr]);

        if (row < 0 || col < 0) {
            printf("\nString is NOT ACCEPTED\n");
            break;
        }

        relation = table[getIndex(stack[row])][col];
        // SHIFT operation
        if (relation == '<' || relation == '=') {

            if (input[ptr] == '$') {
                printf("\nString is NOT ACCEPTED\n");
                break;
            }
            printf("%s\t\t%s\t\tSHIFT %c\n",
                   stack, input + ptr, input[ptr]);

            stack[++top] = input[ptr];
            stack[top + 1] = '\0';

            ptr++;
        }
        // REDUCE operation
        else if (relation == '>') {

            printf("%s\t\t%s\t\t", stack, input + ptr);

            if (reduceHandle(stack, &top)) {

                stack[top + 1] = '\0';

                printf("REDUCE\n");
            }
            else {
                printf("INVALID REDUCTION\n");
                printf("\nString is NOT ACCEPTED\n");
                break;
            }
        }
        // Invalid relation
        else {
            printf("%s\t\t%s\t\tERROR\n",
                   stack, input + ptr);

            printf("\nString is NOT ACCEPTED\n");
            break;
        }
    }
    return 0;
}



/*Updated algorithm for practical record
You can write the following algorithm in your lab record.

Algorithm: Operator Precedence Parsing
1. Start.
2. Declare the required arrays:
   - terminals[] to store terminal symbols.
   - table[][] to store operator precedence relations.
   - stack[] to maintain the parsing stack.
   - input[] to store the input expression.
3. Initialize the stack pointer top = 0 and input pointer ptr = 0.
4. Define the operator precedence table for the given grammar.
5. Read the arithmetic expression from the user.
6. Remove whitespace and convert every operand into the symbol i.
7. Append $ to the input string to indicate the end of input.
8. Initialize the stack with $.
9. Repeat the following steps until the expression is accepted or rejected:
   - Find the topmost terminal in the stack using the topTerminal() function.
   - Find the position of the current input terminal using the getIndex() function.
   - If either terminal is invalid, reject the expression.
   - Check the acceptance condition: if the stack contains $N and the current input symbol is $, accept the expression.
   - Retrieve the precedence relation from the operator precedence table.
10. If the relation is < or =, perform the SHIFT operation:
    - Push the current input symbol onto the stack.
    - Increment the stack pointer and input pointer.
11. If the relation is >, perform the REDUCE operation:
    - Check whether the top of the stack matches any valid grammar production.
    - If the pattern is i, replace it with N.
    - If the pattern is (N), replace it with N.
    - If the pattern is N+N, replace it with N.
    - If the pattern is N*N, replace it with N.
    - If no valid pattern is found, reject the expression.
12. If the precedence relation is blank, reject the expression.
13. Repeat until the input is accepted or rejected.
14. Display the result.
15. Stop.*/