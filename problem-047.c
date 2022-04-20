#include <stdio.h>
#include <stdint.h>

#define MAX 1000000

uint8_t number_prime_factor[MAX];

void init_NPF();

int main() {
    init_NPF();

    int32_t i;
    for (i = 0; i < MAX - 4; ++i) {
        if (number_prime_factor[i] != 4) {
            continue;
        }
        if (number_prime_factor[i + 1] != 4) {
            continue;
        }
        if (number_prime_factor[i + 2] != 4) {
            continue;
        }
        if (number_prime_factor[i + 3] != 4) {
            continue;
        }
        break;
    }

    printf("%d\n", i);
    return 0;
}

void init_NPF() {
    for (uint32_t i = 0; i < MAX; ++i) {
        number_prime_factor[i] = 0;
    }

    for (uint32_t i = 2; i < MAX; ++i) {
        if (number_prime_factor[i] == 0) {
            for (uint32_t j = 2 * i; j < MAX; j += i) {
                ++number_prime_factor[j];
            }
        }
    }
}
