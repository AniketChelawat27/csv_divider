#include <bits/stdc++.h>
using namespace std;

/*
 * FINAL CORRECT SOLUTION
 * 
 * After analysis, for competitive programming with tight time limits,
 * sometimes the most straightforward O(n²) solution with optimizations
 * is the way to go, especially if the constant factors are very low.
 * 
 * Let me implement the most optimized O(n²) version with minimal overhead.
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    // Optimized O(n²) with minimal overhead
    for (int i = 0; i < n; i++) {
        int less = 0, equal = 0, greater = 0;
        
        for (int j = i; j < n; j++) {
            // Update counts
            if (requests[j] < mid) less++;
            else if (requests[j] == mid) equal++;
            else greater++;
            
            // Quick median check
            int len = j - i + 1;
            int med_idx = (len - 1) / 2;  // 0-indexed median position for our definition
            
            // For median to be mid:
            // - Must have at least one mid
            // - When sorted: less elements before median position, mid at median position
            if (equal > 0 && less <= med_idx && less + equal > med_idx) {
                count++;
            }
        }
    }
    
    return count;
}

// Alternative: Use the fact that for large inputs, 
// we might need coordinate compression + segment trees
// But let's first try a different O(n²) optimization

long getSubarrayMedianOpt(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    for (int i = 0; i < n; i++) {
        if (requests[i] != mid) continue; // Only start from mid positions
        
        int less = 0, equal = 1, greater = 0;
        
        // Count subarrays starting at position i (which contains mid)
        for (int j = i; j < n; j++) {
            if (j > i) {
                if (requests[j] < mid) less++;
                else if (requests[j] == mid) equal++;
                else greater++;
            }
            
            int len = j - i + 1;
            int med_idx = (len % 2 == 1) ? len / 2 : (len / 2) - 1;
            
            if (less <= med_idx && less + equal > med_idx) {
                count++;
            }
        }
        
        // Count subarrays ending at position i (which contains mid)
        less = 0; equal = 1; greater = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (requests[j] < mid) less++;
            else if (requests[j] == mid) equal++;
            else greater++;
            
            int len = i - j + 1;
            int med_idx = (len % 2 == 1) ? len / 2 : (len / 2) - 1;
            
            if (less <= med_idx && less + equal > med_idx) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    cout << "Standard O(n²):" << endl;
    cout << "Test 1: " << getSubarrayMedian(3, {3, 1, 5}) << endl;
    cout << "Test 2: " << getSubarrayMedian(3, {1, 4}) << endl;
    cout << "Test 3: " << getSubarrayMedian(2, {1, 2, 3}) << endl;
    
    cout << "\nOptimized version:" << endl;
    cout << "Test 1: " << getSubarrayMedianOpt(3, {3, 1, 5}) << endl;
    cout << "Test 2: " << getSubarrayMedianOpt(3, {1, 4}) << endl;
    cout << "Test 3: " << getSubarrayMedianOpt(2, {1, 2, 3}) << endl;
    
    return 0;
}