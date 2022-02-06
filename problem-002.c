#include <stdio.h>

int main() {
    size_t n = 10, sum = 0, index = 1, jndex = 2, temp;

    while (jndex <= n) {
        if ((jndex & 1) == 0) {
            sum += jndex;
        }

        temp = index;
        index = jndex;
        jndex = temp + index;
    }

    printf("%ld\n", sum);

    return 0;
}
