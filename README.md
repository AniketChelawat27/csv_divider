# Maximum Points Earned - C++ Solution

## Problem Description

This is a dynamic programming problem where you can purchase items to earn points, but purchasing an item affects all other items.

### Rules:
1. When you purchase item `i`, you earn `pointValues[i]` points
2. The purchased item becomes 0 (cannot be purchased again)
3. **ALL OTHER items** decrease by 1 (minimum value is 0)
4. Goal: Find the maximum total points possible

## Solution Approach

The solution uses **memoization with recursive dynamic programming**:
- Try purchasing each available item (value > 0)
- For each purchase, simulate the effect on all other items
- Use memoization to avoid recomputing the same states
- Return the maximum points achievable

## Examples

### Sample Case 0: `[5, 5, 5]` → Output: **12**
```
Initial: [5, 5, 5]
Purchase item 0 (5 points): [0, 4, 4]
Purchase item 1 (4 points): [0, 0, 3]  
Purchase item 2 (3 points): [0, 0, 0]
Total: 5 + 4 + 3 = 12
```

### Sample Case 1: `[1, 3, 5, 2, 4]` → Output: **9**
```
Initial: [1, 3, 5, 2, 4]
Purchase item 2 (5 points): [0, 2, 0, 1, 3]
Purchase item 4 (3 points): [0, 1, 0, 0, 0]
Purchase item 1 (1 point):  [0, 0, 0, 0, 0]
Total: 5 + 3 + 1 = 9
```

### Your Question: `[5, 2, 2, 3, 1]` → Output: **7**

## Compilation & Testing

```bash
# Compile
g++ -o solution solution.cpp

# Test with sample cases
echo "3
5 5 5" | ./solution     # Output: 12

echo "5
1 3 5 2 4" | ./solution # Output: 9

echo "5
5 2 2 3 1" | ./solution # Output: 7
```

## Time Complexity
- **Worst case**: O(n! × n) due to exploring all possible purchase orders
- **With memoization**: Much better in practice due to state reuse
- **Space**: O(states) for memoization

This solution handles all the given sample cases correctly and provides the optimal maximum points.