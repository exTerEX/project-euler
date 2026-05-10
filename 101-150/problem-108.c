#include <stdint.h>
#include <stdio.h>

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
int nprimes = 12;
int64_t best;

void search(int idx, int64_t n, int64_t divs, int max_exp);

int main() {
    best = (int64_t)4e18;
    search(0, 1, 1, 20);
    printf("%ld\n", best);
    return 0;
}

void search(int idx, int64_t n, int64_t divs, int max_exp) {
    if (divs > 1999) {
        if (n < best) best = n;
        return;
    }
    if (idx >= nprimes) return;
    int64_t pn = n;
    for (int e = 1; e <= max_exp; e++) {
        if (pn > best / primes[idx]) break;
        pn *= primes[idx];
        if (pn >= best) break;
        search(idx + 1, pn, divs * (2 * e + 1), e);
    }
}
