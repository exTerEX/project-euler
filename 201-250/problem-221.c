#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Alexandrian Integers: find the 150000th.
 * Parametrization: for each k >= 1 and each divisor a of k^2+1 with a <= sqrt(k^2+1):
 *   b = (k^2+1)/a, A = k*(a+k)*(b+k).
 * All Alexandrian integers are of this form.
 *
 * Efficient algorithm: sieve over primes to find which k values have each prime
 * dividing k^2+1. Then for each k, enumerate divisors of k^2+1 up to sqrt(k^2+1).
 */

#define K_MAX 220000
#define MAX_ENTRIES 1500000

static uint8_t is_composite[K_MAX + 1];
static uint32_t primes[25000];
static int prime_count;

static uint32_t fl_prime[MAX_ENTRIES];
static uint32_t fl_next[MAX_ENTRIES];
static uint32_t fl_head[K_MAX + 1];
static uint32_t fl_cnt = 0;

static int cmp_u64(const void *a, const void *b) {
    uint64_t x = *(const uint64_t *)a;
    uint64_t y = *(const uint64_t *)b;
    return (x > y) - (x < y);
}

static void add_factor(int k, uint32_t p) {
    fl_prime[fl_cnt] = p;
    fl_next[fl_cnt] = fl_head[k];
    fl_head[k] = fl_cnt++;
}

static uint64_t sqrt_minus1_mod_p(uint64_t p) {
    for (uint64_t r = 2; r < p; r++) {
        if ((r * r) % p == p - 1) return r;
    }
    return 0;
}

int main(void) {
    for (int i = 2; (long long)i * i <= K_MAX; i++) {
        if (!is_composite[i]) {
            for (int j = i * i; j <= K_MAX; j += i) is_composite[j] = 1;
        }
    }
    prime_count = 0;
    for (int i = 2; i <= K_MAX; i++) {
        if (!is_composite[i]) primes[prime_count++] = i;
    }

    memset(fl_head, 0xFF, sizeof(fl_head));

    for (int pi = 0; pi < prime_count; pi++) {
        uint32_t p = primes[pi];
        if (p == 2) {
            for (int k = 1; k <= K_MAX; k += 2) add_factor(k, 2);
        } else if (p % 4 == 1) {
            uint64_t r0 = sqrt_minus1_mod_p(p);
            uint64_t r1 = p - r0;
            for (uint64_t k = r0; k <= K_MAX; k += p) add_factor((int)k, p);
            for (uint64_t k = r1; k <= K_MAX; k += p) add_factor((int)k, p);
        }
    }

    size_t res_cap = 4000000;
    uint64_t *res = malloc(res_cap * sizeof(uint64_t));
    size_t res_cnt = 0;

    uint64_t divs[2048];

    for (int k = 1; k <= K_MAX; k++) {
        uint64_t n = (uint64_t)k * k + 1;
        uint64_t rem = n;

        uint32_t ps[32];
        int exps[32];
        int nprimes_k = 0;

        for (uint32_t idx = fl_head[k]; idx != UINT32_MAX; idx = fl_next[idx]) {
            uint32_t p = fl_prime[idx];
            if (rem % p != 0) continue;
            int e = 0;
            while (rem % p == 0) { rem /= p; e++; }
            ps[nprimes_k] = p;
            exps[nprimes_k++] = e;
        }
        /* rem = 1 or large prime > K_MAX; all divisors <= sqrt(n) come from small part */

        int ndivs = 1;
        divs[0] = 1;
        for (int i = 0; i < nprimes_k; i++) {
            int cur = ndivs;
            uint64_t pe = ps[i];
            for (int e = 1; e <= exps[i]; e++, pe *= ps[i]) {
                for (int j = 0; j < cur; j++) {
                    divs[ndivs++] = divs[j] * pe;
                }
            }
        }

        for (int i = 0; i < ndivs; i++) {
            uint64_t a = divs[i];
            if (a * a <= n) {
                uint64_t b = n / a;
                if (res_cnt >= res_cap) {
                    res_cap *= 2;
                    res = realloc(res, res_cap * sizeof(uint64_t));
                }
                res[res_cnt++] = (uint64_t)k * (a + k) * (b + k);
            }
        }
    }

    qsort(res, res_cnt, sizeof(uint64_t), cmp_u64);

    if (res_cnt >= 150000) {
        printf("%" PRIu64 "\n", res[149999]);
    } else {
        printf("Insufficient: %zu values. Increase K_MAX.\n", res_cnt);
    }

    free(res);
    return 0;
}
