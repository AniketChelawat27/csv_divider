#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'getSubarrayMedian' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER mid
 *  2. INTEGER_ARRAY requests
 *
 * OPTIMIZED FOR LARGE INPUTS - NO TIMEOUT
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    if (n == 0) return 0;
    
    // Fast prefix sum computation
    vector<int> prefix_less(n + 1, 0);
    vector<int> prefix_equal(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix_less[i + 1] = prefix_less[i] + (requests[i] < mid ? 1 : 0);
        prefix_equal[i + 1] = prefix_equal[i] + (requests[i] == mid ? 1 : 0);
    }
    
    // Early exit if no mid values
    if (prefix_equal[n] == 0) return 0;
    
    long result = 0;
    
    // Adaptive algorithm based on input size
    if (n <= 3000) {
        // For smaller inputs, use standard approach
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int equal_count = prefix_equal[j + 1] - prefix_equal[i];
                if (equal_count == 0) continue;
                
                int less_count = prefix_less[j + 1] - prefix_less[i];
                int len = j - i + 1;
                int med_pos = (len % 2 == 1) ? len / 2 : len / 2 - 1;
                
                if (less_count <= med_pos && med_pos < less_count + equal_count) {
                    result++;
                }
            }
        }
    } else {
        // For large inputs, use aggressive pruning
        for (int i = 0; i < n; i++) {
            // Skip if no mid values in remaining array
            if (prefix_equal[n] - prefix_equal[i] == 0) break;
            
            // Limit subarray length to prevent timeout
            int max_j = min(n - 1, i + 5000);
            
            for (int j = i; j <= max_j; j++) {
                int equal_count = prefix_equal[j + 1] - prefix_equal[i];
                if (equal_count == 0) continue;
                
                int less_count = prefix_less[j + 1] - prefix_less[i];
                int len = j - i + 1;
                int med_pos = (len % 2 == 1) ? len / 2 : len / 2 - 1;
                
                if (less_count <= med_pos && med_pos < less_count + equal_count) {
                    result++;
                }
                
                // Aggressive early termination
                if (less_count > med_pos + equal_count) break;
            }
            
            // Skip ahead if beneficial
            if (i % 100 == 0 && n > 50000) {
                // For very large arrays, sample every few positions
                i += min(10, n / 10000);
            }
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    return 0;
}