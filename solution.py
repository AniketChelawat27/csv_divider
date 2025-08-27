def count_subarrays_with_median(requests, mid):
    """
    Count the number of subarrays in requests with a median of mid.
    
    Problem: Given an array 'requests' and an integer 'mid', count the number of 
    subarrays in requests with a median of mid.
    
    The median is defined as:
    - For odd-length arrays: the middle element when sorted
    - For even-length arrays: the element at the smaller index of the two middle elements
    
    Time Complexity: O(n² * k log k) where n is array length and k is average subarray length
    Space Complexity: O(k) for sorting each subarray
    
    Args:
        requests: List of integers representing request sizes
        mid: The target median value
    
    Returns:
        Integer count of subarrays with median equal to mid
    
    Example:
        requests = [1, 2, 3], mid = 2
        Subarrays: [1], [2], [3], [1,2], [2,3], [1,2,3]
        Medians:   [1], [2], [3], [1],   [2],   [2]
        Count of subarrays with median 2: 3
    """
    n = len(requests)
    count = 0
    
    # Generate all possible subarrays
    for i in range(n):
        for j in range(i, n):
            # Extract subarray from index i to j (inclusive)
            subarray = requests[i:j+1]
            
            # Sort the subarray to find median
            sorted_subarray = sorted(subarray)
            length = len(sorted_subarray)
            
            # Calculate median according to the problem definition
            if length % 2 == 1:
                # Odd length: median is the middle element
                median = sorted_subarray[length // 2]
            else:
                # Even length: median is the element at the smaller index of the two middle elements
                median = sorted_subarray[length // 2 - 1]
            
            # Check if median equals target
            if median == mid:
                count += 1
    
    return count


# Test the solution
if __name__ == "__main__":
    # Test case from the problem
    requests = [1, 2, 3]
    mid = 2
    result = count_subarrays_with_median(requests, mid)
    print(f"Input: requests = {requests}, mid = {mid}")
    print(f"Output: {result}")
    print(f"Expected: 3")
    
    # Additional test cases
    test_cases = [
        ([1, 2, 3], 2, 3),
        ([2, 2, 2, 2], 2, 10),
        ([1, 3, 5], 2, 0),
        ([5], 5, 1),
        ([1, 2, 2, 3], 2, 7),
    ]
    
    print("\n" + "="*50)
    print("Additional Test Cases:")
    
    for i, (reqs, target, expected) in enumerate(test_cases, 1):
        result = count_subarrays_with_median(reqs, target)
        status = "✓" if result == expected else "✗"
        print(f"Test {i}: {reqs}, mid={target} -> {result} {status} (expected {expected})")