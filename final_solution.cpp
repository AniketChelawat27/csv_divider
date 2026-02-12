#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'getMinimumTime' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY requestedHubs
 *  2. INTEGER_ARRAY transitionTime
 */

long getMinimumTime(vector<int> requestedHubs, vector<int> transitionTime) {
    int n = requestedHubs.size();
    int m = transitionTime.size();
    
    if (n == 0) return 0;
    
    long totalTime = 0;
    int currentHub = 1; // Start at Hub 1 (1-based indexing)
    
    for (int i = 0; i < n; i++) {
        int targetHub = requestedHubs[i];
        
        if (currentHub == targetHub) {
            // Already at the target hub, no time needed
            continue;
        }
        
        // Calculate clockwise time
        long clockwiseTime = 0;
        int pos = currentHub;
        while (pos != targetHub) {
            // transitionTime[pos-1] is time from hub pos to hub (pos%m)+1
            clockwiseTime += transitionTime[pos - 1];
            pos++;
            if (pos > m) pos = 1; // Wrap around
        }
        
        // Calculate counterclockwise time
        long counterclockwiseTime = 0;
        pos = currentHub;
        while (pos != targetHub) {
            // Move counterclockwise: from pos to (pos-1)
            pos--;
            if (pos < 1) pos = m; // Wrap around
            // transitionTime[pos-1] is time from hub pos to hub (pos%m)+1
            // For counterclockwise movement from (pos+1) to pos, we use transitionTime[pos-1]
            counterclockwiseTime += transitionTime[pos - 1];
        }
        
        // Choose the minimum time
        long minTime = min(clockwiseTime, counterclockwiseTime);
        totalTime += minTime;
        
        // Update current position
        currentHub = targetHub;
    }
    
    return totalTime;
}

int main() {
    // Test with the provided examples
    vector<int> requestedHubs1 = {1, 3, 3, 2};
    vector<int> transitionTime1 = {3, 2, 1};
    cout << getMinimumTime(requestedHubs1, transitionTime1) << endl;
    
    vector<int> requestedHubs2 = {2, 3, 3, 1};
    vector<int> transitionTime2 = {3, 2, 1};
    cout << getMinimumTime(requestedHubs2, transitionTime2) << endl;
    
    return 0;
}