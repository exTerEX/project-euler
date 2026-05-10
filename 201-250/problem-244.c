#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum {
    MOVE_UP = 85,
    MOVE_LEFT = 76,
    MOVE_DOWN = 68,
    MOVE_RIGHT = 82,
    BOARD_SIZE = 16,
    WIDTH = 4,
    MODULO = 100000007,
    MAX_STATES = 1048576,
};

typedef struct {
    char pieces[BOARD_SIZE + 1];
    uint32_t checksum;
} Board;

typedef struct {
    Board *data;
    size_t size;
    size_t capacity;
} BoardVec;

static void vec_push(BoardVec *vec, const Board *board) {
    if (vec->size == vec->capacity) {
        size_t new_capacity = vec->capacity == 0 ? 1024 : vec->capacity * 2;
        Board *new_data = realloc(vec->data, new_capacity * sizeof(Board));
        if (new_data == NULL) {
            exit(1);
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size++] = *board;
}

static int board_valid(const Board *board) {
    return board->pieces[0] != '\0';
}

static uint32_t board_hash(const char *pieces) {
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        hash ^= (unsigned char)pieces[i];
        hash *= 16777619u;
    }
    return hash;
}

static int history_contains(char history[][BOARD_SIZE + 1], uint8_t *used, const char *pieces) {
    uint32_t idx = board_hash(pieces) & (MAX_STATES - 1);
    while (used[idx]) {
        if (memcmp(history[idx], pieces, BOARD_SIZE) == 0) {
            return 1;
        }
        idx = (idx + 1) & (MAX_STATES - 1);
    }
    return 0;
}

static void history_insert(char history[][BOARD_SIZE + 1], uint8_t *used, const char *pieces) {
    uint32_t idx = board_hash(pieces) & (MAX_STATES - 1);
    while (used[idx]) {
        if (memcmp(history[idx], pieces, BOARD_SIZE) == 0) {
            return;
        }
        idx = (idx + 1) & (MAX_STATES - 1);
    }
    used[idx] = 1;
    memcpy(history[idx], pieces, BOARD_SIZE + 1);
}

static Board move_board(const Board *board, int move) {
    Board next = {{0}, 0};
    size_t index = 0;
    while (index < BOARD_SIZE && board->pieces[index] != '.') {
        index++;
    }
    if (index == BOARD_SIZE) {
        return next;
    }

    int from_x = (int)(index % WIDTH);
    int from_y = (int)(index / WIDTH);
    int to_x = from_x;
    int to_y = from_y;

    switch (move) {
        case MOVE_UP:
            if (from_y == WIDTH - 1) return next;
            to_y++;
            break;
        case MOVE_DOWN:
            if (from_y == 0) return next;
            to_y--;
            break;
        case MOVE_LEFT:
            if (from_x == WIDTH - 1) return next;
            to_x++;
            break;
        case MOVE_RIGHT:
            if (from_x == 0) return next;
            to_x--;
            break;
        default:
            return next;
    }

    memcpy(next.pieces, board->pieces, BOARD_SIZE + 1);
    size_t swap_index = (size_t)(to_y * WIDTH + to_x);
    char tmp = next.pieces[index];
    next.pieces[index] = next.pieces[swap_index];
    next.pieces[swap_index] = tmp;
    next.checksum = ((uint64_t)board->checksum * 243u + (uint32_t)move) % MODULO;
    return next;
}

static uint32_t search(const char *final_position) {
    BoardVec todo = {0};
    Board start = {".rbbrrbbrrbbrrbb", 0};
    vec_push(&todo, &start);

    char (*history)[BOARD_SIZE + 1] = calloc(MAX_STATES, sizeof(*history));
    uint8_t *used = calloc(MAX_STATES, sizeof(uint8_t));
    if (history == NULL || used == NULL) {
        exit(1);
    }
    history_insert(history, used, start.pieces);

    uint32_t result = 0;
    int last_iteration = 0;
    while (!last_iteration) {
        BoardVec next = {0};
        for (size_t i = 0; i < todo.size; ++i) {
            Board current = todo.data[i];
            if (memcmp(current.pieces, final_position, BOARD_SIZE) == 0) {
                last_iteration = 1;
                result += current.checksum;
            }

            const int moves[] = {MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN};
            for (size_t m = 0; m < sizeof(moves) / sizeof(moves[0]); ++m) {
                Board candidate = move_board(&current, moves[m]);
                if (!board_valid(&candidate)) {
                    continue;
                }
                if (!history_contains(history, used, candidate.pieces)) {
                    vec_push(&next, &candidate);
                    history_insert(history, used, candidate.pieces);
                }
            }
        }
        free(todo.data);
        todo = next;
    }

    free(todo.data);
    free(history);
    free(used);
    return result;
}

int main(void) {
    char final_position[BOARD_SIZE + 1] = ".brbbrbrrbrbbrbr";
    if (!isatty(fileno(stdin))) {
        if (scanf("%16s", final_position) != 1) {
            memcpy(final_position, ".brbbrbrrbrbbrbr", BOARD_SIZE + 1);
        }
    }

    int red = 0, blue = 0, empty = 0, invalid = 0;
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        switch (final_position[i]) {
            case 'r': red++; break;
            case 'b': blue++; break;
            case '.': empty++; break;
            default: invalid++; break;
        }
    }
    if (red != 7 || blue != 8 || empty != 1 || invalid != 0) {
        return 1;
    }

    printf("%u\n", search(final_position));
    return 0;
}