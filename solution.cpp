#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Count the number of subarrays in requests with a median of mid.
 * 
 * Problem: Given an array 'requests' and an integer 'mid', count the number of 
 * subarrays in requests with a median of mid.
 * 
 * The median is defined as:
 * - For odd-length arrays: the middle element when sorted
 * - For even-length arrays: the element at the smaller index of the two middle elements
 * 
 * Time Complexity: O(n² * k log k) where n is array length and k is average subarray length
 * Space Complexity: O(k) for sorting each subarray
 * 
 * @param requests: Vector of integers representing request sizes
 * @param mid: The target median value
 * @return Integer count of subarrays with median equal to mid
 * 
 * Example:
 *     requests = [1, 2, 3], mid = 2
 *     Subarrays: [1], [2], [3], [1,2], [2,3], [1,2,3]
 *     Medians:   [1], [2], [3], [1],   [2],   [2]
 *     Count of subarrays with median 2: 3
 */
int countSubarraysWithMedian(const std::vector<int>& requests, int mid) {
    int n = requests.size();
    int count = 0;
    
    // Generate all possible subarrays
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Extract subarray from index i to j (inclusive)
            std::vector<int> subarray(requests.begin() + i, requests.begin() + j + 1);
            
            // Sort the subarray to find median
            std::sort(subarray.begin(), subarray.end());
            int length = subarray.size();
            
            int median;
            // Calculate median according to the problem definition
            if (length % 2 == 1) {
                // Odd length: median is the middle element
                median = subarray[length / 2];
            } else {
                // Even length: median is the element at the smaller index of the two middle elements
                median = subarray[length / 2 - 1];
            }
            
            // Check if median equals target
            if (median == mid) {
                count++;
            }
        }
    }
    
    return count;
}

// Test function to verify the solution
void runTests() {
    // Test case from the problem
    std::vector<int> requests1 = {1, 2, 3};
    int mid1 = 2;
    int result1 = countSubarraysWithMedian(requests1, mid1);
    std::cout << "Test 1: requests = [1, 2, 3], mid = " << mid1 << std::endl;
    std::cout << "Output: " << result1 << std::endl;
    std::cout << "Expected: 3" << std::endl;
    std::cout << (result1 == 3 ? "✓ PASS" : "✗ FAIL") << std::endl << std::endl;
    
    // Additional test cases
    struct TestCase {
        std::vector<int> requests;
        int mid;
        int expected;
    };
    
    std::vector<TestCase> testCases = {
        {{1, 2, 3}, 2, 3},
        {{2, 2, 2, 2}, 2, 10},
        {{1, 3, 5}, 2, 0},
        {{5}, 5, 1},
        {{1, 2, 2, 3}, 2, 7}
    };
    
    std::cout << "Additional Test Cases:" << std::endl;
    std::cout << "=====================" << std::endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        const auto& tc = testCases[i];
        int result = countSubarraysWithMedian(tc.requests, tc.mid);
        
        std::cout << "Test " << (i + 1) << ": [";
        for (int j = 0; j < tc.requests.size(); j++) {
            std::cout << tc.requests[j];
            if (j < tc.requests.size() - 1) std::cout << ", ";
        }
        std::cout << "], mid=" << tc.mid << " -> " << result;
        std::cout << (result == tc.expected ? " ✓" : " ✗");
        std::cout << " (expected " << tc.expected << ")" << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}