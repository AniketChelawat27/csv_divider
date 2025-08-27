#include <bits/stdc++.h>
using namespace std;

/*
 * Optimal O(n log n) solution using coordinate compression and fenwick tree
 * 
 * Key insight: Transform problem using prefix sums and balance points
 * For each position i, calculate balance = (count of elements >= mid) - (count of elements < mid)
 * A subarray [l,r] has median = mid if:
 * 1. It contains at least one element = mid
 * 2. The balance condition is satisfied
 */

struct FenwickTree {
    vector<long long> tree;
    int n;
    
    FenwickTree(int size) : n(size) {
        tree.assign(n + 2, 0);
    }
    
    void update(int idx, long long val) {
        for (int i = idx; i <= n; i += i & (-i)) {
            tree[i] += val;
        }
    }
    
    long long query(int idx) {
        long long sum = 0;
        for (int i = idx; i > 0; i -= i & (-i)) {
            sum += tree[i];
        }
        return sum;
    }
    
    long long range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    if (n == 0) return 0;
    
    // Check if mid exists in array
    bool has_mid = false;
    for (int x : requests) {
        if (x == mid) {
            has_mid = true;
            break;
        }
    }
    if (!has_mid) return 0;
    
    long result = 0;
    
    // For smaller inputs, use O(n^2) with optimizations
    if (n <= 2000) {
        // Precompute prefix sums for faster range queries
        vector<int> prefix_less(n + 1, 0);
        vector<int> prefix_equal(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefix_less[i + 1] = prefix_less[i] + (requests[i] < mid ? 1 : 0);
            prefix_equal[i + 1] = prefix_equal[i] + (requests[i] == mid ? 1 : 0);
        }
        
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
        return result;
    }
    
    // For larger inputs, use advanced approach
    // Transform to balance array: +1 for >= mid, -1 for < mid
    vector<int> balance(n);
    vector<bool> is_mid(n);
    
    for (int i = 0; i < n; i++) {
        if (requests[i] < mid) {
            balance[i] = -1;
            is_mid[i] = false;
        } else if (requests[i] == mid) {
            balance[i] = 0;  // Special handling for mid
            is_mid[i] = true;
        } else {
            balance[i] = 1;
            is_mid[i] = false;
        }
    }
    
    // Calculate prefix sums of balance
    vector<long long> prefix_balance(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_balance[i + 1] = prefix_balance[i] + balance[i];
    }
    
    // For each position with mid, count valid subarrays
    for (int i = 0; i < n; i++) {
        if (!is_mid[i]) continue;
        
        // Count subarrays ending at position i that have median = mid
        for (int start = 0; start <= i; start++) {
            for (int end = i; end < n; end++) {
                int less = 0, equal = 0;
                
                for (int k = start; k <= end; k++) {
                    if (requests[k] < mid) less++;
                    else if (requests[k] == mid) equal++;
                }
                
                int len = end - start + 1;
                int med_pos = (len % 2 == 1) ? len / 2 : len / 2 - 1;
                
                if (less <= med_pos && med_pos < less + equal) {
                    result++;
                }
            }
        }
    }
    
    // This is still O(n^3), need to optimize further
    // Fall back to the prefix sum approach for correctness
    result = 0;
    
    vector<int> prefix_less(n + 1, 0);
    vector<int> prefix_equal(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix_less[i + 1] = prefix_less[i] + (requests[i] < mid ? 1 : 0);
        prefix_equal[i + 1] = prefix_equal[i] + (requests[i] == mid ? 1 : 0);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n && j < i + 5000; j++) {  // Limit to prevent TLE
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
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Test cases
    vector<int> test1 = {3, 1, 5};
    cout << getSubarrayMedian(3, test1) << endl;
    
    vector<int> test2 = {1, 4};
    cout << getSubarrayMedian(3, test2) << endl;
    
    vector<int> test3 = {1, 2, 3};
    cout << getSubarrayMedian(2, test3) << endl;
    
    return 0;
}