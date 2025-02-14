#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int n, m; // n nodes and m edges
    cin >> n >> m;

    vector<vector<int>> adj(n, vector<int>(m, 0)); // 0 based indexing
    for (int i=0; i<m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    return 0;
}