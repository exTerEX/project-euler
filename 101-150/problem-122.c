#include <stdio.h>
#include <string.h>

#define MAXK 201

int cost[MAXK];

void dfs(int *chain, int depth, int max_depth) {
    int n = chain[depth];
    if (n >= MAXK) return;
    if (cost[n] > depth) cost[n] = depth;
    if (depth == max_depth) return;
    for (int i = depth; i >= 0; i--) {
        int next = n + chain[i];
        if (next < MAXK) {
            chain[depth + 1] = next;
            dfs(chain, depth + 1, max_depth);
        }
    }
}

int main() {
    for (int i = 0; i < MAXK; i++) cost[i] = 100;
    cost[1] = 0;
    int chain[200];
    chain[0] = 1;
    for (int max_depth = 1; max_depth <= 12; max_depth++) {
        dfs(chain, 0, max_depth);
    }
    int sum = 0;
    for (int k = 1; k <= 200; k++) sum += cost[k];
    printf("%d\n", sum);
    return 0;
}
