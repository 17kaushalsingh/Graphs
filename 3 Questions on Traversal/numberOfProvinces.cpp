//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function Template for C++

class Solution 
{
  private:
    void dfsTraversal(int node, vector<vector<int>> &adj, vector<bool> &isVisited)
    {
        isVisited[node] = true;
        
        for (int adjNode = 0; adjNode < adj[node].size(); adjNode++)
        {
            if (adjNode != node && adj[node][adjNode] == 1)
            {
                if (!isVisited[adjNode]) dfsTraversal(adjNode, adj, isVisited);
            }
        }
    }
    
  public:
    int numProvinces(vector<vector<int>> adj, int V) 
    {
        int numProvinces = 0;
        
        vector<bool> isVisited(V, false);
        
        for (int node=0; node<V; node++)
        {
            if (!isVisited[node])
            {
                numProvinces++;
                dfsTraversal(node, adj, isVisited);
            }
        }
        
        return numProvinces;
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int V,x;
        cin>>V;
        
        vector<vector<int>> adj;
        
        for(int i=0; i<V; i++)
        {
            vector<int> temp;
            for(int j=0; j<V; j++)
            {
                cin>>x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }
        

        Solution ob;
        cout << ob.numProvinces(adj,V) << endl;
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends