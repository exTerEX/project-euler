#include <stdint.h>
#include <stdio.h>

static uint32_t count_single(uint32_t digit, uint64_t value) {
    uint32_t result = 0;
    if (value == 0 && digit == 0) {
        return 1;
    }
    while (value > 0) {
        if (value % 10ULL == digit) {
            result++;
        }
        value /= 10ULL;
    }
    return result;
}

static uint64_t count_digit(uint32_t digit, uint64_t value) {
    if (value < 10ULL) {
        return (value < digit) ? 0ULL : 1ULL;
    }

    uint64_t shift = 1;
    uint64_t multiplier = 0;
    while (shift * 10ULL <= value) {
        shift *= 10ULL;
        multiplier++;
    }
    multiplier *= shift / 10ULL;

    uint64_t first = value / shift;
    uint64_t remainder = value % shift;

    uint64_t result = first * multiplier;
    result += count_digit(digit, remainder);

    if (digit == first) {
        result += remainder + 1ULL;
    }
    if (digit < first && digit > 0) {
        result += shift;
    }

    return result;
}

static uint64_t find_all(uint32_t digit, uint64_t from, uint64_t to) {
    uint64_t center = (from + to) / 2ULL;
    if (from == center) {
        return (count_digit(digit, from) == from) ? from : 0ULL;
    }

    uint64_t result = 0;
    uint64_t count_from = count_digit(digit, from);

    while (count_from == from && from < to) {
        result += from;
        from++;
        count_from += count_single(digit, from);
    }
    if (from >= to + 1ULL) {
        return result;
    }

    center = (from + to) / 2ULL;
    uint64_t count_center = count_digit(digit, center);
    uint64_t count_to = count_digit(digit, to);

    if (count_center >= from && center >= count_from && center > from) {
        result += find_all(digit, from, center);
    }
    if (count_to >= center && to >= count_center && center < to) {
        result += find_all(digit, center, to);
    }

    return result;
}

int main(void) {
    const uint64_t limit = 1000000000000ULL;

    uint64_t sum = 0;
    for (uint32_t digit = 1; digit <= 9; digit++) {
        sum += find_all(digit, 0ULL, limit);
    }

    printf("%llu\n", (unsigned long long)sum);
    return 0;
}
