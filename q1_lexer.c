#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"int","float","char","double","void","if","else","while","for","return"};

int isKeyword(const char *s) {
    for (int i = 0; i < 10; i++)
        if (strcmp(s, keywords[i]) == 0) return 1;
    return 0;
}

int main() {
    
    int c;
    char buf[100];
    while ((c = getchar()) != EOF) {

        if (isspace(c)) continue;                    // redundant space / tab / newline -> ignored

        if (isalpha(c) || c == '_') {                // word: keyword or identifier
            int i = 0;
            do { 
                buf[i++] = c; 
                c = getchar(); 
            } 
            while ((isalnum(c) || c == '_') && i < 99);
            buf[i] = 0;
            ungetc(c, stdin);                        // we read one char too far, push it back
            printf("%-12s : %s\n", buf, isKeyword(buf) ? "KEYWORD" : "IDENTIFIER");
        }
        else if (isdigit(c)) {                       // number
            int i = 0;
            do { 
                buf[i++] = c; 
                c = getchar(); 
            } 
            while (isdigit(c) && i < 99);
            buf[i] = 0;
            ungetc(c, stdin);
            printf("%-12s : NUMBER\n", buf);
        }
        else if (strchr("+-*/=<>!", c)) {            // operator (also handles <=, ==, !=, ...)
            int next = getchar();
            if (next == '=') printf("%c=           : OPERATOR\n", c);
            else { 
                ungetc(next, stdin); 
                printf("%-12c : OPERATOR\n", c);
            }
        }
        else if (strchr("(){}[];,", c))              // punctuation
            printf("%-12c : SEPARATOR\n", c);
        else
            printf("%-12c : UNKNOWN\n", c);
    }
    return 0;
}
