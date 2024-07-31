#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define FILENAME "problem-079.txt"
#define LEN 10

int32_t index_score_max(int8_t* scores, int8_t* occurrences) {
    int32_t index = -1;
    float max_scores = 0.0;

    for (int32_t i = 0; i < LEN; ++i) {
        if (occurrences[i] == 0) { continue; }

        if ((float)scores[i] / occurrences[i] > max_scores) {
            index = i;
            max_scores = (float)scores[i] / occurrences[i];
        }
    }

    if (index != -1) { scores[index] = -1; }

    return index;
}

int main() {
    FILE* fp;
    if ((fp = fopen(FILENAME, "r")) == NULL) {
        printf("ERROR: can't open %s\n", FILENAME);
        exit(1);
    }

    int32_t val;
    int8_t scores[LEN] = { 0 }, occurrences[LEN] = { 0 };

    while (fscanf(fp, "%d", &val) != EOF) {
        scores[val / 100] += 3;
        ++occurrences[val / 100];

        scores[val % 100 / 10] += 2;
        ++occurrences[val % 100 / 10];

        scores[val % 10] += 1;
        ++occurrences[val % 10];
    }

    int32_t answer = 0;
    while ((val = index_score_max(scores, occurrences)) != -1) {
        answer = answer * 10 + val;
    }

    printf("%d\n", answer);
    return 0;
}
