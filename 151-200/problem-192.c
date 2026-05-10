#include <math.h>
#include <stdint.h>
#include <stdio.h>

static const int64_t DEN_LIMIT = 1000000000000LL;
static int coeff[64];
static int64_t den[64];

static int isqrt_int(int n) {
    int r = (int)floor(sqrt((double)n));
    while (r * r > n) {
        r--;
    }
    while (r * (r + 2) < n) {
        r++;
    }
    return r;
}

static int64_t best_denominator(int n) {
    int r = isqrt_int(n);
    if (r * r == n) {
        return 0;
    }

    coeff[0] = r;
    den[0] = 1;

    int b = r;
    int c = n - b * b;
    coeff[1] = (b + r) / c;
    den[1] = coeff[1];

    int i = 1;
    while (den[i] < DEN_LIMIT) {
        b = coeff[i] * c - b;
        c = (n - b * b) / c;
        i++;
        coeff[i] = (b + r) / c;
        den[i] = (int64_t)coeff[i] * den[i - 1] + den[i - 2];
    }

    if (den[i] == DEN_LIMIT) {
        return DEN_LIMIT;
    }

    i--;
    int64_t j = (DEN_LIMIT - den[i - 1]) / den[i];
    int64_t candidate = j * den[i] + den[i - 1];

    int a2 = coeff[i + 1];
    if ((j << 1) > a2) {
        return candidate;
    }
    if ((j << 1) < a2) {
        return den[i];
    }

    b = a2 * c - b;
    c = (n - b * b) / c;
    a2 = (b + r) / c;
    int t = i;
    while (t > 0 && coeff[t] == a2) {
        t--;
        b = a2 * c - b;
        c = (n - b * b) / c;
        a2 = (b + r) / c;
    }

    if (t == 0) {
        return (i & 1) ? candidate : den[i];
    }

    if ((i - t) & 1) {
        a2 = coeff[t] - a2;
    } else {
        a2 -= coeff[t];
    }
    return (a2 > 0) ? candidate : den[i];
}

int main(void) {
    int64_t sum = 0;
    for (int n = 2; n <= 100000; n++) {
        sum += best_denominator(n);
    }
    printf("%lld\n", (long long)sum);
    return 0;
}
