#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef _OPENMP
#include <omp.h>
#endif

uint8_t get_perfect_number(uint64_t);
uint8_t is_abundant(uint64_t, uint8_t* abundant);
uint64_t get_next_abundant(uint64_t, uint8_t* abundant);
uint8_t is_sum_of_abundant(uint64_t, uint8_t* abundant);

int main() {
    uint64_t max_n = 28123;

    uint8_t* abundant = (uint8_t*)calloc(max_n >> 3, 1);

    if (!abundant) { perror("Unable to allocate memoey!"); return 1; }

#ifdef _OPENMP
#pragma omp for schedule(runtime)
#endif

    for (uint64_t N = 1; N <= max_n; N++) {
        uint8_t ret = get_perfect_number(N);

        if (ret == 1) {
            int byte_offset = N & 7, index = N >> 3;

#ifdef _OPENMP
#pragma omp critical
#endif
            abundant[index] |= ret << byte_offset;
        }
    }

    uint64_t sum = 0;

#ifdef _OPENMP
#pragma omp parallel for schedule(runtime) reduction(+ : sum)
#endif

    for (uint64_t i = 1; i < max_n; i++) {
        if (!is_sum_of_abundant(i, abundant)) { sum += i; }

#ifdef _OPENMP
#pragma omp critical
#endif

        if (i % 100 == 0) { fflush(stdout); }
    }

    printf("%lu\n", sum);

    free(abundant);

    return 0;
}

uint8_t get_perfect_number(uint64_t N) {
    uint64_t sum = 1;

    for (uint64_t i = 2; i * i <= N; i++) {
        if (N % i == 0) {
            sum += i;
            uint64_t tmp = N / i;

            if (tmp != i) {
                sum += tmp;
            }
        }
    }

    return sum == N ? 0 : (sum > N ? 1 : -1);;
}

uint8_t is_abundant(uint64_t N, uint8_t* abundant) {
    return abundant[N >> 3] & (1 << (N & 7)) ? 1 : 0;
}

uint64_t get_next_abundant(uint64_t N, uint8_t* abundant) {
    uint64_t i;

    for (i = N + 1; !is_abundant(i, abundant); ++i)
    {
        ;
    }

    return i;
}

uint8_t is_sum_of_abundant(uint64_t N, uint8_t* abundant) {
    for (uint64_t i = get_next_abundant(1, abundant); i <= (N >> 1); i = get_next_abundant(i, abundant)) {
        if (is_abundant(N - i, abundant)) { return 1; }
    }

    return 0;
}
