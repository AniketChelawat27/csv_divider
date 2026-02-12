#include <bits/stdc++.h>
using namespace std;

/*
 * Clearer implementation with detailed tracing
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
        
        // Calculate clockwise time: sum of transition times in forward direction
        long clockwiseTime = 0;
        int pos = currentHub;
        while (pos != targetHub) {
            // transitionTime[pos-1] is time from hub pos to hub (pos+1)
            clockwiseTime += transitionTime[pos - 1];
            pos++;
            if (pos > m) pos = 1; // Wrap around
        }
        
        // Calculate counterclockwise time: sum of transition times in reverse direction
        long counterclockwiseTime = 0;
        pos = currentHub;
        while (pos != targetHub) {
            // Move counterclockwise: from pos to (pos-1)
            pos--;
            if (pos < 1) pos = m; // Wrap around
            // transitionTime[pos-1] is time from hub pos to hub (pos+1)
            // So for counterclockwise from (pos+1) to pos, we use transitionTime[pos-1]
            counterclockwiseTime += transitionTime[pos - 1];
        }
        
        // Choose the minimum time
        long minTime = min(clockwiseTime, counterclockwiseTime);
        totalTime += minTime;
        
        // Debug output
        cout << "From hub " << currentHub << " to hub " << targetHub << ":" << endl;
        cout << "  Clockwise time: " << clockwiseTime << endl;
        cout << "  Counterclockwise time: " << counterclockwiseTime << endl;
        cout << "  Chosen: " << minTime << endl;
        
        // Update current position
        currentHub = targetHub;
    }
    
    return totalTime;
}

int main() {
    // Test case 1: Example from problem
    cout << "=== Test Case 1 ===" << endl;
    vector<int> requestedHubs1 = {1, 3, 3, 2};
    vector<int> transitionTime1 = {3, 2, 1};
    cout << "Final result: " << getMinimumTime(requestedHubs1, transitionTime1) << endl;
    cout << "Expected: 4" << endl << endl;
    
    // Test case 2: Sample case
    cout << "=== Test Case 2 ===" << endl;
    vector<int> requestedHubs2 = {2, 3, 3, 1};
    vector<int> transitionTime2 = {3, 2, 1};
    cout << "Final result: " << getMinimumTime(requestedHubs2, transitionTime2) << endl;
    cout << "Expected: 6" << endl;
    
    return 0;
}