#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Optimized version that avoids creating new vectors for each subarray
 */
int countSubarraysWithMedianOptimized(const std::vector<int>& requests, int mid) {
    int n = requests.size();
    int count = 0;
    
    // Generate all possible subarrays
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Create a temporary vector for the current subarray
            std::vector<int> subarray;
            subarray.reserve(j - i + 1);
            
            // Copy elements from i to j
            for (int k = i; k <= j; k++) {
                subarray.push_back(requests[k]);
            }
            
            // Sort the subarray to find median
            std::sort(subarray.begin(), subarray.end());
            int length = subarray.size();
            
            int median;
            if (length % 2 == 1) {
                median = subarray[length / 2];
            } else {
                median = subarray[length / 2 - 1];
            }
            
            if (median == mid) {
                count++;
            }
        }
    }
    
    return count;
}

/**
 * Clean standalone function - main solution
 */
int countSubarraysWithMedian(const std::vector<int>& requests, int mid) {
    int n = requests.size();
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Extract subarray from index i to j (inclusive)
            std::vector<int> subarray(requests.begin() + i, requests.begin() + j + 1);
            
            // Sort to find median
            std::sort(subarray.begin(), subarray.end());
            int length = subarray.size();
            
            // Calculate median based on problem definition
            int median = (length % 2 == 1) ? 
                        subarray[length / 2] :           // Odd: middle element
                        subarray[length / 2 - 1];        // Even: smaller index of two middle
            
            if (median == mid) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    // Example from the problem
    std::vector<int> requests = {1, 2, 3};
    int mid = 2;
    
    int result = countSubarraysWithMedian(requests, mid);
    
    std::cout << "Input: requests = [";
    for (int i = 0; i < requests.size(); i++) {
        std::cout << requests[i];
        if (i < requests.size() - 1) std::cout << ", ";
    }
    std::cout << "], mid = " << mid << std::endl;
    std::cout << "Output: " << result << std::endl;
    
    return 0;
}