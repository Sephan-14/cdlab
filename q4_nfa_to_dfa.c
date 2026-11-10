#include <stdio.h>

int n, m;                 // number of NFA states, number of symbols
char sym[10];             // the symbols, e.g. a b
int d[10][10][10];        // d[s][a][t] = 1 : qs --symbol a--> qt
int isFinal[10];          // isFinal[i] = 1 : qi is final in the NFA

int dstate[50][10];       // dstate[k][i] = 1 : DFA state k contains NFA state qi
int dnext[50][10];        // dnext[k][a] = DFA state reached from k on symbol a
int cnt = 0;              // how many DFA states found so far

int idx(char c) {         // position of a symbol in sym[]
    for (int i = 0; i < m; i++) if (sym[i] == c) return i;
    return -1;
}

// Return the number of this set among the DFA states. If it's new, add it.
int find(int set[]) {
    for (int k = 0; k < cnt; k++) {
        int same = 1;
        for (int i = 0; i < n; i++)
            if (dstate[k][i] != set[i]) same = 0;
        if (same) return k;               // already known
    }
    for (int i = 0; i < n; i++) dstate[cnt][i] = set[i];   // new DFA state
    return cnt++;
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

    printf("Enter each as: from symbol to\n");
    while (t--) { scanf("%d %c %d", &a, &c, &b); d[a][idx(c)][b] = 1; }

    printf("No. of final states: ");    
    scanf("%d", &f);

    printf("Final states: ");           
    while (f--) { scanf("%d", &a); isFinal[a] = 1; }

    int start[10] = {0};
    start[0] = 1;                       // start set = {q0}
    find(start);                        // it becomes DFA state 0 (printed as A)

    for (int k = 0; k < cnt; k++) {     // cnt grows inside this loop - that's the algorithm
        for (int x = 0; x < m; x++) {
            int res[10] = {0};          // the set we reach from DFA state k on symbol x
            for (int i = 0; i < n; i++)
                if (dstate[k][i])                       // every NFA state inside DFA state k
                    for (int j = 0; j < n; j++)
                        if (d[i][x][j]) res[j] = 1;     // add where it goes on x
            dnext[k][x] = find(res);
        }
    }

    printf("\nDFA (A = start, * = final):\n");
    for (int k = 0; k < cnt; k++) {
        int fin = 0;                    // DFA state is final if it holds any NFA final state
        for (int i = 0; i < n; i++) if (dstate[k][i] && isFinal[i]) fin = 1;
        printf("%c%s = { ", 'A' + k, fin ? "*" : " ");

        for (int i = 0; i < n; i++) if (dstate[k][i]) printf("q%d ", i);
        printf("}");
        
        for (int x = 0; x < m; x++) printf("   on %c -> %c", sym[x], 'A' + dnext[k][x]);
        printf("\n");
    }
    return 0;
}