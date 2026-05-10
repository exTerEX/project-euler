#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LIMIT 18

typedef struct {
    uint32_t num;
    uint32_t den;
} Fraction;

typedef struct {
    Fraction *data;
    size_t size;
    size_t cap;
} FracVec;

static uint32_t gcd32(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static Fraction reduce_fraction(uint64_t num, uint64_t den) {
    uint32_t g = gcd32((uint32_t)num, (uint32_t)den);
    Fraction f;
    f.num = (uint32_t)(num / g);
    f.den = (uint32_t)(den / g);
    return f;
}

static Fraction add_fraction(Fraction a, Fraction b) {
    uint64_t num = (uint64_t)a.num * b.den + (uint64_t)b.num * a.den;
    uint64_t den = (uint64_t)a.den * b.den;
    return reduce_fraction(num, den);
}

static Fraction series_fraction(Fraction a, Fraction b) {
    uint64_t num = (uint64_t)a.num * b.num;
    uint64_t den = (uint64_t)a.num * b.den + (uint64_t)b.num * a.den;
    return reduce_fraction(num, den);
}

static void vec_push(FracVec *v, Fraction f) {
    if (v->size == v->cap) {
        size_t new_cap = (v->cap == 0) ? 1024 : v->cap * 2;
        Fraction *p = (Fraction *)realloc(v->data, new_cap * sizeof(Fraction));
        if (p == NULL) {
            exit(1);
        }
        v->data = p;
        v->cap = new_cap;
    }
    v->data[v->size++] = f;
}

static int cmp_fraction(const void *pa, const void *pb) {
    const Fraction *a = (const Fraction *)pa;
    const Fraction *b = (const Fraction *)pb;
    uint64_t left = (uint64_t)a->num * b->den;
    uint64_t right = (uint64_t)b->num * a->den;
    if (left < right) {
        return -1;
    }
    if (left > right) {
        return 1;
    }
    return 0;
}

static int eq_fraction(Fraction a, Fraction b) {
    return (uint64_t)a.num * b.den == (uint64_t)b.num * a.den;
}

static void vec_unique_sorted(FracVec *v) {
    if (v->size == 0) {
        return;
    }
    qsort(v->data, v->size, sizeof(Fraction), cmp_fraction);
    size_t out = 1;
    for (size_t i = 1; i < v->size; i++) {
        if (!eq_fraction(v->data[i], v->data[out - 1])) {
            v->data[out++] = v->data[i];
        }
    }
    v->size = out;
}

int main(void) {
    FracVec circuits[LIMIT + 1];
    for (int i = 0; i <= LIMIT; i++) {
        circuits[i].data = NULL;
        circuits[i].size = 0;
        circuits[i].cap = 0;
    }

    vec_push(&circuits[1], (Fraction){1, 1});

    for (int size = 2; size <= LIMIT; size++) {
        for (int a = 1; a <= size / 2; a++) {
            int b = size - a;
            for (size_t i = 0; i < circuits[a].size; i++) {
                Fraction fa = circuits[a].data[i];
                for (size_t j = 0; j < circuits[b].size; j++) {
                    Fraction fb = circuits[b].data[j];
                    vec_push(&circuits[size], add_fraction(fa, fb));
                    vec_push(&circuits[size], series_fraction(fa, fb));
                }
            }
        }
        vec_unique_sorted(&circuits[size]);
    }

    FracVec all = {NULL, 0, 0};
    for (int i = 1; i <= LIMIT; i++) {
        for (size_t j = 0; j < circuits[i].size; j++) {
            vec_push(&all, circuits[i].data[j]);
        }
    }
    vec_unique_sorted(&all);

    printf("%zu\n", all.size);

    for (int i = 0; i <= LIMIT; i++) {
        free(circuits[i].data);
    }
    free(all.data);
    return 0;
}
