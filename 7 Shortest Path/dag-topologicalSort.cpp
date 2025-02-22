//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++
class Solution 
{
  private:
    void getTopoSort(int node, vector<pair<int, int>> adj[], vector<bool> &vis, stack<int> &st)
    {
        vis[node] = true;
        
        for (auto it : adj[node])
        {
            int adjNode = it.first;
            if (!vis[adjNode]) getTopoSort(adjNode, adj, vis, st);
        }
        
        st.push(node);
    }

  public:
    vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) 
    {
        // create the list from edges
        vector<pair<int, int>> adj[V];
        
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            adj[u].push_back({v, wt});
        }
        
        // get the topoSort ordering
        vector<bool> vis(V, false);
        stack<int> st; // topo sort stack
        
        for (int node=0; node<V; node++)
        {
            if (!vis[node]) getTopoSort(node, adj, vis, st);
        }
        
        vector<int> shortestDst(V, INT_MAX);
        int src = 0;
        shortestDst[src] = 0;
        while(!st.empty())
        {
            int node = st.top();
            st.pop();
            
            // start relaxing edges for neighbours
            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int wt = it.second;
                
                
                // going from node to adjNode if node is reachable
                if (shortestDst[node] != INT_MAX && shortestDst[node] + wt < shortestDst[adjNode])
                {
                    shortestDst[adjNode] = shortestDst[node] + wt;
                }
            }
        }
        
        for (int node=0; node<V; node++)
        {
            if (shortestDst[node] == INT_MAX) shortestDst[node] = -1;
        }
        
        return shortestDst;
    }
};


//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges;
        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            edges.push_back(temp);
        }
        Solution obj;
        vector<int> res = obj.shortestPath(n, m, edges);
        for (auto x : res) {
            cout << x << " ";
        }
        cout << "\n";

        cout << "~"
             << "\n";
    }
}

// } Driver Code Ends