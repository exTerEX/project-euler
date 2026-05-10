#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int main(void) {
    uint32_t limit = 1000000000;
    
    // Use array-based approach for efficiency
    // costs[x] = number of codes with cost x
    uint64_t costs[70];
    memset(costs, 0, sizeof(costs));
    
    // Initial codes: "0" with cost 1, "1" with cost 4
    costs[1] = 1;
    costs[4] = 1;
    uint64_t totalCost = 1 + 4;
    
    // Start with the lowest cost
    uint32_t current = 1;
    uint64_t remaining = limit - 2;
    
    while (remaining > 0) {
        // Find next non-empty cost level
        while (costs[current] == 0) {
            current++;
        }
        
        // Process all codes at this cost level (or as many as we need)
        uint64_t block = costs[current];
        if (block > remaining) {
            block = remaining;
        }
        
        // Generate children: append 0 (cost +1) and 1 (cost +4)
        remaining -= block;
        costs[current] -= block;
        costs[current + 1] += block;
        costs[current + 4] += block;
        
        // Add the cost of generating these children
        // Each child of cost c contributes (c+1) + (c+4) - c = c+5
        totalCost += block * (current + 5);
    }
    
    printf("%" PRIu64 "\n", totalCost);
    return 0;
}
