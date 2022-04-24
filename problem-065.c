#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SIZE 100

void swap(int32_t*, int32_t*);
void add(int32_t*, int32_t*, int32_t);
int32_t sum_digits(int32_t*);
void continued_fraction(int32_t, int32_t*, int32_t*, int32_t*);

int main() {
    int32_t coefs[SIZE];

    coefs[0] = 2;
    for (int32_t i = 1; i < SIZE; ++i) {
        if (i % 3 == 2) { coefs[i] = 2 * (i + 1) / 3; }
        else { coefs[i] = 1; }
    }

    int32_t num[SIZE], den[SIZE];

    continued_fraction(100, coefs, num, den);

    printf("%d\n", sum_digits(num));
    return 0;
}

void swap(int32_t* a, int32_t* b) {
    int32_t tmp[SIZE];

    memcpy(tmp, a, SIZE * sizeof * a);
    memcpy(a, b, SIZE * sizeof * b);
    memcpy(b, tmp, SIZE * sizeof * b);
}

void add(int32_t* num, int32_t* den, int32_t x) {
    for (int32_t i = 0, carry = 0; i < SIZE; ++i)
    {
        carry += x * den[i] + num[i];
        num[i] = carry % 10;
        carry /= 10;
    }
}

int32_t sum_digits(int32_t* ar) {
    int32_t i, s;
    for (i = 0, s = 0; i < SIZE; ++i) {
        s += ar[i];
    }

    return s;
}

void continued_fraction(int32_t n, int32_t* coef, int32_t* num, int32_t* den) {
    if (n < 1) {
        printf("error: can't compute a negative n-th term (n=%d)\n", n);
        return;
    }

    memset(num, 0, SIZE * sizeof * num);
    memset(den, 0, SIZE * sizeof * den);

    for (int32_t i = 0, j = coef[n - 1]; j > 0 && i < SIZE; ++i, j /= 10) {
        num[i] = j % 10;
    }

    den[0] = 1;

    for (int32_t i = n - 2; i >= 0; --i)
    {
        swap(num, den);
        add(num, den, coef[i]);
    }
}
