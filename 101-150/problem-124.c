#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LIMIT 100001

int rad[LIMIT];

typedef struct { int r, n; } Entry;
Entry entries[LIMIT];

int cmp(const void *a, const void *b) {
    Entry *x = (Entry*)a, *y = (Entry*)b;
    if (x->r != y->r) return x->r - y->r;
    return x->n - y->n;
}

int main() {
    for (int i = 1; i < LIMIT; i++) rad[i] = 1;
    for (int p = 2; p < LIMIT; p++) {
        if (rad[p] == 1) {
            for (int j = p; j < LIMIT; j += p)
                rad[j] *= p;
        }
    }
    for (int i = 1; i < LIMIT; i++) {
        entries[i-1].r = rad[i];
        entries[i-1].n = i;
    }
    qsort(entries, LIMIT - 1, sizeof(Entry), cmp);
    printf("%d\n", entries[9999].n);
    return 0;
}
