#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define KEYSIZE 3

int32_t* text;
int32_t size;

void read_ciphered_text(char*);
void decipher(int32_t*, char*, int32_t);
int32_t count_occurrence(int32_t*, int32_t, int32_t*, int32_t);

int main() {
    char key[KEYSIZE], best_key[KEYSIZE];
    int32_t the[] = { 't', 'h', 'e' };

    read_ciphered_text("problem-059.txt");
    int32_t* deciphered_text = calloc(size, sizeof * deciphered_text);

    int32_t max_count_occ = 0;
    for (int32_t i = 0; i < 26; ++i) {
        key[0] = 'a' + i;

        for (int32_t j = 0; j < 26; ++j) {
            key[1] = 'a' + j;

            for (int32_t k = 0; k < 26; ++k) {
                key[2] = 'a' + k;
                decipher(deciphered_text, key, KEYSIZE);

                int32_t n = count_occurrence(deciphered_text, size, the, KEYSIZE);
                if (n > max_count_occ) {
                    memcpy(best_key, key, KEYSIZE);
                    max_count_occ = n;
                }
            }
        }
    }

    decipher(deciphered_text, best_key, KEYSIZE);

    int32_t answer = 0;
    for (int32_t i = 0; i < size; ++i) { answer += deciphered_text[i]; }

    printf("%d\n", answer);
    return 0;
}

void read_ciphered_text(char* filename) {
    char c;
    FILE* fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Impossible to read the ciphered text.\n");
        size = 0;
    }

    size = 0;
    while ((c = fgetc(fp)) != EOF) { if (c == ',') { ++size; } }
    ++size;

    text = calloc(size, sizeof * text);
    fseek(fp, 0, SEEK_SET);
    for (int32_t i = 0; i < size; ++i) { fscanf(fp, "%d,", &text[i]); }
}

void decipher(int32_t* deciphered_text, char* key, int32_t key_size) {
    for (int32_t i = 0; i < size; ++i) {
        deciphered_text[i] = text[i] ^ key[i % key_size];
    }
}

int32_t count_occurrence(int32_t* s, int32_t len, int32_t* sub, int32_t sub_len) {
    int32_t j, count = 0;
    for (int32_t i = 0; i < len - sub_len + 1; ++i) {
        for (j = 0; j < sub_len && s[i + j] == sub[j]; ++j) { ; }
        if (j == sub_len) { ++count; }
    }

    return count;
}
