#include <bits/stdc++.h>

/*
A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that
every edge in the graph connects a node in set A and a node in set B.

Also called the Graph coloring problem, but with 2 colors.

Assuming we are coloring each vertex in the graph with alternate colors:
We can prove a graph is NOT bipartite if it is possible to color two adjacent nodes with the same color.

Else, the graph is bipartite.
*/

bool isBipartite(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> color = vector(n, -1);
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 1;
            if (!_check(i, color, graph))
                return false;
        }
    }
    return true;
}

bool _check(int i, vector<int> &color, vector<vector<int>> &graph) {
    for (int next : graph[i]) {
        if (color[next] == color[i])
            return false;
        else if (color[next] == -1) {
            color[next] = !color[i];
            bool ans = _check(next, color, graph);
            if (!ans)
                return false;
        }
    }
    return true;
}
