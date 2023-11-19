#include <bits/stdc++.h>

using namespace std;

/*
Goal - To find the Longest Palindromic Substring (_lps_) of a given string

Idea - Choose a center and expand around it

1. Odd length palindrome: center is a character of the string
ex: S = aba --> consider 'b' as center and compare sides while expanding
comparison --> S[center-1] == S[center+1]
spl. case --> palindrome of length 1 --> S[center] == S[center]

2. Even length palindrome: center is a space between characters of the string
ex: S = abba --> ab_ba consider empty space after b as center and expand
comparison -->   S[center] == S[center+1]
*/

/*
Exact implementation of above algorithm
TC - O(N^2)
SC - O(N) for answer
*/
string longestPalindromicSubstring(string &S) {
    int N = S.size();
    int max_len = 0, L = 0, R = 0;

    for (int center = 0; center < N; center++) {
        // parity = 0 --> odd length palindromes
        // parity = 1 --> even length palindromes
        for (int parity = 0; parity < 2; parity++) {
            int l = center, r = center + parity;
            while (r < N && l >= 0 && S[l] == S[r]) {
                if (r - l + 1 > max_len) {
                    L = l;
                    R = r;
                    max_len = r - l + 1;
                }
                l--;
                r++;
            }
        }
    }

    return S.substr(L, R - L + 1);
}

int main(int argc, char **argv) {
    vector<string> vs{"aaabaaa", "bcaaaabc", "abcdcbaxyz"};
    for (string s : vs) {
        cout << longestPalindromicSubstring(s) << endl;
    }
    return 0;
}