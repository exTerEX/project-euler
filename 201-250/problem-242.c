#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/* Odd Triplets.
 *
 * Let n = 2t+1 and k = 2m+1 (both odd).
 * Then
 *   f(n,k) = 1/2 * ( C(2t+1,2m+1) + C(t,m) ).
 * The parity pattern simplifies to:
 *   f(n,k) is odd iff t is even and m is even and (m/2) is a bit-subset of (t/2).
 * Therefore, for t = 2u, the number of valid odd k is 2^{popcount(u)};
 * for odd t it is 0.
 *
 * So the answer for n <= N is:
 *   sum_{u=0}^{floor((N-2)/4)} 2^{popcount(u)}.
 *
 * Compute S(M) = sum_{u=0}^M 2^{popcount(u)} with binary digit DP:
 * For each set bit at position i in M, add 2^{ones_before} * 3^i.
 */

static uint64_t sum_pow2_popcount(uint64_t m) {
    uint64_t pow3[64];
    pow3[0] = 1;
    for (int i = 1; i < 64; i++) {
        pow3[i] = pow3[i - 1] * 3ULL;
    }

    uint64_t ans = 0;
    int ones = 0;

    for (int i = 63; i >= 0; i--) {
        if ((m >> i) & 1ULL) {
            ans += (1ULL << ones) * pow3[i];
            ones++;
        }
    }
    ans += (1ULL << ones);
    return ans;
}

int main(void) {
    const uint64_t N = 1000000000000ULL;
    const uint64_t M = (N - 2ULL) / 4ULL;
    printf("%" PRIu64 "\n", sum_pow2_popcount(M));
    return 0;
}
