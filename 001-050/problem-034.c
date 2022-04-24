#include <stdio.h>
#include <stdint.h>

int32_t factorial[] = { 1,1,2,6,24,120,720,5040,40320,362880 };

int32_t is_sum_factorial(int32_t);

int main() {
    int32_t n, answer;
    for (n = 3, answer = 0; n <= 2540160; ++n) {
        if (is_sum_factorial(n)) { answer += n; }
    }

    printf("%d\n", answer);
    return 0;
}

int32_t is_sum_factorial(int32_t n) {
    int32_t sum, i;
    for (sum = 0, i = n; n != 0; n /= 10) {
        sum += factorial[n % 10];
    }

    return sum == i;
}
