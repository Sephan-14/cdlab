#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][30], first[26][30], follow[26][30];
int n;

int add(char s[], char c){
    if (!strchr(s, c)){
        int l = strlen(s);
        s[l] = c;
        s[l + 1] = '\0';
        return 1;
    }
    return 0;
}

void FIRST(char c){
    if (!isupper(c)){
        add(first[c - 'A'], c);
        return;
    }

    for (int i = 0; i < n; i++){
        if (prod[i][0] != c) continue;

        char *rhs = prod[i] + 2;

        if (rhs[0] == '#' && rhs[1] == '\0'){
            add(first[c - 'A'], '#');
            continue;
        }

        int nullable = 1;

        for (int j = 0; rhs[j] && nullable; j++){
            char x = rhs[j];

            if (!isupper(x)){
                if (x != '#')
                    add(first[c - 'A'], x);

                else
                    add(first[c - 'A'], '#');

                nullable = (x == '#');
            }
            else{
                FIRST(x);

                for (int k = 0; first[x - 'A'][k]; k++)
                    if (first[x - 'A'][k] != '#')
                        add(first[c - 'A'], first[x - 'A'][k]);

                nullable = strchr(first[x - 'A'], '#') != NULL;
            }
        }
        if (nullable)
            add(first[c - 'A'], '#');
    }
}
int main(){
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");
    for (int i = 0; i < n; i++)
        scanf("%29s", prod[i]);

    // Calculate FIRST sets repeatedly until stable
    int changed;
    do{
        changed = 0;
        for (int i = 0; i < n; i++){
            char before[30];
            char lhs = prod[i][0];

            strcpy(before, first[lhs - 'A']);
            FIRST(lhs);

            if (strcmp(before, first[lhs - 'A']) != 0)
                changed = 1;
        }
    } while (changed);

    // Start symbol gets $
    add(follow[prod[0][0] - 'A'], '$');
    // Calculate FOLLOW sets repeatedly
    do{
        changed = 0;

        for (int i = 0; i < n; i++){
            char lhs = prod[i][0];
            char *rhs = prod[i] + 2;

            for (int j = 0; rhs[j]; j++){
                char c = rhs[j];

                if (!isupper(c)) continue;

                char temp[30] = "";
                int nullable = 1;

                for (int k = j + 1; rhs[k] && nullable; k++){
                    char x = rhs[k];

                    if (!isupper(x)){
                        if (x != '#')
                            add(temp, x);

                        nullable = (x == '#');
                    }
                    else{
                        for (int t = 0; first[x - 'A'][t]; t++)
                            if (first[x - 'A'][t] != '#')
                                add(temp, first[x - 'A'][t]);

                        nullable = strchr(first[x - 'A'], '#') != NULL;
                    }
                }

                for (int k = 0; temp[k]; k++)
                    changed |= add(follow[c - 'A'], temp[k]);

                if (nullable)
                    for (int k = 0; follow[lhs - 'A'][k]; k++)
                        changed |= add(follow[c - 'A'], follow[lhs - 'A'][k]);
            }
        }
    } while (changed);

    // Display results
    char c;
    do{
        printf("\nEnter non-terminal: ");
        scanf(" %c", &c);

        if (!isupper(c)){
            printf("Enter an uppercase non-terminal.\n");
        }
        else{
            printf("FIRST(%c) = { %s }\n", c, first[c - 'A']);
            printf("FOLLOW(%c) = { %s }\n", c, follow[c - 'A']);
        }
        printf("Continue (0/1)? ");
        scanf("%d", &changed);

    } while (changed == 1);
    return 0;
}

/*Aim: To calculate the FIRST set of a given grammar symbol.

Algorithm:

1. Start the program.
2. Declare the required variables:
- n to store the number of productions.
- a[][] to store the grammar productions.
- f[] to store the elements of the FIRST set.
- m to maintain the number of elements stored in the result array.
3. Read the number of productions n from the user.
4. Read all the grammar productions and store them in the two-dimensional character array a[][].
5. Read the grammar symbol c from the user for which the FIRST set has to be calculated.
6. Initialize the result counter m = 0 to ensure that the result array is empty.
7. Call the function FIRST(c) to calculate the FIRST set of the given symbol.
8. Inside the FIRST(c) function, check whether the given symbol c is a terminal or a non-terminal.
- If c is a terminal, directly add it to the result array f[].
- Increment the counter m after inserting the terminal.
9. If c is a non-terminal, search through all the grammar productions to find the productions whose left-hand side matches c.
10. For every matching production, examine the first symbol on the right-hand side of the production.
11. Check the type of the first symbol:
- If it is a terminal, add that terminal to the FIRST set.
- If it is a non-terminal, recursively call the FIRST() function for that non-terminal.
- If the production derives epsilon, include epsilon in the FIRST set.
12. Continue examining all productions having c on their left-hand side until every matching production has been processed.
13. Return from the recursive function after processing the productions.
14. Display all the elements stored in the result array f[] as the FIRST set of the given symbol.
15. Stop the FIRST calculation.


2: FOLLOW Set
Aim: To calculate the FOLLOW set of a given non-terminal in a grammar.

Algorithm:

1. Start the FOLLOW calculation.
2. Read the grammar symbol c from the user for which the FOLLOW set has to be calculated.
3. Initialize the result counter m = 0 to clear the previously stored FIRST set elements.
4. Call the function FOLLOW(c) to calculate the FOLLOW set of the given non-terminal.
5. Inside the FOLLOW(c) function, check whether the given non-terminal is the start symbol of the grammar.
- If it is the start symbol, add $ to its FOLLOW set because the end-of-input marker always belongs to the FOLLOW set of the start symbol.
6. Traverse all the grammar productions one by one using an outer loop.
7. For each production, traverse its right-hand side from left to right using an inner loop.
8. Check whether the current symbol in the right-hand side matches the given non-terminal c.
9. If the given non-terminal is found, examine the symbol immediately following it.
10. If another symbol exists after the given non-terminal:
- Call the FIRST() function for the next symbol.
- Add the resulting FIRST elements to the FOLLOW set, excluding epsilon.
11. If the given non-terminal occurs at the end of the right-hand side:
- Check whether it is the same as the left-hand-side non-terminal.
- If it is different, recursively call FOLLOW() for the left-hand-side non-terminal.
- Add the resulting FOLLOW elements to the FOLLOW set of the given non-terminal.
12. Continue searching all the productions to identify every occurrence of the given non-terminal.
13. Process all the occurrences and collect the corresponding terminals in the result array f[].
14. Return from the recursive function after processing the productions.
15. Display all the elements stored in f[] as the FOLLOW set of the given non-terminal.
16. Stop the FOLLOW calculation.

Algorithm 3: Main Program
This describes how both functions are executed together in your program.
1. Start.
2. Read the number of grammar productions.
3. Read and store all the grammar productions.
4. Ask the user to enter the grammar symbol for which FIRST and FOLLOW sets are required.
5. Initialize the result counter m = 0.
6. Call the FIRST() function with the entered symbol.
7. Display the calculated FIRST set.
8. Clear the result array and reset the counter m = 0.
9. Call the FOLLOW() function with the entered symbol.
10. Display the calculated FOLLOW set.
11. Ask the user whether another grammar symbol needs to be processed.
12. If the user enters 1, repeat steps 5–11.
13. If the user enters 0, terminate the program.
14. Stop.
*/