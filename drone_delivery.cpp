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
        
        // Calculate clockwise distance and time
        long clockwiseTime = 0;
        int pos = currentHub;
        while (pos != targetHub) {
            // transitionTime is 0-based, but hubs are 1-based
            clockwiseTime += transitionTime[pos - 1];
            pos++;
            if (pos > m) pos = 1; // Wrap around
        }
        
        // Calculate counterclockwise distance and time
        long counterclockwiseTime = 0;
        pos = currentHub;
        while (pos != targetHub) {
            // Move counterclockwise: from pos to pos-1
            int prevPos = (pos == 1) ? m : pos - 1;
            // transitionTime[prevPos-1] is time from prevPos to pos
            // For counterclockwise, we use the transition time in reverse
            counterclockwiseTime += transitionTime[prevPos - 1];
            pos = prevPos;
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
    // Test case 1: Example from problem
    vector<int> requestedHubs1 = {1, 3, 3, 2};
    vector<int> transitionTime1 = {3, 2, 1};
    cout << "Test 1: " << getMinimumTime(requestedHubs1, transitionTime1) << endl;
    // Expected: 4
    
    // Test case 2: Sample case
    vector<int> requestedHubs2 = {2, 3, 3, 1};
    vector<int> transitionTime2 = {3, 2, 1};
    cout << "Test 2: " << getMinimumTime(requestedHubs2, transitionTime2) << endl;
    // Expected: 6
    
    return 0;
}