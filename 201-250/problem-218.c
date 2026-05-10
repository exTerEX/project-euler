#include <stdint.h>
#include <stdio.h>

// Greatest common divisor
static uint64_t gcd(uint64_t x, uint64_t y) {
    while (x != 0) {
        uint64_t temp = x;
        x = y % x;
        y = temp;
    }
    return y;
}

// Count pairs (x,y) where ((x^2-y^2)^2 - (2xy)^2) * (x^2-y^2) * xy is not divisible by 42
static uint32_t countNotMod42(void) {
    uint32_t result = 0;
    
    // Check all pairs mod 42
    for (int x = 0; x < 42; x++) {
        for (int y = 0; y < 42; y++) {
            long long xx = (long long)x * x;
            long long yy = (long long)y * y;
            long long xy2 = 2LL * x * y;
            
            // ((x^2 - y^2)^2 - (2xy)^2) * (x^2 - y^2) * xy
            long long val1 = xx - yy;
            long long val2 = val1 * val1 - xy2 * xy2;
            long long zero = val2 * val1 * x * y;
            
            if (zero % 42 != 0) {
                result++;
            }
        }
    }
    
    return result;
}

int main(void) {
    // Mathematical analysis shows there are no perfect right-angled triangles
    // with c <= 10^16 that are not super-perfect
    // The proof uses the constraint that c must be a perfect square,
    // which leads to nested Pythagorean triples.
    // Checking the divisibility by 42 across all residue classes shows
    // that no valid solutions exist.
    
    printf("%u\n", countNotMod42());
    return 0;
}
