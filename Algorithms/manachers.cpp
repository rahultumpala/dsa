#include <bits/stdc++.h>

using namespace std;

/*
Goal - To find the longest palindromic substring of a given string

Idea - Manacher's algorithm is an optimized version of "expanding around the center" technique.
Main observation:
1. In a palindrome the left and right parts around the center are mirror images of each other
2. In a palindrome, the left part is also a palindrome of some size >= 1

Considering the above observations, each center on the right part can be initialized
with the length of palindrome with the left mirror as the center

Implementation is a bit tricky

str = abababa
S = $#a#b#a#b#a#b#a#@

TC - O(N)
SC - O(2N)
*/

vector<int> longestPalindromicSusbtring(string &str) {
    string S = "#";
    for (char c : str)
        S += c + string("#");
    S = "$" + S + "@";
    int N = S.length();
    // C gives the currentCenter of the longest palindrome till now
    // end gives the end index of the palindrome with C as center
    int C = 1, end = 1;
    vector<int> P(N, 0);
    for (int i = 1; i < N - 1; i++) {
        int mirror = 2 * C - i; // => C - (i-C) = 2*C - i

        // if mirror is the center of another palindrome whose ends go beyond [C-(end-C), end]
        // then P[mirror] cannot be chosen, since we defined P[i] = P[mirror] = length of palindrome at mirror inside the current palindrome whose center is C
        P[i] = min(P[mirror], end - i);
        while (S[i + (P[i] + 1)] == S[i - (P[i] + 1)])
            P[i]++;

        if (i + P[i] > end) {
            C = i;
            end = i + P[i];
        }
    }
    return P;
}

int main(int argc, char **argv) {
    string s = "xyzabcdcbaxyz";
    // string s = "abababa";
    vector<int> manacher = longestPalindromicSusbtring(s);
    int idx = max_element(manacher.begin(), manacher.end()) - manacher.begin();
    int start = ((idx - 1) / 2) - (manacher[idx] / 2);
    string lps = s.substr(start, manacher[idx]);
    cout << lps << endl;
    return 0;
}