#include <math.h>
#include <stdint.h>
#include <stdio.h>

static double sn[181];
static double cs[181];

static uint32_t quad_hash(int a, int b, int c, int d) {
    return ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)c << 8) | (uint32_t)d;
}

int main(void) {
    const double pi = acos(-1.0);
    for (int x = 0; x <= 180; x++) {
        double rad = x * pi / 180.0;
        sn[x] = sin(rad);
        cs[x] = cos(rad);
    }

    int count = 0;
    for (int a = 1; a <= 45; a++) {
        for (int b = a; b <= 180 - 3 * a; b++) {
            for (int c = a; c <= 180 - 2 * a - b; c++) {
                for (int d = a; d <= 180 - a - b - c; d++) {
                    int e = 180 - (b + c + d);
                    int h = 180 - (a + b + c);

                    double x = sn[c + d] / sn[e];
                    double y = sn[c] / sn[h];
                    double z = sqrt(x * x + y * y - 2.0 * x * y * cs[a]);
                    double f_real = acos((x * x + z * z - y * y) / (2.0 * x * z)) * 180.0 / pi;
                    int f = (int)(f_real + 0.5);
                    if (fabs(f_real - f) > 1e-9) {
                        continue;
                    }
                    if (f < a) {
                        break;
                    }

                    int g = 180 - (a + f + h);
                    if (g < a) {
                        break;
                    }

                    uint32_t h0 = quad_hash(a, b, c, d);
                    if (h0 > quad_hash(c, d, e, f)) {
                        continue;
                    }
                    if (h0 > quad_hash(e, f, g, h)) {
                        continue;
                    }
                    if (h0 > quad_hash(g, h, a, b)) {
                        continue;
                    }
                    if (h0 > quad_hash(b, a, h, g)) {
                        continue;
                    }
                    if (h0 > quad_hash(d, c, b, a)) {
                        continue;
                    }
                    if (h0 > quad_hash(f, e, d, c)) {
                        continue;
                    }
                    if (h0 > quad_hash(h, g, f, e)) {
                        continue;
                    }

                    count++;
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}
