#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LIMIT 100000000

int main(void) {
    int max_prime = LIMIT / 2;
    unsigned char *is_prime = (unsigned char *)malloc((size_t)max_prime + 1);
    if (is_prime == NULL) {
        return 1;
    }

    for (int i = 0; i <= max_prime; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = 0;
    is_prime[1] = 0;

    for (int i = 2; (int64_t)i * i <= max_prime; i++) {
        if (!is_prime[i]) {
            continue;
        }
        for (int j = i * i; j <= max_prime; j += i) {
            is_prime[j] = 0;
        }
    }

    int *primes = (int *)malloc(((size_t)max_prime / 2 + 10) * sizeof(int));
    if (primes == NULL) {
        free(is_prime);
        return 1;
    }

    int prime_count = 0;
    for (int i = 2; i <= max_prime; i++) {
        if (is_prime[i]) {
            primes[prime_count++] = i;
        }
    }
    free(is_prime);

    int64_t answer = 0;
    int j = prime_count - 1;
    for (int i = 0; i < prime_count; i++) {
        int64_t p = primes[i];
        if (p * p >= LIMIT) {
            break;
        }
        while (j >= i && p * primes[j] >= LIMIT) {
            j--;
        }
        if (j < i) {
            break;
        }
        answer += (j - i + 1);
    }

    free(primes);
    printf("%lld\n", (long long)answer);
    return 0;
}
