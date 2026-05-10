#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_CLUES 22
#define NUM_DIGITS 16

static uint8_t clues[NUM_CLUES][NUM_DIGITS];
static uint8_t hits[NUM_CLUES];

static uint32_t rng_seed = 0;

static uint32_t myrand(uint32_t mod) {
    rng_seed = 1103515245U * rng_seed + 12345U;
    return (mod == 0) ? 0 : (rng_seed % mod);
}

static void shuffle(uint8_t *digit) {
    uint8_t old = *digit;
    do {
        *digit = (uint8_t)myrand(10);
    } while (*digit == old);
}

static void add_clue(int idx, const char *s, uint8_t correct) {
    for (int i = 0; i < NUM_DIGITS; i++) {
        clues[idx][i] = (uint8_t)(s[i] - '0');
    }
    hits[idx] = correct;
}

static int distance_score(const uint8_t current[NUM_DIGITS]) {
    int errors = 0;
    for (int i = 0; i < NUM_CLUES; i++) {
        int same = 0;
        for (int j = 0; j < NUM_DIGITS; j++) {
            if (current[j] == clues[i][j]) {
                same++;
            }
        }
        int diff = same - hits[i];
        errors += (diff < 0) ? -diff : diff;
    }
    return errors;
}

int main(void) {
    add_clue(0,  "5616185650518293", 2);
    add_clue(1,  "3847439647293047", 1);
    add_clue(2,  "5855462940810587", 3);
    add_clue(3,  "9742855507068353", 3);
    add_clue(4,  "4296849643607543", 3);
    add_clue(5,  "3174248439465858", 1);
    add_clue(6,  "4513559094146117", 2);
    add_clue(7,  "7890971548908067", 3);
    add_clue(8,  "8157356344118483", 1);
    add_clue(9,  "2615250744386899", 2);
    add_clue(10, "8690095851526254", 3);
    add_clue(11, "6375711915077050", 1);
    add_clue(12, "6913859173121360", 1);
    add_clue(13, "6442889055042768", 2);
    add_clue(14, "2321386104303845", 0);
    add_clue(15, "2326509471271448", 2);
    add_clue(16, "5251583379644322", 2);
    add_clue(17, "1748270476758276", 3);
    add_clue(18, "4895722652190306", 1);
    add_clue(19, "3041631117224635", 3);
    add_clue(20, "1841236454324589", 3);
    add_clue(21, "2659862637316867", 2);

    uint8_t current[NUM_DIGITS] = {0};
    for (int i = 0; i < NUM_DIGITS; i++) {
        shuffle(&current[i]);
    }

    const int max_quiet_rounds = 20;
    int quiet_rounds = 0;

    int errors = distance_score(current);
    int previous = errors;

    while (errors != 0) {
        for (int i = 0; i < NUM_DIGITS; i++) {
            uint8_t old = current[i];
            do {
                shuffle(&current[i]);
            } while (current[i] == old);

            int modified = distance_score(current);
            if (modified <= errors) {
                errors = modified;
            } else {
                current[i] = old;
            }
        }

        if (errors == previous) {
            quiet_rounds++;
            if (quiet_rounds == max_quiet_rounds) {
                shuffle(&current[myrand(NUM_DIGITS)]);
                errors = distance_score(current);
                quiet_rounds = 0;
            }
        } else {
            quiet_rounds = 0;
            previous = errors;
        }
    }

    for (int i = 0; i < NUM_DIGITS; i++) {
        printf("%d", current[i]);
    }
    printf("\n");
    return 0;
}
