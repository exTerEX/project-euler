#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t gcd32(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static int append_digits(uint32_t x, uint16_t *mask, int *count) {
    if (x == 0) {
        if ((*mask) & 1U) {
            return 0;
        }
        *mask |= 1U;
        (*count)++;
        return 1;
    }

    while (x > 0) {
        uint32_t d = x % 10U;
        uint16_t bit = (uint16_t)(1U << d);
        if ((*mask) & bit) {
            return 0;
        }
        *mask |= bit;
        (*count)++;
        x /= 10U;
    }
    return 1;
}

static int is_pandigital_factorization(uint32_t factor, uint32_t one, uint32_t two) {
    uint16_t mask = 0;
    int count = 0;
    if (!append_digits(factor, &mask, &count)) {
        return 0;
    }
    if (!append_digits(one, &mask, &count)) {
        return 0;
    }
    if (!append_digits(two, &mask, &count)) {
        return 0;
    }
    return count == 10 && mask == 0x03FF;
}

static int cmp_u32(const void *a, const void *b) {
    uint32_t x = *(const uint32_t *)a;
    uint32_t y = *(const uint32_t *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static void gen_divisors_rec(const uint32_t *pr, const int *ex, int n, int idx,
                             uint32_t cur, uint32_t *out, int *k) {
    if (idx == n) {
        out[(*k)++] = cur;
        return;
    }
    uint32_t p = pr[idx];
    for (int e = 0; e <= ex[idx]; e++) {
        gen_divisors_rec(pr, ex, n, idx + 1, cur, out, k);
        if (e < ex[idx]) {
            cur *= p;
        }
    }
}

static int collect_divisors(uint32_t g, uint32_t *divs) {
    uint32_t tmp = g;
    uint32_t primes[10];
    int exps[10];
    int nf = 0;

    for (uint32_t p = 2; p * p <= tmp; p += (p == 2 ? 1 : 2)) {
        if (tmp % p != 0) {
            continue;
        }
        int e = 0;
        while (tmp % p == 0) {
            tmp /= p;
            e++;
        }
        primes[nf] = p;
        exps[nf] = e;
        nf++;
    }
    if (tmp > 1) {
        primes[nf] = tmp;
        exps[nf] = 1;
        nf++;
    }

    int k = 0;
    gen_divisors_rec(primes, exps, nf, 0, 1U, divs, &k);
    qsort(divs, (size_t)k, sizeof(uint32_t), cmp_u32);
    return k;
}

static int check_perm(const char digits[10]) {
    uint32_t prefix = 0;
    for (int split = 1; split < 10; split++) {
        prefix = prefix * 10U + (uint32_t)(digits[split - 1] - '0');
        if (digits[0] == '0' || digits[split] == '0') {
            continue;
        }

        uint32_t left = prefix;
        uint32_t right = 0;
        for (int i = split; i < 10; i++) {
            right = right * 10U + (uint32_t)(digits[i] - '0');
        }

        uint32_t g = gcd32(left, right);
        if (g <= 1) {
            continue;
        }

        uint32_t divisors[2048];
        int ndiv = collect_divisors(g, divisors);
        for (int i = ndiv - 1; i >= 0; i--) {
            uint32_t f = divisors[i];
            if (f <= 1) {
                continue;
            }
            uint32_t one = left / f;
            uint32_t two = right / f;
            if (is_pandigital_factorization(f, one, two)) {
                return 1;
            }
        }
    }
    return 0;
}

static int prev_permutation(char *a, int n) {
    int i = n - 2;
    while (i >= 0 && a[i] <= a[i + 1]) {
        i--;
    }
    if (i < 0) {
        return 0;
    }

    int j = n - 1;
    while (a[j] >= a[i]) {
        j--;
    }

    char t = a[i];
    a[i] = a[j];
    a[j] = t;

    int l = i + 1;
    int r = n - 1;
    while (l < r) {
        t = a[l];
        a[l] = a[r];
        a[r] = t;
        l++;
        r--;
    }

    return 1;
}

int main(void) {
    char digits[11] = "9876543210";

    do {
        if (check_perm(digits)) {
            printf("%s\n", digits);
            return 0;
        }
    } while (prev_permutation(digits, 10));

    return 1;
}
