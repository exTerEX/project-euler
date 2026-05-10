#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum {
    BORDER_1234,
    BORDER_1432,
    BORDER_3214,
    BORDER_1XX2,
    BORDER_12XX,
    BORDER_XX12,
    BORDER_X12X,
    BORDER_RIGHT,
    BORDER_COUNT
};

typedef struct {
    uint8_t left;
    uint8_t right;
    uint64_t length;
    uint32_t value;
} CacheEntry;

static uint8_t neighbors[BORDER_COUNT][BORDER_COUNT];
static const uint8_t internal_borders[] = {
    BORDER_1234, BORDER_1432, BORDER_3214, BORDER_1XX2,
    BORDER_12XX, BORDER_XX12, BORDER_X12X
};

static CacheEntry cache[5000];
static size_t cache_size = 0;

static void fill(void) {
    memset(neighbors, 0, sizeof(neighbors));
    neighbors[BORDER_1234][BORDER_1234] = 1;
    neighbors[BORDER_1432][BORDER_1432] = 1;
    neighbors[BORDER_3214][BORDER_3214] = 1;
    neighbors[BORDER_1432][BORDER_1XX2] = 1;
    neighbors[BORDER_3214][BORDER_1XX2] = 1;
    neighbors[BORDER_1XX2][BORDER_1234] = 1;
    neighbors[BORDER_1234][BORDER_12XX] = 1;
    neighbors[BORDER_1234][BORDER_XX12] = 1;
    neighbors[BORDER_12XX][BORDER_1432] = 1;
    neighbors[BORDER_XX12][BORDER_3214] = 1;
    neighbors[BORDER_1XX2][BORDER_X12X] = 1;
    neighbors[BORDER_X12X][BORDER_1XX2] = 1;
    neighbors[BORDER_12XX][BORDER_1XX2] = 1;
    neighbors[BORDER_1XX2][BORDER_XX12] = 1;
    neighbors[BORDER_1XX2][BORDER_12XX] = 1;
    neighbors[BORDER_XX12][BORDER_1XX2] = 1;
    neighbors[BORDER_1234][BORDER_RIGHT] = 1;
    neighbors[BORDER_1XX2][BORDER_RIGHT] = 1;
}

static uint32_t search(uint8_t left, uint8_t right, uint64_t length, uint32_t modulo) {
    if (length == 1) {
        return neighbors[left][right];
    }

    for (size_t i = 0; i < cache_size; ++i) {
        if (cache[i].left == left && cache[i].right == right && cache[i].length == length) {
            return cache[i].value;
        }
    }

    uint64_t pow2 = 1;
    while (pow2 < length / 2) {
        pow2 *= 2;
    }

    uint64_t result = 0;
    for (size_t i = 0; i < sizeof(internal_borders) / sizeof(internal_borders[0]); ++i) {
        uint8_t next = internal_borders[i];
        uint64_t left_half = search(left, next, pow2, modulo);
        uint64_t right_half = search(next, right, length - pow2, modulo);
        result += (left_half * right_half) % modulo;
    }

    result %= modulo;
    cache[cache_size++] = (CacheEntry){left, right, length, (uint32_t)result};
    return (uint32_t)result;
}

int main(void) {
    const uint32_t modulo = 100000000U;
    uint64_t limit = 1000000000000ULL;
    fill();

    if (!isatty(fileno(stdin))) {
        if (scanf("%" SCNu64, &limit) != 1) {
            limit = 1000000000000ULL;
        }
    }

    printf("%u\n", search(BORDER_1XX2, BORDER_RIGHT, limit, modulo));
    return 0;
}