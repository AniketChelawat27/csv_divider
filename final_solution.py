def count_subarrays_with_median(requests, mid):
    """
    Count the number of subarrays in requests with a median of mid.
    
    Time complexity: O(n² * k log k) where k is average subarray length
    Space complexity: O(k) for sorting each subarray
    
    Args:
        requests: List of integers representing request sizes
        mid: The target median value
    
    Returns:
        Integer count of subarrays with median equal to mid
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


def debug_test_case(requests, mid):
    """Debug a specific test case by showing all subarrays and their medians."""
    n = len(requests)
    count = 0
    
    print(f"Debugging: requests={requests}, mid={mid}")
    print("All subarrays and their medians:")
    
    for i in range(n):
        for j in range(i, n):
            subarray = requests[i:j+1]
            sorted_subarray = sorted(subarray)
            length = len(sorted_subarray)
            
            if length % 2 == 1:
                median = sorted_subarray[length // 2]
            else:
                median = sorted_subarray[length // 2 - 1]
            
            match = median == mid
            if match:
                count += 1
            
            print(f"  {subarray} -> sorted {sorted_subarray} -> median {median} {'✓' if match else ''}")
    
    print(f"Total count: {count}")
    return count


def comprehensive_test():
    """Run comprehensive tests including the problematic case."""
    
    print("=== COMPREHENSIVE TESTING ===\n")
    
    # Test case 1: Original example
    print("Test 1: Original example")
    result1 = debug_test_case([1, 2, 3], 2)
    print(f"Expected: 3, Got: {result1}\n")
    
    # Test case 2: Debug the problematic case
    print("Test 2: Problematic case [1, 2, 2, 3], mid=2")
    result2 = debug_test_case([1, 2, 2, 3], 2)
    
    # Let's manually calculate what the expected result should be
    print("\nManual verification for [1, 2, 2, 3], mid=2:")
    subarrays_with_median_2 = []
    all_subarrays = [
        [1], [1,2], [1,2,2], [1,2,2,3],
        [2], [2,2], [2,2,3],
        [2], [2,3],
        [3]
    ]
    
    for sub in all_subarrays:
        sorted_sub = sorted(sub)
        length = len(sorted_sub)
        if length % 2 == 1:
            median = sorted_sub[length // 2]
        else:
            median = sorted_sub[length // 2 - 1]
        
        if median == 2:
            subarrays_with_median_2.append(sub)
    
    print(f"Subarrays with median 2: {subarrays_with_median_2}")
    print(f"Count: {len(subarrays_with_median_2)}")
    print(f"Algorithm result: {result2}")


if __name__ == "__main__":
    comprehensive_test()