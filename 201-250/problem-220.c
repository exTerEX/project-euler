#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint64_t steps;
    int64_t dx;
    int64_t dy;
    int turn;  /* 0..3, clockwise quarter-turns */
} Stats;

typedef struct {
    int64_t x;
    int64_t y;
    int dir;   /* 0=up,1=right,2=down,3=left */
} State;

static Stats A[51];
static Stats B[51];

static void rotate_vec(int64_t x, int64_t y, int dir, int64_t *rx, int64_t *ry) {
    if (dir == 0) {
        *rx = x; *ry = y;
    } else if (dir == 1) {
        *rx = y; *ry = -x;
    } else if (dir == 2) {
        *rx = -x; *ry = -y;
    } else {
        *rx = -y; *ry = x;
    }
}

static void apply_stats(State *st, const Stats *s) {
    int64_t rx, ry;
    rotate_vec(s->dx, s->dy, st->dir, &rx, &ry);
    st->x += rx;
    st->y += ry;
    st->dir = (st->dir + s->turn) & 3;
}

static void turn_right(State *st) {
    st->dir = (st->dir + 1) & 3;
}

static void turn_left(State *st) {
    st->dir = (st->dir + 3) & 3;
}

static void forward(State *st) {
    if (st->dir == 0) st->y += 1;
    else if (st->dir == 1) st->x += 1;
    else if (st->dir == 2) st->y -= 1;
    else st->x -= 1;
}

static void build_stats(void) {
    A[0] = (Stats){0, 0, 0, 0};
    B[0] = (Stats){0, 0, 0, 0};

    for (int n = 1; n <= 50; n++) {
        State st;

        /* A_n = A_{n-1} R B_{n-1} F R */
        st = (State){0, 0, 0};
        apply_stats(&st, &A[n - 1]);
        turn_right(&st);
        apply_stats(&st, &B[n - 1]);
        forward(&st);
        turn_right(&st);
        A[n].steps = A[n - 1].steps + B[n - 1].steps + 1;
        A[n].dx = st.x;
        A[n].dy = st.y;
        A[n].turn = st.dir;

        /* B_n = L F A_{n-1} L B_{n-1} */
        st = (State){0, 0, 0};
        turn_left(&st);
        forward(&st);
        apply_stats(&st, &A[n - 1]);
        turn_left(&st);
        apply_stats(&st, &B[n - 1]);
        B[n].steps = A[n - 1].steps + B[n - 1].steps + 1;
        B[n].dx = st.x;
        B[n].dy = st.y;
        B[n].turn = st.dir;
    }
}

static void walk_A(int n, uint64_t *remaining, State *st);
static void walk_B(int n, uint64_t *remaining, State *st);

static void walk_A(int n, uint64_t *remaining, State *st) {
    if (*remaining == 0 || n == 0) return;

    if (*remaining >= A[n].steps) {
        apply_stats(st, &A[n]);
        *remaining -= A[n].steps;
        return;
    }

    walk_A(n - 1, remaining, st);
    if (*remaining == 0) return;
    turn_right(st);

    walk_B(n - 1, remaining, st);
    if (*remaining == 0) return;

    forward(st);
    (*remaining)--;
    if (*remaining == 0) return;
    turn_right(st);
}

static void walk_B(int n, uint64_t *remaining, State *st) {
    if (*remaining == 0 || n == 0) return;

    if (*remaining >= B[n].steps) {
        apply_stats(st, &B[n]);
        *remaining -= B[n].steps;
        return;
    }

    turn_left(st);
    if (*remaining == 0) return;

    forward(st);
    (*remaining)--;
    if (*remaining == 0) return;

    walk_A(n - 1, remaining, st);
    if (*remaining == 0) return;

    turn_left(st);
    walk_B(n - 1, remaining, st);
}

int main(void) {
    const uint64_t target_steps = 1000000000000ULL;
    uint64_t remaining = target_steps;
    State st = {0, 0, 0};

    build_stats();

    /* D_50 = F A_50, with initial heading up */
    if (remaining > 0) {
        forward(&st);
        remaining--;
    }
    walk_A(50, &remaining, &st);

    printf("%" PRId64 ",%" PRId64 "\n", st.x, st.y);
    return 0;
}
