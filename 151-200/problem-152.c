#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned __int128 u128;

typedef struct {
    u128 num;
    u128 den;
} Fraction;

typedef struct {
    Fraction f;
    uint32_t count;
} SumCount;

static const int candidates[] = {
    2,3,4,5,6,7,8,9,10,12,13,14,15,16,18,20,21,24,27,28,
    30,32,35,36,39,40,42,45,48,52,54,56,60,63,64,65,70,72,80
};

static const int num_candidates = (int)(sizeof(candidates) / sizeof(candidates[0]));
static const int split_index = 25; /* first number >= 40 */

static Fraction unit_fractions[39];
static Fraction remaining_total[26];

static SumCount *tail_counts = NULL;
static size_t tail_count_size = 0;

static u128 gcd128(u128 a, u128 b) {
    while (b != 0) {
        u128 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static Fraction reduce(Fraction f) {
    if (f.num == 0) {
        f.den = 1;
        return f;
    }
    u128 g = gcd128(f.num, f.den);
    f.num /= g;
    f.den /= g;
    return f;
}

static Fraction add_fraction(Fraction a, Fraction b) {
    if (a.num == 0) {
        return b;
    }
    if (b.num == 0) {
        return a;
    }
    u128 g = gcd128(a.den, b.den);
    u128 ad = a.den / g;
    u128 bd = b.den / g;
    Fraction out;
    out.num = a.num * bd + b.num * ad;
    out.den = a.den * bd;
    return reduce(out);
}

static int cmp_half(Fraction f) {
    u128 half_floor = f.den / 2;
    if (f.num < half_floor) {
        return -1;
    }
    if (f.num > half_floor) {
        return 1;
    }
    return (f.den & 1U) ? -1 : 0;
}

static Fraction half_minus(Fraction f) {
    Fraction out;
    if ((f.den & 1U) == 0) {
        out.num = f.den / 2 - f.num;
        out.den = f.den;
    } else {
        out.num = f.den - 2 * f.num;
        out.den = 2 * f.den;
    }
    return reduce(out);
}

static int frac_cmp_pair(Fraction a, Fraction b) {
    if (a.num < b.num) {
        return -1;
    }
    if (a.num > b.num) {
        return 1;
    }
    if (a.den < b.den) {
        return -1;
    }
    if (a.den > b.den) {
        return 1;
    }
    return 0;
}

static int cmp_fraction_qsort(const void *pa, const void *pb) {
    const Fraction *a = (const Fraction *)pa;
    const Fraction *b = (const Fraction *)pb;
    return frac_cmp_pair(*a, *b);
}

static void build_tail_sums(void) {
    int tail_len = num_candidates - split_index;
    size_t total = (size_t)1 << tail_len;
    Fraction *all = (Fraction *)malloc(total * sizeof(Fraction));
    if (all == NULL) {
        exit(1);
    }

    for (size_t mask = 0; mask < total; mask++) {
        Fraction cur = (Fraction){0, 1};
        for (int i = 0; i < tail_len; i++) {
            if (((mask >> i) & 1U) == 0U) {
                continue;
            }
            cur = add_fraction(cur, unit_fractions[split_index + i]);
        }
        all[mask] = cur;
    }

    qsort(all, total, sizeof(Fraction), cmp_fraction_qsort);

    tail_counts = (SumCount *)malloc(total * sizeof(SumCount));
    if (tail_counts == NULL) {
        free(all);
        exit(1);
    }

    tail_count_size = 0;
    for (size_t i = 0; i < total; ) {
        size_t j = i + 1;
        while (j < total && frac_cmp_pair(all[i], all[j]) == 0) {
            j++;
        }
        tail_counts[tail_count_size].f = all[i];
        tail_counts[tail_count_size].count = (uint32_t)(j - i);
        tail_count_size++;
        i = j;
    }

    free(all);
}

static uint64_t count_tail(Fraction need) {
    size_t lo = 0;
    size_t hi = tail_count_size;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        int cmp = frac_cmp_pair(tail_counts[mid].f, need);
        if (cmp < 0) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo < tail_count_size && frac_cmp_pair(tail_counts[lo].f, need) == 0) {
        return tail_counts[lo].count;
    }
    return 0;
}

static uint64_t dfs_first(int idx, Fraction current) {
    if (cmp_half(current) > 0) {
        return 0;
    }

    if (idx == split_index) {
        Fraction need = half_minus(current);
        return count_tail(need);
    }

    Fraction best_possible = add_fraction(current, remaining_total[idx]);
    if (cmp_half(best_possible) < 0) {
        return 0;
    }

    uint64_t result = dfs_first(idx + 1, current);
    Fraction with_current = add_fraction(current, unit_fractions[idx]);
    result += dfs_first(idx + 1, with_current);
    return result;
}

int main(void) {
    for (int i = 0; i < num_candidates; i++) {
        uint64_t n = (uint64_t)candidates[i];
        unit_fractions[i].num = 1;
        unit_fractions[i].den = (u128)n * (u128)n;
    }

    Fraction tail_all = (Fraction){0, 1};
    for (int i = split_index; i < num_candidates; i++) {
        tail_all = add_fraction(tail_all, unit_fractions[i]);
    }

    remaining_total[split_index] = tail_all;
    for (int i = split_index - 1; i >= 0; i--) {
        remaining_total[i] = add_fraction(remaining_total[i + 1], unit_fractions[i]);
    }

    build_tail_sums();
    uint64_t answer = dfs_first(0, (Fraction){0, 1});

    printf("%llu\n", (unsigned long long)answer);

    free(tail_counts);
    return 0;
}
