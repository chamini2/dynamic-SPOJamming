#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT 1000000 // Need to change this to a closer value

using namespace std;

int N; 
int goal[16];
int board[16];
int dp[16][65540]; // 16 * 2^16 + 5


int solve(int pos, int map) {
    if (pos >= N)
        return 0; 

    if (dp[pos][map] != -1) {
        return dp[pos][map];
    }

    int moves = MAX_INT; 

    for (int i = 0; i < N; ++i) {
        if (!(map & 1 << i)) {
            int rowDist = abs(i - pos); 
            int colDist = abs(goal[i] - board[pos]); 
            moves = min(moves, solve(pos + 1, map | 1 << i) + rowDist + colDist); 
        }
    }

    return dp[pos][map] = moves; 
}

int main() {

    while(1) {
        cin >> N; 
        if (N == 0) break; 

        for (int i = 0; i < N; ++i) {
            scanf("%d", &board[i]); 
        }

        for (int i = 0; i < N; ++i) {
            scanf("%d", &goal[i]); 
        }

        memset(dp, -1, sizeof(int) * 16 * 65540); 
        cout << solve(0, 0) << endl; 
    }
}
