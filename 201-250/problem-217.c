#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Balanced Numbers: T(47) mod 3^15
 * A k-digit number is balanced if sum of first ceil(k/2) digits = sum of last ceil(k/2) digits.
 * For even k: left half h=k/2 digits, right half h=k/2 digits (no overlap).
 * For odd k: left half h=(k+1)/2 digits, right half h=(k+1)/2 digits (middle digit shared).
 *
 * We compute contribution for each digit count k from 1 to 47.
 * DP tables indexed by [half_length][digit_sum]:
 *   cnt_free[h][s] = count of h-digit strings (all digits 0-9) with digit sum s
 *   val_free[h][s] = sum of values (mod MOD) of such strings
 *   cnt_lead[h][s] = count of h-digit strings (first digit 1-9, rest 0-9) with digit sum s
 *   val_lead[h][s] = sum of values of such strings
 */

#define MOD 14348907ULL  /* 3^15 */
#define MAX_H 25
#define MAX_SUM (9 * MAX_H + 1)

static uint64_t cnt_free[MAX_H][MAX_SUM];
static uint64_t val_free[MAX_H][MAX_SUM];
static uint64_t cnt_lead[MAX_H][MAX_SUM];
static uint64_t val_lead[MAX_H][MAX_SUM];

/* pow10[i] = 10^i mod MOD */
static uint64_t pow10[50];

int main(void) {
    pow10[0] = 1;
    for (int i = 1; i < 50; i++) {
        pow10[i] = pow10[i-1] * 10 % MOD;
    }

    /* Build tables for h=1..24 */
    /* h=1: */
    for (int d = 0; d <= 9; d++) {
        cnt_free[1][d] = (cnt_free[1][d] + 1) % MOD;
        val_free[1][d] = (val_free[1][d] + d) % MOD;
    }
    for (int d = 1; d <= 9; d++) {
        cnt_lead[1][d] = (cnt_lead[1][d] + 1) % MOD;
        val_lead[1][d] = (val_lead[1][d] + d) % MOD;
    }
    for (int h = 2; h < MAX_H; h++) {
        for (int s = 0; s < MAX_SUM; s++) {
            if (cnt_free[h-1][s] == 0 && val_free[h-1][s] == 0) continue;
            /* Append one more digit 0-9 */
            for (int d = 0; d <= 9; d++) {
                int ns = s + d;
                if (ns >= MAX_SUM) continue;
                /* new_val = old_val * 10 + d * cnt_old */
                cnt_free[h][ns] = (cnt_free[h][ns] + cnt_free[h-1][s]) % MOD;
                val_free[h][ns] = (val_free[h][ns] + val_free[h-1][s] * 10 % MOD + (uint64_t)d * cnt_free[h-1][s]) % MOD;
            }
        }
        for (int s = 0; s < MAX_SUM; s++) {
            if (cnt_lead[h-1][s] == 0 && val_lead[h-1][s] == 0) continue;
            for (int d = 0; d <= 9; d++) {
                int ns = s + d;
                if (ns >= MAX_SUM) continue;
                cnt_lead[h][ns] = (cnt_lead[h][ns] + cnt_lead[h-1][s]) % MOD;
                val_lead[h][ns] = (val_lead[h][ns] + val_lead[h-1][s] * 10 % MOD + (uint64_t)d * cnt_lead[h-1][s]) % MOD;
            }
        }
    }

    uint64_t total = 0;

    for (int k = 1; k <= 47; k++) {
        int h = (k + 1) / 2;
        if (k % 2 == 0) {
            /* Even k: left half h digits (leading nonzero), right half h digits (free) */
            /* Number = left_val * 10^h + right_val */
            /* Sum over s: (val_lead[h][s] * 10^h + val_free[h][s] * cnt_lead[h][s]) */
            /* Wait: for each matching pair (left,right) with same sum s:
             * contribution = left_val * 10^h + right_val
             * sum over all pairs = sum_s [val_lead[h][s] * cnt_free[h][s] * 10^h + cnt_lead[h][s] * val_free[h][s]] */
            for (int s = 0; s < MAX_SUM; s++) {
                if (cnt_lead[h][s] == 0 && cnt_free[h][s] == 0) continue;
                uint64_t term = val_lead[h][s] * cnt_free[h][s] % MOD * pow10[h] % MOD;
                term = (term + cnt_lead[h][s] * val_free[h][s]) % MOD;
                total = (total + term) % MOD;
            }
        } else {
            /* Odd k: middle digit m (0-9, first digit must be nonzero → m=0 allowed since k>=3 middle isn't first)
             * Actually for k=1: h=1, number = d1, left=d1, right=d1, always balanced.
             * For k>=3 odd: number has digits d1..d_{h}..d_k where middle is d_h.
             * Left half = d1..d_h (h digits, d1 nonzero)
             * Right half = d_{k-h+1}..d_k = d_h..d_k (h digits, d_h can be 0 if h>1)
             * They overlap at d_h.
             * Condition: sum(d1..d_h) = sum(d_h..d_k)
             * Let left_sum = sum(d1..d_{h-1}) + m, right_sum = m + sum(d_{h+1}..d_k)
             * Condition: sum(d1..d_{h-1}) = sum(d_{h+1}..d_k)
             * Number value = d1..d_{h-1} * 10^(k - h + 1) + m * 10^(h-1) + d_{h+1}..d_k
             *              = left_prefix_val * 10^(h) + m * 10^(h-1) + right_suffix_val
             *
             * For k=1: h=1, prefix has 0 digits, middle is the digit, suffix has 0 digits.
             *   All single digits 1-9 are balanced. Sum = 45.
             */
            if (k == 1) {
                /* single digits 1-9, sum = 45 */
                total = (total + 45) % MOD;
                continue;
            }
            /* Prefix: h-1 digits, first digit nonzero → cnt_lead[h-1][s], val_lead[h-1][s]
             * Suffix: h-1 digits, all free → cnt_free[h-1][s], val_free[h-1][s]
             * Middle digit m: 0-9
             * Number = prefix_val * 10^(h) + m * 10^(h-1) + suffix_val
             * (note: k = 2h-1, so suffix starts at position h+1, value = suffix_val as is)
             */
            for (int s = 0; s < MAX_SUM; s++) {
                if (cnt_lead[h-1][s] == 0 && cnt_free[h-1][s] == 0) continue;
                /* For each middle digit m 0-9, pair prefix sum s with suffix sum s */
                for (int m = 0; m <= 9; m++) {
                    uint64_t lv = val_lead[h-1][s];
                    uint64_t lc = cnt_lead[h-1][s];
                    uint64_t rv = val_free[h-1][s];
                    uint64_t rc = cnt_free[h-1][s];
                    /* contribution: lv * rc * 10^h + m * lc * rc * 10^(h-1) + rv * lc */
                    uint64_t term = lv * rc % MOD * pow10[h] % MOD;
                    term = (term + (uint64_t)m % MOD * lc % MOD * rc % MOD * pow10[h-1]) % MOD;
                    term = (term + rv * lc % MOD) % MOD;
                    total = (total + term) % MOD;
                }
            }
        }
    }

    printf("%" PRIu64 "\n", total);
    return 0;
}
