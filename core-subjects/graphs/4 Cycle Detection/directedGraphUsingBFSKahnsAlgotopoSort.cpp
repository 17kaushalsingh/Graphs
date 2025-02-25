//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution 
{
  private:
    vector<int> getTopoSort(int n, vector<vector<int>> &adj)
    {
        vector<int> topo;
        
        vector<int> inDeg(n, 0);
        for (int i=0; i<n; i++)
        {
            for (auto adjNode : adj[i]) inDeg[adjNode]++;
        }
        
        queue<int> q;
        
        for (int i=0; i<n; i++) if (inDeg[i] == 0) q.push(i);
        
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            
            for (auto adjNode : adj[node])
            {
                inDeg[adjNode]--;
                
                if (inDeg[adjNode] == 0) q.push(adjNode);
            }
        }
        
        return topo;
    }
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(vector<vector<int>> &adj) 
    {
        int n = adj.size();
        
        vector<int> topoSort = getTopoSort(n, adj);
        
        return (topoSort.size() != n);
    }
};

//{ Driver Code Starts.

int main() {

    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;

        vector<vector<int>> adj(V);

        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        cout << obj.isCyclic(adj) << "\n";

        cout << "~"
             << "\n";
    }

    return 0;
}

// } Driver Code Ends