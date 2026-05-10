#include <stdio.h>
#include <string.h>

#define LIMIT 1000000

static int ways[LIMIT + 1];

int main(void) {
    memset(ways, 0, sizeof(ways));

    for (int outer = 3;; outer++) {
        int min_tiles = outer * outer - (outer - 2) * (outer - 2);
        if (min_tiles > LIMIT) {
            break;
        }

        for (int inner = outer - 2; inner > 0; inner -= 2) {
            int tiles = outer * outer - inner * inner;
            if (tiles > LIMIT) {
                break;
            }
            ways[tiles]++;
        }
    }

    int answer = 0;
    for (int n = 1; n <= LIMIT; n++) {
        if (ways[n] >= 1 && ways[n] <= 10) {
            answer++;
        }
    }

    printf("%d\n", answer);
    return 0;
}
