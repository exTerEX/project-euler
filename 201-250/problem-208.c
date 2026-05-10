#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t visited[5] = {0, 0, 0, 0, 0};
static uint8_t max_per_arc = 0;
static uint64_t *cache = NULL;
static uint64_t unknown = ~0ULL;

static uint64_t search(uint8_t arcs_left, uint8_t current_arc) {
    if (arcs_left == 0) {
        if (current_arc != 0) {
            return 0;
        }
        if (visited[0] != visited[1] || visited[2] != visited[3] || visited[0] != visited[2]) {
            return 0;
        }
        return 1;
    }

    uint64_t base = (uint64_t)max_per_arc + 1ULL;
    uint64_t id = current_arc;
    id = id * base + visited[0];
    id = id * base + visited[1];
    id = id * base + visited[2];
    id = id * base + visited[3];
    id = id * base + visited[4];

    if (cache[id] != unknown) {
        return cache[id];
    }

    uint64_t result = 0;

    uint8_t left = (uint8_t)((current_arc + 1U) % 5U);
    if (visited[left] < max_per_arc) {
        visited[left]++;
        result += search((uint8_t)(arcs_left - 1U), left);
        visited[left]--;
    }

    uint8_t right = (uint8_t)((current_arc + 4U) % 5U);
    if (visited[right] < max_per_arc) {
        visited[right]++;
        result += search((uint8_t)(arcs_left - 1U), right);
        visited[right]--;
    }

    cache[id] = result;
    return result;
}

int main(void) {
    const uint8_t arcs = 70;
    max_per_arc = (uint8_t)(arcs / 5U);

    uint64_t base = (uint64_t)max_per_arc + 1ULL;
    uint64_t cache_size = 5ULL;
    for (int i = 0; i < 5; i++) {
        cache_size *= base;
    }

    cache = (uint64_t *)malloc(cache_size * sizeof(uint64_t));
    if (cache == NULL) {
        return 1;
    }
    for (uint64_t i = 0; i < cache_size; i++) {
        cache[i] = unknown;
    }

    uint64_t answer = search(arcs, 0);
    printf("%llu\n", (unsigned long long)answer);

    free(cache);
    return 0;
}
