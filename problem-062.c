#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAXLEN 15
#define HASHSIZE 10000

struct permutation {
    char* repr;
    int8_t count;
    int64_t smallest;
    struct permutation* next;
};

uint32_t hash(char* s);
char* largest_permutation(int64_t n);
struct permutation* insert(struct permutation** hashtab, int64_t n);

struct permutation* insert(struct permutation** hashtab, int64_t n) {
    char* representation = largest_permutation(n * n * n);

    uint32_t hashval = hash(representation);

    for (struct permutation* p = hashtab[hashval]; p != NULL; p = p->next) {
        if (strcmp(p->repr, representation) == 0) /* found */ {
            p->count++;
            return p;
        }
    }

    struct permutation* p = (struct permutation*)malloc(sizeof * p);
    p->repr = representation;
    p->count = 1;
    p->smallest = n * n * n;
    p->next = hashtab[hashval];
    hashtab[hashval] = p;

    return p;
}

int main() {
    struct permutation** hashtab = calloc(HASHSIZE, sizeof * hashtab);

    for (int64_t i = 345; i < HASHSIZE; ++i) {
        struct permutation* current = insert(hashtab, i);

        if (current->count == 5) {
            printf("%ld\n", current->smallest);
            break;
        }
    }

    return 0;
}

uint32_t hash(char* s) {
    uint32_t hashval;

    for (hashval = 0; *s != '\0'; ++s) { hashval = *s + 31 * hashval; }

    return hashval % HASHSIZE;
}

char* largest_permutation(int64_t n) {
    char* permutation = malloc(MAXLEN);

    int8_t digits[10] = { 0 };
    while (n > 0) {
        ++digits[n % 10];
        n /= 10;
    }

    int32_t i, pos;
    for (i = 9, pos = 0; i > -1 && pos < MAXLEN; --i) {
        if (digits[i] == 0) { continue; }

        while (digits[i]-- > 0) { permutation[pos++] = '0' + i; }
    }

    permutation[pos] = '\0';

    return permutation;
}
