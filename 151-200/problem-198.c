#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int p;
    int q;
} Frac;

int main(void) {
    const int max_denom = 100000000;
    const int frac_limit = 100;

    size_t cap = 1 << 20;
    Frac *stack = (Frac *)malloc(cap * sizeof(Frac));
    if (stack == NULL) {
        return 1;
    }
    size_t top = 0;

    int64_t n = 0;
    int64_t m = 1;
    stack[top++] = (Frac){1, frac_limit / 2};

    int64_t count = 0;
    while (top > 0) {
        Frac f = stack[top - 1];
        int64_t N = f.p;
        int64_t M = f.q;

        int64_t n2 = n + N;
        int64_t m2 = m + M;
        int64_t p = n * M + N * m;
        int64_t q = 2 * m * M;

        if (q <= max_denom) {
            if (top == cap) {
                cap *= 2;
                Frac *tmp = (Frac *)realloc(stack, cap * sizeof(Frac));
                if (tmp == NULL) {
                    free(stack);
                    return 1;
                }
                stack = tmp;
            }
            stack[top++] = (Frac){(int)n2, (int)m2};
            if (frac_limit * p < q) {
                count++;
            }
            continue;
        }

        n = N;
        m = M;
        top--;
    }

    free(stack);
    printf("%lld\n", (long long)count);
    return 0;
}
