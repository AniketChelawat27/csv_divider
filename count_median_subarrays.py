def count_subarrays_with_median(requests, mid):
    """
    Count the number of subarrays in requests with a median of mid.
    
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


def test_solution():
    """Test the solution with the provided example and additional test cases."""
    
    # Test case 1: Given example
    requests1 = [1, 2, 3]
    mid1 = 2
    result1 = count_subarrays_with_median(requests1, mid1)
    print(f"Test 1: requests={requests1}, mid={mid1}")
    print(f"Result: {result1}")
    print("Expected: 3")
    
    # Let's verify by listing all subarrays and their medians
    print("\nDetailed breakdown:")
    n = len(requests1)
    for i in range(n):
        for j in range(i, n):
            subarray = requests1[i:j+1]
            sorted_subarray = sorted(subarray)
            length = len(sorted_subarray)
            
            if length % 2 == 1:
                median = sorted_subarray[length // 2]
            else:
                median = sorted_subarray[length // 2 - 1]
            
            print(f"Subarray {subarray} -> sorted {sorted_subarray} -> median {median} {'✓' if median == mid1 else ''}")
    
    print("\n" + "="*50)
    
    # Test case 2: All elements same
    requests2 = [2, 2, 2, 2]
    mid2 = 2
    result2 = count_subarrays_with_median(requests2, mid2)
    print(f"Test 2: requests={requests2}, mid={mid2}")
    print(f"Result: {result2}")
    print("Expected: 10 (all subarrays)")
    
    print("\n" + "="*50)
    
    # Test case 3: No matching median
    requests3 = [1, 3, 5]
    mid3 = 2
    result3 = count_subarrays_with_median(requests3, mid3)
    print(f"Test 3: requests={requests3}, mid={mid3}")
    print(f"Result: {result3}")
    print("Expected: 0")
    
    print("\n" + "="*50)
    
    # Test case 4: Single element
    requests4 = [5]
    mid4 = 5
    result4 = count_subarrays_with_median(requests4, mid4)
    print(f"Test 4: requests={requests4}, mid={mid4}")
    print(f"Result: {result4}")
    print("Expected: 1")


if __name__ == "__main__":
    test_solution()