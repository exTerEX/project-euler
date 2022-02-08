#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME_LEN 20

void sort(uint8_t[][MAX_NAME_LEN], uint32_t);

int main() {
    uint8_t names[5200][MAX_NAME_LEN];

    FILE* fp = fopen("problem-022.txt", "rt");

    if (!fp) { perror("Unable to open file"); return 1; }

    uint64_t count = 0;

    do {
        uint32_t ret = fscanf(fp, "\"%[^\",]\",", names[count++]);

        if (ret <= 0) { continue; }
    } while (!feof(fp));

    fclose(fp);

    sort(names, count);

    uint64_t sum_score = 0;

    for (uint32_t i = 0; i < count; i++) {
        uint64_t score = 0;

        for (uint32_t j = 0; names[i][j] != '\0'; j++) {
            score += names[i][j] - 'A' + 1;
        }

        sum_score += score * (i + 1);
    }

    printf("%lu\n", sum_score);

    return 0;
}

void sort(uint8_t data[][MAX_NAME_LEN], uint32_t length) {
    // Ciura gap sequence
    const uint32_t gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };

    for (uint32_t i = 0; i < 8; i++) {
        uint32_t gap = gaps[i];

        for (uint32_t j = gap; j < length; j++) {
            uint8_t buffer[MAX_NAME_LEN];
            strcpy(buffer, data[j]);

            uint32_t k;

            for (k = j; k >= gap && strcmp(data[k - gap], buffer) > 0; k -= gap) {
                strcpy(data[k], data[k - gap]);
            }

            strcpy(data[k], buffer);
        }
    }
}
