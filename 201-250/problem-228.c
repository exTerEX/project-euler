#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Minkowski sum of regular polygons S_1864 + S_1865 + ... + S_1909.
 * The Minkowski sum of convex polygons has sides corresponding to the
 * sorted union of all edge normal directions.
 * S_n has n edges with normals at angles 2*pi*k/n for k=0..n-1.
 * Total sides = number of distinct fractions k/n (mod 1) in lowest terms
 * for n in [1864, 1909], k in [0, n-1].
 * Equivalently: count fractions p/q in [0,1) with gcd(p,q)=1 where q | n
 * for some n in [1864, 1909], i.e., q divides at least one n in range. */

typedef struct {
    int64_t num, den;
} Frac;

static int frac_cmp(const void *a, const void *b) {
    const Frac *fa = (const Frac *)a;
    const Frac *fb = (const Frac *)b;
    /* compare a/b vs c/d: a*d vs c*b */
    int64_t lhs = fa->num * fb->den;
    int64_t rhs = fb->num * fa->den;
    if (lhs < rhs) return -1;
    if (lhs > rhs) return 1;
    return 0;
}

static int64_t gcd(int64_t a, int64_t b) {
    while (b) { int64_t t = b; b = a % b; a = t; }
    return a;
}

int main(void) {
    /* Collect all distinct fractions k/n for n in [1864,1909], k in [0,n-1]
     * represented in lowest terms. Max total fractions: sum of n from 1864 to 1909
     * = 46 * (1864+1909)/2 = 46 * 1886.5 = 86779. */
    int count = 0;
    int max_fracs = 100000;
    Frac *fracs = malloc((size_t)max_fracs * sizeof(Frac));

    for (int n = 1864; n <= 1909; n++) {
        for (int k = 0; k < n; k++) {
            int64_t g = gcd(k == 0 ? n : k, n); /* gcd(k,n) but handle k=0 */
            if (k == 0) {
                fracs[count].num = 0;
                fracs[count].den = 1;
            } else {
                fracs[count].num = k / g;
                fracs[count].den = n / g;
            }
            count++;
        }
    }

    /* Sort and count distinct */
    qsort(fracs, (size_t)count, sizeof(Frac), frac_cmp);

    int distinct = 0;
    for (int i = 0; i < count; i++) {
        if (i == 0 || fracs[i].num != fracs[i-1].num || fracs[i].den != fracs[i-1].den) {
            distinct++;
        }
    }

    printf("%d\n", distinct);
    free(fracs);
    return 0;
}
