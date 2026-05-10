#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t *data;
    size_t size;
    size_t cap;
} U64Vec;

static void vec_push(U64Vec *v, uint64_t x) {
    if (v->size == v->cap) {
        size_t new_cap = (v->cap == 0) ? 1024 : v->cap * 2;
        uint64_t *p = (uint64_t *)realloc(v->data, new_cap * sizeof(uint64_t));
        if (p == NULL) {
            exit(1);
        }
        v->data = p;
        v->cap = new_cap;
    }
    v->data[v->size++] = x;
}

static int cmp_u64(const void *a, const void *b) {
    uint64_t x = *(const uint64_t *)a;
    uint64_t y = *(const uint64_t *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod) {
    return (uint64_t)((__uint128_t)a * b % mod);
}

static uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1ULL) {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

static int is_prime(uint64_t n) {
    if (n < 2) {
        return 0;
    }
    static const uint64_t small[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (size_t i = 0; i < sizeof(small) / sizeof(small[0]); i++) {
        if (n == small[i]) {
            return 1;
        }
        if (n % small[i] == 0) {
            return 0;
        }
    }

    uint64_t d = n - 1;
    int s = 0;
    while ((d & 1ULL) == 0ULL) {
        d >>= 1;
        s++;
    }

    static const uint64_t bases[] = {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL};
    for (size_t i = 0; i < sizeof(bases) / sizeof(bases[0]); i++) {
        uint64_t a = bases[i] % n;
        if (a == 0) {
            continue;
        }

        uint64_t x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }

        int witness = 1;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                witness = 0;
                break;
            }
        }
        if (witness) {
            return 0;
        }
    }

    return 1;
}

static int contains_200(uint64_t n) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%llu", (unsigned long long)n);
    return strstr(buf, "200") != NULL;
}

static int is_prime_proof(uint64_t n) {
    uint64_t place = 1;
    uint64_t highest = 1;
    while (highest <= n / 10ULL) {
        highest *= 10ULL;
    }

    while (place <= highest) {
        int old_digit = (int)((n / place) % 10ULL);

        for (int d = 0; d <= 9; d++) {
            if (d == old_digit) {
                continue;
            }
            if (place == highest && d == 0) {
                continue;
            }

            int64_t delta = (int64_t)(d - old_digit) * (int64_t)place;
            uint64_t candidate = (uint64_t)((int64_t)n + delta);
            if (is_prime(candidate)) {
                return 0;
            }
        }

        place *= 10ULL;
    }
    return 1;
}

static int build_primes(int max_n, int **out_primes) {
    unsigned char *is_prime_arr = (unsigned char *)malloc((size_t)max_n + 1);
    if (is_prime_arr == NULL) {
        return 0;
    }
    for (int i = 0; i <= max_n; i++) {
        is_prime_arr[i] = 1;
    }
    is_prime_arr[0] = 0;
    is_prime_arr[1] = 0;

    for (int i = 2; (int64_t)i * i <= max_n; i++) {
        if (!is_prime_arr[i]) {
            continue;
        }
        for (int j = i * i; j <= max_n; j += i) {
            is_prime_arr[j] = 0;
        }
    }

    int count = 0;
    for (int i = 2; i <= max_n; i++) {
        if (is_prime_arr[i]) {
            count++;
        }
    }

    int *primes = (int *)malloc((size_t)count * sizeof(int));
    if (primes == NULL) {
        free(is_prime_arr);
        return 0;
    }

    int idx = 0;
    for (int i = 2; i <= max_n; i++) {
        if (is_prime_arr[i]) {
            primes[idx++] = i;
        }
    }

    free(is_prime_arr);
    *out_primes = primes;
    return count;
}

int main(void) {
    const int target_index = 200;
    uint64_t limit = 10000000000ULL;

    while (1) {
        int max_p = (int)sqrt((double)(limit / 8ULL)) + 100;
        int *primes = NULL;
        int prime_count = build_primes(max_p, &primes);
        if (prime_count == 0 || primes == NULL) {
            free(primes);
            return 1;
        }

        U64Vec candidates = {NULL, 0, 0};

        for (int iq = 0; iq < prime_count; iq++) {
            uint64_t q = (uint64_t)primes[iq];
            uint64_t q3 = q * q * q;
            if (q3 > limit / 4ULL) {
                break;
            }

            uint64_t pmax2 = limit / q3;
            for (int ip = 0; ip < prime_count; ip++) {
                uint64_t p = (uint64_t)primes[ip];
                if (p == q) {
                    continue;
                }
                uint64_t p2 = p * p;
                if (p2 > pmax2) {
                    break;
                }

                uint64_t value = p2 * q3;
                if (contains_200(value)) {
                    vec_push(&candidates, value);
                }
            }
        }

        free(primes);

        if (candidates.size == 0) {
            free(candidates.data);
            limit *= 2ULL;
            continue;
        }

        qsort(candidates.data, candidates.size, sizeof(uint64_t), cmp_u64);
        size_t uniq = 1;
        for (size_t i = 1; i < candidates.size; i++) {
            if (candidates.data[i] != candidates.data[uniq - 1]) {
                candidates.data[uniq++] = candidates.data[i];
            }
        }
        candidates.size = uniq;

        int found = 0;
        uint64_t answer = 0;
        for (size_t i = 0; i < candidates.size; i++) {
            uint64_t v = candidates.data[i];
            if (is_prime_proof(v)) {
                found++;
                if (found == target_index) {
                    answer = v;
                    break;
                }
            }
        }

        free(candidates.data);

        if (found >= target_index) {
            printf("%llu\n", (unsigned long long)answer);
            return 0;
        }

        limit *= 2ULL;
    }
}
