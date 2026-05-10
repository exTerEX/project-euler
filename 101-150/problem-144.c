#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main() {
    double x1 = 0.0, y1 = 10.1;
    double x2 = -0.01400, y2 = 1.48150;

    int count = 0;
    while (!(fabs(x2) < 0.01 && y2 > 0)) {
        count++;

        double nx = 8.0 * x2, ny = 2.0 * y2;
        double len = sqrt(nx * nx + ny * ny);
        nx /= len; ny /= len;

        double dx = x2 - x1, dy = y2 - y1;
        double dlen = sqrt(dx * dx + dy * dy);
        dx /= dlen; dy /= dlen;

        double dot = dx * nx + dy * ny;
        double rx = dx - 2.0 * dot * nx;
        double ry = dy - 2.0 * dot * ny;

        double A = 4.0 * rx * rx + ry * ry;
        double B = 8.0 * x2 * rx + 2.0 * y2 * ry;
        double C = 4.0 * x2 * x2 + y2 * y2 - 100.0;
        double disc = B * B - 4.0 * A * C;
        double t1 = (-B - sqrt(disc)) / (2.0 * A);
        double t2 = (-B + sqrt(disc)) / (2.0 * A);
        double t = (t1 > 1e-9) ? t1 : t2;

        x1 = x2; y1 = y2;
        x2 = x2 + t * rx; y2 = y2 + t * ry;
    }

    printf("%d\n", count);
    return 0;
}
