#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Configuration
#define NUM_DICE 20
#define MAX_POINTS 12
#define NUM_TOP 10
#define SUM_TOP 70

// Pre-computed factorials
uint64_t factorial[NUM_DICE + 1];

// Count permutations of the dice configuration
// Uses formula: n! / (n1! * n2! * ... * nk!)
uint64_t count(uint32_t *dices, int size) {
    static uint32_t howOften[MAX_POINTS + 1];
    
    // Re-initialize count array
    memset(howOften, 0, sizeof(howOften));
    
    // Count occurrences of each value
    for (int i = 0; i < size; i++) {
        howOften[dices[i]]++;
    }
    
    // Compute permutations: n! / (c1! * c2! * ... * c12!)
    uint64_t result = factorial[NUM_DICE];
    for (int i = 1; i <= MAX_POINTS; i++) {
        if (howOften[i] > 1) {
            result /= factorial[howOften[i]];
        }
    }
    
    return result;
}

// Recursively generate dice configurations
uint64_t search(uint32_t *dices, int size, uint32_t sum_top) {
    // All dice generated?
    if (size == NUM_DICE) {
        return count(dices, size);
    }
    
    // Check if top dice sum is correct
    if (size == NUM_TOP) {
        if (sum_top != SUM_TOP) {
            return 0;
        }
    }
    
    // Maximum value for next die (descending order)
    uint32_t maxDice = MAX_POINTS;
    if (size > 0) {
        maxDice = dices[size - 1];
    }
    
    // Try all possible values for the next die
    uint64_t result = 0;
    for (uint32_t dice = 1; dice <= maxDice; dice++) {
        dices[size] = dice;
        uint32_t newSum = sum_top;
        if (size < NUM_TOP) {
            newSum += dice;
        }
        result += search(dices, size + 1, newSum);
    }
    
    return result;
}

int main(void) {
    // Pre-compute factorials
    factorial[0] = 1;
    for (int i = 1; i <= NUM_DICE; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
    
    // Start the search
    uint32_t dices[NUM_DICE];
    uint64_t result = search(dices, 0, 0);
    
    printf("%lu\n", result);
    return 0;
}
