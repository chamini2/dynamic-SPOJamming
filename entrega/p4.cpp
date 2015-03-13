#include <iostream>
#include <cstring>
#define MAX 200

int rows, cols;
char map[MAX+1][MAX+1];
int dp[MAX + 2]; 

int solve() {
    if (map[0][0] == '#') {
        return 0; 
    }
    dp[1] = 0;

    int maxWoods = 0; 
    for (int r = 0; r < rows; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < cols; ++c) {
                if (map[r][c] == '#' || (dp[c] == -1 && dp[c + 1] == -1)) {
                    dp[c + 1] = -1; 
                } else  {
                    dp[c + 1] = (map[r][c] == 'T' ? 1 : 0) + std::max(dp[c + 1], dp[c]); 
                }
                maxWoods = std::max(dp[c + 1], maxWoods); 
            }
        } else  {
            for (int c = cols - 1; c >= 0; --c) {
                if (map[r][c] == '#' || (dp[c + 2] == -1 && dp[c + 1] == -1)) {
                    dp[c + 1] = -1; 
                } else  {
                    dp[c + 1] = (map[r][c] == 'T' ? 1 : 0) + std::max(dp[c + 2], dp[c + 1]); 
                }
                maxWoods = std::max(dp[c + 1], maxWoods); 
            }

        }
    }

    return maxWoods; 
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::cin >> rows >> cols;
        for (int i = 0; i < rows; ++i) {
            std::cin >> map[i];
        }
        memset(dp, -1, sizeof(dp)); 
        std::cout << solve() << std::endl; 
    }
}
