#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LIMIT 50000000

int main() {
    uint8_t *cnt = calloc(LIMIT, 1);
    for (int a = 1; a < LIMIT; a++) {
        for (int b = 1; (int64_t)a * b < LIMIT; b++) {
            int n = a * b;
            if ((a + b) % 4 == 0 && b < 3 * a) {
                if (cnt[n] < 2) cnt[n]++;
            }
        }
    }
    int answer = 0;
    for (int n = 1; n < LIMIT; n++)
        if (cnt[n] == 1) answer++;
    free(cnt);
    printf("%d\n", answer);
    return 0;
}
