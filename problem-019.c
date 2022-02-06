#include <stdio.h>

size_t get_days(short);
size_t is_leap_year(short);

int main() {
    size_t count_sundays = 0;
    const short start_year = 1901;
    const short end_year = 2000;

    size_t start_day = 2;

    for (size_t year = start_year; year <= end_year; year++) {
        size_t is_leap = is_leap_year(year);

        for (size_t month = 0; month < 12; month++) {
            if (year == end_year && month == 11) {
                continue;
            }

            size_t days = get_days(month);

            if (is_leap && month == 1) {
                days++;
            }

            start_day = ((days % 7) + start_day) % 7;

            if (start_day == 0) {
                count_sundays++;
            }
        }
    }

    printf("%ld\n", count_sundays);

    return 0;
}

size_t get_days(short month) {
    if (month == 1) {
        return 28;
    }
    else if (month <= 6) {
        if (month & 0x01)
            return 30;
        else {
            return 31;
        }
    }

    if (month & 0x01) {
        return 31;
    }

    return 30;
}

size_t is_leap_year(short year) {
    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
        return 1;
    }

    return 0;
}
