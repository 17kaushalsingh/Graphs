//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution 
{
  private:
    void dfs(int node, vector<vector<int>> &adj, vector<bool> &isVisited, stack<int> &st)
    {
        isVisited[node] = true;
        
        for (auto adjNode : adj[node])
        {
            if (!isVisited[adjNode]) dfs(adjNode, adj, isVisited, st);
        }
        
        st.push(node);
    }
  public:

    vector<int> topologicalSort(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        
        stack<int> st;
        vector<bool> isVisited(n, false);
        
        for (int i=0; i<n; i++)
        {
            if (!isVisited[i]) dfs(i, adj, isVisited, st);
        }
        
        vector<int> topo;
        while(!st.empty())
        {
            topo.push_back(st.top());
            st.pop();
        }
        
        return topo;
    }
};

//{ Driver Code Starts.

/*  Function to check if elements returned by user
 *   contains the elements in topological sorted form
 *   V: number of vertices
 *   *res: array containing elements in topological sorted form
 *   adj[]: graph input
 */
int check(int V, vector<int> &res, vector<vector<int>> adj) {

    if (V != res.size())
        return 0;

    vector<int> map(V, -1);
    for (int i = 0; i < V; i++) {
        map[res[i]] = i;
    }
    for (int i = 0; i < V; i++) {
        for (int v : adj[i]) {
            if (map[i] > map[v])
                return 0;
        }
    }
    return 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, E;
        cin >> N >> E;
        int u, v;

        vector<vector<int>> adj(N);

        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        vector<int> res = obj.topologicalSort(adj);

        cout << check(N, res, adj) << endl;

        cout << "~"
             << "\n";
    }

    return 0;
}
// } Driver Code Ends