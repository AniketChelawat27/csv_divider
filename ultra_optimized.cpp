#include <bits/stdc++.h>
using namespace std;

/*
 * ULTRA-OPTIMIZED O(n²) Solution
 * 
 * This is the fastest possible O(n²) implementation:
 * - Minimal function calls
 * - Cache-friendly memory access
 * - Compiler optimizations
 * - Reduced branching
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    const int n = requests.size();
    long count = 0;
    
    for (int i = 0; i < n; ++i) {
        int less = 0, equal = 0;
        
        for (int j = i; j < n; ++j) {
            // Branchless counting
            const int val = requests[j];
            less += (val < mid);
            equal += (val == mid);
            
            // Quick median position calculation
            const int len = j - i + 1;
            const int med_pos = (len % 2 == 1) ? (len >> 1) : ((len >> 1) - 1);
            
            // Check median condition with minimal branching
            count += (equal > 0) & (less <= med_pos) & ((less + equal) > med_pos);
        }
    }
    
    return count;
}

// Alternative approach: Early termination optimizations
long getSubarrayMedianFast(int mid, vector<int> requests) {
    const int n = requests.size();
    long count = 0;
    
    // Pre-compute positions of mid elements for potential early termination
    vector<int> mid_pos;
    for (int i = 0; i < n; ++i) {
        if (requests[i] == mid) {
            mid_pos.push_back(i);
        }
    }
    
    if (mid_pos.empty()) return 0;
    
    for (int i = 0; i < n; ++i) {
        int less = 0, equal = 0;
        
        for (int j = i; j < n; ++j) {
            if (requests[j] < mid) less++;
            else if (requests[j] == mid) equal++;
            
            if (equal > 0) {
                const int len = j - i + 1;
                const int med_pos = (len & 1) ? (len >> 1) : ((len >> 1) - 1);
                
                if (less <= med_pos && (less + equal) > med_pos) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

int main() {
    // Test ultra-optimized version
    cout << getSubarrayMedian(3, {3, 1, 5}) << "\n";
    cout << getSubarrayMedian(3, {1, 4}) << "\n"; 
    cout << getSubarrayMedian(2, {1, 2, 3}) << "\n";
    
    return 0;
}