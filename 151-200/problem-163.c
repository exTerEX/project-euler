#include <stdint.h>
#include <stdio.h>

int main(void) {
    const int64_t n = 36;

    int64_t value = 1678LL * n * n * n
                  + 3117LL * n * n
                  + 88LL * n
                  - 345LL * (n % 2)
                  - 320LL * (n % 3)
                  - 90LL * (n % 4)
                  - 288LL * ((n * n * n - n * n + n) % 5);

    printf("%lld\n", (long long)(value / 240));
    return 0;
}
