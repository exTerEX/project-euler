#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 20000000

// Sieve of Eratosthenes
static uint8_t isPrime[LIMIT + 1];

void sieve(void) {
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = 0;
    
    for (uint32_t i = 2; i * i <= LIMIT; i++) {
        if (isPrime[i]) {
            for (uint32_t j = i * i; j <= LIMIT; j += i) {
                isPrime[j] = 0;
            }
        }
    }
}

// Calculate sum of prime factors of n! using Legendre's formula
uint64_t add(uint32_t n) {
    uint64_t sum = 0;
    
    for (uint32_t p = 2; p <= n; p++) {
        if (isPrime[p]) {
            // For each prime p, count how many times it divides n!
            // Using Legendre's formula: floor(n/p) + floor(n/p^2) + floor(n/p^3) + ...
            uint64_t multiplePower = p;
            uint64_t count = n / multiplePower;
            
            while (count > 0) {
                sum += (uint64_t)p * count;
                
                // Check for overflow before multiplying
                if (multiplePower > n / p) break;
                multiplePower *= p;
                count = n / multiplePower;
            }
        }
    }
    
    return sum;
}

int main(void) {
    uint32_t n = 20000000;
    uint32_t k = 15000000;
    
    // Generate all primes up to n
    sieve();
    
    // Calculate sum of prime factors of C(n,k) = C(n, n-k)
    // C(n,k) = n! / (k! * (n-k)!)
    // sum of prime factors = add(n) - add(k) - add(n-k)
    
    uint64_t result = add(n) - add(k) - add(n - k);
    
    printf("%lu\n", result);
    return 0;
}
