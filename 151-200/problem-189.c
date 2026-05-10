#include <stdint.h>
#include <stdio.h>
#include <string.h>

static const unsigned int height = 8;
static const unsigned int num_colors = 3;

static unsigned char triangles[64];
static uint64_t cache[7000];

static unsigned int get_id(unsigned int row) {
    unsigned int first = row * row;
    unsigned int width = 2 * row + 1;

    unsigned int result = row;
    for (unsigned int i = first + 2; i < first + width; i += 2) {
        int diff = (int)triangles[i - 2] - (int)triangles[i];
        if (diff < 0) {
            diff += (int)num_colors;
        }
        result = result * num_colors + (unsigned int)diff;
    }

    unsigned int reverse = row;
    for (unsigned int i = first + width - 1; i >= first + 2; i -= 2) {
        int diff = (int)triangles[i - 2] - (int)triangles[i];
        if (diff < 0) {
            diff += (int)num_colors;
        }
        reverse = reverse * num_colors + (unsigned int)diff;
        if (i == first + 2) {
            break;
        }
    }

    return (result < reverse) ? result : reverse;
}

static uint64_t search(unsigned int row, unsigned int col) {
    unsigned int first = row * row;
    unsigned int index = first + col;
    unsigned int width = 2 * row + 1;

    unsigned int next_row = row;
    unsigned int next_col = col + 1;
    if (next_col == width) {
        next_row++;
        next_col = 0;
    }

    unsigned int prev_id = 0;
    if (col == 0) {
        if (row == height) {
            return 1;
        }

        if (row == 0) {
            memset(cache, 0, sizeof(cache));
        } else {
            prev_id = get_id(row - 1);
            if (cache[prev_id] != 0) {
                return cache[prev_id];
            }
        }
    }

    uint64_t result = 0;
    if ((col & 1U) == 0U) {
        for (unsigned char color = 1; color <= num_colors; color++) {
            if (col > 0 && triangles[index - 1] == color) {
                continue;
            }
            triangles[index] = color;
            result += search(next_row, next_col);
        }
    } else {
        for (unsigned char color = 1; color <= num_colors; color++) {
            if (triangles[index - 1] == color || triangles[index - 2 * row] == color) {
                continue;
            }
            triangles[index] = color;
            result += search(next_row, next_col);
        }
    }

    if (col == 0 && row > 0) {
        cache[prev_id] = result;
    }

    return result;
}

int main(void) {
    uint64_t answer = search(0, 0);
    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
