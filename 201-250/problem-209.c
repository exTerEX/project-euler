#include <stdint.h>
#include <stdio.h>

int main(void) {
    const int N = 64;
    uint8_t next_state[64];

    for (int x = 0; x < N; x++) {
        int a = (x >> 5) & 1;
        int b = (x >> 4) & 1;
        int c = (x >> 3) & 1;
        int d = (x >> 2) & 1;
        int e = (x >> 1) & 1;
        int f = x & 1;

        int g = a ^ (b & c);
        int y = (b << 5) | (c << 4) | (d << 3) | (e << 2) | (f << 1) | g;
        next_state[x] = (uint8_t)y;
    }

    uint64_t lucas[65];
    lucas[0] = 2;
    lucas[1] = 1;
    for (int i = 2; i <= 64; i++) {
        lucas[i] = lucas[i - 1] + lucas[i - 2];
    }

    uint8_t used[64] = {0};
    uint64_t answer = 1;

    for (int s = 0; s < N; s++) {
        if (used[s]) {
            continue;
        }

        int cur = s;
        int len = 0;
        do {
            used[cur] = 1;
            cur = next_state[cur];
            len++;
        } while (cur != s);

        answer *= lucas[len];
    }

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
