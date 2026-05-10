#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static const char A[] =
    "14159265358979323846264338327950288419716939937510"
    "58209749445923078164062862089986280348253421170679";

static const char B[] =
    "82148086513282306647093844609550582231725359408128"
    "48111745028410270193852110555964462294895493038196";

static char digit_at(uint64_t index, const uint64_t *fib_lengths, uint32_t fib_count) {
    uint32_t current = 1;
    while (index >= fib_lengths[current]) {
        current++;
    }

    while (1) {
        if (current == 1) {
            return A[index];
        }
        if (current == 2) {
            return B[index];
        }

        if (index < fib_lengths[current - 2]) {
            current -= 2;
        } else {
            index -= fib_lengths[current - 2];
            current -= 1;
        }
    }
}

int main(void) {
    const uint64_t block_size = sizeof(A) - 1;
    uint64_t fib_lengths[128] = {0, block_size};
    uint32_t fib_count = 2;

    while (fib_lengths[fib_count - 1] < (1ULL << 63)) {
        fib_lengths[fib_count] = fib_lengths[fib_count - 1] + fib_lengths[fib_count - 2];
        fib_count++;
    }

    char result[19];
    for (int32_t n = 17; n >= 0; --n) {
        uint64_t index = 127 + 19 * (uint64_t)n;
        for (int32_t power = 0; power < n; ++power) {
            index *= 7;
        }

        result[17 - n] = digit_at(index - 1, fib_lengths, fib_count);
    }
    result[18] = '\0';

    printf("%s\n", result);
    return 0;
}