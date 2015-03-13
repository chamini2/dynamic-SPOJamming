#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <ostream>

#define LINE_SIZE 152

using namespace std;

int N, M, abbrSize; // N : Size of entire phrase, M: Number of words, abbrSize: Number of letters
string importantPhrase; 
vector<string> insig_words; 
string abbr_orig; 
string abbr; 

long long dp[151][151][2];

long long solve(int pos, int letter, int word, bool ob) {

    if (abbrSize - letter < M - (word + 1)) {
        return 0;  // No enough letter to accomplish
    }
    // I'm on the last word and all the letter have been placed
    if (word == M - 1 && letter >= abbrSize) {
        return 1; 
    }
    // Went to last position and there are letters remaining
    if (pos >= N && letter < abbrSize) {
        return 0; 
    }

    if (dp[pos][letter][ob] != -1) { 
        return dp[pos][letter][ob]; 
    }

    if (importantPhrase[pos] == ' ') {
        if (ob) return 0; 
        return solve(pos + 1, letter, word + 1, true); 
    }
    if (importantPhrase[pos] != abbr[letter]) {
        return solve(pos + 1, letter, word, ob); 
    }

    dp[pos][letter][ob] = solve(pos + 1, letter + 1, word, false) + solve(pos + 1, letter, word, ob); 

    return dp[pos][letter][ob];
}

int main() {
    
    int n; 
    ostringstream os; 
    char buf[LINE_SIZE]; 
    char iWord[LINE_SIZE]; 

    scanf("%d\n", &n); 
    while (n != 0) {

        insig_words.clear(); 
        insig_words.reserve(n); 
        for (int i = 0; i < n; ++i) {
            scanf("%s\n", iWord); 
            insig_words.push_back(iWord); 
        }
        while (fgets(buf, LINE_SIZE, stdin)) { 

            int size = strlen(buf); 
            if (buf[size - 1] == '\n') buf[size - 1] = '\0';

            if (strcmp(buf, "LAST CASE") == 0) break; 

            istringstream iss(buf); 
            iss >> abbr_orig;
            abbr = abbr_orig;
            abbrSize = abbr_orig.size(); 
            for (int i = 0; i < abbrSize; ++i) {
                abbr[i] = tolower(abbr[i]); 
            }

            string word; 
            M = 0; 
            while (iss >> word) {
                if (find(insig_words.begin(),
                            insig_words.end(), word) == insig_words.end()) {
                    ++M; 
                    os << word << " "; 
                }
            }

            importantPhrase = os.str(); 
            N = importantPhrase.size(); 

            memset(dp, -1, sizeof(int) * 151 * 151 * 2); 
            long long result = solve(0, 0, 0, true);
            cout << abbr_orig; 
            if (result == 0) {
                cout << " is not a valid abbreviation\n";
            } else {
                cout << " can be formed in " << result << " ways\n"; 
            
            }

            os.clear();
            os.str(""); 
        }

        scanf("%d\n", &n); 
    }
}
