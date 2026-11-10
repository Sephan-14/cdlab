#include <stdio.h>
#include <ctype.h>
#include <string.h>

char op_stack[50];
char val_stack[50][10];

int op_top = -1;
int val_top = -1;
int temp_count = 1;

void push_op(char c){
    op_stack[++op_top] = c;
}
char pop_op() {
    return op_stack[op_top--];
}
void push_val(char *val) {
    strcpy(val_stack[++val_top], val);
}
void pop_val(char *val) {
    strcpy(val, val_stack[val_top--]);
}
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
void generate_3ac() {
    char op, arg1[10], arg2[10], temp[10];

    op = pop_op();

    pop_val(arg2);
    pop_val(arg1);

    snprintf(temp, sizeof(temp), "t%d", temp_count++);

    printf("%s = %s %c %s\n", temp, arg1, op, arg2);

    push_val(temp);
}
int main() {
    char expr[100];
    char result_var[10] = "x";
    int expect_operand = 1;

    printf("Enter an expression: ");
    fgets(expr, sizeof(expr), stdin);

    printf("\nInput Expression: %s = %s", result_var, expr);

    printf("\nGenerated Three-Address Code:\n");
    printf("-----------------------------\n");

    for (int i = 0; expr[i] != '\0'; i++) {

        if (isspace((unsigned char)expr[i])) continue;
        if (isalnum((unsigned char)expr[i])) {
            if (!expect_operand) {
                printf("Invalid expression!\n");
                return 1;
            }
            char val[2] = {expr[i], '\0'};
            push_val(val);
            expect_operand = 0;
        }
        else if (expr[i] == '(') {
            if (!expect_operand) {
                printf("Invalid expression!\n");
                return 1;
            }
            push_op('(');
            expect_operand = 1;
        }
        else if (expr[i] == ')') {

            if (expect_operand) {
                printf("Invalid expression!\n");
                return 1;
            }
            while (op_top != -1 && op_stack[op_top] != '(') {
                generate_3ac();
            }
            if (op_top == -1) {
                printf("Invalid expression!\n");
                return 1;
            }
            pop_op();
            expect_operand = 0;
        }

        else if (expr[i] == '+' || expr[i] == '-' ||
                 expr[i] == '*' || expr[i] == '/') {

            if (expect_operand) {
                printf("Invalid expression!\n");
                return 1;
            }
            while (op_top != -1 &&
                   op_stack[op_top] != '(' &&
                   precedence(op_stack[op_top]) >= precedence(expr[i])) {

                generate_3ac();
            }

            push_op(expr[i]);
            expect_operand = 1;
        }
        else {
            printf("Invalid character in expression!\n");
            return 1;
        }
    }
    if (expect_operand) {
        printf("Invalid expression!\n");
        return 1;
    }

    while (op_top != -1) {
        if (op_stack[op_top] == '(') {
            printf("Invalid expression!\n");
            return 1;
        }
        generate_3ac();
    }
    if (val_top != 0) {
        printf("Invalid expression!\n");
        return 1;
    }
    char final_temp[10];
    pop_val(final_temp);
    printf("%s = %s\n", result_var, final_temp);
    return 0;
}

/*Algorithm: Generation of Three-Address Code Using Stacks
1. Start.
2. Declare an operator stack and a value stack.
3. Initialize op_top = -1, val_top = -1, and temp_count = 1.
4. Read the arithmetic expression.
5. Scan the expression from left to right.
6. If the current character is a whitespace, skip it.
7. If the current character is an operand:
   - Check whether an operand is expected.
   - Push the operand onto the value stack.
8. If the current character is an opening parenthesis:
   - Push ( onto the operator stack.
9. If the current character is a closing parenthesis:
   - Pop operators and operands.
   - Generate three-address instructions until ( is found.
   - Remove ( from the operator stack.
10. If the current character is an operator:
    - Compare its precedence with the operator at the top of the operator stack.
    - While the stack operator has greater than or equal precedence, generate three-address code.
    - Push the current operator onto the operator stack.
11. After scanning the entire expression:
    - Check whether the expression is valid.
    - Pop all remaining operators and generate three-address instructions.
12. Pop the final value from the value stack.
13. Assign the final value to the result variable.
14. Stop.*/