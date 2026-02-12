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
    long result = 0;
    
    // For each starting position
    for (int i = 0; i < n; i++) {
        vector<int> subarray;
        
        // For each ending position from current start
        for (int j = i; j < n; j++) {
            subarray.push_back(requests[j]);
            
            // Create a copy to sort and find median
            vector<int> sorted_sub = subarray;
            sort(sorted_sub.begin(), sorted_sub.end());
            
            int len = sorted_sub.size();
            int median;
            
            if (len % 2 == 1) {
                // Odd length - middle element
                median = sorted_sub[len / 2];
            } else {
                // Even length - smaller of two middle elements
                median = sorted_sub[len / 2 - 1];
            }
            
            if (median == mid) {
                result++;
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