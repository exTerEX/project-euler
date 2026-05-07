#include <stdio.h>
#include <string.h>

#define FILENAME "problem-096.txt"

static int grid[9][9];

static int solve(int pos) {
    if (pos == 81) return 1;
    int r = pos / 9, c = pos % 9;
    if (grid[r][c] != 0) return solve(pos + 1);
    for (int d = 1; d <= 9; d++) {
        int ok = 1;
        for (int i = 0; i < 9 && ok; i++) {
            if (grid[r][i] == d) ok = 0;
            if (grid[i][c] == d) ok = 0;
        }
        if (ok) {
            int br = (r/3)*3, bc = (c/3)*3;
            for (int i = br; i < br+3 && ok; i++)
                for (int j = bc; j < bc+3 && ok; j++)
                    if (grid[i][j] == d) ok = 0;
        }
        if (ok) {
            grid[r][c] = d;
            if (solve(pos + 1)) return 1;
            grid[r][c] = 0;
        }
    }
    return 0;
}

int main() {
    FILE *f = fopen(FILENAME, "r");
    if (!f) { printf("ERROR: can't open %s\n", FILENAME); return 1; }
    int total = 0;
    char line[32];
    for (int g = 0; g < 50; g++) {
        fgets(line, sizeof(line), f);
        for (int r = 0; r < 9; r++) {
            fgets(line, sizeof(line), f);
            for (int c = 0; c < 9; c++)
                grid[r][c] = line[c] - '0';
        }
        solve(0);
        total += grid[0][0]*100 + grid[0][1]*10 + grid[0][2];
    }
    fclose(f);
    printf("%d\n", total);
    return 0;
}
