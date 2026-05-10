#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

bool is_prime(uint64_t n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (uint64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

uint64_t sum_primes_with_run(int d, int run) {
    char num[11];
    num[10] = '\0';
    uint64_t total = 0;
    for (int mask = 0; mask < (1 << 10); mask++) {
        if (__builtin_popcount(mask) != run) continue;
        for (int i = 0; i < 10; i++)
            num[i] = (mask & (1 << i)) ? ('0' + d) : '?';
        int blanks[10], nb = 0;
        for (int i = 0; i < 10; i++) if (num[i] == '?') blanks[nb++] = i;
        int other_digits[9], no = 0;
        for (int x = 0; x <= 9; x++) if (x != d) other_digits[no++] = x;
        int counters[10] = {0};
        int total_combos = 1;
        for (int i = 0; i < nb; i++) total_combos *= 9;
        for (int c = 0; c < total_combos; c++) {
            for (int i = 0; i < nb; i++)
                num[blanks[i]] = '0' + other_digits[counters[i]];
            if (num[0] == '0') goto next;
            {
                uint64_t n = 0;
                for (int i = 0; i < 10; i++) n = n * 10 + (num[i] - '0');
                if (is_prime(n)) total += n;
            }
            next:;
            for (int i = nb - 1; i >= 0; i--) {
                counters[i]++;
                if (counters[i] < 9) break;
                counters[i] = 0;
            }
        }
    }
    return total;
}

int main() {
    uint64_t answer = 0;
    for (int d = 0; d <= 9; d++) {
        for (int run = 10; run >= 0; run--) {
            uint64_t s = sum_primes_with_run(d, run);
            if (s > 0) { answer += s; break; }
        }
    }
    printf("%lu\n", answer);
    return 0;
}
