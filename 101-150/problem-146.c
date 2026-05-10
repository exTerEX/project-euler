#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_prime(int64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

int main() {
    int offsets[] = {1, 3, 7, 9, 13, 27};
    int64_t sum = 0;
    for (int64_t n = 10; n < 150000000; n += 10) {
        int64_t n2 = n * n;
        bool ok = true;
        for (int i = 0; i < 6; i++) {
            if (!is_prime(n2 + offsets[i])) { ok = false; break; }
        }
        if (ok) sum += n;
    }
    printf("%ld\n", sum);
    return 0;
}
