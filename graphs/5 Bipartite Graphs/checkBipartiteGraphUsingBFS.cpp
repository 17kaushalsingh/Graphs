//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  public:
    bool isBipartite(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        
        queue<pair<int, int>> q; // node, color
        vector<int> color(n, -1);
        // -1 not visited
        // 0 red
        // 1 black
        
        q.push({0,0});
        color[0] = 0;
        
        while(!q.empty())
        {
            int node = q.front().first;
            int col = q.front().second;
            q.pop();
            
            for (auto adjNode : adj[node])
            {
                if (color[adjNode] == -1) // not yet touched
                {
                    int ncolor;
                    (col == 0) ? (ncolor = 1) : (ncolor = 0);
                    q.push({adjNode, ncolor});
                    color[adjNode] = ncolor;
                }
                
                else if (color[adjNode] == col) return false;
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