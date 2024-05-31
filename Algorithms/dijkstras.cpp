#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

/*
    Graph is stored as an adjacency list.

    Graph is read from an weighted edge list and converted into an adjacency list.

    Edges have weights, so the adj list will contain a pair of integers,
    representing the node, weight of the edge connecting the source and destination nodes.


    soure ->  [next, weight]
    int   ,  pair<int, int>
*/
map<int, vector<pii>> adj;


void dijkstra(int start)
{

    // Comparison function used by the priority queue.
    auto compare = [](pii x, pii y)
    {
        // contains vertex, cost;
        // store in non-increasing order of cost
        return x.second >= y.second;
    };

    priority_queue<pii, vector<pii>, decltype(compare)> heap(compare);
    heap.push({start, 0});
    set<int> visited;
    while (!heap.empty())
    {
        auto [cur, cost] = heap.top();
        // do something with cur here
        heap.pop();
        for (auto [next, weight] : adj[cur])
        {
            if (visited.find(next) != visited.end()) continue; // skip already visited nodes
            heap.push({next, weight + cost});
        }
    }
    visited.clear();
}

int main()
{
    return 0;
}