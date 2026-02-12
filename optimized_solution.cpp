#include <bits/stdc++.h>
using namespace std;

/*
 * Optimized solution using transformation approach
 * Time Complexity: O(n²)
 * Space Complexity: O(n)
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long result = 0;
    
    // For each possible starting position
    for (int i = 0; i < n; i++) {
        vector<int> current;
        
        // Extend subarray from position i
        for (int j = i; j < n; j++) {
            current.push_back(requests[j]);
            
            // Count elements less than, equal to, and greater than mid
            int less = 0, equal = 0, greater = 0;
            for (int x : current) {
                if (x < mid) less++;
                else if (x == mid) equal++;
                else greater++;
            }
            
            int len = current.size();
            int median_pos = (len % 2 == 1) ? len / 2 : len / 2 - 1;
            
            // Check if median can be mid
            // For median to be mid:
            // 1. There must be at least one occurrence of mid
            // 2. The median position should fall in the range where mid appears
            if (equal > 0) {
                // In sorted order: [elements < mid][elements = mid][elements > mid]
                // Median position is median_pos (0-indexed)
                // Mid appears at positions [less, less + equal - 1]
                if (less <= median_pos && median_pos < less + equal) {
                    result++;
                }
            }
        }
    }
    
    return result;
}

int main() {
    // Test case 1: [3, 1, 5], mid = 3
    vector<int> test1 = {3, 1, 5};
    cout << "Test 1: " << getSubarrayMedian(3, test1) << endl; // Expected: 2
    
    // Test case 2: [1, 4], mid = 3  
    vector<int> test2 = {1, 4};
    cout << "Test 2: " << getSubarrayMedian(3, test2) << endl; // Expected: 0
    
    // Test case 3: [1, 2, 3], mid = 2
    vector<int> test3 = {1, 2, 3};
    cout << "Test 3: " << getSubarrayMedian(2, test3) << endl; // Expected: 3
    
    return 0;
}