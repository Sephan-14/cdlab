
#include <stdio.h>
#include <string.h>

int main() {
    char icode[10][30];
    char str[30], opr[4];

    int i = 0;

    printf("Enter intermediate code (type exit to stop):\n");

    // Read intermediate code
    while (i < 10) {
        scanf("%29s", icode[i]);

        if (strcmp(icode[i], "exit") == 0)
            break;

        i++;
    }
    printf("\n--- Target Code Generation ---\n");

    for (int j = 0; j < i; j++) {

        strcpy(str, icode[j]);

        // Check the basic format: a=b+c
        if (strlen(str) != 5 || str[1] != '=') {
            printf("Invalid intermediate code: %s\n", str);
            continue;
        }
        switch (str[3]) {
            case '+':
                strcpy(opr, "ADD");
                break;

            case '-':
                strcpy(opr, "SUB");
                break;

            case '*':
                strcpy(opr, "MUL");
                break;

            case '/':
                strcpy(opr, "DIV");
                break;

            default:
                printf("Invalid operator in: %s\n", str);
                continue;
        }
        printf("MOV R%d, %c\n", j, str[2]);
        printf("%s R%d, %c\n", opr, j, str[4]);
        printf("MOV %c, R%d\n", str[0], j);
    }
    return 0;
}

/*Algorithm: Target Code Generation from Intermediate Code
1. Start.
2. Declare an array to store intermediate-code statements.
3. Initialize the statement counter i = 0.
4. Read intermediate-code statements from the user.
5. Continue reading until:
   - The user enters exit, or
   - The maximum array capacity is reached.
6. Display the target-code generation heading.
7. Process each intermediate-code statement one by one.
8. Copy the current statement into a temporary string.
9. Check whether the statement follows the expected format a=b+c.
10. Extract the individual components:
    - str[0]: Destination variable.
    - str[2]: First operand.
    - str[3]: Arithmetic operator.
    - str[4]: Second operand.
11. Identify the arithmetic operator using a switch statement:
    - + → ADD
    - - → SUB
    - * → MUL
    - / → DIV
12. Generate the first target instruction to move the first operand into a register.
13. Generate the second target instruction to perform the arithmetic operation.
14. Generate the third target instruction to move the result from the register into the destination variable.
15. Repeat steps 8–14 for all intermediate-code statements.
16. Stop.*/