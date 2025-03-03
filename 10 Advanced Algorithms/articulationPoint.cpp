//{ Driver Code Starts
//Initial Template for C++

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends

//User function Template for C++

class Solution 
{
  int timer = 0;
  
  private:
    void dfs(int node, int parent, vector<int>adj[], vector<bool> &vis, vector<int> &tInsertion, vector<int> &tLow, vector<bool> &isArticulation)
    {
        vis[node] = true;
        int child = 0;
        
        tInsertion[node] = tLow[node] = timer;
        timer++;
        
        for (int adjNode : adj[node])
        {
            if (adjNode == parent) continue;
            
            if (! vis[adjNode])
            {
                child++;
                dfs(adjNode, node, adj, vis, tInsertion, tLow, isArticulation);
                
                tLow[node] = min(tLow[node], tLow[adjNode]);
                
                // can node be an articulation point
                // tLow[adjNode] < tInsertion[node] okay
                if (parent != -1 && tLow[adjNode] >= tInsertion[node]) isArticulation[node] = true;
            }
            
            else
            {
                tLow[node] = min(tLow[node], tInsertion[adjNode]);
            }
        }
        
        if (parent == -1 && child > 1) isArticulation[node] = true;
    }
    
  public:
    vector<int> articulationPoints(int n, vector<int>adj[]) 
    {
        vector<bool> vis(n, false);
        
        vector<int> tInsertion(n), tLow(n);
        
        vector<bool> isArticulation(n, false);
        
        for (int i=0; i<n; i++)
        {
            if (!vis[i]) dfs(i, -1, adj, vis, tInsertion, tLow, isArticulation);
        }
        
        vector<int> ans;
        for (int i=0; i<n; i++)
        {
            if (isArticulation[i]) ans.push_back(i);
        }
        
        if (ans.size() == 0) return {-1};
        return ans;
    }
};


//{ Driver Code Starts.

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
		cin >> V >> E;
		vector<int>adj[V];
		for(int i = 0; i < E; i++){
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		Solution obj;
		vector<int> ans = obj.articulationPoints(V, adj);
		for(auto i: ans)cout << i << " ";
		cout << "\n";
	
cout << "~" << "\n";
}
	return 0;
}
// } Driver Code Ends