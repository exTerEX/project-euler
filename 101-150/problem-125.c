#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define LIMIT 100000000LL

bool is_palindrome(int64_t n) {
    char s[20];
    int len = 0;
    int64_t tmp = n;
    while (tmp > 0) { s[len++] = tmp % 10; tmp /= 10; }
    for (int i = 0; i < len/2; i++)
        if (s[i] != s[len-1-i]) return false;
    return true;
}

bool found[100000001];

int main() {
    memset(found, 0, sizeof(found));
    int64_t total = 0;
    for (int64_t a = 1; a * a < LIMIT; a++) {
        int64_t sum = a * a;
        for (int64_t b = a + 1; sum + b*b < LIMIT; b++) {
            sum += b * b;
            if (sum < LIMIT && is_palindrome(sum) && !found[sum]) {
                found[sum] = true;
                total += sum;
            }
        }
    }
    printf("%ld\n", total);
    return 0;
}
