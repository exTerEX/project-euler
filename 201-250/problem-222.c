#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef float Number;

static unsigned int min_radius = 30;
static unsigned int max_radius = 50;
static unsigned int num_balls = 21;
static unsigned int pipe_radius = 50;

static Number distance_y(unsigned int radius_a, unsigned int radius_b) {
    unsigned int sum = radius_a + radius_b;
    unsigned int gap = 2 * pipe_radius - sum;
    return sqrtf((float)(sum * sum - gap * gap));
}

static Number search(unsigned int mask, unsigned int last_radius) {
    const unsigned int shift = 19;
    const Number invalid = -1.0f;
    static Number *cache = NULL;
    static size_t cache_size = 0;

    if (mask == 0) {
        return distance_y(last_radius, max_radius) + max_radius;
    }

    if (cache == NULL) {
        cache_size = ((size_t)1 << shift) * (max_radius - min_radius + 1);
        cache = malloc(cache_size * sizeof(Number));
        if (cache == NULL) {
            exit(1);
        }
        for (size_t i = 0; i < cache_size; ++i) {
            cache[i] = invalid;
        }
    }

    size_t id = mask + ((size_t)(last_radius - min_radius) << shift);
    if (cache[id] != invalid) {
        return cache[id];
    }

    Number best = 1e30f;
    for (unsigned int radius = min_radius; radius <= max_radius; ++radius) {
        unsigned int bit = 1U << (radius - min_radius);
        if ((mask & bit) == 0U) {
            continue;
        }

        Number height = distance_y(radius, last_radius) + search(mask & ~bit, radius);
        if (height < best) {
            best = height;
        }
    }

    cache[id] = best;
    return best;
}

int main(void) {
    unsigned int mask;
    if (!isatty(fileno(stdin))) {
        if (scanf("%u %u %u", &pipe_radius, &min_radius, &max_radius) != 3) {
            pipe_radius = 50;
            min_radius = 30;
            max_radius = 50;
        }
    }

    if (min_radius >= max_radius || pipe_radius < max_radius) {
        return 1;
    }

    num_balls = max_radius - min_radius + 1;
    mask = (1U << num_balls) - 1U;

    for (unsigned int radius = max_radius - 1; radius <= max_radius; ++radius) {
        mask &= ~(1U << (radius - min_radius));
    }

    unsigned int first = max_radius - 1;
    Number best = first + search(mask, first);
    printf("%u\n", (unsigned int)lroundf(1000.0f * best));
    return 0;
}