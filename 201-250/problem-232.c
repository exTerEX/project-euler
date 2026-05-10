#include <stdio.h>
#include <string.h>

#define MAX_SCORE 100

// Cache for memoization
static double cache[MAX_SCORE + 1][MAX_SCORE + 1];
static int cached[MAX_SCORE + 1][MAX_SCORE + 1];

// Probability player 1 wins one turn (50% chance of heads)
#define WIN1  0.5
#define LOSE1 0.5

// Return probability that player 2 wins given current score needs
double twoWins(int needOne, int needTwo) {
    // Player 2 won
    if (needTwo <= 0) return 1.0;
    // Player 1 won
    if (needOne <= 0) return 0.0;
    
    // Check cache
    if (cached[needOne][needTwo]) {
        return cache[needOne][needTwo];
    }
    
    double best = 0.0;
    
    // Try different bet amounts (T tosses for player 2)
    for (int bet = 1; bet <= 32; bet++) {
        double win2 = 1.0 / (1 << bet);  // Probability of all heads: 1/2^bet
        double lose2 = 1.0 - win2;
        
        // Points for player 2 if she wins her turn
        int scoreTwo = (bet == 0) ? 0 : (1 << (bet - 1));  // 2^(bet-1)
        int nextNeedTwo = needTwo - scoreTwo;
        if (nextNeedTwo < 0) nextNeedTwo = 0;
        
        // Case 1: Player 2 wins her turn AND player 1 wins his turn
        double prob1 = win2 * WIN1;
        double contrib1 = prob1 * twoWins(needOne - 1, nextNeedTwo);
        
        // Case 2: Player 2 wins her turn AND player 1 loses his turn
        double prob2 = win2 * LOSE1;
        double contrib2 = prob2 * twoWins(needOne, nextNeedTwo);
        
        // Case 3: Player 2 loses her turn AND player 1 wins his turn
        double prob3 = lose2 * WIN1;
        double contrib3 = prob3 * twoWins(needOne - 1, needTwo);
        
        // Case 4: Both lose (nothing changes) - probability lose2 * LOSE1
        // This creates a recurrence we need to solve
        double probBothLose = lose2 * LOSE1;
        
        // Solving: current = contrib1 + contrib2 + contrib3 + probBothLose * current
        // current * (1 - probBothLose) = contrib1 + contrib2 + contrib3
        // current = (contrib1 + contrib2 + contrib3) / (1 - probBothLose)
        
        double numerator = contrib1 + contrib2 + contrib3;
        double denominator = 1.0 - probBothLose;
        
        if (denominator < 1e-10) {
            // Both players keep losing infinitely - shouldn't happen
            continue;
        }
        
        double current = numerator / denominator;
        
        // Update best choice for player 2
        if (current > best) {
            best = current;
        }
        
        // Stop if we've checked enough bets (optimization)
        if (bet > 8 && nextNeedTwo == 0) break;
    }
    
    cached[needOne][needTwo] = 1;
    cache[needOne][needTwo] = best;
    return best;
}

int main(void) {
    // Initialize cache
    memset(cached, 0, sizeof(cached));
    
    // Player 1 goes first
    // Case 1: Player 1 gets heads (scores 1)
    double prob1 = 0.5 * twoWins(MAX_SCORE - 1, MAX_SCORE);
    
    // Case 2: Player 1 gets tails (scores 0)
    double prob2 = 0.5 * twoWins(MAX_SCORE, MAX_SCORE);
    
    double result = prob1 + prob2;
    
    printf("%.8f\n", result);
    return 0;
}
