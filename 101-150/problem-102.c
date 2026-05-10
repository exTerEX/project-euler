#include <stdint.h>
#include <stdio.h>

int sign(int64_t x);
int contains_origin(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3);

int main() {
    FILE *fp = fopen("101-150/problem-102.txt", "r");
    if (!fp) { perror("Unable to open file"); return 1; }
    int count = 0;
    int64_t x1, y1, x2, y2, x3, y3;
    while (fscanf(fp, "%ld,%ld,%ld,%ld,%ld,%ld", &x1, &y1, &x2, &y2, &x3, &y3) == 6) {
        if (contains_origin(x1, y1, x2, y2, x3, y3)) count++;
    }
    fclose(fp);
    printf("%d\n", count);
    return 0;
}

int sign(int64_t x) {
    return (x > 0) - (x < 0);
}

int contains_origin(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3) {
    int64_t d1 = x1 * y2 - x2 * y1;
    int64_t d2 = x2 * y3 - x3 * y2;
    int64_t d3 = x3 * y1 - x1 * y3;
    return sign(d1) == sign(d2) && sign(d2) == sign(d3);
}
