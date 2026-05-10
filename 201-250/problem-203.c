#include <stdint.h>
#include <stdio.h>

static int is_squarefree(uint64_t x) {
    for (uint64_t p = 2; p * p <= x; p++) {
        uint64_t sq = p * p;
        if (x % sq == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    const int rows = 51;

    uint64_t row[52] = {1};
    uint64_t next[52] = {0};

    uint64_t seen[2000];
    int seen_n = 0;

    seen[seen_n++] = 1;

    for (int r = 1; r < rows; r++) {
        next[0] = 1;
        next[r] = 1;
        for (int c = 1; c < r; c++) {
            next[c] = row[c - 1] + row[c];
        }

        for (int c = 1; c <= r / 2; c++) {
            uint64_t v = next[c];
            int exists = 0;
            for (int i = 0; i < seen_n; i++) {
                if (seen[i] == v) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                seen[seen_n++] = v;
            }
        }

        for (int c = 0; c <= r; c++) {
            row[c] = next[c];
        }
    }

    uint64_t sum = 0;
    for (int i = 0; i < seen_n; i++) {
        if (is_squarefree(seen[i])) {
            sum += seen[i];
        }
    }

    printf("%llu\n", (unsigned long long)sum);
    return 0;
}
