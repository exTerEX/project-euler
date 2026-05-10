#include <stdint.h>
#include <stdio.h>

static unsigned __int128 pow_u128(unsigned __int128 base, int exp) {
    unsigned __int128 result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main(void) {
    unsigned __int128 total = 0;

    for (int n = 1; n <= 16; n++) {
        unsigned __int128 all = 15 * pow_u128(16, n - 1);

        unsigned __int128 miss0 = pow_u128(15, n);
        unsigned __int128 miss1 = 14 * pow_u128(15, n - 1);
        unsigned __int128 missA = 14 * pow_u128(15, n - 1);

        unsigned __int128 miss01 = pow_u128(14, n);
        unsigned __int128 miss0A = pow_u128(14, n);
        unsigned __int128 miss1A = 13 * pow_u128(14, n - 1);

        unsigned __int128 miss01A = pow_u128(13, n);

        unsigned __int128 count = all - (miss0 + miss1 + missA)
                               + (miss01 + miss0A + miss1A)
                               - miss01A;
        total += count;
    }

    printf("%llX\n", (unsigned long long)total);
    return 0;
}
