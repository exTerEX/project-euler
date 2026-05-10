#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double side;
    uint32_t left;
    uint32_t below;
} Square;

typedef struct {
    Square *data;
    size_t size;
    size_t capacity;
} Heap;

static double side_length(double x, double y) {
    double diff = x - y;
    return 0.5 * (sqrt(diff * diff + 4.0) - x - y);
}

static void swap_squares(Square *a, Square *b) {
    Square temp = *a;
    *a = *b;
    *b = temp;
}

static void push_heap(Heap *heap, Square square) {
    if (heap->size == heap->capacity) {
        size_t new_capacity = heap->capacity == 0 ? 16 : heap->capacity * 2;
        Square *new_data = realloc(heap->data, new_capacity * sizeof(Square));
        if (new_data == NULL) {
            exit(1);
        }
        heap->data = new_data;
        heap->capacity = new_capacity;
    }

    size_t index = heap->size++;
    heap->data[index] = square;
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent].side >= heap->data[index].side) {
            break;
        }
        swap_squares(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

static Square pop_heap(Heap *heap) {
    Square result = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    size_t index = 0;
    while (1) {
        size_t left = 2 * index + 1;
        size_t right = left + 1;
        size_t largest = index;

        if (left < heap->size && heap->data[left].side > heap->data[largest].side) {
            largest = left;
        }
        if (right < heap->size && heap->data[right].side > heap->data[largest].side) {
            largest = right;
        }
        if (largest == index) {
            break;
        }

        swap_squares(&heap->data[index], &heap->data[largest]);
        index = largest;
    }

    return result;
}

int main(void) {
    const uint32_t target_left = 3;
    const uint32_t target_below = 3;
    uint32_t result = 0;
    uint32_t candidates = 1;

    Heap heap = {0};
    push_heap(&heap, (Square){1.0, 0.0, side_length(1.0, 0.0), 0, 0});

    while (candidates > 0) {
        Square current = pop_heap(&heap);
        result++;

        Square top = {
            current.x,
            current.y + current.side,
            side_length(current.x, current.y + current.side),
            current.left,
            current.below + 1,
        };
        Square right = {
            current.x + current.side,
            current.y,
            side_length(current.x + current.side, current.y),
            current.left + 1,
            current.below,
        };

        push_heap(&heap, top);
        push_heap(&heap, right);

        if (top.left <= target_left && top.below <= target_below) {
            candidates++;
        }
        if (right.left <= target_left && right.below <= target_below) {
            candidates++;
        }
        if (current.left <= target_left && current.below <= target_below) {
            candidates--;
        }
    }

    printf("%u\n", result);
    free(heap.data);
    return 0;
}