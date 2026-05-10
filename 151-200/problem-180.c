#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    uint64_t num;
    uint64_t den;
} Frac;

static uint64_t gcd64(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static Frac reduce(Frac f) {
    uint64_t g = gcd64(f.num, f.den);
    f.num /= g;
    f.den /= g;
    return f;
}

static Frac add_frac(Frac a, Frac b) {
    uint64_t g = gcd64(a.den, b.den);
    __uint128_t ad = a.den / g;
    __uint128_t bd = b.den / g;
    Frac out;
    out.num = (uint64_t)((__uint128_t)a.num * bd + (__uint128_t)b.num * ad);
    out.den = (uint64_t)((__uint128_t)a.den * bd);
    return reduce(out);
}

static Frac mul_frac(Frac a, Frac b) {
    uint64_t g1 = gcd64(a.num, b.den);
    uint64_t g2 = gcd64(b.num, a.den);
    __uint128_t n = (__uint128_t)(a.num / g1) * (b.num / g2);
    __uint128_t d = (__uint128_t)(a.den / g2) * (b.den / g1);
    Frac out = {(uint64_t)n, (uint64_t)d};
    return reduce(out);
}

static Frac div_frac(Frac a, Frac b) {
    Frac inv = {b.den, b.num};
    return mul_frac(a, inv);
}

static int cmp_frac(const void *pa, const void *pb) {
    const Frac *a = (const Frac *)pa;
    const Frac *b = (const Frac *)pb;
    if (a->num < b->num) {
        return -1;
    }
    if (a->num > b->num) {
        return 1;
    }
    if (a->den < b->den) {
        return -1;
    }
    if (a->den > b->den) {
        return 1;
    }
    return 0;
}

static void push_frac(Frac **arr, size_t *size, size_t *cap, Frac f) {
    if (*size == *cap) {
        size_t new_cap = (*cap == 0) ? 1024 : (*cap * 2);
        Frac *tmp = (Frac *)realloc(*arr, new_cap * sizeof(Frac));
        if (tmp == NULL) {
            exit(1);
        }
        *arr = tmp;
        *cap = new_cap;
    }
    (*arr)[(*size)++] = f;
}

static int in_S(Frac z) {
    return z.num < z.den && z.den <= 35;
}

int main(void) {
    Frac S[500];
    int sn = 0;
    for (uint64_t b = 2; b <= 35; b++) {
        for (uint64_t a = 1; a < b; a++) {
            if (gcd64(a, b) == 1) {
                S[sn++] = (Frac){a, b};
            }
        }
    }

    Frac *vals = NULL;
    size_t vals_size = 0;
    size_t vals_cap = 0;

    for (int i = 0; i < sn; i++) {
        Frac x = S[i];
        for (int j = i; j < sn; j++) {
            Frac y = S[j];

            Frac z = add_frac(x, y);
            if (in_S(z)) {
                push_frac(&vals, &vals_size, &vals_cap, add_frac(add_frac(x, y), z));
            }

            z = div_frac(mul_frac(x, y), add_frac(x, y));
            if (in_S(z)) {
                push_frac(&vals, &vals_size, &vals_cap, add_frac(add_frac(x, y), z));
            }

            uint64_t num = x.num * x.num * y.den * y.den + y.num * y.num * x.den * x.den;
            uint64_t den = x.den * x.den * y.den * y.den;
            uint64_t snum = (uint64_t)sqrt((double)num);
            while ((snum + 1) * (snum + 1) <= num) {
                snum++;
            }
            while (snum * snum > num) {
                snum--;
            }
            uint64_t sden = (uint64_t)sqrt((double)den);
            while ((sden + 1) * (sden + 1) <= den) {
                sden++;
            }
            while (sden * sden > den) {
                sden--;
            }

            if (snum * snum == num && sden * sden == den) {
                Frac root = reduce((Frac){snum, sden});

                z = root;
                if (in_S(z)) {
                    push_frac(&vals, &vals_size, &vals_cap, add_frac(add_frac(x, y), z));
                }

                z = div_frac(mul_frac(x, y), root);
                if (in_S(z)) {
                    push_frac(&vals, &vals_size, &vals_cap, add_frac(add_frac(x, y), z));
                }
            }
        }
    }

    qsort(vals, vals_size, sizeof(Frac), cmp_frac);

    Frac total = {0, 1};
    for (size_t i = 0; i < vals_size; i++) {
        if (i == 0 || cmp_frac(&vals[i], &vals[i - 1]) != 0) {
            total = add_frac(total, vals[i]);
        }
    }

    printf("%llu\n", (unsigned long long)(total.num + total.den));
    free(vals);
    return 0;
}
