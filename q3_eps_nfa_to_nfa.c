// Q3: NFA with epsilon -> NFA without epsilon (plain arrays, no bit tricks).
// Rule: new_move(s,a) = closure( move( closure(s), a ) )
// A set of states is an int array: set[i] = 1 means qi is in the set.
#include <stdio.h>

int n, m;                 // number of states, number of symbols
char sym[10];             // the symbols, e.g. a b
int eps[10][10];          // eps[a][b] = 1  : qa --e--> qb
int d[10][10][10];        // d[s][a][t] = 1 : qs --symbol a--> qt
int isFinal[10];          // isFinal[i] = 1 : qi is a final state (start is q0)

int idx(char c) {         // position of a symbol in sym[]
    for (int i = 0; i < m; i++) if (sym[i] == c) return i;
    return -1;
}

// Add to 'set' every state reachable by e-moves. Repeat until nothing new is added.
void closure(int set[]) {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++)
            if (set[i])
                for (int j = 0; j < n; j++)
                    if (eps[i][j] && !set[j]) { set[j] = 1; changed = 1; }
    }
}

void printSet(int set[]) {
    printf("{ ");
    for (int i = 0; i < n; i++) if (set[i]) printf("q%d ", i);
    printf("}");
}

int main() {
    int t, a, b, f; char c;
    printf("No. of states: ");             
    scanf("%d", &n);

    printf("No. of symbols: ");            
    scanf("%d", &m);

    printf("Symbols: ");                   
    for (int i = 0; i < m; i++) scanf(" %c", &sym[i]);

    printf("No. of transitions: ");        
    scanf("%d", &t);

    printf("Enter each as: from symbol to   (use e for epsilon)\n");

    while (t--) {
        scanf("%d %c %d", &a, &c, &b);
        if (c == 'e') eps[a][b] = 1;
        
        else d[a][idx(c)][b] = 1;
    }

    printf("No. of final states: ");  
    scanf("%d", &f);

    printf("Final states: ");              
    while (f--) { scanf("%d", &a); isFinal[a] = 1; }

    printf("\nNFA without epsilon:\n");
    for (int s = 0; s < n; s++) {
        int cl[10] = {0};
        cl[s] = 1;
        closure(cl);                                   // step 1: closure(s)

        int fin = 0;                                   // final if closure holds a final state
        for (int i = 0; i < n; i++) if (cl[i] && isFinal[i]) fin = 1;
        printf("q%d%s", s, fin ? " (final)" : "");

        for (int x = 0; x < m; x++) {
            int res[10] = {0};
            for (int i = 0; i < n; i++)                // step 2: move on symbol x
                if (cl[i])
                    for (int j = 0; j < n; j++)
                        if (d[i][x][j]) res[j] = 1;
            closure(res);                              // step 3: closure again
            printf("  on %c -> ", sym[x]);
            printSet(res);
        }
        printf("\n");
    }
    return 0;
}