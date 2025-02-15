#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfsTraversal(int startNode, vector<int> adj[], vector<bool> &isVisited, vector<int> &bfsTraversalAns)
{
    queue<int> q;
    q.push(startNode);
    isVisited[startNode] = true;

    while (!q.empty())
    {
        int frontNode = q.front();
        q.pop();
        bfsTraversalAns.push_back(frontNode);

        for (auto adjNode : adj[frontNode])
        {
            if (!isVisited[adjNode])
            {
                isVisited[adjNode] = true;
                q.push(adjNode);
            }
        }
    }
}

static void printArray(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
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
    vector<int> bfsTraversalAns;

    for (int node=0; node<n; node++)
    {
        if (!isVisited[node]) bfsTraversal(node, adj, isVisited, bfsTraversalAns);
    }

    printArray(bfsTraversalAns);

    return 0;
}