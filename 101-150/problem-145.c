#include <stdio.h>

int reverse_num(int n) {
    int r = 0;
    while (n > 0) { r = r * 10 + n % 10; n /= 10; }
    return r;
}

int all_odd_digits(int n) {
    while (n > 0) {
        if ((n % 10) % 2 == 0) return 0;
        n /= 10;
    }
    return 1;
}

int main() {
    int count = 0;
    for (int n = 1; n < 1000000000; n++) {
        if (n % 10 == 0) continue;
        if (all_odd_digits(n + reverse_num(n))) count++;
    }
    printf("%d\n", count);
    return 0;
}
