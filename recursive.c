#include <stdio.h>
#include <stdlib.h>

char ip[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error(){
    printf("\nSyntax Error: Invalid expression\n");
    exit(0);
}

void match(char c){
    if (ip[pos] == c)
        pos++;
    else
        error();
}
// E -> T E'
void E(){
    printf("E -> T E'\n");
    T();
    Eprime();
}

// E' -> + T E' | epsilon
void Eprime(){
    if (ip[pos] == '+'){
        printf("E' -> + T E'\n");
        match('+');
        T();
        Eprime();
    }
    else{
        printf("E' -> epsilon\n");
    }
}

// T -> F T'
void T(){
    printf("T -> F T'\n");
    F();
    Tprime();
}

// T' -> * F T' | epsilon
void Tprime(){
    if (ip[pos] == '*'){
        printf("T' -> * F T'\n");
        match('*');
        F();
        Tprime();
    }
    else{
        printf("T' -> epsilon\n");
    }
}

// F -> i | ( E )
void F(){
    if (ip[pos] == 'i' || ip[pos] == 'I'){
        printf("F -> i\n");
        pos++;
    }
    else if (ip[pos] == '('){
        printf("F -> ( E )\n");
        match('(');
        E();
        match(')');
    }
    else{
        error();
    }
}
int main(){
    printf("Enter input expression: ");
    scanf("%99s", ip);

    printf("\nSequence of production rules:\n");

    E();

    if (ip[pos] == '\0')
        printf("\nString Accepted\n");
    else
        printf("\nSyntax Error: Extra characters found\n");

    return 0;
}



/*Algorithm: Recursive Descent Parsing
Step 1: Initialization
1. Start the program.
2. Declare a character array ip to store the input expression.
3. Initialize an integer variable pos = 0 to keep track of the current position in the input string.
4. Declare the functions E(), Eprime(), T(), Tprime() and F() corresponding to the grammar productions.
5. Read the input expression from the user.
Step 2: Start parsing
6. Call the function E() to begin parsing the input expression.
7. Display the production rule E → T E'.
8. Call the function T() to identify and process the term.
9. After processing T, call Eprime() to check for additional expressions involving the + operator.
Step 3: Process E'
10. Check whether the current input character is +.
11. If the current character is +:
    - Display the production rule E' → + T E'.
    - Call match('+') to verify and consume the plus operator.
    - Call T() to parse the next term.
    - Recursively call Eprime() to check for additional plus operators.
12. If the current character is not +:
    - Apply the epsilon production E' → ε.
    - Return to the calling function.
Step 4: Process T
13. Display the production rule T → F T'.
14. Call the function F() to identify and process the factor.
15. After processing F, call Tprime() to check for multiplication operations.
Step 5: Process T'
16. Check whether the current input character is *.
17. If the current character is *:
    - Display the production rule T' → * F T'.
    - Call match('*') to verify and consume the multiplication operator.
    - Call F() to parse the next factor.
    - Recursively call Tprime() to check for additional multiplication operators.
18. If the current character is not *:
    - Apply the epsilon production T' → ε.
    - Return to the calling function.
Step 6: Process F
19. Check the current input character.
20. If the character is i or I:
    - Display the production rule F → i.
    - Increment pos to consume the identifier.
21. Otherwise, if the current character is an opening parenthesis (:
    - Display the production rule F → ( E ).
    - Call match('(') to consume the opening parenthesis.
    - Call E() to parse the expression inside the parentheses.
    - Call match(')') to verify and consume the closing parenthesis.
22. If neither condition is satisfied, call the error() function to report a syntax error.
Step 7: Character matching
23. The match(c) function checks whether the current input character matches the expected character c.
24. If both characters match, increment pos to move to the next input character.
25. Otherwise, call the error() function.
Step 8: Final validation
26. After the E() function completes, check whether the current input character is the null character '\0'.
27. If it is '\0', the entire input expression has been successfully parsed. Display String Accepted.
28. Otherwise, display Syntax Error because some extra or invalid characters remain.
29. Stop the program.*/