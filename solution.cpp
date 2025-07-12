#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'calculateMaximumPointsEarned' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY pointValues as parameter.
 */

long calculateMaximumPointsEarned(vector<int> pointValues) {
    int n = pointValues.size();
    if (n == 0) return 0;
    
    // Use memoization with state compression
    map<vector<int>, long> memo;
    
    function<long(vector<int>&)> solve = [&](vector<int>& arr) -> long {
        // Base case: all items have 0 value
        bool hasPositive = false;
        for (int val : arr) {
            if (val > 0) {
                hasPositive = true;
                break;
            }
        }
        if (!hasPositive) return 0;
        
        // Check memo
        if (memo.find(arr) != memo.end()) {
            return memo[arr];
        }
        
        long maxPoints = 0;
        
        // Try purchasing each item
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] > 0) {
                // Make a copy and simulate the purchase
                vector<int> newArr = arr;
                long points = newArr[i];
                
                // Set current item to 0
                newArr[i] = 0;
                
                // Reduce ALL OTHER items by 1 (minimum 0)
                for (int j = 0; j < newArr.size(); j++) {
                    if (j != i) {
                        newArr[j] = max(0, newArr[j] - 1);
                    }
                }
                
                // Recursively solve for remaining state
                long totalPoints = points + solve(newArr);
                maxPoints = max(maxPoints, totalPoints);
            }
        }
        
        memo[arr] = maxPoints;
        return maxPoints;
    };
    
    return solve(pointValues);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> pointValues(n);
    for (int i = 0; i < n; i++) {
        cin >> pointValues[i];
    }
    
    long result = calculateMaximumPointsEarned(pointValues);
    cout << result << endl;
    
    return 0;
}