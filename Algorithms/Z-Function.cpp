#include <bits/stdc++.h>

using namespace std;

/*
S = aaaaabbkaade
Z = 043210002100
*/

// TC = O(N^2)
// SC = O(N) for Z array
vector<int> z_function_unoptimized(string S) {
    int N = S.length();
    vector<int> Z(N, 0);
    for (int i = 1; i < N; i++) {
        while (i + Z[i] < N && S[i + Z[i]] == S[Z[i]]) {
            Z[i]++;
        }
    }
    return Z;
}

/*
Notes:

1. Z[idx] = Length of the Longest Common Prefix starting at idx
*/

// TC = O(N) => OPTIMIZED
// SC = O(N) for Z array
vector<int> z_function(string S) {
    int N = S.length();
    int l = 0, r = 0;
    vector<int> Z(N, 0);
    for (int i = 1; i < N; i++) {
        if (r > i) {
            Z[i] = r - i;
        }

        while (i + Z[i] < N && S[i + Z[i]] == S[Z[i]]) {
            Z[i]++;
        }
        r = max(r, i + Z[i]);
    }
    return Z;
}

int main(int argc, char **argv) {
    string S = "aaaaabbkaade";
    vector<int> Z2 = z_function(S);
    return 0;
}