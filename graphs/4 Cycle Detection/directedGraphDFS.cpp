//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution 
{
  private:
    bool checkForCycle(int node, vector<vector<int>> &adj, vector<bool> &isVisited, vector<bool> &isPathVisited)
    {
        isVisited[node] = true;
        isPathVisited[node] = true;
        
        for (auto adjNode : adj[node])
        {
            if (!isVisited[adjNode])
            {
                if (checkForCycle(adjNode, adj, isVisited, isPathVisited)) return true;
            }
            
            if (isPathVisited[adjNode]) return true;
        }
        
        isPathVisited[node] = false;
        
        return false;
    }
    
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(vector<vector<int>> &adj) 
    {
        int n = adj.size();
        
        vector<bool> isVisited(n, false), isPathVisited(n, false);
        
        for (int i=0; i<n; i++)
        {
            if (!isVisited[i])
            {
                if (checkForCycle(i, adj, isVisited, isPathVisited)) return true;
            }
        }
        
        return false;
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