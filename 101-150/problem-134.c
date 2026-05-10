#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define LIMIT 1100000

bool sieve[LIMIT];

void make_sieve() {
    for (int i = 2; i < LIMIT; i++) sieve[i] = true;
    for (int i = 2; (int64_t)i * i < LIMIT; i++)
        if (sieve[i])
            for (int j = i * i; j < LIMIT; j += i) sieve[j] = false;
}

int64_t ext_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y) {
    if (b == 0) { *x = 1; *y = 0; return a; }
    int64_t x1, y1;
    int64_t g = ext_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

int main() {
    make_sieve();
    int primes[100000];
    int np = 0;
    for (int i = 2; i < LIMIT; i++)
        if (sieve[i]) primes[np++] = i;

    int64_t total = 0;
    for (int i = 2; i < np && primes[i - 1] <= 1000000; i++) {
        int64_t p1 = primes[i - 1];
        if (p1 < 5) continue;
        int64_t p2 = primes[i];
        int d = 0;
        int64_t tmp = p1;
        while (tmp > 0) { d++; tmp /= 10; }
        int64_t mod1 = 1;
        for (int j = 0; j < d; j++) mod1 *= 10;
        int64_t x, y;
        ext_gcd(p2, mod1, &x, &y);
        int64_t inv_p2 = ((x % mod1) + mod1) % mod1;
        int64_t t = ((__int128)p1 * inv_p2) % mod1;
        int64_t S = p2 * t;
        total += S;
    }
    printf("%ld\n", total);
    return 0;
}
