#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef uint64_t ull;

static ull factorial_value;
static const unsigned int factor_primes[] = {2, 3, 5, 7, 11, 13};
static const unsigned int factor_exponents[] = {10, 5, 2, 1, 1, 1};

static ull *candidates = NULL;
static size_t candidate_count = 0;
static size_t candidate_capacity = 0;

static ull *results = NULL;
static size_t result_count = 0;
static size_t result_capacity = 0;

static ull mulmod(ull a, ull b, ull mod) {
    return ((unsigned __int128)a * b) % mod;
}

static ull powmod(ull base, ull exponent, ull mod) {
    ull result = 1;
    while (exponent > 0) {
        if ((exponent & 1U) != 0U) {
            result = mulmod(result, base, mod);
        }
        base = mulmod(base, base, mod);
        exponent >>= 1U;
    }
    return result;
}

static int is_prime(ull n) {
    static const ull witnesses[] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
    static const ull small_primes[] = {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL};

    if (n < 2) {
        return 0;
    }
    for (size_t i = 0; i < sizeof(small_primes) / sizeof(small_primes[0]); ++i) {
        ull prime = small_primes[i];
        if (n == prime) {
            return 1;
        }
        if (n % prime == 0) {
            return 0;
        }
    }

    ull d = n - 1;
    unsigned int shift = 0;
    while ((d & 1U) == 0U) {
        d >>= 1U;
        shift++;
    }

    for (size_t i = 0; i < sizeof(witnesses) / sizeof(witnesses[0]); ++i) {
        ull a = witnesses[i] % n;
        if (a == 0) {
            continue;
        }
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }

        int maybe_prime = 0;
        for (unsigned int r = 1; r < shift; ++r) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                maybe_prime = 1;
                break;
            }
            if (x == 1) {
                return 0;
            }
        }
        if (!maybe_prime) {
            return 0;
        }
    }
    return 1;
}

static void push_candidate(ull value) {
    if (candidate_count == candidate_capacity) {
        size_t new_capacity = candidate_capacity == 0 ? 128 : candidate_capacity * 2;
        ull *new_data = realloc(candidates, new_capacity * sizeof(ull));
        if (new_data == NULL) {
            exit(1);
        }
        candidates = new_data;
        candidate_capacity = new_capacity;
    }
    candidates[candidate_count++] = value;
}

static void push_result(ull value) {
    if (result_count == result_capacity) {
        size_t new_capacity = result_capacity == 0 ? 4096 : result_capacity * 2;
        ull *new_data = realloc(results, new_capacity * sizeof(ull));
        if (new_data == NULL) {
            exit(1);
        }
        results = new_data;
        result_capacity = new_capacity;
    }
    results[result_count++] = value;
}

static int compare_ull(const void *a, const void *b) {
    ull x = *(const ull *)a;
    ull y = *(const ull *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static void find_candidates(size_t index, ull number) {
    if (index == sizeof(factor_primes) / sizeof(factor_primes[0])) {
        if (is_prime(number + 1)) {
            push_candidate(number + 1);
        }
        return;
    }

    ull current = number;
    for (unsigned int exponent = 0; exponent <= factor_exponents[index]; ++exponent) {
        find_candidates(index + 1, current);
        current *= factor_primes[index];
    }
}

static void search_results(ull number, ull phi, size_t start_index, ull largest_prime) {
    for (size_t i = start_index; i < candidate_count; ++i) {
        ull current = candidates[i];
        ull next_number = number * current;
        ull next_phi = phi * (current - 1);
        if (current == largest_prime) {
            next_phi += phi;
        }
        if (next_phi > factorial_value) {
            break;
        }
        if (next_phi == factorial_value) {
            push_result(next_number);
            break;
        }
        if (factorial_value % next_phi == 0) {
            search_results(next_number, next_phi, i, current);
        }
    }
}

int main(void) {
    unsigned int thirteen = 13;
    unsigned int index = 150000;
    if (!isatty(fileno(stdin))) {
        if (scanf("%u %u", &thirteen, &index) != 2) {
            thirteen = 13;
            index = 150000;
        }
    }

    factorial_value = 1;
    for (unsigned int i = 2; i <= thirteen; ++i) {
        factorial_value *= i;
    }

    find_candidates(0, 1);
    qsort(candidates, candidate_count, sizeof(ull), compare_ull);
    size_t unique_count = 0;
    for (size_t i = 0; i < candidate_count; ++i) {
        if (i == 0 || candidates[i] != candidates[i - 1]) {
            candidates[unique_count++] = candidates[i];
        }
    }
    candidate_count = unique_count;

    search_results(1, 1, 0, 1);
    qsort(results, result_count, sizeof(ull), compare_ull);

    printf("%" PRIu64 "\n", results[index - 1]);

    free(candidates);
    free(results);
    return 0;
}