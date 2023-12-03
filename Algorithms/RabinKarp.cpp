#include <bits/stdc++.h>
using namespace std;

/*
Goal: To search for a pattern in a text, efficiently.

Rabin Karp Algorithm:
This algorithm employs hashing to quickly compare the hash values of substrings, allowing for faster pattern matching.

TC = O(N+M)
where N is the length of the text and M is the length of the pattern

The idea is to generate hashes and compare hashes instead of comparing each character.

We use a simple hash function using 31 as the prime number and 1e9+9 as the prime module.
*/

// return the indexes where pattern begins in text
vector<int> search(string text, string pattern) {
    vector<int> occurrences;

    int T = text.length();
    int P = pattern.length();
    int N = max(T, P);

    if (P > T)
        return occurrences;

    long long p = 31;
    long long mod = 1e9 + 9;

    vector<long long> p_pow(N, 1);
    for (int i = 1; i < N; i++) {
        p_pow[i] = (p_pow[i - 1] * p) % mod;
    }

    vector<long long> t_hash(T + 1, 0);
    for (int i = 0; i < T; i++) {
        t_hash[i + 1] = (t_hash[i] + (text[i] - 'a' + 1) * p_pow[i]) % mod;
    }

    long long p_hash = 0;
    for (int i = 0; i < P; i++) {
        p_hash = (p_hash + (pattern[i] - 'a' + 1) * p_pow[i]) % mod;
    }

    for (int i = 0; i + P <= T; i++) {
        long long cur_h = (t_hash[i + P] - t_hash[i] + mod) % mod;
        if (cur_h == p_hash * p_pow[i] % mod) {
            occurrences.push_back(i);
        }
    }
    return occurrences;
}

int main(int argc, char **argv) {
    string pattern = "hello";
    string text = "helloteststringforrabinkarpalgorithmcontainingAhelloworldsubstringinit";
    vector<int> occurrences = search(text, pattern);
    cout << "Occurrences = " << occurrences.size() << endl;
    for (int idx : occurrences) {
        printf("index: %d string: %s\n", idx, text.substr(idx, pattern.length()).c_str());
    }
    return 0;
}