#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int width = 9;
static unsigned int height = 12;

typedef struct {
    uint64_t key;
    uint64_t value;
    uint8_t used;
} CacheEntry;

#define CACHE_CAP (1u << 21)
static CacheEntry *cache = NULL;

static uint64_t hash64(uint64_t x) {
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return x;
}

static int cache_get(uint64_t key, uint64_t *value) {
    uint64_t idx = hash64(key) & (CACHE_CAP - 1);
    while (cache[idx].used) {
        if (cache[idx].key == key) {
            *value = cache[idx].value;
            return 1;
        }
        idx = (idx + 1) & (CACHE_CAP - 1);
    }
    return 0;
}

static void cache_put(uint64_t key, uint64_t value) {
    uint64_t idx = hash64(key) & (CACHE_CAP - 1);
    while (cache[idx].used && cache[idx].key != key) {
        idx = (idx + 1) & (CACHE_CAP - 1);
    }
    cache[idx].used = 1;
    cache[idx].key = key;
    cache[idx].value = value;
}

static int use_cell(unsigned int pos, unsigned int *row) {
    unsigned int mask = 1u << pos;
    if ((*row & mask) != 0) {
        return 0;
    }
    *row |= mask;
    return 1;
}

static uint64_t search(unsigned int rows_left, unsigned int row_a,
                       unsigned int row_b, unsigned int row_c) {
    if (rows_left == 0) {
        return 1;
    }

    unsigned int full = (1u << width) - 1u;
    if (row_a == full) {
        return search(rows_left - 1, row_b, row_c, 0u);
    }

    unsigned int pos = 0;
    while ((row_a & (1u << pos)) != 0u) {
        pos++;
    }

    uint64_t key = rows_left;
    key = (key << width) | row_a;
    key = (key << width) | row_b;
    key = (key << width) | row_c;

    uint64_t cached;
    if (cache_get(key, &cached)) {
        return cached;
    }

    uint64_t result = 0;
    unsigned int a, b, c;

    a = row_a;
    b = row_b;
    c = row_c;
    if (rows_left >= 2 && pos < width - 1 &&
        use_cell(pos, &a) && use_cell(pos + 1, &a) && use_cell(pos, &b)) {
        result += search(rows_left, a, b, c);
    }

    a = row_a;
    b = row_b;
    c = row_c;
    if (rows_left >= 2 && pos < width - 1 &&
        use_cell(pos, &a) && use_cell(pos + 1, &a) && use_cell(pos + 1, &b)) {
        result += search(rows_left, a, b, c);
    }

    a = row_a;
    b = row_b;
    c = row_c;
    if (rows_left >= 2 && pos < width - 1 &&
        use_cell(pos, &a) && use_cell(pos, &b) && use_cell(pos + 1, &b)) {
        result += search(rows_left, a, b, c);
    }

    a = row_a;
    b = row_b;
    c = row_c;
    if (rows_left >= 2 && pos > 0 && pos < width &&
        use_cell(pos, &a) && use_cell(pos - 1, &b) && use_cell(pos, &b)) {
        result += search(rows_left, a, b, c);
    }

    a = row_a;
    b = row_b;
    c = row_c;
    if (rows_left >= 3 && pos < width &&
        use_cell(pos, &a) && use_cell(pos, &b) && use_cell(pos, &c)) {
        result += search(rows_left, a, b, c);
    }

    a = row_a;
    b = row_b;
    c = row_c;
    if (rows_left >= 1 && pos < width - 2 &&
        use_cell(pos, &a) && use_cell(pos + 1, &a) && use_cell(pos + 2, &a)) {
        result += search(rows_left, a, b, c);
    }

    cache_put(key, result);
    return result;
}

int main(void) {
    if (width > height) {
        unsigned int tmp = width;
        width = height;
        height = tmp;
    }

    cache = (CacheEntry *)calloc(CACHE_CAP, sizeof(CacheEntry));
    if (cache == NULL) {
        return 1;
    }

    uint64_t answer = search(height, 0u, 0u, 0u);
    printf("%llu\n", (unsigned long long)answer);

    free(cache);
    return 0;
}
