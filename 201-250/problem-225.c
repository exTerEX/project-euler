#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    const uint32_t target_index = 124;
    const uint32_t max_steps = 22710;
    uint32_t current = 1;
    uint32_t found = 0;

    while (found < target_index) {
        current += 2;

        uint32_t tri1 = 1;
        uint32_t tri2 = 1;
        uint32_t tri3 = 1;
        bool is_divisor = false;

        for (uint32_t step = 0; step <= max_steps; ++step) {
            uint32_t next = (tri1 + tri2 + tri3) % current;
            if (next == 0) {
                is_divisor = true;
                break;
            }

            tri1 = tri2;
            tri2 = tri3;
            tri3 = next;
            if (tri1 == 1 && tri2 == 1 && tri3 == 1) {
                break;
            }
        }

        if (!is_divisor) {
            found++;
        }
    }

    printf("%u\n", current);
    return 0;
}