#include <bits/stdc++.h>
using namespace std;

/*
 * OPTIMIZED Solution: O(n^2) time, O(1) space
 * 
 * Key insight: Instead of sorting each subarray, we can determine if the median equals 'mid'
 * by tracking counts and using the median position constraint.
 * 
 * For a subarray to have median = mid:
 * 1. It must contain at least one element equal to mid
 * 2. When sorted, 'mid' must appear at the median position
 * 
 * We achieve this by ensuring:
 * - elements < mid ≤ median_position  
 * - elements ≥ mid ≥ median_position + 1
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    // Try all possible subarrays
    for (int i = 0; i < n; i++) {
        int less_than_mid = 0;     // Count of elements < mid
        int equal_to_mid = 0;      // Count of elements = mid  
        int greater_than_mid = 0;  // Count of elements > mid
        
        for (int j = i; j < n; j++) {
            // Update counts for current element
            if (requests[j] < mid) {
                less_than_mid++;
            } else if (requests[j] == mid) {
                equal_to_mid++;
            } else {
                greater_than_mid++;
            }
            
            // Calculate median position for current subarray [i...j]
            int length = j - i + 1;
            int median_position;
            
            if (length % 2 == 1) {
                // Odd length: median is at middle position
                median_position = length / 2;
            } else {
                // Even length: median is at smaller index of two middle elements
                median_position = (length / 2) - 1;
            }
            
            // Check if median would be 'mid' when subarray is sorted
            // Condition: mid must exist AND be at the correct position when sorted
            if (equal_to_mid > 0 && 
                less_than_mid <= median_position && 
                (less_than_mid + equal_to_mid) > median_position) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    return 0;
}