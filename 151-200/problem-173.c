#include <stdint.h>
#include <stdio.h>

int main(void) {
    const int limit = 1000000;
    int64_t count = 0;

    for (int outer = 3;; outer++) {
        int min_tiles = outer * outer - (outer - 2) * (outer - 2);
        if (min_tiles > limit) {
            break;
        }

        for (int inner = outer - 2; inner > 0; inner -= 2) {
            int tiles = outer * outer - inner * inner;
            if (tiles > limit) {
                break;
            }
            count++;
        }
    }

    printf("%lld\n", (long long)count);
    return 0;
}
