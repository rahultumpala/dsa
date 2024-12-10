#include <bits/stdc++.h>

using namespace std;

#define forn(i, k, e) for (int i = k; i < e; i++)
#define fat(x) for (auto &it : x)
#define pr_vec(x)                 \
    fat(x) { cout << it << " "; } \
    cout << endl

/*
Generate all possible permutations for an array of size N ( containing 1..N ).
Print them in lexicographical order.

Ex: N = 3

1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1


permutations are recursive.
all valid permutations of [1 2 3 4] is a set of
{ 1 + permutations of [2 3 4] ,
  2 + permutations of [1 3 4] ,
  3 + permutations of [1 2 4] ,
  4 + permutations of [1 2 3]
}

For a given N, there are N! (N Factorial) permutations.
*/

vector<vector<int>> permute(vector<int> &array)
{
    int N = array.size();
    if (N == 0 || N == 1)
        return vector<vector<int>>{array};
    if (N == 2)
    {
        return vector<vector<int>>{array, vector<int>{array[1], array[0]}};
    }
    else
    {
        vector<vector<int>> permutations;
        forn(i, 0, N)
        {
            vector<int> cp;
            forn(j, 0, N)
            {
                if (i == j)
                    continue;
                else
                    cp.push_back(array[j]);
            }
            vector<vector<int>> sub_permutations = permute(cp);
            for (vector<int> &p : sub_permutations)
            {
                p.insert(p.begin(), array[i]);
                permutations.push_back(p);
            }
        }
        return permutations;
    }
}

int32_t main()
{
    vector<int> array;
    int N = 5;
    for (int i = 0; i < N; i++)
    {
        array.push_back(i + 1);
    }
    vector<vector<int>> permutations = permute(array);
    for (vector<int> v : permutations)
    {
        pr_vec(v);
    }
    cout << "Total Permutations : " << permutations.size() << endl;
    return 0;
}
