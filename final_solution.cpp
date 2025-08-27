#include <bits/stdc++.h>
using namespace std;

/*
 * Highly optimized solution for counting subarrays with specific median
 * 
 * Key insight: Transform the problem by mapping values relative to mid
 * - For each element: +1 if >= mid, -1 if < mid, but track actual values
 * - Use the fact that median position in sorted array determines the result
 * 
 * Time Complexity: O(n²)
 * Space Complexity: O(n)
 */

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long result = 0;
    
    // Check each possible subarray
    for (int i = 0; i < n; i++) {
        int less_count = 0;    // Count of elements < mid
        int equal_count = 0;   // Count of elements == mid
        int greater_count = 0; // Count of elements > mid
        
        for (int j = i; j < n; j++) {
            // Update counts as we extend the subarray
            if (requests[j] < mid) {
                less_count++;
            } else if (requests[j] == mid) {
                equal_count++;
            } else {
                greater_count++;
            }
            
            int total_len = j - i + 1;
            
            // Calculate median position (0-indexed)
            int median_pos;
            if (total_len % 2 == 1) {
                median_pos = total_len / 2;  // For odd length
            } else {
                median_pos = total_len / 2 - 1;  // For even length (smaller of two middle)
            }
            
            // Check if median can be 'mid'
            // In sorted order: [less_count elements < mid][equal_count elements = mid][greater_count elements > mid]
            // Median is at position median_pos
            // For median to be 'mid', median_pos must fall in the range [less_count, less_count + equal_count - 1]
            
            if (equal_count > 0 && 
                less_count <= median_pos && 
                median_pos < less_count + equal_count) {
                result++;
            }
        }
    }
    
    return result;
}

// Alternative main function for competitive programming format
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // For testing with provided examples
    vector<int> test1 = {3, 1, 5};
    cout << "Test 1 ([3,1,5], mid=3): " << getSubarrayMedian(3, test1) << endl;
    
    vector<int> test2 = {1, 4};
    cout << "Test 2 ([1,4], mid=3): " << getSubarrayMedian(3, test2) << endl;
    
    vector<int> test3 = {1, 2, 3};
    cout << "Test 3 ([1,2,3], mid=2): " << getSubarrayMedian(2, test3) << endl;
    
    // Uncomment below for actual input reading
    /*
    int mid;
    cin >> mid;
    
    int n;
    cin >> n;
    
    vector<int> requests(n);
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }
    
    cout << getSubarrayMedian(mid, requests) << endl;
    */
    
    return 0;
}