#include <stdio.h>
#include <stdint.h>

#define MIN 2
#define MAX 100

int main() {
    int32_t n_duplicate = 0;
    uint8_t done[MAX - MIN + 1] = { 0 };

    for (int32_t i = MIN; i <= MAX; ++i) {
        int32_t n = i;

        for (int32_t j = MIN; j <= MAX; ++j) {
            n *= i;

            if (n > MAX || done[n - MIN]) { break; }

            done[n - MIN] = 1;

            if (j == 2) {
                n_duplicate += MAX / 2 - 1;
                continue;
            }

            for (int32_t k = MIN; k <= MAX; ++k) {
                int32_t exponent = j * k;

                if (exponent <= MAX) {
                    ++n_duplicate;
                    continue;
                }

                for (int32_t l = MIN; l < j; ++l) {
                    if (!(exponent % l) && exponent / l <= MAX) {
                        ++n_duplicate;
                        break;
                    }
                }
            }
        }
    }

    printf("%d\n", (MAX - MIN + 1) * (MAX - MIN + 1) - n_duplicate);

    return 0;
}
