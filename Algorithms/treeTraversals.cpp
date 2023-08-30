#include <bits/stdc++.h>

using namespace std;

/*
A Tree is also technically a graph with N nodes and N-1 edges.
Level order traversal of a binary tree is similar to doing a Breadth-first search on a graph.
DFS is dfs, no variations.

structure of the tree node we will be using.
*/
typedef struct node
{
    int val;
    node *left;
    node *right;
} node;

/*

I will just print the values. Modify as you wish.

*/
void levelOrderTraversal(node *root)
{
    if (root == nullptr)
        return;
    queue<pair<node *, int>> q;
    int curDepth = 0;
    q.push({root, curDepth});
    while (!q.empty())
    {
        node *top = q.front().first;
        int depth = q.front().second;
        q.pop();
        if (depth > curDepth)
        {
            cout << endl; // print a new line to show we are one level deeper.
            curDepth = depth;
        }
        cout << top->val << " ";

        // elements are pushed in left to right manner
        if (top->left != nullptr)
            q.push({top->left, depth + 1});
        if (top->right != nullptr)
            q.push({top->right, depth + 1});
    }
    cout << endl; // print new line after last level in the tree.
}

/**
    N-ary Tree Level Order Traversal.

    struct used to represent an N-ary tree node.
**/
typedef struct NAryTreeNode
{
    int val;
    vector<NAryTreeNode *> children;
} NAryTreeNode;


/*
    The way we handle children of the root node changes, everything else is the same.
*/
void levelOrderTraversal(NAryTreeNode *root)
{
    if (root == nullptr)
        return;
    queue<pair<NAryTreeNode *, int>> q;
    int curDepth = 0;
    q.push({root, curDepth});
    while (!q.empty())
    {
        NAryTreeNode *top = q.front().first;
        int depth = q.front().second;
        q.pop();
        if (depth > curDepth)
        {
            cout << endl; // print a new line to show we are one level deeper.
            curDepth = depth;
        }
        cout << top->val << " ";

        // elements are pushed in left to right manner
        for (NAryTreeNode *child : top->children)
        {
            q.push({child, depth + 1});
        }
    }
    cout << endl; // print new line after last level in the tree.
}

int main()
{
    return 0;
}