#include <stdio.h>
#include <stdlib.h>

size_t get_product(FILE*, size_t, size_t);

int main() {
    size_t position = 0, nDigits = 4, max_product = 0;
    FILE* fp = fopen("problem-008.txt", "rt");

    if (!fp) {
        perror("Unable to open file");
        return 1;
    }

    do {
        size_t product = get_product(fp, ftell(fp), nDigits);

        if (product > max_product) {
            max_product = product;
            position = ftell(fp) - 1;
        }
    } while (!feof(fp));

    printf("%ld\n", max_product);
    fseek(fp, position, SEEK_SET);

    fclose(fp);

    return 0;
}

size_t get_product(FILE* fp, size_t start_pos, size_t nDigits) {
    char ch = ' ', n = 0;
    size_t product = 1, count = 0;

    for (size_t index = 0; index < nDigits; index++, count++) {
        ch = getc(fp);

        if (ch < 0x30 || ch > 0x39) {
            if (ch == EOF) {
                return 0;
            }

            index--;

            continue;
        }

        n = ch - 0x30;

        if (n == 0) {
            return 0;
        }

        product *= n;
    }

    fseek(fp, -count + 1, SEEK_CUR);

    return product;
}
