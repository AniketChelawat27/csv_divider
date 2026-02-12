#include <bits/stdc++.h>
using namespace std;

// Brute force solution (correct)
long bruteForce(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            vector<int> subarray;
            for (int k = i; k <= j; k++) {
                subarray.push_back(requests[k]);
            }
            
            sort(subarray.begin(), subarray.end());
            int len = subarray.size();
            int medianIndex = (len % 2 == 1) ? len / 2 : (len / 2) - 1;
            
            if (subarray[medianIndex] == mid) {
                count++;
                cout << "Found subarray [" << i << "," << j << "]: ";
                for (int x : subarray) cout << x << " ";
                cout << "median = " << subarray[medianIndex] << endl;
            }
        }
    }
    return count;
}

// My optimized attempt
long optimized(int mid, vector<int> requests) {
    int n = requests.size();
    long count = 0;
    
    for (int i = 0; i < n; i++) {
        int greater_equal = 0;
        int less = 0;
        int equal = 0;
        
        for (int j = i; j < n; j++) {
            if (requests[j] > mid) {
                greater_equal++;
            } else if (requests[j] == mid) {
                equal++;
                greater_equal++;
            } else {
                less++;
            }
            
            int length = j - i + 1;
            int median_pos = (length % 2 == 1) ? length / 2 : (length / 2) - 1;
            
            if (equal > 0 && less <= median_pos && greater_equal >= (median_pos + 1)) {
                count++;
                cout << "Optimized found [" << i << "," << j << "]: less=" << less << " equal=" << equal 
                     << " greater=" << (greater_equal-equal) << " median_pos=" << median_pos << endl;
            }
        }
    }
    return count;
}

int main() {
    // Test case 1: [3, 1, 5], mid = 3
    cout << "=== TEST 1: [3,1,5] mid=3 ===" << endl;
    vector<int> test1 = {3, 1, 5};
    cout << "BRUTE FORCE:" << endl;
    long bf1 = bruteForce(3, test1);
    cout << "OPTIMIZED:" << endl;
    long opt1 = optimized(3, test1);
    cout << "BF: " << bf1 << " OPT: " << opt1 << "\n" << endl;
    
    // Test case 2: [1, 4], mid = 3
    cout << "=== TEST 2: [1,4] mid=3 ===" << endl;
    vector<int> test2 = {1, 4};
    cout << "BRUTE FORCE:" << endl;
    long bf2 = bruteForce(3, test2);
    cout << "OPTIMIZED:" << endl;
    long opt2 = optimized(3, test2);
    cout << "BF: " << bf2 << " OPT: " << opt2 << "\n" << endl;
    
    // Test case 3: [1, 2, 3], mid = 2
    cout << "=== TEST 3: [1,2,3] mid=2 ===" << endl;
    vector<int> test3 = {1, 2, 3};
    cout << "BRUTE FORCE:" << endl;
    long bf3 = bruteForce(2, test3);
    cout << "OPTIMIZED:" << endl;
    long opt3 = optimized(2, test3);
    cout << "BF: " << bf3 << " OPT: " << opt3 << endl;
    
    return 0;
}