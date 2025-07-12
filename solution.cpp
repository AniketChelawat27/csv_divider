#include <bits/stdc++.h>
using namespace std;

bool canDefeat(vector<int> x, vector<int> y) {
    // Generate all permutations of x
    vector<vector<int>> permX;
    sort(x.begin(), x.end());
    do {
        permX.push_back(x);
    } while(next_permutation(x.begin(), x.end()));
    
    // Generate all permutations of y
    vector<vector<int>> permY;
    sort(y.begin(), y.end());
    do {
        permY.push_back(y);
    } while(next_permutation(y.begin(), y.end()));
    
    // For each permutation of x, check if y can counter it
    for(auto& px : permX) {
        bool canBeCountered = false;
        for(auto& py : permY) {
            int yWins = 0;
            for(int i = 0; i < 3; i++) {
                if(py[i] > px[i]) yWins++;
            }
            if(yWins >= 2) {
                canBeCountered = true;
                break;
            }
        }
        if(!canBeCountered) {
            return true; // X can defeat Y
        }
    }
    return false;
}

int possibleWinners(vector<int> boost_a, vector<int> boost_b, vector<int> boost_c) {
    int n = boost_a.size();
    int count = 0;
    
    for(int i = 0; i < n; i++) {
        bool canDefeatAll = true;
        vector<int> playerI = {boost_a[i], boost_b[i], boost_c[i]};
        
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            vector<int> playerJ = {boost_a[j], boost_b[j], boost_c[j]};
            
            if(!canDefeat(playerI, playerJ)) {
                canDefeatAll = false;
                break;
            }
        }
        
        if(canDefeatAll) {
            count++;
        }
    }
    
    return count;
}

int main() {
    // Test with the provided example
    vector<int> boost_a = {9, 4, 2};
    vector<int> boost_b = {5, 12, 10};
    vector<int> boost_c = {11, 3, 13};
    
    cout << "Result: " << possibleWinners(boost_a, boost_b, boost_c) << endl;
    
    // Let's also verify individual matchups
    vector<int> player1 = {9, 5, 11};
    vector<int> player2 = {4, 12, 3};
    vector<int> player3 = {2, 10, 13};
    
    cout << "Player 1 can defeat Player 2: " << canDefeat(player1, player2) << endl;
    cout << "Player 1 can defeat Player 3: " << canDefeat(player1, player3) << endl;
    cout << "Player 2 can defeat Player 1: " << canDefeat(player2, player1) << endl;
    cout << "Player 2 can defeat Player 3: " << canDefeat(player2, player3) << endl;
    cout << "Player 3 can defeat Player 1: " << canDefeat(player3, player1) << endl;
    cout << "Player 3 can defeat Player 2: " << canDefeat(player3, player2) << endl;
    
    return 0;
}