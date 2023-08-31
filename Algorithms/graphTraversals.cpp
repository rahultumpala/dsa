#include <bits/stdc++.h>

using namespace std;

/*
    Graphs can be represented in various ways such as
        1. Edge list
        2. Adjacency list
        3. Adjacency matrix
    Since most platforms give input as an edge list, we will assume that the input edge list has been
    converted into an adjacency list and stored in the variable [map<int, vector<int>> adj]

    Also, for our purposes, the graph is undirected and can have cycles.

    Adjacency list representation.
*/
map<int, vector<int>> adj;

// BFS
void bfs(int start)
{
    set<int> visited;
    queue<int> q;
    q.push(start);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        // do something with cur node here
        for (int next : adj[cur])
        {
            if (visited.find(next) != visited.end())
                continue; // do not add visited nodes to queue
            q.push(next);
        }
        visited.insert(cur);
    }
}

// DFS
set<int> visited;

void dfs(int cur)
{
    visited.insert(cur);
    // do something with cur node here
    for (int next : adj[cur])
    {
        if (visited.find(next) != visited.end())
            continue; // do not dfs into visited nodes

        dfs(next);
    }
    visited.erase(cur); // backtracking step
}

int main()
{
    /*
        converting an edge list [vector<vector<int>>] to an adjacency list [map<int, vector<int>>]
    */
    vector<vector<int>> edgeList; // will be of type [ [a,b] , [a, c] , [b, c] , [c, d] ]
    for (auto edge : edgeList)
    {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]); // remove this step if edge list represents a directed graph
    }
    return 0;
}