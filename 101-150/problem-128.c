#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_prime(uint64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i+2) == 0) return false;
    return true;
}

int main() {
    int target = 2000;
    /*
     * In the hex spiral, only H(k)=3k^2-3k+2 (first of ring k) and
     * L(k)=3k^2+3k+1 (last of ring k) can have PD=3, plus tile 1.
     *
     * Neighbors of H(k) have differences: 1, 1, 6k-6, 6k-1, 6k, 6k+1, 12k+5
     *   Prime candidates: 6k-1, 6k+1, 12k+5
     *
     * Neighbors of L(k) (k>=2) have differences: 1, 1, 6k, 6k+5, 6k+6, 12k-7
     *   Prime candidates: 6k-1, 6k+5, 12k-7
     *
     * Tile 2 = H(1): 6*1-1=5, 6*1+1=7, 12*1+5=17, all prime -> PD=3.
     * Tile 7 = L(1): check gives false positive; L(k) formula only valid k>=2.
     */
    int count = 2; /* tiles 1 and 2 */

    for (uint64_t k = 2; ; k++) {
        if (is_prime(6*k-1) && is_prime(6*k+1) && is_prime(12*k+5)) {
            count++;
            if (count == target) {
                printf("%lu\n", 3*k*k - 3*k + 2);
                return 0;
            }
        }
        if (is_prime(6*k-1) && is_prime(6*k+5) && is_prime(12*k-7)) {
            count++;
            if (count == target) {
                printf("%lu\n", 3*k*k + 3*k + 1);
                return 0;
            }
        }
    }
    return 0;
}
