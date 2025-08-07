//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

//Position this line where user code will be pasted.
class Solution 
{
  private:
    void dfs1(int node, vector<vector<int>> &adj, vector<bool> &vis, stack<int> &st)
    {
        vis[node] = true;
        
        for (auto adjNode : adj[node])
        {
            if (!vis[adjNode]) dfs1(adjNode, adj, vis, st);
        }
        
        st.push(node);
    }

    void dfs2(int node, vector<int> adj[], vector<bool> &vis)
    {
        vis[node] = true;
        
        for (auto adjNode : adj[node])
        {
            if (!vis[adjNode]) dfs2(adjNode, adj, vis);
        }
    }
    
  public:
    int kosaraju(vector<vector<int>> &adj) 
    {
        int n = adj.size();
        
        // sort the edges in order of finish time
        stack<int> st;
        vector<bool> vis(n, false);
        
        for (int node=0; node<n; node++)
        {
            if (!vis[node]) dfs1(node, adj, vis, st);
        }
        
        // reverse all the edges
        vector<int> rev[n];
        for (int node=0; node<n; node++)
        {
            vis[node] = false;
            for (auto adjNode : adj[node])
            {
                rev[adjNode].push_back(node);
            }
        }
        
        // do the dfs on rev graph in order of finish time
        int scc = 0;
        while(!st.empty())
        {
            int node = st.top();
            st.pop();
            
            if (!vis[node])
                {
                    scc++;
                    dfs2(node, rev, vis);
                }
        }

        return scc;
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
        cout << obj.kosaraju(adj) << "\n";

        // cout << "~"
        //      << "\n";
    }

    return 0;
}

// } Driver Code Ends