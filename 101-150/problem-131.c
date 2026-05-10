#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_prime(int64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

int main() {
    int count = 0;
    for (int64_t k = 1; ; k++) {
        int64_t p = 3 * k * k + 3 * k + 1;
        if (p >= 1000000) break;
        if (is_prime(p)) count++;
    }
    printf("%d\n", count);
    return 0;
}
