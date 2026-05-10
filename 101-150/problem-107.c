#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40
#define INF (1 << 30)

int adj[MAXN][MAXN];
int n;

int main() {
    FILE *fp = fopen("101-150/problem-107.txt", "r");
    if (!fp) { perror("Unable to open file"); return 1; }

    char line[512];
    n = 0;
    while (fgets(line, sizeof(line), fp) && n < MAXN) {
        int col = 0;
        char *tok = strtok(line, ",\n");
        while (tok) {
            adj[n][col] = (tok[0] == '-') ? 0 : atoi(tok);
            col++; tok = strtok(NULL, ",\n");
        }
        n++;
    }
    fclose(fp);

    int64_t total = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            total += adj[i][j];

    bool in_mst[MAXN] = {false};
    int key[MAXN];
    for (int i = 0; i < n; i++) key[i] = INF;
    key[0] = 0;
    int64_t mst_weight = 0;

    for (int iter = 0; iter < n; iter++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!in_mst[i] && (u == -1 || key[i] < key[u])) u = i;
        in_mst[u] = true;
        mst_weight += key[u];
        for (int v = 0; v < n; v++) {
            if (!in_mst[v] && adj[u][v] > 0 && adj[u][v] < key[v])
                key[v] = adj[u][v];
        }
    }

    printf("%ld\n", total - mst_weight);
    return 0;
}
