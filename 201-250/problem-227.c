#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef double Number;

int main(void) {
    unsigned int players = 100;
    if (!isatty(fileno(stdin))) {
        if (scanf("%u", &players) != 1) {
            players = 100;
        }
    }

    const Number epsilon = 0.00000000001;
    size_t size = players / 2 + 1;
    Number *last = calloc(size, sizeof(Number));
    Number *next = calloc(size, sizeof(Number));
    if (last == NULL || next == NULL) {
        free(last);
        free(next);
        return 1;
    }

    last[size - 1] = 1.0;
    Number expected = 0.0;

    for (unsigned int iteration = 1;; ++iteration) {
        for (size_t i = 0; i < size; ++i) {
            next[i] = 0.0;
        }

        for (size_t current = 1; current < size; ++current) {
            Number minus2 = 1.0 / 36.0;
            Number minus1 = 8.0 / 36.0;
            Number same = 18.0 / 36.0;
            Number plus1 = 8.0 / 36.0;
            Number plus2 = 1.0 / 36.0;

            if (current == 1) {
                same += minus2;
                minus2 = 0.0;
            } else if (current + 1 == size - 1) {
                same += plus2;
                plus2 = 0.0;
            } else if (current == size - 1) {
                minus2 += plus2;
                minus1 += plus1;
                plus2 = 0.0;
                plus1 = 0.0;
            }

            if (current >= 2) {
                next[current - 2] += minus2 * last[current];
            }
            next[current - 1] += minus1 * last[current];
            next[current] += same * last[current];
            if (current + 1 < size) {
                next[current + 1] += plus1 * last[current];
            }
            if (current + 2 < size) {
                next[current + 2] += plus2 * last[current];
            }
        }

        Number *swap = last;
        last = next;
        next = swap;

        Number finished = last[0];
        Number delta = finished * iteration;
        expected += delta;

        if (iteration > players * players && delta < epsilon) {
            break;
        }
    }

    printf("%.6f\n", expected);
    free(last);
    free(next);
    return 0;
}