#include <stdint.h>
#include <stdio.h>

typedef struct {
    unsigned __int128 n;
    uint64_t value;
} MemoEntry;

static MemoEntry memo[4096];
static int memo_size = 0;

static uint64_t ways(unsigned __int128 n) {
    if (n == 0) {
        return 1;
    }

    for (int i = 0; i < memo_size; i++) {
        if (memo[i].n == n) {
            return memo[i].value;
        }
    }

    uint64_t result;
    if ((n & 1) != 0) {
        result = ways((n - 1) >> 1);
    } else {
        result = ways(n >> 1) + ways((n >> 1) - 1);
    }

    memo[memo_size].n = n;
    memo[memo_size].value = result;
    memo_size++;

    return result;
}

int main(void) {
    unsigned __int128 n = 1;
    for (int i = 0; i < 25; i++) {
        n *= 10;
    }

    uint64_t answer = ways(n);
    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
