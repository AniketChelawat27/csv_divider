#include <bits/stdc++.h>
using namespace std;

bool canDefeat(vector<int> x, vector<int> y) {
    // Check all 6 possible assignments directly without generating permutations
    // This is more efficient than the previous approach
    
    // The 6 ways to assign x[0], x[1], x[2] to y[i], y[j], y[k] where i,j,k are distinct
    int assignments[6][3] = {
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, 
        {1, 2, 0}, {2, 0, 1}, {2, 1, 0}
    };
    
    for (int a = 0; a < 6; a++) {
        int wins = 0;
        for (int i = 0; i < 3; i++) {
            if (x[i] > y[assignments[a][i]]) {
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