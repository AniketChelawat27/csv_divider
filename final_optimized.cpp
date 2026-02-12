#include <bits/stdc++.h>
using namespace std;

/*
 * Optimized solution for counting subarrays with median = mid
 * Time Complexity: O(n^2) - much better than O(n^3) brute force
 * Space Complexity: O(1)
 *
 * Key insight: Instead of sorting each subarray, we can determine if median = mid
 * by tracking counts of elements relative to mid and checking median position constraints.
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
            // Update counts for current element
            if (requests[j] > mid) {
                greater_equal++;
            } else if (requests[j] == mid) {
                equal++;
                greater_equal++;
            } else {
                less++;
            }
            
            // Calculate median position for current subarray length
            int length = j - i + 1;
            int median_pos;
            
            if (length % 2 == 1) {
                // Odd length: median at position length/2 (0-indexed)
                median_pos = length / 2;
            } else {
                // Even length: median at position (length/2 - 1) (0-indexed)
                median_pos = (length / 2) - 1;
            }
            
            // For median to equal mid, we need:
            // 1. At least one element equal to mid in the subarray
            // 2. Number of elements < mid should be <= median_pos
            // 3. Number of elements >= mid should be >= (median_pos + 1)
            //    This ensures that when sorted, mid appears at the median position
            if (equal > 0 && less <= median_pos && greater_equal >= (median_pos + 1)) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    return 0;
}