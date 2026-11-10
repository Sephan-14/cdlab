#include <stdio.h>

int n;
int eps[10][10];     // eps[a][b] = 1  means  qa --epsilon--> qb
int visited[10];     // visited[i] = 1 means qi is in the closure

void dfs(int s) {
    visited[s] = 1;                          // s can always reach itself
    for (int i = 0; i < n; i++)
        if (eps[s][i] && !visited[i])        // epsilon move to a new state?
            dfs(i);                          // then follow it too
}

int main(){
    
    int t, a, b;
    printf("No. of states: ");                
    scanf("%d", &n);
    printf("No. of epsilon transitions: ");   
    scanf("%d", &t);
    printf("Enter each as: from to\n");
    while (t--) { 
        scanf("%d %d", &a, &b); 
        eps[a][b] = 1;
    }

    for (int s = 0; s < n; s++) {
        for (int i = 0; i < n; i++) visited[i] = 0;   // fresh start for each state
        dfs(s);
        printf("eps-closure(q%d) ={", s);
        for (int i = 0; i < n; i++)
            if (visited[i]) printf("q%d ", i);
        printf("}\n");
    }
    
    return 0;
}
