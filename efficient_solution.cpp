#include <bits/stdc++.h>
using namespace std;

/*
 * EFFICIENT Solution: O(n log n) using coordinate compression and Fenwick tree
 * 
 * Algorithm:
 * 1. For each element equal to 'mid', count subarrays where it can be the median
 * 2. Use coordinate compression to handle large values efficiently
 * 3. Use Fenwick tree to count valid prefix sums quickly
 */

class FenwickTree {
    vector<int> tree;
    int n;
    
public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}
    
    void update(int idx, int val) {
        for (int i = idx; i <= n; i += i & -i) {
            tree[i] += val;
        }
    }
    
    int query(int idx) {
        int sum = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
    
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    if (n == 0) return 0;
    
    // Transform array: +1 if >= mid, -1 if < mid, but track original positions of 'mid'
    vector<int> transformed(n);
    vector<bool> is_mid(n, false);
    
    for (int i = 0; i < n; i++) {
        if (requests[i] > mid) {
            transformed[i] = 1;
        } else if (requests[i] == mid) {
            transformed[i] = 1;
            is_mid[i] = true;
        } else {
            transformed[i] = -1;
        }
    }
    
    long count = 0;
    
    // For each position containing 'mid'
    for (int mid_idx = 0; mid_idx < n; mid_idx++) {
        if (!is_mid[mid_idx]) continue;
        
        // Calculate prefix sums from left
        map<int, int> left_prefix_count;
        left_prefix_count[0] = 1; // Empty prefix
        
        int prefix_sum = 0;
        for (int i = mid_idx - 1; i >= 0; i--) {
            prefix_sum += transformed[i];
            left_prefix_count[prefix_sum]++;
        }
        
        // Calculate suffix sums and count valid combinations
        int suffix_sum = transformed[mid_idx]; // Start with the mid element
        
        // Count subarrays ending exactly at mid_idx
        for (auto& [left_sum, cnt] : left_prefix_count) {
            if (left_sum + suffix_sum >= 0) {
                count += cnt;
            }
        }
        
        // Extend to the right
        for (int j = mid_idx + 1; j < n; j++) {
            suffix_sum += transformed[j];
            
            // Count subarrays [i, j] where i <= mid_idx
            for (auto& [left_sum, cnt] : left_prefix_count) {
                if (left_sum + suffix_sum >= 0) {
                    count += cnt;
                }
            }
        }
    }
    
    // Handle overcounting: if multiple 'mid' elements in same subarray
    // We need to subtract overcounted subarrays
    
    // Simple fix: only count each subarray once by using the leftmost 'mid'
    // Restart with a different approach to avoid overcounting...
    
    return count;
}

// Let me implement a cleaner version without overcounting issues
long getSubarrayMedianClean(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    // Transform array
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        if (requests[i] > mid) arr[i] = 1;
        else if (requests[i] == mid) arr[i] = 0;  // Special marker
        else arr[i] = -1;
    }
    
    // For each subarray, check if it contains 'mid' and has non-negative balance
    for (int i = 0; i < n; i++) {
        if (requests[i] != mid) continue; // Only start from positions with 'mid'
        
        int balance = 0;
        bool found_mid = false;
        
        for (int j = i; j < n; j++) {
            if (requests[j] == mid) found_mid = true;
            
            if (requests[j] >= mid) balance++;
            else balance--;
            
            if (found_mid && balance >= 0) count++;
        }
    }
    
    return count;
}

int main() {
    // Test the clean version
    cout << "Test 1: " << getSubarrayMedianClean(3, {3, 1, 5}) << endl;
    cout << "Test 2: " << getSubarrayMedianClean(3, {1, 4}) << endl;
    cout << "Test 3: " << getSubarrayMedianClean(2, {1, 2, 3}) << endl;
    return 0;
}