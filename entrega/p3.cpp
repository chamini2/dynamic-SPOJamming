#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int N; 
int seq[201];
int dp[201][201][201];


int solve(int pos, int lastB, int lastW) {
    if (pos > N) 
        return 0; 

    if (dp[pos][lastB][lastW] != -1) {
        return dp[pos][lastB][lastW];
    }

    int blanks = 200; 
    if (lastB == 0 || seq[pos] > seq[lastB]) {
        blanks = min(blanks, solve(pos + 1, pos, lastW)); 
    } 

    if (lastW == 0 || seq[pos] < seq[lastW]) {
        blanks = min(blanks, solve(pos + 1, lastB, pos)); 
    }

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
