#include <math.h>
#include <stdio.h>

static double fill_gap(double k1, double k2, double k3, int depth) {
    if (depth == 0) {
        return 0.0;
    }

    double k4 = k1 + k2 + k3 + 2.0 * sqrt(k1 * k2 + k2 * k3 + k1 * k3);
    double area = 1.0 / (k4 * k4);

    area += fill_gap(k1, k2, k4, depth - 1);
    area += fill_gap(k1, k3, k4, depth - 1);
    area += fill_gap(k2, k3, k4, depth - 1);
    return area;
}

int main(void) {
    const int depth = 10;
    double k = 1.0 + 2.0 / sqrt(3.0);

    double covered = 3.0 / (k * k);
    covered += fill_gap(k, k, k, depth);
    covered += 3.0 * fill_gap(-1.0, k, k, depth);

    double uncovered = 1.0 - covered;
    printf("%.8f\n", uncovered);
    return 0;
}
