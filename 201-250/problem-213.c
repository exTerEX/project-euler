#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    const int n = 30;
    const int steps = 50;
    const int cells = n * n;

    long double empty_prob[900];
    for (int i = 0; i < cells; i++) {
        empty_prob[i] = 1.0L;
    }

    long double cur[900];
    long double nxt[900];

    for (int start = 0; start < cells; start++) {
        for (int i = 0; i < cells; i++) {
            cur[i] = 0.0L;
        }
        cur[start] = 1.0L;

        for (int s = 0; s < steps; s++) {
            for (int i = 0; i < cells; i++) {
                nxt[i] = 0.0L;
            }

            for (int idx = 0; idx < cells; idx++) {
                long double p = cur[idx];
                if (p == 0.0L) {
                    continue;
                }

                int r = idx / n;
                int c = idx % n;
                int deg = 4;
                if (r == 0 || r == n - 1) {
                    deg--;
                }
                if (c == 0 || c == n - 1) {
                    deg--;
                }

                long double q = p / (long double)deg;
                if (r > 0) {
                    nxt[idx - n] += q;
                }
                if (r + 1 < n) {
                    nxt[idx + n] += q;
                }
                if (c > 0) {
                    nxt[idx - 1] += q;
                }
                if (c + 1 < n) {
                    nxt[idx + 1] += q;
                }
            }

            for (int i = 0; i < cells; i++) {
                cur[i] = nxt[i];
            }
        }

        for (int i = 0; i < cells; i++) {
            empty_prob[i] *= (1.0L - cur[i]);
        }
    }

    long double answer = 0.0L;
    for (int i = 0; i < cells; i++) {
        answer += empty_prob[i];
    }

    printf("%.6Lf\n", answer);
    return 0;
}
