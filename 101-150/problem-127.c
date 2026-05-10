#include <stdio.h>
#include <stdint.h>

#define LIMIT 120000

int rad[LIMIT];

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

int main() {
    for (int i = 1; i < LIMIT; i++) rad[i] = 1;
    for (int p = 2; p < LIMIT; p++) {
        if (rad[p] == 1) {
            for (int j = p; j < LIMIT; j += p)
                rad[j] *= p;
        }
    }

    int64_t sum = 0;
    for (int c = 3; c < LIMIT; c++) {
        int rc = rad[c];
        for (int a = 1; 2 * a < c; a++) {
            int b = c - a;
            if ((int64_t)rad[a] * rad[b] * rc >= c) continue;
            if (gcd(a, b) != 1) continue;
            sum += c;
        }
    }
    printf("%ld\n", sum);
    return 0;
}
