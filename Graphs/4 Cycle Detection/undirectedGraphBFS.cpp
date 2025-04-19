#include<iostream>
#include<vector>
#include<queue>

using namespace std;

bool detectCycle(int node, vector<int> adj[], vector<bool> &isVisited)
{
    queue<pair<int, int>> q; // node, parent
    q.push(make_pair(node, -1));
    isVisited[node] = true;

    while(!q.empty())
    {
        auto front = q.front();
        q.pop();

        int frontNode = front.first;
        int parent = front.second;

        for (auto adjNode : adj[frontNode])
        {
            if (adjNode == parent) continue;

            if (isVisited[adjNode]) return true;

            q.push(make_pair(adjNode, frontNode));
            isVisited[adjNode] = true;
        }
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
            if(detectCycle(node, adj, isVisited)) cout << "Cycle detected" << endl;
            return 0;
        }
    }
    
    cout << "Cycle not detected" << endl;

    return 0;
}