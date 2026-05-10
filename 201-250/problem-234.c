#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LIMIT 999966663333ULL
#define SIEVE_LIMIT 1000100

static uint8_t sieve[SIEVE_LIMIT];

void fillSieve(uint32_t limit) {
    if (limit >= SIEVE_LIMIT) limit = SIEVE_LIMIT - 1;
    
    memset(sieve, 1, limit + 1);
    sieve[0] = sieve[1] = 0;
    
    for (uint32_t i = 2; i * i <= limit; i++) {
        if (sieve[i]) {
            for (uint32_t j = i * i; j <= limit; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

uint8_t isPrime(uint32_t x) {
    if (x >= SIEVE_LIMIT) return 0;
    return sieve[x];
}

int main(void) {
    uint64_t limit = LIMIT;
    uint32_t sqrtLimit = (uint32_t)sqrt((double)limit) + 100;
    
    fillSieve(sqrtLimit);
    
    uint64_t sum = 0;
    
    // Find consecutive prime pairs
    uint64_t last = 2;
    while (last * last <= limit) {
        // Find next prime
        uint64_t next = last + 1;
        while (next < SIEVE_LIMIT && !isPrime(next)) {
            next++;
        }
        
        if (next >= SIEVE_LIMIT) break;
        
        uint64_t from = last * last;
        uint64_t to = next * next;
        
        // Add multiples of last only (not both)
        for (uint64_t i = from + last; i < to && i <= limit; i += last) {
            sum += i;
        }
        
        // Adjust to-boundary if needed
        while (to > limit && to - next > limit) {
            to -= next;
        }
        
        // Add multiples of next only (not both)
        for (uint64_t i = to - next; i > from && i <= limit; i -= next) {
            sum += i;
        }
        
        // Subtract multiples of both (counted twice)
        uint64_t lcm = last * next;
        uint64_t startMult = from + (lcm - (from % lcm)) % lcm;
        
        for (uint64_t i = startMult; i < to && i <= limit; i += lcm) {
            if (i > from) {
                sum -= 2 * i;
            }
        }
        
        last = next;
    }
    
    printf("%lu\n", sum);
    return 0;
}
