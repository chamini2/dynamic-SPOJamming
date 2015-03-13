#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int N; 
int seq[201];
int dp[201][201][201];


// lastB == 0 && lastW == 0 means first case (nothing is painted)
int solve(int pos, int lastB, int lastW) {
    // Saw all the positions, return 0
    if (pos > N) 
        return 0; 

    // Memoization
    if (dp[pos][lastB][lastW] != -1) {
        return dp[pos][lastB][lastW];
    }

    int blanks = 200; 
    // If nothing is painted black or can paint black, then paint 
    if (lastB == 0 || seq[pos] > seq[lastB]) {
        blanks = min(blanks, solve(pos + 1, pos, lastW)); 
    } 

    // If nothing is painted white or can paint white, then paint 
    if (lastW == 0 || seq[pos] < seq[lastW]) {
        blanks = min(blanks, solve(pos + 1, lastB, pos)); 
    }

    // Get the min between paiting black, white or not paiting + 1
    blanks = min(blanks, solve(pos + 1, lastB, lastW) + 1); 

    return dp[pos][lastB][lastW] = blanks; 
}


int main() {

    while (1) {
        cin >> N;
        if (N == -1) break; 
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &seq[i]); 
        }

        memset(dp, -1, sizeof(int) * 201 * 201 * 201); 
        cout << solve(1, 0, 0) << endl; 
    }
}
