#include <bits/stdc++.h>
using namespace std;

bool canDefeat(vector<int> x, vector<int> y) {
    // Generate all permutations of x
    vector<vector<int>> permX;
    sort(x.begin(), x.end());
    do {
        permX.push_back(x);
    } while(next_permutation(x.begin(), x.end()));
    
    // Generate all permutations of y
    vector<vector<int>> permY;
    sort(y.begin(), y.end());
    do {
        permY.push_back(y);
    } while(next_permutation(y.begin(), y.end()));
    
    // For each permutation of x, check if there exists a permutation of y where x wins >= 2 rounds
    for(auto& px : permX) {
        for(auto& py : permY) {
            int xWins = 0;
            for(int i = 0; i < 3; i++) {
                if(px[i] > py[i]) xWins++;
            }
            if(xWins >= 2) {
                return true; // X can defeat Y
            }
        }
    }
    return false;
}

int possibleWinners(vector<int> boost_a, vector<int> boost_b, vector<int> boost_c) {
    int n = boost_a.size();
    int count = 0;
    
    for(int i = 0; i < n; i++) {
        bool canDefeatAll = true;
        vector<int> playerI = {boost_a[i], boost_b[i], boost_c[i]};
        
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            vector<int> playerJ = {boost_a[j], boost_b[j], boost_c[j]};
            
            if(!canDefeat(playerI, playerJ)) {
                canDefeatAll = false;
                break;
            }
        }
        
        if(canDefeatAll) {
            count++;
        }
    }
    
    return count;
}