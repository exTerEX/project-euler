#include <stdio.h>

int main() {
    int N = 1000, p = 0, sum = 0;

    for (int index = 0; index < N; index++) {
        if (index % 3 == 0 || index % 5 == 0) {
            sum = sum + index;
        }
    }

    printf("%d\n", sum);

    return 0;
}
