#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int count;

void generate(int *digits, int n, int start) {
    if (start == n) { count++; return; }
    int num = 0;
    for (int end = start; end < n; end++) {
        num = num * 10 + digits[end];
        if (num > 1 && is_prime(num))
            generate(digits, n, end + 1);
    }
}

int perm[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

void permute(int *arr, int l, int r) {
    if (l == r) {
        generate(arr, 9, 0);
        return;
    }
    for (int i = l; i <= r; i++) {
        int tmp = arr[l]; arr[l] = arr[i]; arr[i] = tmp;
        permute(arr, l + 1, r);
        tmp = arr[l]; arr[l] = arr[i]; arr[i] = tmp;
    }
}

int main() {
    count = 0;
    permute(perm, 0, 8);
    printf("%d\n", count);
    return 0;
}
