#include <bits/stdc++.h>
using namespace std;

inline bool canDefeat(int x1, int x2, int x3, int y1, int y2, int y3) {
    // Check all 6 possible assignments directly with early termination
    // Using individual parameters instead of vectors for better performance
    
    // Assignment 1: x1 vs y1, x2 vs y2, x3 vs y3
    if ((x1 > y1) + (x2 > y2) + (x3 > y3) >= 2) return true;
    
    // Assignment 2: x1 vs y1, x2 vs y3, x3 vs y2
    if ((x1 > y1) + (x2 > y3) + (x3 > y2) >= 2) return true;
    
    // Assignment 3: x1 vs y2, x2 vs y1, x3 vs y3
    if ((x1 > y2) + (x2 > y1) + (x3 > y3) >= 2) return true;
    
    // Assignment 4: x1 vs y2, x2 vs y3, x3 vs y1
    if ((x1 > y2) + (x2 > y3) + (x3 > y1) >= 2) return true;
    
    // Assignment 5: x1 vs y3, x2 vs y1, x3 vs y2
    if ((x1 > y3) + (x2 > y1) + (x3 > y2) >= 2) return true;
    
    // Assignment 6: x1 vs y3, x2 vs y2, x3 vs y1
    if ((x1 > y3) + (x2 > y2) + (x3 > y1) >= 2) return true;
    
    return false;
}

int possibleWinners(vector<int> boost_a, vector<int> boost_b, vector<int> boost_c) {
    int n = boost_a.size();
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        bool canDefeatAll = true;
        
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            
            if (!canDefeat(boost_a[i], boost_b[i], boost_c[i], 
                          boost_a[j], boost_b[j], boost_c[j])) {
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