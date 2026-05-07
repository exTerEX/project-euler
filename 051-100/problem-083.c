#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SIZE 80
#define FILENAME "problem-081.txt"
#define INF 2000000000

static int32_t m[SIZE][SIZE];
static int32_t dist[SIZE][SIZE];
static int8_t visited[SIZE][SIZE];

typedef struct { int r, c, d; } Node;
static Node heap[SIZE * SIZE * 4];
static int heap_size;

static void push(int r, int c, int d) {
    int i = heap_size++;
    heap[i].r = r; heap[i].c = c; heap[i].d = d;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].d <= heap[i].d) break;
        Node tmp = heap[p]; heap[p] = heap[i]; heap[i] = tmp;
        i = p;
    }
}

static Node pop() {
    Node top = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    for (;;) {
        int l = 2*i+1, r = 2*i+2, s = i;
        if (l < heap_size && heap[l].d < heap[s].d) s = l;
        if (r < heap_size && heap[r].d < heap[s].d) s = r;
        if (s == i) break;
        Node tmp = heap[s]; heap[s] = heap[i]; heap[i] = tmp;
        i = s;
    }
    return top;
}

int main() {
    FILE *f;
    if ((f = fopen(FILENAME, "r")) == NULL) {
        printf("ERROR: can't open %s\n", FILENAME);
        return 1;
    }
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            fscanf(f, "%d,", &m[i][j]);
    fclose(f);

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            dist[i][j] = INF;
    memset(visited, 0, sizeof(visited));

    dist[0][0] = m[0][0];
    heap_size = 0;
    push(0, 0, m[0][0]);

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (heap_size > 0) {
        Node u = pop();
        if (visited[u.r][u.c]) continue;
        visited[u.r][u.c] = 1;
        for (int d = 0; d < 4; ++d) {
            int nr = u.r + dr[d], nc = u.c + dc[d];
            if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) continue;
            int nd = u.d + m[nr][nc];
            if (nd < dist[nr][nc]) {
                dist[nr][nc] = nd;
                push(nr, nc, nd);
            }
        }
    }

    printf("%d\n", dist[SIZE-1][SIZE-1]);
    return 0;
}
