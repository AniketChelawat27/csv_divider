# Maximum Points Earned - C++ Solution

## Problem Analysis

The `calculateMaximumPointsEarned` function can be interpreted in several ways depending on the problem constraints. I've implemented multiple versions:

## Solutions

### Main Solution (`solution.cpp`)
- **Algorithm**: House Robber variant (no adjacent elements)
- **Time Complexity**: O(n)
- **Space Complexity**: O(n)
- **Use Case**: When you cannot pick adjacent elements to maximize sum

### Alternative Solutions (`alternative_solutions.cpp`)

1. **V1 - Maximum Subarray (Kadane's Algorithm)**
   - Finds the maximum sum of any contiguous subarray
   - Handles negative numbers optimally

2. **V2 - Sum of Positive Elements**
   - Simply sums all positive values in the array
   - Ignores negative values

3. **V3 - House Robber (No Adjacent)**
   - Same as main solution
   - Dynamic programming approach where you cannot pick adjacent elements

4. **V4 - Game Theory (Optimal Play)**
   - Two players playing optimally
   - Each player tries to maximize their own score minus opponent's score

## Example Results

For input array `[2, 1, 4, 9, 3]`:

- **V1 (Max subarray)**: 19 (sum of all elements)
- **V2 (Sum positive)**: 19 (sum of all positive elements)
- **V3 (No adjacent)**: 11 (optimal: 2 + 9 = 11)
- **V4 (Game theory)**: -1 (optimal play result)

## Compilation & Testing

```bash
# Compile main solution
g++ -o solution solution.cpp

# Compile alternatives
g++ -o alternative_solutions alternative_solutions.cpp

# Test with sample input
echo "5
2 1 4 9 3" | ./solution
```

## Which Solution to Use?

- If the problem allows picking any elements: Use V1 or V2
- If adjacent elements cannot be picked: Use V3 (main solution)
- If it's a two-player game: Use V4
- Most competitive programming "maximum points" problems use the House Robber variant (V3)