#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define MAXLEN 100

int32_t word_value(char*);
int32_t is_triangular(int32_t);
int32_t read_word(FILE*, char*);

int main()
{
    FILE* fp;
    char word[MAXLEN];
    int32_t answer = 0;

    fp = fopen("001-050/problem-042.txt", "r");
    while (read_word(fp, word) != EOF) {
        if (is_triangular(word_value(word))) { ++answer; }
    }

    printf("%d\n", answer);
    return 0;
}

int32_t word_value(char* s) {
    int32_t val;
    for (val = 0; *s != '\0'; ++s) { val += (*s - 'A' + 1); }

    return val;
}

int32_t is_triangular(int32_t n) {
    int32_t m = (int32_t)sqrt(n * 2);

    return m * (m + 1) / 2 == n;
}

int32_t read_word(FILE* fp, char* dest) {
    int32_t c;

    while ((c = fgetc(fp)) != EOF && !isupper(c)) { ; }
    *dest++ = c;

    while ((c = fgetc(fp)) != EOF && isupper(c)) { *dest++ = c; }
    *dest = '\0';

    return c;
}
