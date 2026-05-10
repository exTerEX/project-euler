#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define USERS 1000000
#define PM 524287

static int parent[USERS];
static int size_set[USERS];

static int find_set(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

static void unite(int a, int b) {
    int ra = find_set(a);
    int rb = find_set(b);
    if (ra == rb) {
        return;
    }
    if (size_set[ra] < size_set[rb]) {
        int tmp = ra;
        ra = rb;
        rb = tmp;
    }
    parent[rb] = ra;
    size_set[ra] += size_set[rb];
}

static int lagged_fib_next(void) {
    static int initialized = 0;
    static int s[55];
    static int k = 0;

    if (!initialized) {
        for (int i = 1; i <= 55; i++) {
            int64_t x = 100003LL - 200003LL * i + 300007LL * i * i * i;
            int v = (int)(x % 1000000);
            if (v < 0) {
                v += 1000000;
            }
            s[i - 1] = v;
        }
        initialized = 1;
    }

    int value;
    if (k < 55) {
        value = s[k];
    } else {
        value = (s[(k - 24) % 55] + s[(k - 55) % 55]) % 1000000;
        s[k % 55] = value;
    }
    k++;
    return value;
}

int main(void) {
    for (int i = 0; i < USERS; i++) {
        parent[i] = i;
        size_set[i] = 1;
    }

    int successful_calls = 0;
    while (size_set[find_set(PM)] < 990000) {
        int caller = lagged_fib_next();
        int called = lagged_fib_next();
        if (caller == called) {
            continue;
        }
        successful_calls++;
        unite(caller, called);
    }

    printf("%d\n", successful_calls);
    return 0;
}
