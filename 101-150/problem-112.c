#include <stdio.h>
#include <stdbool.h>

bool is_bouncy(int n) {
    int prev = n % 10;
    n /= 10;
    bool inc = false, dec = false;
    while (n > 0) {
        int d = n % 10;
        if (d < prev) inc = true;
        if (d > prev) dec = true;
        if (inc && dec) return true;
        prev = d;
        n /= 10;
    }
    return false;
}

int main() {
    int bouncy = 0;
    for (int n = 1; ; n++) {
        if (is_bouncy(n)) bouncy++;
        if (bouncy * 100 == n * 99) {
            printf("%d\n", n);
            return 0;
        }
    }
    return 0;
}
