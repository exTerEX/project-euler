#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LIMIT 1000001

static uint32_t sigma[LIMIT];
static uint8_t visited[LIMIT];
static uint32_t chain[LIMIT];
static uint8_t in_chain[LIMIT];

int main() {
    for (uint32_t i = 1; i < LIMIT; i++)
        for (uint32_t j = 2*i; j < LIMIT; j += i)
            sigma[j] += i;

    int best_len = 0;
    uint32_t best_min = 0;

    for (uint32_t start = 2; start < LIMIT; start++) {
        if (visited[start]) continue;
        memset(in_chain, 0, sizeof(in_chain));

        int len = 0;
        uint32_t cur = start;
        while (cur < LIMIT && !visited[cur] && !in_chain[cur]) {
            in_chain[cur] = 1;
            chain[len++] = cur;
            cur = sigma[cur];
        }

        int in_cycle = (cur < LIMIT && !visited[cur] && in_chain[cur]);
        uint32_t cycle_node = cur;

        for (int i = 0; i < len; i++) visited[chain[i]] = 1;

        if (!in_cycle) continue;

        int cycle_start = 0;
        while (chain[cycle_start] != cycle_node) cycle_start++;
        int cycle_len = len - cycle_start;

        if (cycle_len > best_len) {
            best_len = cycle_len;
            uint32_t min_val = chain[cycle_start];
            for (int i = cycle_start + 1; i < len; i++)
                if (chain[i] < min_val) min_val = chain[i];
            best_min = min_val;
        }
    }

    printf("%u\n", best_min);
    return 0;
}
