#include <stdio.h>
#include <stdlib.h>

typedef struct big_int {
    char data;
    struct big_int* next;
    struct big_int* prev;
} big_int_t;

big_int_t* add_digit(big_int_t*, char);
void remove_digits(big_int_t*, int);

int main() {
    u_int32_t n = 100;
    big_int_t* ptr = add_digit(NULL, 1);
    const big_int_t* ptr0 = ptr;
    u_int64_t sum_digits = 0;

    for (u_int32_t index = 1; index <= n; index++) {
        int carry = 0;
        ptr = (big_int_t*)ptr0;

        while (ptr) {
            u_int32_t temp = ptr->data * index + carry;

            if (temp >= 10) {
                carry = div(temp, 10).quot;
                temp = div(temp, 10).rem;
            }
            else {
                carry = 0;
            }

            if (carry > 0 && ptr->next == NULL) {
                add_digit(ptr, 0);
            }

            ptr->data = temp;

            if (index == n) {
                sum_digits += temp;
            }

            if (ptr->next) {
                ptr = ptr->next;
            }
            else {
                break;
            }
        }
    }

    printf("%lu\n", sum_digits);

    remove_digits((big_int_t*)ptr0, -1);

    return 0;
}

big_int_t* add_digit(big_int_t* digit, char value) {
    if (digit == NULL) {
        digit = (big_int_t*)malloc(sizeof(big_int_t));

        if (!digit) {
            perror("Unable to allocate memory!");
            return NULL;
        }

        digit->data = value;
        digit->next = NULL;
        digit->prev = NULL;

        return digit;
    }

    if (digit->next) {
        digit->next->data = value;

        return digit->next;
    }

    digit->next = (big_int_t*)malloc(sizeof(big_int_t));

    if (digit->next == NULL) {
        perror("Unable to allocate memory!");
        return NULL;
    }

    digit->next->data = value;
    digit->next->next = NULL;
    digit->next->prev = digit;

    return digit->next;
}

void remove_digits(big_int_t* digit, int n) {
    if (digit == NULL) {
        return;
    }

    if (digit->next == NULL) {
        free(digit);
        digit = NULL;
        return;
    }

    if (n > 0) {
        return;
    }

    return;
}
