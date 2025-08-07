//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution 
{
  private:
    bool dfs(int node, vector<int> adj[], vector<bool> &isVisited, vector<bool> &isPathVisited, vector<bool> &isSafeNode)
    {
       isVisited[node] = true;
       isPathVisited[node] = true;
       isSafeNode[node] = false;
       
       for (auto adjNode : adj[node])
       {
           if (!isVisited[adjNode])
           {
               if (dfs(adjNode, adj, isVisited, isPathVisited, isSafeNode)) return true;
           }
           
           else if (isPathVisited[adjNode]) return true;
       }
       
       isPathVisited[node] = false;
       isSafeNode[node] = true;
       return false;
    }
  public:
    vector<int> eventualSafeNodes(int V, vector<int> adj[]) 
    {
        int n = V;
        
        vector<bool> isVisited(n, false);
        vector<bool> isPathVisited(n, false);
        vector<bool> isSafeNode(n, false);
        
        for (int i=0; i<n; i++)
        {
            if (!isVisited[i]) dfs(i, adj, isVisited, isPathVisited, isSafeNode);
        }
        
        vector<int> safeNodes;
        for (int i=0; i<n; i++) if (isSafeNode[i]) safeNodes.push_back(i);
        
        return safeNodes;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {

        int V, E;
        cin >> V >> E;
        vector<int> adj[V];

        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        vector<int> safeNodes = obj.eventualSafeNodes(V, adj);
        for (auto i : safeNodes) {
            cout << i << " ";
        }
        cout << endl;
    
cout << "~" << "\n";
}
}

// } Driver Code Ends