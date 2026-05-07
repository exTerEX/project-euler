#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LIMIT 1000000
#define MAXVAL 3000000

static int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
static int chain_gen[MAXVAL];

static int next_n(int n) {
    int s = 0;
    while (n > 0) { s += fac[n % 10]; n /= 10; }
    return s;
}

int main() {
    memset(chain_gen, 0, sizeof(chain_gen));
    int count = 0;

    for (int n = 1; n < LIMIT; ++n) {
        int len = 0;
        int cur = n;
        while (cur >= MAXVAL || chain_gen[cur] != n) {
            if (cur < MAXVAL) chain_gen[cur] = n;
            ++len;
            cur = next_n(cur);
        }
        if (len == 60) ++count;
    }

    printf("%d\n", count);
    return 0;
}
