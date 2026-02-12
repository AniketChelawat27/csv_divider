#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'getSubarrayMedian' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER mid
 *  2. INTEGER_ARRAY requests
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    // For each starting position
    for (int i = 0; i < n; i++) {
        vector<int> current;
        
        // For each ending position from i
        for (int j = i; j < n; j++) {
            current.push_back(requests[j]);
            
            // Create a sorted version to find median
            vector<int> sorted_current = current;
            sort(sorted_current.begin(), sorted_current.end());
            
            int len = sorted_current.size();
            int medianIndex;
            
            if (len % 2 == 1) {
                // Odd length: median is middle element
                medianIndex = len / 2;
            } else {
                // Even length: median is element at smaller index of two middle elements
                medianIndex = (len / 2) - 1;
            }
            
            if (sorted_current[medianIndex] == mid) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    // Test case 1: [3, 1, 5], mid = 3
    vector<int> requests1 = {3, 1, 5};
    cout << "Test 1: " << getSubarrayMedian(3, requests1) << endl; // Expected: 2
    
    // Test case 2: [1, 4], mid = 3
    vector<int> requests2 = {1, 4};
    cout << "Test 2: " << getSubarrayMedian(3, requests2) << endl; // Expected: 0
    
    // Test case 3: [1, 2, 3], mid = 2
    vector<int> requests3 = {1, 2, 3};
    cout << "Test 3: " << getSubarrayMedian(2, requests3) << endl; // Expected: 3
    
    return 0;
}