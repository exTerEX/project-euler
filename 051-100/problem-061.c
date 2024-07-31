#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LOW 1000
#define MAX 10000
#define CYCLE_LENGTH 6

int32_t count[CYCLE_LENGTH];
int32_t* numbers[CYCLE_LENGTH];

int32_t compute_triangle(int32_t);
int32_t compute_square(int32_t);
int32_t compute_penta(int32_t);
int32_t compute_hexa(int32_t);
int32_t compute_hepta(int32_t);
int32_t compute_octa(int32_t);
int32_t* generate_numbers(int32_t*, int32_t(*)(int32_t));
void print_array(int32_t*, int32_t);
int32_t next_permutation(int32_t*, int32_t);

int main() {
    int32_t s[CYCLE_LENGTH], i, answer = 0, found = 0;

    for (i = 0; i < CYCLE_LENGTH; ++i) { s[i] = i; }

    numbers[0] = generate_numbers(&count[0], compute_triangle);
    numbers[1] = generate_numbers(&count[1], compute_square);
    numbers[2] = generate_numbers(&count[2], compute_penta);
    numbers[3] = generate_numbers(&count[3], compute_hexa);
    numbers[4] = generate_numbers(&count[4], compute_hepta);
    numbers[5] = generate_numbers(&count[5], compute_octa);

    while (!found) {
        for (int32_t n1 = 0; n1 < count[s[0]]; ++n1) {
            for (int32_t n2 = 0; n2 < count[s[1]]; ++n2) {
                if (numbers[s[0]][n1] % 100 != numbers[s[1]][n2] / 100) { continue; }

                for (int32_t n3 = 0; n3 < count[s[2]]; ++n3) {
                    if (numbers[s[1]][n2] % 100 != numbers[s[2]][n3] / 100) { continue; }

                    for (int32_t n4 = 0; n4 < count[s[3]]; ++n4) {
                        if (numbers[s[2]][n3] % 100 != numbers[s[3]][n4] / 100) { continue; }

                        for (int32_t n5 = 0; n5 < count[s[4]]; ++n5) {
                            if (numbers[s[3]][n4] % 100 != numbers[s[4]][n5] / 100) { continue; }

                            for (int32_t n6 = 0; n6 < count[s[5]]; ++n6) {
                                if (numbers[s[4]][n5] % 100 != numbers[s[5]][n6] / 100
                                    || numbers[s[5]][n6] % 100 != numbers[s[0]][n1] / 100) {
                                    continue;
                                }

                                answer = numbers[s[0]][n1];
                                answer += numbers[s[1]][n2];
                                answer += numbers[s[2]][n3];
                                answer += numbers[s[3]][n4];
                                answer += numbers[s[4]][n5];
                                answer += numbers[s[5]][n6];
                                found = 1;
                            }
                        }
                    }
                }
            }
        }

        next_permutation(s, CYCLE_LENGTH);
        ++i;
    }

    printf("%d\n", answer);

    for (i = 0; i < CYCLE_LENGTH; ++i) { free(numbers[i]); }

    return 0;
}

int32_t compute_triangle(int32_t n) { return n * (n + 1) / 2; }

int32_t compute_square(int32_t n) { return n * n; }

int32_t compute_penta(int32_t n) { return n * (3 * n - 1) / 2; }

int32_t compute_hexa(int32_t n) { return n * (2 * n - 1); }

int32_t compute_hepta(int32_t n) { return n * (5 * n - 3) / 2; }

int32_t compute_octa(int32_t n) { return n * (3 * n - 2); }

int32_t* generate_numbers(int32_t* n_numbers, int32_t(*formula)(int32_t)) {
    int32_t* numbers = 0;
    for (int32_t n = 1; ; ++n) {
        int32_t polygonal = formula(n);
        if (polygonal >= MAX) { break; }
        if (polygonal >= LOW && polygonal % 100 >= 10) { ++* n_numbers; }
    }

    numbers = calloc(*n_numbers, sizeof * numbers);
    for (int32_t n = 1, i = 0; ; ++n) {
        int32_t polygonal = formula(n);

        if (polygonal >= MAX) { break; }
        if (polygonal >= LOW && polygonal % 100 >= 10) { numbers[i++] = polygonal; }
    }

    return numbers;
}

void print_array(int32_t* ar, int32_t size) {
    for (int32_t i = 0; i < size; ++i) {
        printf("%d%c", ar[i], i % 10 == 9 ? '\n' : ' ');
    }

    printf("\n");
}

int32_t next_permutation(int32_t* ar, int32_t size) {
    int32_t k, l, temp;
    for (k = size - 2; k >= 0 && ar[k] >= ar[k + 1]; --k) { ; }
    if (k < 0) { return -1; }

    for (l = size - 1; l > k + 1 && ar[k] >= ar[l]; --l) { ; }
    if (l == size) { return -1; }

    temp = ar[l];
    ar[l] = ar[k];
    ar[k] = temp;

    for (k = k + 1, l = size - 1; k < l; k++, l--) {
        temp = ar[k], ar[k] = ar[l], ar[l] = temp;
    }

    return 1;
}
