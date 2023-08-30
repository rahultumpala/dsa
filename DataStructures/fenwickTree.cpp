#include <bits/stdc++.h>

using namespace std;

class FenwickTree
{
private:
    vector<int> values, tree;

    int prefixSum(int r)
    {
        int ans = 0;
        r++; // since we are using one indexed tree
        while (r > 0)
        {
            ans += tree[r];
            r = r & (r - 1);
        }
        return ans;
    }

public:
    FenwickTree(vector<int> array)
    {
        values = array;
        construct();
    }

    void construct()
    {
        // creating one indexed tree
        tree = vector<int>(values.size() + 1, 0);
        int i = 1, n = values.size();
        while (i <= n)
        {
            int parent = i + (i & -i);
            tree[i] += values[i - 1];
            if (parent <= n)
                tree[parent] += tree[i];
            i++;
        }
    }

    int sum(int l, int r)
    {
        return prefixSum(r) - prefixSum(l - 1);
    }

    void printTree()
    {
        printf("Index  ArrayValue  BinaryIndex  TreeValue\n");
        for (int i = tree.size(); i > 0; i--)
        {
            printf("[%3d]     [%4d]    [%s]    [%4d]\n", i, values[i - 1], bitset<8>(i).to_string().c_str(), tree[i]);
        }
    }
};

void validate(vector<pair<int, int>> ranges, FenwickTree *tree, vector<int> array)
{
    tree->printTree();
    printf("Range    ExpectedSum  Result\n");
    for (auto r : ranges)
    {
        int x = r.first, y = r.second;
        int expectedSum = 0;
        for (int i = x; i <= y; i++)
            expectedSum += array[i];
        printf("[%2d, %2d]   [%4d]     [%4d]\n", x, y, expectedSum, tree->sum(x, y));
    }
}

int main()
{
    vector<int> testArray1{3, 8, 2, 5, 1, 6, 9, 4, 7, 10, 12, 15, 11, 13, 14};
    vector<pair<int, int>> testRanges1{{2, 8}, {0, 4}, {6, 11}, {1, 7}, {3, 5}, {9, 13}, {0, 14}, {4, 10}, {12, 14}, {7, 9}};

    vector<int> testArray2{23, 87, 42, 9, 51, 78, 15, 63, 94, 1,
                           37, 66, 32, 84, 70, 49, 18, 8, 57, 91,
                           29, 59, 6, 45, 72, 5, 20, 39, 96, 10,
                           74, 26, 53, 17, 81, 55, 13, 68, 31, 80,
                           48, 99, 21, 36, 60, 3, 76, 43, 12, 27};
    vector<pair<int, int>> testRanges2{{15, 22}, {6, 29}, {4, 4}, {36, 47}, {6, 30}, {21, 38}, {21, 34}, {32, 46}, {12, 30}, {4, 29}, {9, 26}, {7, 17}, {5, 25}, {8, 35}, {28, 29}, {12, 22}, {0, 32}, {9, 11}, {5, 14}, {0, 20}, {12, 14}, {36, 42}, {6, 18}, {0, 17}, {14, 22}, {6, 28}, {27, 32}, {2, 9}, {24, 37}, {18, 35}, {9, 15}, {12, 15}, {11, 21}, {12, 26}, {0, 3}, {28, 37}, {15, 20}, {5, 6}, {22, 41}, {2, 21}, {4, 35}, {0, 37}, {27, 37}, {19, 40}, {2, 24}, {0, 40}, {6, 34}, {6, 11}, {5, 24}, {11, 27}};

    FenwickTree *testTree1 = new FenwickTree(testArray1);
    validate(testRanges1, testTree1, testArray1);

    FenwickTree *testTree2 = new FenwickTree(testArray2);
    validate(testRanges2, testTree2, testArray2);
    return 0;
}