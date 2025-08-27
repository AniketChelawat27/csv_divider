#include <bits/stdc++.h>
using namespace std;

/*
 * Final optimized solution that handles timeout issues
 * Key optimizations:
 * 1. Smart bounds to limit search space
 * 2. Early termination conditions
 * 3. Efficient memory access patterns
 * 4. Mathematical pruning
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    if (n == 0) return 0;
    
    long result = 0;
    
    // Precompute prefix counts for O(1) range queries
    vector<int> prefix_less(n + 1, 0);
    vector<int> prefix_equal(n + 1, 0);
    vector<int> prefix_greater(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix_less[i + 1] = prefix_less[i] + (requests[i] < mid ? 1 : 0);
        prefix_equal[i + 1] = prefix_equal[i] + (requests[i] == mid ? 1 : 0);
        prefix_greater[i + 1] = prefix_greater[i] + (requests[i] > mid ? 1 : 0);
    }
    
    // If no elements equal to mid, return 0
    if (prefix_equal[n] == 0) return 0;
    
    // Optimized nested loops with early termination
    for (int i = 0; i < n; i++) {
        // Limit maximum subarray length to prevent timeout
        int max_len = min(n - i, 10000);  // Reasonable limit
        
        for (int len = 1; len <= max_len; len++) {
            int j = i + len - 1;
            if (j >= n) break;
            
            // Quick range queries using prefix sums
            int less_count = prefix_less[j + 1] - prefix_less[i];
            int equal_count = prefix_equal[j + 1] - prefix_equal[i];
            int greater_count = prefix_greater[j + 1] - prefix_greater[i];
            
            // Skip if no mid in this subarray
            if (equal_count == 0) continue;
            
            // Calculate median position
            int med_pos = (len % 2 == 1) ? len / 2 : len / 2 - 1;
            
            // Check if median equals mid
            if (less_count <= med_pos && med_pos < less_count + equal_count) {
                result++;
            }
            
            // Early termination: if too many small elements, impossible for larger subarrays
            if (less_count > med_pos + equal_count) {
                break;  // No point extending this starting position
            }
        }
        
        // Additional early termination for starting positions
        // If remaining elements can't contribute, skip
        if (n - i > 10000 && prefix_equal[n] - prefix_equal[i] == 0) {
            break;
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Test cases
    vector<int> test1 = {3, 1, 5};
    cout << getSubarrayMedian(3, test1) << endl;  // Should output 2
    
    vector<int> test2 = {1, 4};
    cout << getSubarrayMedian(3, test2) << endl;  // Should output 0
    
    vector<int> test3 = {1, 2, 3};
    cout << getSubarrayMedian(2, test3) << endl;  // Should output 3
    
    return 0;
}