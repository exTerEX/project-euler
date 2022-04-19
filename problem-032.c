#include <stdio.h>
#include <stdint.h>

int32_t is_pandigital(int32_t, int32_t, int32_t);

int main() {
    int32_t c, answer = 0;
    int8_t done[10000] = { 0 };

    for (int32_t a = 1; a < 10; ++a) {
        for (int32_t b = 1000; b < 10000; ++b) {
            if (is_pandigital(a, b, c = a * b) && !done[c]){
                answer += c;
                done[c] = 1;
            }
        }
    }

    for (int32_t a = 10; a < 100; ++a) {
        for (int32_t b = 100; b < 1000; ++b) {
            if (is_pandigital(a, b, c = a * b) && !done[c]){
                answer += c;
                done[c] = 1;
            }
        }
    }

    printf("%u\n", answer);
    return 0;
}

int32_t is_pandigital(int32_t m1, int32_t m2, int32_t product) {
    int32_t counter[10] = { 0 };

    for (; m1 > 0; m1 /= 10) {
        ++counter[m1 % 10];
    }
    for (; m2 > 0; m2 /= 10) {
        ++counter[m2 % 10];
    }
    for (; product > 0; product /= 10) {
        ++counter[product % 10];
    }

    for (int32_t i = 1; i < 10; ++i) {
        if (counter[i] != 1) {
            return 0;
        }
    }

    return counter[0] == 0;
}

