#include <bits/stdc++.h>

using namespace std;

/*
S   = aabaaab
KMP = 0101223

each element of KMP is incremented atmost once

NOTES:

1. KMP[idx] = Length of Longest Common Prefix(LCP) of S ending at idx
2. *max_element(KMP.begin(), KMP.end()) = to get the length of LCP
3. KMP[|S|-1] = Length of longest common prefix that is also a suffix of S

To find longest palindrome in S that is either a prefix or a suffix of S
soln. = max element of ( KMP(S + "#" + rev(S))[|S|-1] , KMP(rev(S) + "#" + S)[|S|-1]] ) where rev(S) = reversed version of S
*/

vector<int> prefix_function(string S) {
    int N = S.length();
    vector<int> KMP(N, 0);
    int c = 0;
    for (int i = 1; i < N; i++) {
        while (c > 0 && S[i] != S[c]) {
            c = KMP[c - 1];
        }

        if (S[c] == S[i]) {
            c++;
        }
        KMP[i] = c;
    }
    return KMP;
}

int main(int argc, char *argv[]) {
    string s = "aabaaab";
    vector<int> KMP = prefix_function(s);
    for (int i : KMP)
        cout << i << " ";
    return 0;
}