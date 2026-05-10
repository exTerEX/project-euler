#include <stdint.h>
#include <stdio.h>

static int gcd_int(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static int divisor_count(uint64_t n) {
    int count = 1;
    for (uint64_t p = 2; p * p <= n; p++) {
        if (n % p != 0) {
            continue;
        }
        int exp = 0;
        while (n % p == 0) {
            n /= p;
            exp++;
        }
        count *= (exp + 1);
    }
    if (n > 1) {
        count *= 2;
    }
    return count;
}

int main(void) {
    int factors[128];
    int factor_count = 0;

    for (int a = 0; a <= 9; a++) {
        int64_t p5 = 1;
        for (int i = 0; i < a; i++) {
            p5 *= 5;
        }
        for (int b = 0; b <= 9; b++) {
            int64_t p2 = 1;
            for (int i = 0; i < b; i++) {
                p2 *= 2;
            }
            int64_t v = p2 * p5;
            if (v <= 1000000000LL) {
                factors[factor_count++] = (int)v;
            }
        }
    }

    uint64_t answer = 0;
    for (int n = 1; n <= 9; n++) {
        int base = 1;
        for (int i = 0; i < n; i++) {
            base *= 10;
        }

        for (int i = 0; i < factor_count; i++) {
            int d = factors[i];
            if (d > base || (base % d) != 0) {
                continue;
            }

            int pairs[2][2];
            int pair_count = 0;
            pairs[pair_count][0] = 1;
            pairs[pair_count][1] = d;
            pair_count++;

            int t = d;
            int twos = 0;
            int fives = 0;
            while (t % 2 == 0) {
                twos++;
                t /= 2;
            }
            while (t % 5 == 0) {
                fives++;
                t /= 5;
            }
            if (t == 1 && twos > 0 && fives > 0) {
                int p2 = 1;
                int p5 = 1;
                for (int k = 0; k < twos; k++) {
                    p2 *= 2;
                }
                for (int k = 0; k < fives; k++) {
                    p5 *= 5;
                }
                pairs[pair_count][0] = p2;
                pairs[pair_count][1] = p5;
                pair_count++;
            }

            for (int j = 0; j < pair_count; j++) {
                uint64_t p = (uint64_t)(base / d) * (uint64_t)(pairs[j][0] + pairs[j][1]);
                answer += (uint64_t)divisor_count(p);
            }
        }
    }

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
