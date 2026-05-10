#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t cap;
} IntVec;

static void vec_push(IntVec *v, int x) {
    if (v->size == v->cap) {
        size_t new_cap = (v->cap == 0) ? 1024 : v->cap * 2;
        int *p = (int *)realloc(v->data, new_cap * sizeof(int));
        if (p == NULL) {
            exit(1);
        }
        v->data = p;
        v->cap = new_cap;
    }
    v->data[v->size++] = x;
}

static IntVec small_primes = {NULL, 0, 0};
static uint64_t small_limit = 1;

static void ensure_small_primes(uint64_t limit) {
    if (limit <= small_limit) {
        return;
    }

    uint8_t *mark = (uint8_t *)calloc((size_t)limit + 1, 1);
    if (mark == NULL) {
        exit(1);
    }

    for (uint64_t i = 2; i * i <= limit; i++) {
        if (mark[i]) {
            continue;
        }
        for (uint64_t j = i * i; j <= limit; j += i) {
            mark[j] = 1;
        }
    }

    free(small_primes.data);
    small_primes.data = NULL;
    small_primes.size = 0;
    small_primes.cap = 0;

    for (uint64_t i = 2; i <= limit; i++) {
        if (!mark[i]) {
            vec_push(&small_primes, (int)i);
        }
    }

    free(mark);
    small_limit = limit;
}

static inline uint64_t get_number(uint64_t x, uint64_t y) {
    return x + y * (y - 1ULL) / 2ULL;
}

static uint64_t process_line(uint32_t line) {
    uint64_t from = (line <= 2) ? 1ULL : get_number(1, line - 2);
    uint64_t to = get_number(1, line + 3) - 1ULL;

    uint64_t root = (uint64_t)sqrt((long double)to);
    while ((root + 1) * (root + 1) <= to) {
        root++;
    }
    ensure_small_primes(root);

    size_t seg_size = (size_t)(to - from + 1);
    uint8_t *segment = (uint8_t *)malloc(seg_size);
    uint8_t *three_plus = (uint8_t *)calloc(seg_size, 1);
    if (segment == NULL || three_plus == NULL) {
        free(segment);
        free(three_plus);
        exit(1);
    }
    memset(segment, 1, seg_size);

    for (size_t i = 0; i < small_primes.size; i++) {
        uint64_t p = (uint64_t)small_primes.data[i];
        uint64_t pp = p * p;
        if (pp > to) {
            break;
        }

        uint64_t start = (from + p - 1) / p * p;
        if (start < pp) {
            start = pp;
        }
        for (uint64_t v = start; v <= to; v += p) {
            segment[(size_t)(v - from)] = 0;
        }
    }
    if (from == 1) {
        segment[0] = 0;
    }

    #define IS_PRIME_NUM(num) ((num) >= from && (num) <= to && segment[(size_t)((num) - from)] != 0)

    for (int y = (int)line - 1; y <= (int)line + 1; y++) {
        for (int x = 1; x <= y; x++) {
            uint64_t center = get_number((uint64_t)x, (uint64_t)y);
            if (!IS_PRIME_NUM(center)) {
                continue;
            }

            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (ny < 1 || nx < 1 || nx > ny) {
                        continue;
                    }
                    uint64_t nnum = get_number((uint64_t)nx, (uint64_t)ny);
                    if (IS_PRIME_NUM(nnum)) {
                        count++;
                        if (count >= 3) {
                            break;
                        }
                    }
                }
                if (count >= 3) {
                    break;
                }
            }

            if (count >= 3) {
                three_plus[(size_t)(center - from)] = 1;
            }
        }
    }

    uint64_t sum = 0;
    for (uint64_t x = 1; x <= line; x++) {
        uint64_t current = get_number(x, line);
        if (!IS_PRIME_NUM(current)) {
            continue;
        }

        int ok = 0;
        for (int dx = -1; dx <= 1 && !ok; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = (int)x + dx;
                int ny = (int)line + dy;
                if (ny < 1 || nx < 1 || nx > ny) {
                    continue;
                }
                uint64_t v = get_number((uint64_t)nx, (uint64_t)ny);
                if (v >= from && v <= to && three_plus[(size_t)(v - from)]) {
                    ok = 1;
                    break;
                }
            }
        }

        if (ok) {
            sum += current;
        }
    }

    free(segment);
    free(three_plus);
    return sum;
}

int main(void) {
    uint64_t answer = process_line(5678027) + process_line(7208785);
    printf("%llu\n", (unsigned long long)answer);
    free(small_primes.data);
    return 0;
}
