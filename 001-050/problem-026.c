#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 1000

int main() {
    int32_t t_cycle = 0, answer;
    int32_t* seen = (int32_t*)calloc(MAX, sizeof(int32_t));

    for (int32_t d = MAX; d > 1; --d) {
        if (t_cycle > d - 1) break;

        for (int32_t i = 0; i < MAX; ++i) { seen[i] = 0; }

        int32_t remainder = 1;
        int32_t pos = 0;
        while (seen[remainder] == 0 && remainder != 0) {
            seen[remainder] = pos;
            remainder = (remainder * 10) % d;
            ++pos;
        }

        if (pos - seen[remainder] > t_cycle) {
            t_cycle = pos - seen[remainder];
            answer = d;
        }
    }

    printf("%d\n", answer);
    free(seen);

    return 0;
}
