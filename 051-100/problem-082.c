#include <stdio.h>
#include <stdint.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SIZE 80
#define FILENAME "problem-081.txt"

int main() {
    FILE *f;
    if ((f = fopen(FILENAME, "r")) == NULL) {
        printf("ERROR: can't open %s\n", FILENAME);
        return 1;
    }

    int32_t m[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            fscanf(f, "%d,", &m[i][j]);
    fclose(f);

    int32_t dp[SIZE];
    for (int i = 0; i < SIZE; ++i) dp[i] = m[i][0];

    for (int j = 1; j < SIZE; ++j) {
        for (int i = 0; i < SIZE; ++i) dp[i] += m[i][j];
        for (int i = 1; i < SIZE; ++i) dp[i] = MIN(dp[i], dp[i-1] + m[i][j]);
        for (int i = SIZE - 2; i >= 0; --i) dp[i] = MIN(dp[i], dp[i+1] + m[i][j]);
    }

    int32_t ans = dp[0];
    for (int i = 1; i < SIZE; ++i) if (dp[i] < ans) ans = dp[i];
    printf("%d\n", ans);
    return 0;
}
