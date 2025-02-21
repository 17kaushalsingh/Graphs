//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution 
{
  public:
  
    
  public:
    vector<int> eventualSafeNodes(int V, vector<int> adj[]) 
    {
        int n = V;
        
        vector<int> revGraph[n];
        
        for (int i=0; i<n; i++)
        {
            for (auto adjNode : adj[i])
            {
                // i --> adjNode
                // we want to reverse it
                revGraph[adjNode].push_back(i);
            }
        }
        
        vector<int> inDeg(n, 0); // an array with size n and all entries marked as 0
        
        for (int i=0; i<n; i++)
        {
            for (auto adjNode : revGraph[i])
            {
                inDeg[adjNode]++;
            }
        }
        
        queue<int> q;
        for (int node=0; node<n; node++) if(inDeg[node] == 0) q.push(node);
        
        vector<int> safeNodes;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            
            safeNodes.push_back(node);
            
            for (auto adjNode : revGraph[node])
            {
                inDeg[adjNode]--;
                
                if (inDeg[adjNode] == 0) q.push(adjNode);
            }
        }
        
        sort(safeNodes.begin(), safeNodes.end());
        
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