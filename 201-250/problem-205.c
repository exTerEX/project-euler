#include <stdint.h>
#include <stdio.h>

static void build_dist(int dice, int sides, uint64_t *dist, int max_sum) {
    static uint64_t prev[64];
    static uint64_t next[64];

    for (int i = 0; i <= max_sum; i++) {
        prev[i] = 0;
        next[i] = 0;
    }
    prev[0] = 1;

    for (int d = 0; d < dice; d++) {
        for (int s = 0; s <= max_sum; s++) {
            next[s] = 0;
        }
        for (int sum = 0; sum <= max_sum; sum++) {
            uint64_t ways = prev[sum];
            if (ways == 0) {
                continue;
            }
            for (int face = 1; face <= sides; face++) {
                if (sum + face <= max_sum) {
                    next[sum + face] += ways;
                }
            }
        }
        for (int s = 0; s <= max_sum; s++) {
            prev[s] = next[s];
        }
    }

    for (int s = 0; s <= max_sum; s++) {
        dist[s] = prev[s];
    }
}

int main(void) {
    const int peter_dice = 9;
    const int peter_sides = 4;
    const int colin_dice = 6;
    const int colin_sides = 6;
    const int max_sum = 36;

    uint64_t peter[64] = {0};
    uint64_t colin[64] = {0};

    build_dist(peter_dice, peter_sides, peter, max_sum);
    build_dist(colin_dice, colin_sides, colin, max_sum);

    uint64_t total_peter = 0;
    uint64_t total_colin = 0;
    for (int s = 0; s <= max_sum; s++) {
        total_peter += peter[s];
        total_colin += colin[s];
    }

    uint64_t colin_prefix = 0;
    long double win = 0.0L;
    for (int s = 0; s <= max_sum; s++) {
        uint64_t wins_against_colin = colin_prefix;
        if (peter[s] > 0) {
            win += (long double)peter[s] * (long double)wins_against_colin;
        }
        colin_prefix += colin[s];
    }

    long double prob = win / ((long double)total_peter * (long double)total_colin);
    printf("%.7Lf\n", prob);
    return 0;
}
