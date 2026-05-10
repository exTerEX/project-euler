#include <stdint.h>
#include <stdio.h>

static uint64_t mod_inverse_u64(uint64_t a, uint64_t mod) {
    int64_t t = 0, new_t = 1;
    int64_t r = (int64_t)mod, new_r = (int64_t)(a % mod);

    while (new_r != 0) {
        int64_t q = r / new_r;
        int64_t tmp_t = t - q * new_t;
        t = new_t;
        new_t = tmp_t;

        int64_t tmp_r = r - q * new_r;
        r = new_r;
        new_r = tmp_r;
    }

    if (t < 0) {
        t += (int64_t)mod;
    }
    return (uint64_t)t;
}

static int factorize_distinct(uint64_t n, uint64_t *primes) {
    int count = 0;
    for (uint64_t p = 2; p * p <= n; p += (p == 2 ? 1 : 2)) {
        if (n % p != 0) {
            continue;
        }
        primes[count++] = p;
        while (n % p == 0) {
            n /= p;
        }
    }
    if (n > 1) {
        primes[count++] = n;
    }
    return count;
}

static uint64_t count_mod3(uint64_t m, uint64_t r) {
    if (m == 0) {
        return 0;
    }
    if (r == 0) {
        return m / 3;
    }
    if (r == 1) {
        return (m + 2) / 3;
    }
    return (m + 1) / 3;
}

int main(void) {
    const uint64_t reflections = 12017639147ULL;
    const uint64_t n = (reflections + 3ULL) / 2ULL;
    const uint64_t limit = n / 2ULL;

    uint64_t primes[32];
    int pc = factorize_distinct(n, primes);

    uint64_t valid_half = 0;
    int subset_count = 1 << pc;
    for (int mask = 0; mask < subset_count; mask++) {
        uint64_t d = 1;
        int bits = 0;
        for (int i = 0; i < pc; i++) {
            if ((mask >> i) & 1) {
                d *= primes[i];
                bits++;
            }
        }

        uint64_t m = limit / d;
        uint64_t inv = mod_inverse_u64(d % 3ULL, 3ULL);
        uint64_t t_residue = (2ULL * inv) % 3ULL;
        uint64_t cnt = count_mod3(m, t_residue);

        if (bits & 1) {
            valid_half -= cnt;
        } else {
            valid_half += cnt;
        }
    }

    uint64_t answer = 2ULL * valid_half;
    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
