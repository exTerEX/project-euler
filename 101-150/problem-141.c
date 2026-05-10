#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

int64_t gcd(int64_t a, int64_t b) { return b ? gcd(b, a % b) : a; }

bool is_square(int64_t n) {
    if (n < 0) return false;
    int64_t s = (int64_t)sqrtl((long double)n);
    while (s * s > n) s--;
    while ((s + 1) * (s + 1) <= n) s++;
    return s * s == n;
}

int main() {
    int64_t LIMIT = 1000000000000LL;
    int64_t results[10000];
    int nr = 0;

    for (int64_t k = 2; ; k++) {
        if (k * k * k > LIMIT) break;
        for (int64_t j = 1; j < k; j++) {
            if (gcd(j, k) != 1) continue;
            for (int64_t a = 1; ; a++) {
                int64_t n = a * j * (a * k * k * k + j);
                if (n >= LIMIT) break;
                if (is_square(n) && nr < 10000) {
                    results[nr++] = n;
                }
            }
        }
    }

    for (int i = 1; i < nr; i++) {
        int64_t key = results[i];
        int j = i - 1;
        while (j >= 0 && results[j] > key) { results[j + 1] = results[j]; j--; }
        results[j + 1] = key;
    }

    int64_t sum = 0;
    for (int i = 0; i < nr; i++) {
        if (i == 0 || results[i] != results[i - 1]) sum += results[i];
    }

    printf("%ld\n", sum);
    return 0;
}
