class Solution 
{
    int timer = 0;
private:
    void dfs(int node, int parent, vector<vector<int>> &adj, vector<bool> &vis, vector<int> &tInsertion, vector<int> &tLow, vector<vector<int>> &bridges)
    {
        vis[node] = true;

        tInsertion[node] = tLow[node] = timer;
        timer++;

        for (int adjNode : adj[node])
        {
            if (adjNode == parent) continue;

            if (!vis[adjNode])
            {
                dfs(adjNode, node, adj, vis, tInsertion, tLow, bridges);

                tLow[node] = min(tLow[node], tLow[adjNode]);

                // can node --> adjNode be a bridge
                if (tLow[adjNode] > tInsertion[node]) bridges.push_back({node, adjNode});
            }

            else
            {
                tLow[node] = min(tLow[node], tLow[adjNode]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
    {
        vector<vector<int>> adj(n);

        for (auto edge : connections)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<bool> vis(n, false);

        vector<int> tInsertion(n), tLow(n);

        vector<vector<int>> bridges;

        for (int i=0; i<n; i++)
        {
            if (!vis[i]) dfs(i, -1, adj, vis, tInsertion, tLow, bridges);
        }

        return bridges;
    }
};