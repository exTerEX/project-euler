#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NLIMBS 16
#define BASE 1000000000ULL

typedef struct { uint64_t d[NLIMBS]; } Big;

static void bigzero(Big *a) { memset(a->d, 0, sizeof(a->d)); }

static void bmul10(Big *a) {
    uint64_t carry = 0;
    for (int i = 0; i < NLIMBS; ++i) {
        uint64_t v = a->d[i] * 10 + carry;
        a->d[i] = v % BASE; carry = v / BASE;
    }
}

static void badd(Big *a, uint64_t v) {
    for (int i = 0; i < NLIMBS && v; ++i) {
        uint64_t s = a->d[i] + v;
        a->d[i] = s % BASE; v = s / BASE;
    }
}

static void bmulsmall(Big *r, const Big *a, uint64_t x) {
    uint64_t carry = 0;
    for (int i = 0; i < NLIMBS; ++i) {
        uint64_t v = a->d[i] * x + carry;
        r->d[i] = v % BASE; carry = v / BASE;
    }
}

static int bigcmp(const Big *a, const Big *b) {
    for (int i = NLIMBS - 1; i >= 0; --i) {
        if (a->d[i] > b->d[i]) return 1;
        if (a->d[i] < b->d[i]) return -1;
    }
    return 0;
}

static void bsub(Big *a, const Big *b) {
    uint64_t borrow = 0;
    for (int i = 0; i < NLIMBS; ++i) {
        uint64_t av = a->d[i], bv = b->d[i] + borrow;
        if (av >= bv) { a->d[i] = av - bv; borrow = 0; }
        else { a->d[i] = BASE + av - bv; borrow = 1; }
    }
}

static int digit_sum_sqrt(int n) {
    Big r, p20, tmp, prod;
    bigzero(&r); bigzero(&p20);
    badd(&r, (uint64_t)n);

    int dsum = 0;
    for (int step = 0; step < 100; ++step) {
        if (step > 0) { bmul10(&r); bmul10(&r); }

        int x = 0;
        for (int xi = 9; xi >= 1; --xi) {
            memcpy(&tmp, &p20, sizeof(Big));
            badd(&tmp, xi);
            bmulsmall(&prod, &tmp, xi);
            if (bigcmp(&prod, &r) <= 0) { x = xi; break; }
        }

        dsum += x;
        memcpy(&tmp, &p20, sizeof(Big));
        badd(&tmp, x);
        bmulsmall(&prod, &tmp, x);
        bsub(&r, &prod);
        bmul10(&p20);
        badd(&p20, 20 * x);
    }
    return dsum;
}

int main() {
    int total = 0;
    for (int n = 2; n <= 99; ++n) {
        int sq = (int)__builtin_sqrt((double)n);
        if (sq * sq == n) continue;
        total += digit_sum_sqrt(n);
    }
    printf("%d\n", total);
    return 0;
}
