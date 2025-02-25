#include<iostream>
#include<vector>
#include<queue>

using namespace std;

bool detectCycle(int node, int parent, vector<int> adj[], vector<bool> &isVisited)
{
    isVisited[node] = true;

    for (auto adjNode : adj[node])
    {
        if (adjNode == parent) continue;

        if (isVisited[adjNode]) return true; // cycle detected
        
        if (detectCycle(adjNode, node, adj, isVisited) == true) return true; // cycle detected
    }

    return false;
}

int main()
{
    int n, m; // n nodes and m edges
    cin >> n >> m;

    vector<int> adj[n];

    for (int i=0; i<m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> isVisited(n, false);

    for (int node=0; node<n; node++)
    {
        if (!isVisited[node])
        {
            if(detectCycle(node, -1, adj, isVisited)) cout << "Cycle detected" << endl;
            return 0;
        }
    }
    
    cout << "Cycle not detected" << endl;

    return 0;
}