//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution 
{
  private:
    bool dfs(int node, int col, vector<vector<int>> &adj, vector<int> &color)
    {
        color[node] = col;
        
        for (auto adjNode : adj[node])
        {
            if (color[adjNode] == -1)
            {
                int ncolor = (col == 0) ? 1 : 0;
                if (dfs(adjNode, ncolor, adj, color) == false) return false;
            }
            
            if (color[adjNode] == col) return false;
        }
        
        return true;
    }
  public:
    bool isBipartite(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        vector<int> color(n, -1);
        
        for (int i=0; i<n; i++)
        {
            if (color[i] == -1)
            {
                if (dfs(i, 0, adj, color) == false) return false;
            }
        }
        
        return true;
        
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj(V);
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        bool ans = obj.isBipartite(adj);
        if (ans)
            cout << "true\n";
        else
            cout << "false\n";

        cout << "~"
             << "\n";
    }
    return 0;
}
// } Driver Code Ends