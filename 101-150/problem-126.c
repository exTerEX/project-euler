#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define LIMIT 20000

int cnt[LIMIT];

int main() {
    memset(cnt, 0, sizeof(cnt));
    for (int a = 1; ; a++) {
        if (6 * a * a >= LIMIT) break;
        for (int b = a; ; b++) {
            if (2 * (a*b + a*b + b*b) >= LIMIT) break;
            for (int c = b; ; c++) {
                int base = 2 * (a*b + b*c + a*c);
                if (base >= LIMIT) break;
                int perim = 4 * (a + b + c);
                for (int n = 1; ; n++) {
                    int64_t v = base + (int64_t)(n-1)*perim + 4LL*(n-1)*(n-2);
                    if (v >= LIMIT) break;
                    cnt[v]++;
                }
            }
        }
    }
    for (int i = 1; i < LIMIT; i++) {
        if (cnt[i] == 1000) { printf("%d\n", i); return 0; }
    }
    return 0;
}
