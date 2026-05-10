#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x1, y1, x2, y2;
} Segment;

typedef struct {
    int64_t xn, xd;
    int64_t yn, yd;
} Point;

static int64_t abs64(int64_t x) {
    return (x < 0) ? -x : x;
}

static int64_t gcd64(int64_t a, int64_t b) {
    a = abs64(a);
    b = abs64(b);
    while (b != 0) {
        int64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static int cmp_point(const void *pa, const void *pb) {
    const Point *a = (const Point *)pa;
    const Point *b = (const Point *)pb;
    if (a->xn != b->xn) {
        return (a->xn < b->xn) ? -1 : 1;
    }
    if (a->xd != b->xd) {
        return (a->xd < b->xd) ? -1 : 1;
    }
    if (a->yn != b->yn) {
        return (a->yn < b->yn) ? -1 : 1;
    }
    if (a->yd != b->yd) {
        return (a->yd < b->yd) ? -1 : 1;
    }
    return 0;
}

int main(void) {
    Segment segments[5000];

    int64_t s = 290797;
    int t[20000];
    for (int i = 0; i < 20000; i++) {
        s = (s * s) % 50515093;
        t[i] = (int)(s % 500);
    }
    for (int i = 0; i < 5000; i++) {
        segments[i].x1 = t[4 * i];
        segments[i].y1 = t[4 * i + 1];
        segments[i].x2 = t[4 * i + 2];
        segments[i].y2 = t[4 * i + 3];
    }

    size_t cap = 3500000;
    size_t used = 0;
    Point *pts = (Point *)malloc(cap * sizeof(Point));
    if (pts == NULL) {
        return 1;
    }

    for (int i = 0; i < 5000; i++) {
        int64_t px = segments[i].x1;
        int64_t py = segments[i].y1;
        int64_t rx = segments[i].x2 - segments[i].x1;
        int64_t ry = segments[i].y2 - segments[i].y1;

        for (int j = i + 1; j < 5000; j++) {
            int64_t qx = segments[j].x1;
            int64_t qy = segments[j].y1;
            int64_t sx = segments[j].x2 - segments[j].x1;
            int64_t sy = segments[j].y2 - segments[j].y1;

            int64_t den = rx * sy - ry * sx;
            if (den == 0) {
                continue;
            }

            int64_t dx = qx - px;
            int64_t dy = qy - py;
            int64_t tnum = dx * sy - dy * sx;
            int64_t unum = dx * ry - dy * rx;

            if (den < 0) {
                den = -den;
                tnum = -tnum;
                unum = -unum;
            }

            if (!(tnum > 0 && tnum < den && unum > 0 && unum < den)) {
                continue;
            }

            int64_t xnum = px * den + rx * tnum;
            int64_t ynum = py * den + ry * tnum;

            int64_t gx = gcd64(xnum, den);
            int64_t gy = gcd64(ynum, den);

            if (used == cap) {
                size_t new_cap = cap * 2;
                Point *p = (Point *)realloc(pts, new_cap * sizeof(Point));
                if (p == NULL) {
                    free(pts);
                    return 1;
                }
                pts = p;
                cap = new_cap;
            }

            pts[used].xn = xnum / gx;
            pts[used].xd = den / gx;
            pts[used].yn = ynum / gy;
            pts[used].yd = den / gy;
            used++;
        }
    }

    qsort(pts, used, sizeof(Point), cmp_point);

    size_t distinct = 0;
    for (size_t i = 0; i < used; i++) {
        if (i == 0 || cmp_point(&pts[i], &pts[i - 1]) != 0) {
            distinct++;
        }
    }

    printf("%zu\n", distinct);
    free(pts);
    return 0;
}
