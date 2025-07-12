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
    
    // Key insight: If we select k items with values v1, v2, ..., vk
    // and purchase them in decreasing order, the total points is:
    // sum(vi) - k*(k-1)/2
    // So for each k, we should select the k largest values
    
    // Sort in decreasing order
    sort(pointValues.begin(), pointValues.end(), greater<int>());
    
    long maxPoints = 0;
    long currentSum = 0;
    
    // Try selecting k items (k = 0, 1, 2, ..., n)
    for (int k = 0; k <= n; k++) {
        if (k == 0) {
            maxPoints = max(maxPoints, 0L);
            continue;
        }
        
        // Add the k-th largest value
        currentSum += pointValues[k-1];
        
        // Calculate total points for selecting k items
        long penalty = (long)k * (k - 1) / 2;
        long totalPoints = currentSum - penalty;
        
        maxPoints = max(maxPoints, totalPoints);
    }
    
    return maxPoints;
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