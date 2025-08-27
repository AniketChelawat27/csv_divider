#include <bits/stdc++.h>
using namespace std;

/*
 * Correct optimized solution
 * Key insight: For a subarray to have median = mid, when we sort the subarray:
 * - The element at median position must equal mid
 * - For this to happen, we need the right balance of elements >= mid and < mid
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    // For each starting position
    for (int i = 0; i < n; i++) {
        int greater_equal = 0;  // Count of elements >= mid
        int less = 0;          // Count of elements < mid
        int equal = 0;         // Count of elements == mid
        
        // For each ending position from i
        for (int j = i; j < n; j++) {
            // Update counts
            if (requests[j] > mid) {
                greater_equal++;
            } else if (requests[j] == mid) {
                equal++;
                greater_equal++;
            } else {
                less++;
            }
            
            // Check if this subarray has median = mid
            int length = j - i + 1;
            int median_pos;
            
            if (length % 2 == 1) {
                // Odd length: median at position length/2 (0-indexed)
                median_pos = length / 2;
            } else {
                // Even length: median at position (length/2 - 1) (0-indexed)
                median_pos = (length / 2) - 1;
            }
            
            // For median to be mid:
            // 1. We need at least one element equal to mid
            // 2. Number of elements < mid should be <= median_pos
            // 3. Number of elements >= mid should be >= (median_pos + 1)
            if (equal > 0 && less <= median_pos && greater_equal >= (median_pos + 1)) {
                count++;
            }
        }
    }
    
    return count;
}

// Test function
void testSolution() {
    // Test case 1: [3, 1, 5], mid = 3
    vector<int> requests1 = {3, 1, 5};
    cout << "Test 1: " << getSubarrayMedian(3, requests1) << endl; // Expected: 2
    
    // Test case 2: [1, 4], mid = 3  
    vector<int> requests2 = {1, 4};
    cout << "Test 2: " << getSubarrayMedian(3, requests2) << endl; // Expected: 0
    
    // Test case 3: [1, 2, 3], mid = 2
    vector<int> requests3 = {1, 2, 3};
    cout << "Test 3: " << getSubarrayMedian(2, requests3) << endl; // Expected: 3
    
    // Debug: Let's trace through test case 3
    cout << "\nDebug Test 3 [1, 2, 3], mid = 2:" << endl;
    vector<int> debug = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        for (int j = i; j < 3; j++) {
            vector<int> sub;
            for (int k = i; k <= j; k++) {
                sub.push_back(debug[k]);
            }
            sort(sub.begin(), sub.end());
            int len = sub.size();
            int med_idx = (len % 2 == 1) ? len/2 : (len/2 - 1);
            cout << "Subarray [" << i << "," << j << "]: ";
            for (int x : sub) cout << x << " ";
            cout << "-> median at idx " << med_idx << " = " << sub[med_idx] << endl;
        }
    }
}

int main() {
    testSolution();
    return 0;
}