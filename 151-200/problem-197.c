#include <math.h>
#include <stdio.h>

static double f(double x) {
    double y = pow(2.0, 30.403243784 - x * x);
    return floor(y) * 1e-9;
}

int main(void) {
    double u = -1.0;

    for (int i = 0; i < 1000000; i++) {
        u = f(u);
    }

    double answer = u + f(u);
    printf("%.9f\n", answer);
    return 0;
}
