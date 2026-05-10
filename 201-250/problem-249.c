#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 5000
#define MODULO 10000000000000000ULL
#define MAX_SUM 1700000

// Sieve of Eratosthenes - large version
static uint8_t primeSieve[MAX_SUM + 1];

void fillSieve(int limit) {
    if (limit > MAX_SUM) limit = MAX_SUM;
    if (limit < 2) return;
    
    for (int i = 0; i <= limit; i++) {
        primeSieve[i] = 1;
    }
    primeSieve[0] = primeSieve[1] = 0;
    
    for (int i = 2; i * i <= limit; i++) {
        if (primeSieve[i]) {
            for (int j = i * i; j <= limit; j += i) {
                primeSieve[j] = 0;
            }
        }
    }
}

int main(void) {
    // First pass: generate primes and calculate sum
    fillSieve(LIMIT);
    
    uint32_t maxSum = 0;
    for (int i = 2; i <= LIMIT; i++) {
        if (primeSieve[i]) {
            maxSum += i;
        }
    }
    
    // Now extend the sieve to cover maxSum
    fillSieve(maxSum);
    
    // DP array: count[s] = number of subsets with sum s
    uint64_t *count = (uint64_t *)calloc(maxSum + 1, sizeof(uint64_t));
    
    // Initially, one empty set with sum 0
    count[0] = 1;
    uint32_t largest = 0;
    
    // Add each prime to the existing subsets
    for (int prime = 2; prime <= LIMIT; prime++) {
        if (primeSieve[prime]) {
            largest += prime;
            
            // Process in descending order to avoid collisions
            for (uint32_t s = largest; s >= prime; s--) {
                count[s] += count[s - prime];
                count[s] %= MODULO;
            }
        }
    }
    
    // Count subsets whose sum is prime
    uint64_t result = 0;
    for (uint32_t i = 0; i <= maxSum; i++) {
        if (primeSieve[i]) {
            result += count[i];
            result %= MODULO;
        }
    }
    
    printf("%lu\n", result);
    free(count);
    return 0;
}
