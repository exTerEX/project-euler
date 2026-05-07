#include <stdio.h>
#include <string.h>

#define FILENAME "problem-089.txt"

static int roman_to_int(const char *s) {
    static const int val[256] = {['I']=1, ['V']=5, ['X']=10, ['L']=50,
                                  ['C']=100, ['D']=500, ['M']=1000};
    int total = 0, n = (int)strlen(s);
    for (int i = 0; i < n; i++) {
        int v = val[(unsigned char)s[i]];
        int nxt = (i+1 < n) ? val[(unsigned char)s[i+1]] : 0;
        total += (v < nxt) ? -v : v;
    }
    return total;
}

static int int_to_roman_len(int n) {
    static const int vals[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    static const int lens[] = {1,2,1,2,1,2,1,2,1,2,1,2,1};
    int len = 0;
    for (int i = 0; i < 13; i++)
        while (n >= vals[i]) { len += lens[i]; n -= vals[i]; }
    return len;
}

int main() {
    FILE *f = fopen(FILENAME, "r");
    if (!f) { printf("ERROR: can't open %s\n", FILENAME); return 1; }
    char buf[100];
    int saved = 0;
    while (fgets(buf, sizeof(buf), f)) {
        int len = (int)strlen(buf);
        while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) buf[--len] = 0;
        if (len == 0) continue;
        saved += len - int_to_roman_len(roman_to_int(buf));
    }
    fclose(f);
    printf("%d\n", saved);
    return 0;
}
