#include <bits/stdc++.h>
using namespace std;

bool canDefeat(vector<int> x, vector<int> y) {
    // Instead of generating all permutations, we'll check all possible matchups directly
    // There are 3! = 6 ways to assign x's boosters to y's boosters
    
    // Try all 6 possible matchups between x and y
    vector<vector<int>> assignments = {
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, 
        {1, 2, 0}, {2, 0, 1}, {2, 1, 0}
    };
    
    for (auto& assignment : assignments) {
        int xWins = 0;
        for (int i = 0; i < 3; i++) {
            if (x[i] > y[assignment[i]]) {
                xWins++;
            }
        }
        if (xWins >= 2) {
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