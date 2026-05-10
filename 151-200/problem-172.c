#include <stdint.h>
#include <stdio.h>

static uint64_t fact[19];
static int counts[10];
static unsigned __int128 total = 0;

static void search_counts(int digit, int remaining) {
    if (digit == 10) {
        if (remaining != 0) {
            return;
        }

        unsigned __int128 all = fact[18];
        for (int i = 0; i < 10; i++) {
            all /= fact[counts[i]];
        }

        unsigned __int128 leading_zero = 0;
        if (counts[0] > 0) {
            leading_zero = fact[17];
            leading_zero /= fact[counts[0] - 1];
            for (int i = 1; i < 10; i++) {
                leading_zero /= fact[counts[i]];
            }
        }

        total += all - leading_zero;
        return;
    }

    int max_use = remaining < 3 ? remaining : 3;
    for (int c = 0; c <= max_use; c++) {
        counts[digit] = c;
        search_counts(digit + 1, remaining - c);
    }
}

int main(void) {
    fact[0] = 1;
    for (int i = 1; i <= 18; i++) {
        fact[i] = fact[i - 1] * (uint64_t)i;
    }

    search_counts(0, 18);

    printf("%llu\n", (unsigned long long)total);
    return 0;
}
