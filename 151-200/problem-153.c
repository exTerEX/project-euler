#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LIMIT 100000000U
#define SMALL_MAX 1000000U

typedef struct {
    uint32_t key;
    uint64_t value;
} CacheEntry;

static uint64_t *prefix_h = NULL;
static CacheEntry *cache = NULL;
static size_t cache_size = 0;
static size_t cache_cap = 0;

static uint32_t gcd32(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static uint64_t calc_h(uint32_t n) {
    uint64_t result = 0;
    uint32_t i = 1;
    while (i <= n) {
        uint32_t q = n / i;
        uint32_t j = n / q;
        __uint128_t len = (uint64_t)(j - i + 1);
        __uint128_t sum = (__uint128_t)(i + j) * len / 2;
        result += (uint64_t)((__uint128_t)q * sum);
        i = j + 1;
    }
    return result;
}

static uint64_t H(uint32_t n) {
    if (n <= SMALL_MAX) {
        return prefix_h[n];
    }

    for (size_t i = 0; i < cache_size; i++) {
        if (cache[i].key == n) {
            return cache[i].value;
        }
    }

    uint64_t v = calc_h(n);
    if (cache_size == cache_cap) {
        size_t new_cap = (cache_cap == 0) ? 256 : cache_cap * 2;
        CacheEntry *tmp = (CacheEntry *)realloc(cache, new_cap * sizeof(CacheEntry));
        if (tmp == NULL) {
            exit(1);
        }
        cache = tmp;
        cache_cap = new_cap;
    }
    cache[cache_size++] = (CacheEntry){n, v};
    return v;
}

static void build_small_prefix(void) {
    uint64_t *sigma = (uint64_t *)calloc(SMALL_MAX + 1, sizeof(uint64_t));
    prefix_h = (uint64_t *)calloc(SMALL_MAX + 1, sizeof(uint64_t));
    if (sigma == NULL || prefix_h == NULL) {
        free(sigma);
        free(prefix_h);
        exit(1);
    }

    for (uint32_t i = 1; i <= SMALL_MAX; i++) {
        for (uint32_t j = i; j <= SMALL_MAX; j += i) {
            sigma[j] += i;
        }
    }

    for (uint32_t i = 1; i <= SMALL_MAX; i++) {
        prefix_h[i] = prefix_h[i - 1] + sigma[i];
    }

    free(sigma);
}

int main(void) {
    build_small_prefix();

    uint64_t total = H(LIMIT);
    uint32_t root = 10000;

    for (uint32_t a = 1; a <= root; a++) {
        uint32_t a2 = a * a;
        if (a2 >= LIMIT) {
            break;
        }
        uint32_t bmax = (uint32_t)(sqrt((double)(LIMIT - a2)));
        while ((uint64_t)(bmax + 1) * (bmax + 1) <= (uint64_t)(LIMIT - a2)) {
            bmax++;
        }
        while ((uint64_t)bmax * bmax > (uint64_t)(LIMIT - a2)) {
            bmax--;
        }

        for (uint32_t b = 1; b <= bmax; b++) {
            if (gcd32(a, b) != 1) {
                continue;
            }
            uint32_t t = a2 + b * b;
            uint32_t m = LIMIT / t;
            total += 2ULL * a * H(m);
        }
    }

    printf("%llu\n", (unsigned long long)total);

    free(prefix_h);
    free(cache);
    return 0;
}
