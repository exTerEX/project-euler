#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 12
#define MAXLINE 256

bool is_special(int *a, int n);

int main() {
    FILE *fp = fopen("101-150/problem-105.txt", "r");
    if (!fp) { perror("Unable to open file"); return 1; }
    char line[MAXLINE];
    int total = 0;
    while (fgets(line, sizeof(line), fp)) {
        int a[MAXN], n = 0;
        char *tok = strtok(line, ",\n");
        while (tok && n < MAXN) { a[n++] = atoi(tok); tok = strtok(NULL, ",\n"); }
        if (n > 0 && is_special(a, n)) {
            for (int i = 0; i < n; i++) total += a[i];
        }
    }
    fclose(fp);
    printf("%d\n", total);
    return 0;
}

bool is_special(int *a, int n) {
    int count = 0;
    int sums[1 << MAXN];
    int min_sum[MAXN + 1], max_sum[MAXN + 1];
    for (int i = 0; i <= n; i++) { min_sum[i] = 1 << 30; max_sum[i] = 0; }
    for (int mask = 1; mask < (1 << n); mask++) {
        int s = 0, bits = 0;
        for (int i = 0; i < n; i++) if (mask & (1 << i)) { s += a[i]; bits++; }
        for (int j = 0; j < count; j++) if (sums[j] == s) return false;
        sums[count++] = s;
        if (s < min_sum[bits]) min_sum[bits] = s;
        if (s > max_sum[bits]) max_sum[bits] = s;
    }
    for (int k = 1; k < n; k++) if (min_sum[k + 1] <= max_sum[k]) return false;
    return true;
}
