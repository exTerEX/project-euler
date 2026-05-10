#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int v;
    int gap;
    uint64_t second_even;
    uint8_t *bits;
    size_t bits_len;
    uint64_t *prefix;
    size_t prefix_len;
    uint64_t cycle_t_start;
    uint64_t cycle_t_end;
    uint64_t cycle_len;
    uint64_t ones_before_cycle;
    uint64_t ones_per_cycle;
    uint64_t *cycle_prefix;
    size_t cycle_prefix_len;
    uint64_t odd_before_second_even;
    uint64_t second_even_index;
} UlamCycle;

static uint64_t brute_kth_ulam(uint64_t a, uint64_t b, size_t k) {
    uint64_t seq[4096];
    size_t len = 0;
    seq[len++] = a;
    if (k == 1) {
        return a;
    }
    seq[len++] = b;

    while (len < k) {
        uint64_t cand = seq[len - 1] + 1;
        for (;;) {
            int ways = 0;
            for (size_t i = 0; i < len; i++) {
                for (size_t j = i + 1; j < len; j++) {
                    if (seq[i] + seq[j] == cand) {
                        ways++;
                        if (ways > 1) {
                            break;
                        }
                    }
                }
                if (ways > 1) {
                    break;
                }
            }
            if (ways == 1) {
                break;
            }
            cand++;
        }
        seq[len++] = cand;
    }

    return seq[k - 1];
}

static int seq_contains(const uint64_t *seq, size_t len, uint64_t value) {
    for (size_t i = 0; i < len; i++) {
        if (seq[i] == value) {
            return 1;
        }
    }
    return 0;
}

static void build_seed_sequence(int v, uint64_t min_last, uint64_t *seq, size_t *len_out) {
    size_t len = 0;
    seq[len++] = 2;
    seq[len++] = (uint64_t)v;

    while (seq[len - 1] < min_last) {
        uint64_t cand = seq[len - 1] + 1;
        for (;;) {
            int ways = 0;
            for (size_t i = 0; i < len; i++) {
                for (size_t j = i + 1; j < len; j++) {
                    if (seq[i] + seq[j] == cand) {
                        ways++;
                        if (ways > 1) {
                            break;
                        }
                    }
                }
                if (ways > 1) {
                    break;
                }
            }
            if (ways == 1) {
                break;
            }
            cand++;
        }
        seq[len++] = cand;
    }

    *len_out = len;
}

static void init_ulam_cycle(UlamCycle *uc, int v) {
    memset(uc, 0, sizeof(*uc));
    uc->v = v;
    uc->gap = v + 1;
    uc->second_even = 2ULL * (uint64_t)uc->gap;

    uint64_t seed[2048];
    size_t seed_len = 0;
    build_seed_sequence(v, 2ULL * (uint64_t)uc->gap + 1ULL, seed, &seed_len);

    uint32_t states = 1U << (uint32_t)uc->gap;
    size_t max_bits = (size_t)uc->gap + (size_t)states + 8U;

    uc->bits_len = (size_t)uc->gap;
    uc->bits = (uint8_t *)malloc(max_bits * sizeof(uint8_t));
    if (uc->bits == NULL) {
        exit(1);
    }

    for (int t = 0; t < uc->gap; t++) {
        uint64_t odd = 2ULL * (uint64_t)t + 1ULL;
        uc->bits[t] = seq_contains(seed, seed_len, odd) ? 1U : 0U;
    }

    uc->prefix_len = max_bits + 1U;
    uc->prefix = (uint64_t *)malloc(uc->prefix_len * sizeof(uint64_t));
    if (uc->prefix == NULL) {
        exit(1);
    }
    uc->prefix[0] = 0;
    for (size_t i = 0; i < uc->bits_len; i++) {
        uc->prefix[i + 1] = uc->prefix[i] + (uint64_t)uc->bits[i];
    }

    int *seen = (int *)malloc(states * sizeof(int));
    if (seen == NULL) {
        exit(1);
    }
    for (uint32_t i = 0; i < states; i++) {
        seen[i] = -1;
    }

    uint32_t state = 0;
    for (int i = 0; i < uc->gap; i++) {
        state = (state << 1U) | (uint32_t)uc->bits[i];
    }
    seen[state] = 0;

    uint32_t lower_mask = (uc->gap == 1) ? 0U : ((1U << (uint32_t)(uc->gap - 1)) - 1U);
    int step = 0;
    int cycle_start_step = -1;
    int cycle_end_step = -1;

    for (;;) {
        uint32_t oldest = (state >> (uint32_t)(uc->gap - 1)) & 1U;
        uint32_t newest = state & 1U;
        uint8_t next_bit = (uint8_t)(oldest ^ newest);

        uc->bits[uc->bits_len++] = next_bit;
        uc->prefix[uc->bits_len] = uc->prefix[uc->bits_len - 1] + (uint64_t)next_bit;

        state = ((state & lower_mask) << 1U) | (uint32_t)next_bit;
        step++;

        if (seen[state] >= 0) {
            cycle_start_step = seen[state];
            cycle_end_step = step;
            break;
        }
        seen[state] = step;
    }

    uc->cycle_t_start = (uint64_t)(uc->gap - 1 + cycle_start_step);
    uc->cycle_t_end = (uint64_t)(uc->gap - 1 + cycle_end_step);
    uc->cycle_len = uc->cycle_t_end - uc->cycle_t_start;

    uc->ones_before_cycle = uc->prefix[uc->cycle_t_start + 1ULL];
    uc->ones_per_cycle = uc->prefix[uc->cycle_t_end + 1ULL] - uc->ones_before_cycle;

    uc->cycle_prefix_len = (size_t)uc->cycle_len + 1;
    uc->cycle_prefix = (uint64_t *)calloc(uc->cycle_prefix_len, sizeof(uint64_t));
    if (uc->cycle_prefix == NULL) {
        exit(1);
    }

    for (uint64_t i = 0; i < uc->cycle_len; i++) {
        uint64_t t = uc->cycle_t_start + 1ULL + i;
        uc->cycle_prefix[i + 1ULL] = uc->cycle_prefix[i] + (uint64_t)uc->bits[t];
    }

    uc->odd_before_second_even = uc->prefix[(size_t)uc->gap];
    uc->second_even_index = 2ULL + uc->odd_before_second_even;

    free(seen);
}

static uint64_t odd_term_by_rank(const UlamCycle *uc, uint64_t odd_rank) {
    uint64_t t = 0;

    if (odd_rank <= uc->ones_before_cycle) {
        size_t lo = 1;
        size_t hi = (size_t)(uc->cycle_t_start + 1ULL);
        while (lo < hi) {
            size_t mid = lo + (hi - lo) / 2;
            if (uc->prefix[mid] >= odd_rank) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        t = (uint64_t)lo - 1ULL;
    } else {
        uint64_t rem = odd_rank - uc->ones_before_cycle;
        uint64_t full = (rem - 1ULL) / uc->ones_per_cycle;
        uint64_t rem_inside = rem - full * uc->ones_per_cycle;

        size_t lo = 1;
        size_t hi = uc->cycle_prefix_len - 1;
        while (lo < hi) {
            size_t mid = lo + (hi - lo) / 2;
            if (uc->cycle_prefix[mid] >= rem_inside) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        t = uc->cycle_t_start + full * uc->cycle_len + (uint64_t)lo;
    }

    return 2ULL * t + 1ULL;
}

static uint64_t kth_term(const UlamCycle *uc, uint64_t k) {
    if (k == 1ULL) {
        return 2ULL;
    }
    if (k == uc->second_even_index) {
        return uc->second_even;
    }
    if (k < uc->second_even_index) {
        return odd_term_by_rank(uc, k - 1ULL);
    }
    return odd_term_by_rank(uc, k - 2ULL);
}

static void free_ulam_cycle(UlamCycle *uc) {
    free(uc->bits);
    free(uc->prefix);
    free(uc->cycle_prefix);
    memset(uc, 0, sizeof(*uc));
}

int main(void) {
    const uint64_t k = 100000000000ULL;
    uint64_t sum = 0;

    for (int n = 2; n <= 10; n++) {
        int v = 2 * n + 1;
        UlamCycle uc;
        init_ulam_cycle(&uc, v);

        for (uint64_t t = 1; t <= 200; t += 17) {
            uint64_t fast = kth_term(&uc, t);
            uint64_t slow = brute_kth_ulam(2ULL, (uint64_t)v, (size_t)t);
            if (fast != slow) {
                free_ulam_cycle(&uc);
                return 1;
            }
        }

        sum += kth_term(&uc, k);
        free_ulam_cycle(&uc);
    }

    printf("%llu\n", (unsigned long long)sum);
    return 0;
}
