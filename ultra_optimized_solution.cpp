#include <bits/stdc++.h>
using namespace std;

bool canDefeat(vector<int> x, vector<int> y) {
    // Sort both arrays to make comparisons easier
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    
    // Check all possible ways X can win >= 2 rounds
    // We'll check if X can win 2 or 3 rounds
    
    // Method: For each booster of X, count how many boosters of Y it can beat
    // Then use this to determine if X can win >= 2 rounds
    
    int beats[3] = {0, 0, 0}; // beats[i] = number of Y's boosters that X[i] can beat
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (x[i] > y[j]) {
                beats[i]++;
            }
        }
    }
    
    // Now we need to check if we can assign X's boosters to Y's boosters
    // such that X wins >= 2 rounds
    
    // Try all possible assignments using bitmask
    for (int mask = 0; mask < (1 << 3); mask++) {
        if (__builtin_popcount(mask) != 3) continue; // We need exactly 3 assignments
        
        // This represents which Y boosters are used
        vector<bool> used(3, false);
        vector<int> assignment(3, -1);
        
        bool valid = true;
        int bit = 0;
        
        for (int i = 0; i < 3; i++) {
            while (bit < 3 && used[bit]) bit++;
            if (bit >= 3) {
                valid = false;
                break;
            }
            assignment[i] = bit;
            used[bit] = true;
            bit++;
        }
        
        if (!valid) continue;
        
        int wins = 0;
        for (int i = 0; i < 3; i++) {
            if (x[i] > y[assignment[i]]) {
                wins++;
            }
        }
        
        if (wins >= 2) {
            return true;
        }
    }
    
    return false;
}

int possibleWinners(vector<int> boost_a, vector<int> boost_b, vector<int> boost_c) {
    int n = boost_a.size();
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        bool canDefeatAll = true;
        vector<int> playerI = {boost_a[i], boost_b[i], boost_c[i]};
        
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            vector<int> playerJ = {boost_a[j], boost_b[j], boost_c[j]};
            
            if (!canDefeat(playerI, playerJ)) {
                canDefeatAll = false;
                break;
            }
        }
        
        if (canDefeatAll) {
            count++;
        }
    }
    
    return count;
}