#include <bits/stdc++.h>
using namespace std;

// Copy the optimized function
long getSubarrayMedian(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    for (int i = 0; i < n; i++) {
        int less_than_mid = 0;
        int equal_to_mid = 0;
        int greater_than_mid = 0;
        
        for (int j = i; j < n; j++) {
            if (requests[j] < mid) {
                less_than_mid++;
            } else if (requests[j] == mid) {
                equal_to_mid++;
            } else {
                greater_than_mid++;
            }
            
            int length = j - i + 1;
            int median_position = (length % 2 == 1) ? length / 2 : (length / 2) - 1;
            
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
    // Test cases
    cout << "Test 1: " << getSubarrayMedian(3, {3, 1, 5}) << endl; // Expected: 2
    cout << "Test 2: " << getSubarrayMedian(3, {1, 4}) << endl;    // Expected: 0
    cout << "Test 3: " << getSubarrayMedian(2, {1, 2, 3}) << endl; // Expected: 3
    return 0;
}