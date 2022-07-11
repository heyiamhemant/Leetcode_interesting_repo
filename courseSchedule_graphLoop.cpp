#include <bits/stdc++.h>
using namespace std;

bool dfs(int node, vector<vector<int>> &adj, vector<int> &visited, vector<int> &dfsvisit)
{
    if (visited[node] == 0)
    {
        visited[node] = 1;
        dfsvisit[node] = 1;
    }
    bool result = false; // assume cycle not exists
    for (int i : adj[node])
    {
        if (dfsvisit[i] == 1)
            return true;                         // cycle exists
        result = dfs(i, adj, visited, dfsvisit); // check cycle for all adjacent
    }
    dfsvisit[node] = 0;
    return result;
}
