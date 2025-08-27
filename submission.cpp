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
    
    // Iterate through all possible subarrays
    for (int i = 0; i < n; i++) {
        int less_count = 0;    // Elements < mid
        int equal_count = 0;   // Elements == mid  
        int greater_count = 0; // Elements > mid
        
        for (int j = i; j < n; j++) {
            // Update counts as we extend subarray from i to j
            if (requests[j] < mid) {
                less_count++;
            } else if (requests[j] == mid) {
                equal_count++;
            } else {
                greater_count++;
            }
            
            int subarray_length = j - i + 1;
            
            // Find median position in sorted subarray (0-indexed)
            int median_position;
            if (subarray_length % 2 == 1) {
                // Odd length: middle element
                median_position = subarray_length / 2;
            } else {
                // Even length: smaller of two middle elements
                median_position = subarray_length / 2 - 1;
            }
            
            // Check if median equals mid
            // In sorted order: [less_count elements < mid][equal_count elements = mid][greater_count elements > mid]
            // Median is at position median_position
            // For median to be mid: median_position must be in range [less_count, less_count + equal_count - 1]
            
            if (equal_count > 0 && 
                less_count <= median_position && 
                median_position < less_count + equal_count) {
                result++;
            }
        }
    }
    
    return result;
}

int main() {
    // Example usage and testing
    vector<int> requests1 = {3, 1, 5};
    cout << getSubarrayMedian(3, requests1) << endl; // Output: 2
    
    vector<int> requests2 = {1, 4}; 
    cout << getSubarrayMedian(3, requests2) << endl; // Output: 0
    
    return 0;
}