#include <stdint.h>
#include <stdio.h>

static uint64_t gcd64(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static uint64_t phi(uint64_t n) {
    uint64_t result = n;
    for (uint64_t p = 2; p * p <= n; p++) {
        if (n % p != 0) {
            continue;
        }
        while (n % p == 0) {
            n /= p;
        }
        result -= result / p;
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

static uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if ((exp & 1ULL) != 0) {
            result = (uint64_t)((__uint128_t)result * base % mod);
        }
        base = (uint64_t)((__uint128_t)base * base % mod);
        exp >>= 1;
    }
    return result;
}

static uint64_t tetration_mod(uint64_t a, uint64_t h, uint64_t mod) {
    if (mod == 1) {
        return 0;
    }
    if (h == 1) {
        return a % mod;
    }

    uint64_t ph = phi(mod);
    uint64_t e = tetration_mod(a, h - 1, ph);

    if (gcd64(a, mod) == 1) {
        return mod_pow(a, e, mod);
    }
    return mod_pow(a, e + ph, mod);
}

int main(void) {
    uint64_t answer = tetration_mod(1777, 1855, 100000000);
    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
