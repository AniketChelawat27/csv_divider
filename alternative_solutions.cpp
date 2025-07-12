#include <bits/stdc++.h>
using namespace std;

// Alternative 1: Maximum sum subarray (Kadane's algorithm)
long calculateMaximumPointsEarned_V1(vector<int> pointValues) {
    long maxSum = LLONG_MIN;
    long currentSum = 0;
    
    for (int val : pointValues) {
        currentSum = max((long)val, currentSum + val);
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}

// Alternative 2: Sum of all positive elements
long calculateMaximumPointsEarned_V2(vector<int> pointValues) {
    long totalSum = 0;
    
    for (int val : pointValues) {
        if (val > 0) {
            totalSum += val;
        }
    }
    
    return totalSum;
}

// Alternative 3: House Robber with no adjacent elements (as in main solution)
long calculateMaximumPointsEarned_V3(vector<int> pointValues) {
    int n = pointValues.size();
    
    if (n == 0) return 0;
    if (n == 1) return max(0, pointValues[0]);
    
    vector<long> dp(n);
    dp[0] = max(0, pointValues[0]);
    dp[1] = max(dp[0], (long)pointValues[1]);
    
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1], dp[i-2] + pointValues[i]);
    }
    
    return dp[n-1];
}

// Alternative 4: Game theory - optimal play between two players
long calculateMaximumPointsEarned_V4(vector<int> pointValues) {
    int n = pointValues.size();
    if (n == 0) return 0;
    if (n == 1) return pointValues[0];
    
    // dp[i][j] = max points first player can get from subarray [i, j]
    vector<vector<long>> dp(n, vector<long>(n, 0));
    
    // Base case: single elements
    for (int i = 0; i < n; i++) {
        dp[i][i] = pointValues[i];
    }
    
    // Fill for lengths 2 to n
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            // Player can pick from either end
            dp[i][j] = max(pointValues[i] - dp[i+1][j], 
                          pointValues[j] - dp[i][j-1]);
        }
    }
    
    return dp[0][n-1];
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
    
    cout << "V1 (Max subarray): " << calculateMaximumPointsEarned_V1(pointValues) << endl;
    cout << "V2 (Sum positive): " << calculateMaximumPointsEarned_V2(pointValues) << endl;
    cout << "V3 (No adjacent): " << calculateMaximumPointsEarned_V3(pointValues) << endl;
    cout << "V4 (Game theory): " << calculateMaximumPointsEarned_V4(pointValues) << endl;
    
    return 0;
}