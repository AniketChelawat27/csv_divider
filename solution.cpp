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
    
    // Handle edge cases
    if (n == 0) return 0;
    if (n == 1) return pointValues[0];
    
    // This appears to be the "House Robber" problem variant
    // where we cannot pick adjacent elements to maximize sum
    vector<long> dp(n);
    dp[0] = max(0, pointValues[0]);  // Can choose not to pick first element
    dp[1] = max(dp[0], (long)pointValues[1]);
    
    for (int i = 2; i < n; i++) {
        // Either pick current element + best from i-2, or don't pick current
        dp[i] = max(dp[i-1], dp[i-2] + pointValues[i]);
    }
    
    return dp[n-1];
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