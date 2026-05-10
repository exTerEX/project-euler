#include <stdio.h>

int main() {
    int dart_vals[62], nt = 0;
    for (int i = 1; i <= 20; i++) dart_vals[nt++] = i;
    dart_vals[nt++] = 25;
    for (int i = 1; i <= 20; i++) dart_vals[nt++] = 2 * i;
    dart_vals[nt++] = 50;
    for (int i = 1; i <= 20; i++) dart_vals[nt++] = 3 * i;

    int doubles[21], nd = 0;
    for (int i = 1; i <= 20; i++) doubles[nd++] = 2 * i;
    doubles[nd++] = 50;

    int count = 0;
    for (int d = 0; d < nd; d++) {
        int last = doubles[d];
        if (last <= 99) count++;
        for (int i = 0; i < nt; i++) {
            if (dart_vals[i] + last <= 99) count++;
        }
        for (int i = 0; i < nt; i++) {
            for (int j = i; j < nt; j++) {
                if (dart_vals[i] + dart_vals[j] + last <= 99) count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}
