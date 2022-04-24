#include <stdio.h>
#include <stdint.h>

int32_t is_curious(int32_t, int32_t);
void simplify(int64_t*, int64_t*);

int main() {
    int64_t n = 1, m = 1;

    for (int32_t a = 10; a < 100; ++a) {
        for (int32_t b = a + 1; b < 100; ++b) {
            if (is_curious(a, b)) {
                n *= a;
                m *= b;
            }
        }
    }

    simplify(&n, &m);
    printf("%lu\n", m);

    return 0;
}

int32_t is_curious(int32_t n, int32_t m) {
    int32_t a = n / 10;
    int32_t b = n % 10;
    int32_t c = m / 10;
    int32_t d = m % 10;

    if (b == 0 && d == 0) { return 0; }

    if (a == c) {
        return (float)b / d == (float)n / m;
    }
    else if (a == d) {
        return (float)b / c == (float)n / m;
    }
    else if (b == c) {
        return (float)a / d == (float)n / m;
    }
    else if (b == d) {
        return (float)a / c == (float)n / m;
    }

    return 0;
}

void simplify(int64_t* n, int64_t* m)
{
    for (int64_t i = *n; i > 1; --i) {
        if (*n % i == 0 && *m % i == 0) {
            *n /= i;
            *m /= i;
        }
    }
}
