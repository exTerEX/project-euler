#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define FILENAME "problem-099.txt"

int main() {
    FILE* f;
    if ((f = fopen(FILENAME, "r")) == NULL) {
        printf("ERROR: can't open %s\n", FILENAME);
        exit(1);
    }

    int32_t base, exp;
    fscanf(f, "%d,%d", &base, &exp);
    double largest_val = (float)exp * log(base);
    ;

    int32_t index = 2, largest_index = 1;
    while (fscanf(f, "%d,%d", &base, &exp) != EOF) {
        double val = (float)exp * log(base);

        if (val > largest_val) {
            largest_val = val;
            largest_index = index;
        }

        ++index;
    }

    printf("%d\n", largest_index);

    fclose(f);
    return 0;
}
