#include <bits/stdc++.h>
using namespace std;

/*
 * Optimized solution using transformation approach
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    // For each starting position
    for (int i = 0; i < n; i++) {
        int balance = 0;  // Running sum of transformed values
        bool hasMid = false;  // Track if we've seen the target value
        
        // For each ending position from i
        for (int j = i; j < n; j++) {
            // Transform current element
            if (requests[j] >= mid) {
                balance++;
            } else {
                balance--;
            }
            
            // Check if current element equals mid
            if (requests[j] == mid) {
                hasMid = true;
            }
            
            // A subarray has median = mid if:
            // 1. It contains at least one element equal to mid
            // 2. The balance (sum of transformed values) >= 0
            if (hasMid && balance >= 0) {
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
    
    // Additional test case: [2, 2, 2], mid = 2
    vector<int> requests4 = {2, 2, 2};
    cout << "Test 4: " << getSubarrayMedian(2, requests4) << endl; // Expected: 6
}

int main() {
    testSolution();
    return 0;
}