#include <math.h>
#include <stdio.h>
#include <unistd.h>

static const double EPSILON = 0.00000001;

static double blancmange(double x) {
    double result = 0.0;
    for (unsigned int n = 0;; ++n) {
        double power = pow(2.0, (double)n);
        double s = power * x - floor(power * x);
        if (s > 0.5) {
            s = 1.0 - s;
        }

        double add = s / power;
        result += add;
        if (add < EPSILON) {
            return result;
        }
    }
}

static double find_intersection(double circle_x, double circle_y, double radius, double x, double step) {
    while (1) {
        double y = blancmange(x);
        double dx = x - circle_x;
        double dy = y - circle_y;
        double distance = sqrt(dx * dx + dy * dy);
        double error = fabs(distance - radius);
        int turn_around = 0;

        if (error < EPSILON) {
            return x;
        }

        if (distance < radius) {
            if ((dx > 0.0 && step < 0.0) || (dx < 0.0 && step > 0.0)) {
                turn_around = 1;
            }
        } else {
            if ((dx > 0.0 && step > 0.0) || (dx < 0.0 && step < 0.0)) {
                turn_around = 1;
            }
        }

        if (turn_around) {
            step = -step / 2.0;
        }
        x += step;
    }
}

static double integrate(double circle_x, double circle_y, double radius, double from, double to, double step) {
    double area = 0.0;
    for (double x = from; x <= to; x += step) {
        double upper = blancmange(x);
        double lower = circle_y - sqrt(radius * radius - (x - circle_x) * (x - circle_x));
        area += (upper - lower) * step;
    }
    return area;
}

int main(void) {
    double circle_x = 0.25;
    double circle_y = 0.5;
    double radius = 0.25;
    if (!isatty(fileno(stdin))) {
        if (scanf("%lf %lf %lf", &circle_x, &circle_y, &radius) != 3) {
            circle_x = 0.25;
            circle_y = 0.5;
            radius = 0.25;
        }
    }

    double from = find_intersection(circle_x, circle_y, radius, circle_x, -0.1);
    double to = find_intersection(circle_x, circle_y, radius, circle_x, +0.1);
    double area = integrate(circle_x, circle_y, radius, from, to, 0.00001);
    printf("%.8f\n", area);
    return 0;
}