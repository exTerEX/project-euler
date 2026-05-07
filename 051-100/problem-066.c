#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define LIMBS 20
#define BASE 1000000000ULL

typedef struct { uint64_t d[LIMBS]; int n; } Big;

static void bset(Big *b, uint64_t v) {
    memset(b->d, 0, sizeof(b->d));
    b->n = 0;
    do { b->d[b->n++] = v % BASE; v /= BASE; } while (v);
}

static void bcpy(Big *dst, const Big *src) {
    dst->n = src->n;
    memcpy(dst->d, src->d, src->n * sizeof(uint64_t));
}

static void bmuladd(Big *r, const Big *a, uint64_t mul, const Big *add) {
    uint64_t carry = 0;
    int maxn = a->n > add->n ? a->n : add->n;
    r->n = 0;
    for (int i = 0; i < maxn || carry; ++i) {
        uint64_t v = carry;
        if (i < a->n) v += a->d[i] * mul;
        if (i < add->n) v += add->d[i];
        r->d[i] = v % BASE;
        carry = v / BASE;
        r->n = i + 1;
    }
}

static int bgt(const Big *a, const Big *b) {
    if (a->n != b->n) return a->n > b->n;
    for (int i = a->n - 1; i >= 0; --i)
        if (a->d[i] != b->d[i]) return a->d[i] > b->d[i];
    return 0;
}

static uint32_t cf_period(uint32_t D, uint32_t a0) {
    uint32_t m = 0, d = 1, a = a0, p = 0;
    do {
        m = d * a - m;
        d = (D - m * m) / d;
        a = (a0 + m) / d;
        ++p;
    } while (a != 2 * a0);
    return p;
}

static void pell_x(uint32_t D, uint32_t a0, uint32_t iters, Big *x) {
    Big hp, hc, kp, kc, hn, kn;
    bset(&hp, 1); bset(&hc, a0);
    bset(&kp, 0); bset(&kc, 1);
    uint32_t m = 0, d = 1, a = a0;
    for (uint32_t i = 0; i < iters; ++i) {
        m = d * a - m;
        d = (D - m * m) / d;
        a = (a0 + m) / d;
        bmuladd(&hn, &hc, a, &hp);
        bmuladd(&kn, &kc, a, &kp);
        bcpy(&hp, &hc); bcpy(&hc, &hn);
        bcpy(&kp, &kc); bcpy(&kc, &kn);
    }
    bcpy(x, &hc);
}

int main() {
    Big best, cur;
    uint32_t best_d = 0;
    bset(&best, 0);

    for (uint32_t D = 2; D <= 1000; ++D) {
        uint32_t a0 = (uint32_t)sqrt((double)D);
        if (a0 * a0 == D) continue;
        uint32_t r = cf_period(D, a0);
        uint32_t iters = (r % 2 == 0) ? r - 1 : 2 * r - 1;
        pell_x(D, a0, iters, &cur);
        if (bgt(&cur, &best)) {
            bcpy(&best, &cur);
            best_d = D;
        }
    }

    printf("%u\n", best_d);
    return 0;
}
