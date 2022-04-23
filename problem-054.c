#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HANDSIZE 5
#define FILENAME "problem-054.txt"

enum hands {
    HIGH_CARD, PAIR, TWO_PAIR, THREE,
    STRAIGHT, FLUSH, FULL_HOUSE, FOUR,
    STRAIGHT_FLUSH, ROYAL_FLUSH
};

enum suit { DIAMONDS, CLUBS, HEARTS, SPADES };

struct card {
    int8_t value;
    enum suit color;
};

struct card parse(char*);
bool is_straight(int32_t*);
bool is_flush(int32_t*);
bool is_three(int32_t*);
int32_t is_pair(int32_t*);
enum hands find_rank(struct card*);
int32_t handle_tie(struct card*, struct card*, enum hands);

int main() {
    FILE* fp;
    char buf[10];

    struct card* p1 = calloc(HANDSIZE, sizeof * p1);
    struct card* p2 = calloc(HANDSIZE, sizeof * p2);

    if ((fp = fopen(FILENAME, "r")) == NULL) {
        printf("ERROR: can't open %s\n", FILENAME);
        return 1;
    }

    int32_t i = 0, vp1 = 0;
    while (fscanf(fp, "%s", buf) != EOF) {
        if (i < HANDSIZE) {
            p1[i] = parse(buf);
        }
        else {
            p2[i - HANDSIZE] = parse(buf);
        }
        ++i;

        if (i == 2 * HANDSIZE) {
            int32_t rp1 = find_rank(p1), rp2 = find_rank(p2);

            if (rp1 > rp2) {
                ++vp1;
            }
            else if (rp1 == rp2) {
                if (handle_tie(p1, p2, rp1) == 1) {
                    ++vp1;
                }
            }

            i = 0;
        }
    }

    printf("%d\n", vp1);
    return 0;
}

struct card parse(char* s) {
    int32_t len = strlen(s);
    struct card c;

    if (len != 2) {
        printf("ERROR: can't parse %s\n", s);
        exit(1);
    }
    else {
        if (isdigit(s[0])) {
            c.value = s[0] - '0';
        }
        else {
            switch (s[0]) {
            case 'T':
                c.value = 10;
                break;
            case 'J':
                c.value = 11;
                break;
            case 'Q':
                c.value = 12;
                break;
            case 'K':
                c.value = 13;
                break;
            case 'A':
                c.value = 14;
                break;
            }
        }
    }

    switch (s[len - 1]) {
    case 'D':
        c.color = DIAMONDS;
        break;
    case 'C':
        c.color = CLUBS;
        break;
    case 'H':
        c.color = HEARTS;
        break;
    case 'S':
        c.color = SPADES;
        break;
    }

    return c;
}

bool is_straight(int32_t* values) {
    int32_t j;
    for (int32_t i = 0; i < 11; ++i) {
        if (values[i] == 0) { continue; }
        for (j = i + 1; j < 15 && values[j] == 1; ++j) { ; }
        if (j - i == 5) { return true; }
    }

    return false;
}

bool is_flush(int32_t* suit) {
    return (suit[0] == HANDSIZE || suit[1] == HANDSIZE
        || suit[2] == HANDSIZE || suit[3] == HANDSIZE);
}

bool is_three(int32_t* values) {
    for (int32_t i = 0; i < 15; ++i) {
        if (values[i] == 3) {
            return true;
        }
    }

    return false;
}

int32_t is_pair(int32_t* values) {
    int32_t n;
    for (int32_t i = 0, n = 0; i < 15; ++i) {
        if (values[i] == 2) {
            ++n;
        }
    }

    return n;
}

enum hands find_rank(struct card* hand) {
    int32_t i, values[15] = { 0 }, suit[4] = { 0 };
    for (i = 0; i < HANDSIZE; ++i) {
        ++values[hand[i].value];
        ++suit[hand[i].color];
    }

    if (values[10] == 1 && values[11] == 1 && values[12] == 1
        && values[13] == 1 && values[14] == 1
        && is_flush(suit)) {
        return ROYAL_FLUSH;
    }

    if (is_straight(values)) {
        return is_flush(suit) ? STRAIGHT_FLUSH : STRAIGHT;
    }

    if (values[hand[0].value] == 4 || values[hand[1].value] == 4) {
        return FOUR;
    }

    if (is_three(values)) { return is_pair(values) ? FULL_HOUSE : THREE; }

    if (is_flush(suit)) { return FLUSH; }

    return is_pair(values);
}

int32_t handle_tie(struct card* p1, struct card* p2, enum hands rank) {
    int32_t count_1[15] = { 0 }, count_2[15] = { 0 };
    for (int32_t i = 0; i < HANDSIZE; ++i) {
        ++count_1[p1[i].value];
        ++count_2[p2[i].value];
    }

    int32_t value_1, value_2;
    if (rank == 1) {
        for (int32_t i = 0; i < 15; ++i) {
            if (count_1[i] == 2) {
                value_1 = i;
            }
            if (count_2[i] == 2) {
                value_2 = i;
            }
        }

        if (value_1 != value_2) {
            return value_1 > value_2 ? 1 : 2;
        }
    }

    for (int32_t i = 14; i >= 0; --i) {
        if (count_1[i] == 1 && count_2[i] == 0) { return 1; }
        if (count_2[i] == 1 && count_1[i] == 0) { return 2; }
    }

    return 0;
}
