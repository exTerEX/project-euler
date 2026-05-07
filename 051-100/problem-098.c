#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define FILENAME "problem-098.txt"
#define MAX_WORDS 2000
#define MAX_LEN 20

static char words[MAX_WORDS][MAX_LEN];
static int nwords;

static void sort_letters(const char *s, char *out, int n) {
    for (int i = 0; i < n; i++) out[i] = s[i];
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (out[j] < out[i]) { char t = out[i]; out[i] = out[j]; out[j] = t; }
    out[n] = 0;
}

static int is_perfect_sq(uint64_t n) {
    if (n == 0) return 0;
    uint64_t s = (uint64_t)sqrt((double)n);
    while (s > 0 && s*s > n) s--;
    while ((s+1)*(s+1) <= n) s++;
    return s*s == n;
}

static uint64_t try_mapping(const char *w1, const char *w2, uint64_t sq1, int len) {
    int digit[26], used[10];
    memset(digit, -1, sizeof(digit));
    memset(used, 0, sizeof(used));
    uint64_t tmp = sq1;
    int digs[MAX_LEN];
    for (int i = len-1; i >= 0; i--) { digs[i] = (int)(tmp % 10); tmp /= 10; }
    for (int i = 0; i < len; i++) {
        int c = w1[i] - 'A', d = digs[i];
        if (digit[c] == -1) {
            if (used[d]) return 0;
            digit[c] = d; used[d] = 1;
        } else if (digit[c] != d) {
            return 0;
        }
    }
    if (digit[w1[0]-'A'] == 0 || digit[w2[0]-'A'] == 0) return 0;
    uint64_t sq2 = 0;
    for (int i = 0; i < len; i++) {
        int c = w2[i] - 'A';
        if (digit[c] == -1) return 0;
        sq2 = sq2 * 10 + (uint64_t)digit[c];
    }
    return is_perfect_sq(sq2) ? sq2 : 0;
}

int main() {
    FILE *f = fopen(FILENAME, "r");
    if (!f) { printf("ERROR: can't open %s\n", FILENAME); return 1; }
    char buf[20000];
    fgets(buf, sizeof(buf), f);
    fclose(f);
    nwords = 0;
    char *tok = strtok(buf, ",\"\n\r");
    while (tok && nwords < MAX_WORDS) {
        strncpy(words[nwords++], tok, MAX_LEN-1);
        tok = strtok(NULL, ",\"\n\r");
    }

    uint64_t best = 0;
    for (int i = 0; i < nwords; i++) {
        int li = (int)strlen(words[i]);
        char sig_i[MAX_LEN];
        sort_letters(words[i], sig_i, li);
        for (int j = i+1; j < nwords; j++) {
            int lj = (int)strlen(words[j]);
            if (lj != li) continue;
            char sig_j[MAX_LEN];
            sort_letters(words[j], sig_j, li);
            if (strcmp(sig_i, sig_j) != 0) continue;
            uint64_t lo = 1;
            for (int k = 1; k < li; k++) lo *= 10;
            uint64_t hi = lo * 10;
            for (uint64_t r = (uint64_t)ceil(sqrt((double)lo)); r*r < hi; r++) {
                uint64_t sq1 = r*r;
                uint64_t sq2 = try_mapping(words[i], words[j], sq1, li);
                if (sq2) { if (sq1>best) best=sq1; if (sq2>best) best=sq2; }
                sq2 = try_mapping(words[j], words[i], sq1, li);
                if (sq2) { if (sq1>best) best=sq1; if (sq2>best) best=sq2; }
            }
        }
    }
    printf("%lu\n", best);
    return 0;
}
