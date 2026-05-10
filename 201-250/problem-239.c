#include <stdio.h>
#include <math.h>

// Factorial - returns double for large ranges
double factorial(unsigned int n) {
    double result = 1.0;
    while (n > 1) {
        result *= n;
        n--;
    }
    return result;
}

// Binomial coefficient: n choose k
double choose(unsigned int n, unsigned int k) {
    return factorial(n) / (factorial(n - k) * factorial(k));
}

// Count derangements
// move: number of primes to move
// dontCare: number of non-prime disks (can be anywhere)
double derangements(unsigned int move, unsigned int dontCare) {
    if (move < 1) {
        return factorial(dontCare);
    }
    
    move--;
    double result = dontCare * derangements(move, dontCare);
    if (move > 0) {
        result += move * derangements(move - 1, dontCare + 1);
    }
    
    return result;
}

int main(void) {
    unsigned int disks = 100;
    unsigned int primes = 25;  // primes < 100
    unsigned int moved = 22;   // exactly 22 primes out of position
    
    unsigned int unchanged = primes - moved;
    
    // Count ways for the derangement
    double result = derangements(moved, disks - primes);
    
    // Multiply by number of ways to choose which primes stay in place
    result *= choose(primes, unchanged);
    
    // Divide by total permutations
    result /= factorial(disks);
    
    printf("%.12f\n", result);
    return 0;
}
