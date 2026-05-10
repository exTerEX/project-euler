#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define LIMIT 1000000

int cnt[LIMIT];

int main() {
    memset(cnt, 0, sizeof(cnt));
    for (int a = 1; a < LIMIT; a++) {
        for (int b = 1; (int64_t)a * b < LIMIT; b++) {
            int n = a * b;
            if ((a + b) % 4 == 0 && b < 3 * a) cnt[n]++;
        }
    }
    int answer = 0;
    for (int n = 1; n < LIMIT; n++)
        if (cnt[n] == 10) answer++;
    printf("%d\n", answer);
    return 0;
}
