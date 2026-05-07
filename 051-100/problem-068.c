#include <stdio.h>
#include <stdint.h>
#include <string.h>

static char best[20];

static void try_inner(int *inner) {
    int s = inner[0] + inner[1] + inner[2] + inner[3] + inner[4];
    if ((55 + s) % 5 != 0) return;
    int arm = (55 + s) / 5;

    int outer[5];
    int used[11] = {0};
    for (int i = 0; i < 5; ++i) used[inner[i]] = 1;

    int has10 = 0, valid = 1;
    for (int i = 0; i < 5 && valid; ++i) {
        outer[i] = arm - inner[i] - inner[(i + 1) % 5];
        if (outer[i] < 1 || outer[i] > 10 || used[outer[i]]) { valid = 0; break; }
        used[outer[i]] = 1;
        if (outer[i] == 10) has10 = 1;
    }
    if (!valid || !has10) return;
    for (int v = 1; v <= 10 && valid; ++v) if (!used[v]) valid = 0;
    if (!valid) return;

    int min_idx = 0;
    for (int i = 1; i < 5; ++i)
        if (outer[i] < outer[min_idx]) min_idx = i;

    char buf[20];
    int pos = 0;
    for (int i = 0; i < 5; ++i) {
        int k = (min_idx + i) % 5;
        pos += sprintf(buf + pos, "%d%d%d", outer[k], inner[k], inner[(k + 1) % 5]);
    }
    buf[pos] = '\0';
    if (pos == 16 && strcmp(buf, best) > 0) strcpy(best, buf);
}

int main() {
    strcpy(best, "0000000000000000");
    int p[5], u[10] = {0};

    for (int a = 1; a <= 9; ++a) { p[0]=a; u[a-1]=1;
    for (int b = 1; b <= 9; ++b) { if(u[b-1]) continue; p[1]=b; u[b-1]=1;
    for (int c = 1; c <= 9; ++c) { if(u[c-1]) continue; p[2]=c; u[c-1]=1;
    for (int d = 1; d <= 9; ++d) { if(u[d-1]) continue; p[3]=d; u[d-1]=1;
    for (int e = 1; e <= 9; ++e) { if(u[e-1]) continue; p[4]=e;
        try_inner(p);
    }
    u[d-1]=0; }
    u[c-1]=0; }
    u[b-1]=0; }
    u[a-1]=0; }

    printf("%s\n", best);
    return 0;
}
