#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LIMIT 50000000

static uint8_t composite[LIMIT];

int main() {
    for (uint32_t i = 2; (uint64_t)i * i < LIMIT; ++i) {
        if (!composite[i]) {
            for (uint32_t j = i * i; j < LIMIT; j += i)
                composite[j] = 1;
        }
    }

static uint8_t found[LIMIT];
    memset(found, 0, sizeof(found));

    for (uint32_t p2 = 2; p2 < LIMIT; ++p2) {
        if (composite[p2]) continue;
        uint64_t p2sq = (uint64_t)p2 * p2;
        if (p2sq >= LIMIT) break;
        for (uint32_t p3 = 2; p3 < LIMIT; ++p3) {
            if (composite[p3]) continue;
            uint64_t p3cu = (uint64_t)p3 * p3 * p3;
            if (p2sq + p3cu >= LIMIT) break;
            for (uint32_t p4 = 2; p4 < LIMIT; ++p4) {
                if (composite[p4]) continue;
                uint64_t v = p2sq + p3cu + (uint64_t)p4 * p4 * p4 * p4;
                if (v >= LIMIT) break;
                found[v] = 1;
            }
        }
    }

    uint32_t count = 0;
    for (uint32_t i = 2; i < LIMIT; ++i)
        if (found[i]) ++count;

    printf("%u\n", count);
    return 0;
}
