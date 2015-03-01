#include <iostream>
#include <cstring>
#define MAX 200

int rows, cols;
char map[MAX+1][MAX+1];
int cache[MAX+1][MAX+1];

int rec(int i, int j, bool right) {
    if (i == rows || j == -1 || j == cols || map[i][j] == '#') return 0;
    if (cache[i][j] != -1) return cache[i][j];

    int dir = right ? 1 : -1;

    return cache[i][j] = (map[i][j] == 'T' ? 1 : 0) + 
                          std::max(rec(i    , j + dir,  right), 
                                   rec(i + 1, j      , !right));
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::cin >> rows >> cols;
        for (int i = 0; i < rows; ++i) {
            std::cin >> map[i];
        }
        memset(cache, -1, sizeof(cache));

        std::cout << rec(0,0,true) << std::endl;
    }
}