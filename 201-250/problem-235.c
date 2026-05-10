#include <stdio.h>
#include <math.h>

// Compute s(r) for the arithmetic-geometric sequence
// u(k) = (900 - 3k) * r^(k-1)
// s(n) = sum of u(k) for k=1..n
double s(double r) {
    double result = 0.0;
    double x = 1.0;  // r^0
    
    for (int k = 1; k <= 5000; k++) {
        result += (900.0 - 3.0 * k) * x;
        x *= r;
    }
    
    return result;
}

int main(void) {
    // Find r such that s(5000) = -600,000,000,000
    // Using bisection method
    
    double lower = 0.0;
    double upper = 2.0;
    double target = -600000000000.0;
    
    // Bisect until precision is reached
    while (upper - lower > 1e-13) {
        double mid = (upper + lower) / 2.0;
        double current = s(mid);
        
        if (current < target) {
            upper = mid;
        } else {
            lower = mid;
        }
    }
    
    double result = (upper + lower) / 2.0;
    
    printf("%.12f\n", result);
    return 0;
}
