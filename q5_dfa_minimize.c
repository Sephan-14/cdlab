// Q5: DFA minimization (table-filling method).
// dist[i][j] = 1 means "qi and qj are DIFFERENT" (some input tells them apart).
// Start: final vs non-final are different.
// Repeat: if on some symbol qi and qj go to a different pair, then qi and qj are different.
// Pairs never marked are equivalent -> merge them into one state.
#include <stdio.h>

int n, m;
char sym[10];
int d[10][10];          // d[state][symbol] = next state
int isFinal[10];
int dist[10][10];       // dist[i][j] = 1 : qi and qj are different
int rep[10];            // rep[i] = smallest state equivalent to qi (its group leader)

int main() {
    int f, x;
    printf("No. of states: ");        scanf("%d", &n);
    printf("No. of symbols: ");       scanf("%d", &m);
    printf("Symbols: ");              for (int a = 0; a < m; a++) scanf(" %c", &sym[a]);
    printf("Transition table (one row per state, one column per symbol):\n");
    for (int i = 0; i < n; i++) for (int a = 0; a < m; a++) scanf("%d", &d[i][a]);
    printf("No. of final states: ");  scanf("%d", &f);
    printf("Final states: ");         while (f--) { scanf("%d", &x); isFinal[x] = 1; }

    // Step 1: one final, one non-final -> different
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (isFinal[i] != isFinal[j]) dist[i][j] = 1;

    // Step 2: keep marking until a full pass marks nothing new
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!dist[i][j])
                    for (int a = 0; a < m; a++)
                        if (dist[d[i][a]][d[j][a]]) {   // their next states are already different
                            dist[i][j] = 1;
                            changed = 1;
                            break;
                        }
    }

    // Step 3: group leader of qi = first state j that is NOT different from qi
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            if (!dist[j][i]) { rep[i] = j; break; }

    printf("\nMinimized DFA (start = group of q%d):\n", rep[0]);
    for (int i = 0; i < n; i++) {
        if (rep[i] != i) continue;                      // print each group once, via its leader
        printf("{");
        for (int j = 0; j < n; j++) if (rep[j] == i) printf(" q%d", j);
        printf(" }%s", isFinal[i] ? " (final)" : "");
        for (int a = 0; a < m; a++) printf("   on %c -> q%d", sym[a], rep[d[i][a]]);
        printf("\n");
    }
    return 0;
}