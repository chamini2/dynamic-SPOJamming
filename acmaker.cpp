#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#define MAX_LENGTH 150
#define ull unsigned long long

char inswords[100][MAX_LENGTH + 1];
int size, ws, chrs;

char *acronym;
char *input;
char last_case[] = "LAST CASE";

char phrase[MAX_LENGTH];
int phrase_size;

ull cache[MAX_LENGTH + 1][MAX_LENGTH + 1][2];

ull rec(int i, int w, int l, bool must) {

    // If just saw the last acronym letter, and the last word, 
    // and we used at least one letter in it, then it's all good
    if (l == chrs && w == 1 && !must) return 1;

    // If we saw the last acronym letter, but it's not a valid usage; 
    // or if we ran out of phrase
    if (l == chrs || phrase[i] == '\0') return 0;

    // If we've been here, don't recalculate
    if (cache[i][l][must] != -1) return cache[i][l][must];

    if (phrase[i] == ' ') {
        // If changing from one word of the phrase to the next one
        // Check if we've used at least one letter in it
        if (must) return 0;
        else      return cache[i][l][must] = rec(i+1, w-1, l, true);
    }

    char chr = acronym[l] + 32;
    ull ans = 0;

    if (chr == phrase[i])
        // If we found the current acronym letter, take it
        ans = rec(i+1, w, l+1, false);

    // Or don't take it, whatever
    ans += rec(i+1, w, l, must);

    // Store the result, we don't want to do this again
    return cache[i][l][must] = ans;
}

int main() {
    size_t max_length = MAX_LENGTH;
    int ins;
    int pos;

    input = new char[MAX_LENGTH + 1];

    for (std::cin >> ins; ins > 0; std::cin >> ins) {

        for (int i = 0; i < ins; ++i) 
            scanf("%s\n", inswords[i]);

        while (true) {
            size = getline(&input, &max_length, stdin) - 1;
            input[size] = '\0';

            if (strcmp(input, last_case) == 0) break;

            acronym = strtok(input, " ");
            chrs = strlen(acronym);

            memset(phrase, 0, sizeof(phrase));
            memset(cache, -1, sizeof(cache));
            phrase_size = 0;

            input = acronym;
            // Tokenize all words, ignoring unnecesary ones
            for (ws = 0; (input = strtok(NULL, " ")); ++ws) {
                bool is = false;
                for (int j = 0; !is && j < ins; ++j) {
                    is = strcmp(input, inswords[j]) == 0;
                }

                if (is) {
                  --ws;  
                } else {
                    strcpy(phrase + phrase_size, input);
                    phrase_size += strlen(input);
                    phrase[phrase_size] = ' ';
                    ++phrase_size;
                }
            }

            // Finishing up the copying
            --phrase_size;
            phrase[phrase_size] = '\0';

            // First character in the phrase, number of words, first character of the acronym
            ull result = rec(0, ws, 0, true);

            std::cout << acronym;
            if (result > 0) std::cout << " can be formed in " << result << " ways";
            else            std::cout << " is not a valid abbreviation";
            std::cout << std::endl;
        }
    }
}
