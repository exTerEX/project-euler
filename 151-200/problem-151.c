#include <stdio.h>
#include <string.h>

static double memo[17][17][17][17];
static unsigned char seen[17][17][17][17];

static double expected_single_sheet(int a2, int a3, int a4, int a5) {
    int total = a2 + a3 + a4 + a5;
    if (total == 0) {
        return 0.0;
    }

    if (seen[a2][a3][a4][a5]) {
        return memo[a2][a3][a4][a5];
    }
    seen[a2][a3][a4][a5] = 1;

    double result = 0.0;
    if (total == 1 && !(a2 == 0 && a3 == 0 && a4 == 0 && a5 == 1)) {
        result += 1.0;
    }

    if (a2 > 0) {
        result += (double)a2 / total * expected_single_sheet(a2 - 1, a3 + 1, a4 + 1, a5 + 1);
    }
    if (a3 > 0) {
        result += (double)a3 / total * expected_single_sheet(a2, a3 - 1, a4 + 1, a5 + 1);
    }
    if (a4 > 0) {
        result += (double)a4 / total * expected_single_sheet(a2, a3, a4 - 1, a5 + 1);
    }
    if (a5 > 0) {
        result += (double)a5 / total * expected_single_sheet(a2, a3, a4, a5 - 1);
    }

    memo[a2][a3][a4][a5] = result;
    return result;
}

int main(void) {
    memset(seen, 0, sizeof(seen));
    printf("%.6f\n", expected_single_sheet(1, 1, 1, 1));
    return 0;
}
