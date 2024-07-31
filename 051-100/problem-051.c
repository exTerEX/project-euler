#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 1000000

uint8_t sieve[MAX];

void init_sieve();
int32_t generate_number(uint8_t*, int32_t, int32_t, int32_t);
int32_t family_length(uint8_t*, int32_t, int32_t, int32_t);

int main() {
    int32_t i, j, k;

    uint8_t patterns[10][6] = {
        {1, 1, 1, 0, 0, 0},
        {1, 1, 0, 1, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {0, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 0},
        {0, 0, 1, 1, 1, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 0},
    };

    init_sieve();
    for (i = 0; i < 10; ++i) {
        for (j = 100; j < 1000; ++j) {
            for (k = 0; k <= 2; ++k) {
                if (patterns[i][0] == 1 && k == 0) {
                    continue;
                }
                if (family_length(patterns[i], 6, k, j) == 8) {
                    goto end;
                }
            }
        }
    }

end:
    printf("%d\n", generate_number(patterns[i], 6, k, j));

    return 0;
}

void init_sieve() {
    int32_t i, j;

    for (int32_t i = 0; i < MAX; ++i)
        sieve[i] = 1;
    sieve[0] = sieve[1] = 0;

    for (int32_t i = 2; i < MAX; ++i) {
        if (sieve[i]) {
            for (int32_t j = 2 * i; j < MAX; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int32_t generate_number(uint8_t* pattern, int32_t len,
    int32_t repeated, int32_t non_repeated) {
    uint8_t* digits = calloc(len, sizeof * digits);
    for (int32_t i = 0; i < len; ++i)
    {
        if (pattern[i] == 1) {
            digits[i] = repeated;
        }
        else
        {
            digits[i] = non_repeated % 10;
            non_repeated /= 10;
        }
    }

    int32_t number = 0;
    for (int32_t i = 0; i < len; ++i) { number = 10 * number + digits[i]; }

    return number;
}

int32_t family_length(uint8_t* pattern, int32_t len,
    int32_t repeated, int32_t non_repeated) {
    int32_t count = 0;

    for (; repeated < 10; ++repeated) {
        if (sieve[generate_number(pattern, len, repeated, non_repeated)]) {
            ++count;
        }
    }

    return count;
}
