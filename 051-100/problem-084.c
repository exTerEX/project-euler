#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SQUARES 40
#define ITER 20000000

static uint32_t lcg_state = 0xdeadbeef;
static uint32_t lcg_next(void) {
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return lcg_state;
}

static int next_rr(int sq) {
    if (sq < 5 || sq >= 35) return 5;
    if (sq < 15) return 15;
    if (sq < 25) return 25;
    return 35;
}

static int next_util(int sq) {
    if (sq < 12 || sq >= 28) return 12;
    return 28;
}

static int apply_special(int sq) {
    if (sq == 30) return 10;
    if (sq == 2 || sq == 17 || sq == 33) {
        int card = (int)((lcg_next() >> 14) % 16);
        if (card == 0) return 0;
        if (card == 1) return 10;
        return sq;
    }
    if (sq == 7 || sq == 22 || sq == 36) {
        int card = (int)((lcg_next() >> 14) % 16);
        int dest = sq;
        if (card == 0) dest = 0;
        else if (card == 1) dest = 10;
        else if (card == 2) dest = 11;
        else if (card == 3) dest = 24;
        else if (card == 4) dest = 39;
        else if (card == 5) dest = 5;
        else if (card == 6 || card == 7) dest = next_rr(sq);
        else if (card == 8) dest = next_util(sq);
        else if (card == 9) dest = (sq - 3 + SQUARES) % SQUARES;
        if (dest != sq) {
            if (dest == 2 || dest == 17 || dest == 33) return apply_special(dest);
        }
        return dest;
    }
    return sq;
}

int main() {
    uint64_t counts[SQUARES];
    memset(counts, 0, sizeof(counts));

    int pos = 0, doubles = 0;
    for (int iter = 0; iter < ITER; ++iter) {
        int d1 = (int)((lcg_next() >> 14) % 4) + 1;
        int d2 = (int)((lcg_next() >> 14) % 4) + 1;

        if (d1 == d2) {
            if (++doubles == 3) {
                pos = 10;
                doubles = 0;
                counts[pos]++;
                continue;
            }
        } else {
            doubles = 0;
        }

        pos = apply_special((pos + d1 + d2) % SQUARES);
        counts[pos]++;
    }

    int top[3] = {-1, -1, -1};
    for (int i = 0; i < SQUARES; ++i) {
        if (top[0] < 0 || counts[i] > counts[top[0]]) {
            top[2] = top[1]; top[1] = top[0]; top[0] = i;
        } else if (top[1] < 0 || counts[i] > counts[top[1]]) {
            top[2] = top[1]; top[1] = i;
        } else if (top[2] < 0 || counts[i] > counts[top[2]]) {
            top[2] = i;
        }
    }
    printf("%02d%02d%02d\n", top[0], top[1], top[2]);
    return 0;
}
