#include "../commons.cpp"

void dfsTraversal(int node, vector<int> adj[], vector<bool> &isVisited, vector<int> &dfsTraversalAns)
{
    isVisited[node] = true;
    dfsTraversalAns.push_back(node);

    for (auto adjNode : adj[node])
    {
        if (!isVisited[adjNode])
        {
            dfsTraversal(adjNode, adj, isVisited, dfsTraversalAns);
        }
    }
}

int main()
{
    // assume the graph is given
    int n, m; // m nodes and n edges
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
    vector<int> dfsTraversalAns;

    for (int node=0; node<n; node++)
    {
        if (!isVisited[node]) dfsTraversal(node, adj, isVisited, dfsTraversalAns);
    }

    GraphUtils::printArray(dfsTraversalAns);

    return 0;
}