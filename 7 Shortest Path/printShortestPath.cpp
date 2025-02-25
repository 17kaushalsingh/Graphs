//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) 
    {
        vector<pair<int, int>> adj[n+1];
        
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // dst, node
        vector<int> shortestDst(n+1, INT_MAX);
        vector<int> parent(n+1, -1);
        
        shortestDst[1] = 0;
        parent[1] = 1;
        pq.push({0, 1});
        
        while(!pq.empty())
        {
            int dst =pq.top().first;
            int node = pq.top().second;
            pq.pop();
            
            if (shortestDst[node] != INT_MAX)
            {
                for (auto it : adj[node])
                {
                    int adjNode = it.first;
                    int wt = it.second;
                    
                    if (dst + wt < shortestDst[adjNode])
                    {
                        shortestDst[adjNode] = dst + wt;
                        pq.push({dst+wt, adjNode});
                        parent[adjNode] = node;
                    }
                }
            }
        }
        
        if (shortestDst[n] == INT_MAX) return{-1};
        
        // backtrack the path using parent array
        vector<int> path;
        
        int lastStep = n;
        while(parent[lastStep] != lastStep)
        {
            path.push_back(lastStep);
            lastStep = parent[lastStep];
        }
        path.push_back(lastStep);
        
        
        // add the path weight to reach n from 1
        path.push_back(shortestDst[n]);
        
        // reverse the path to get the correct order
        reverse(path.begin(), path.end());
        
        return path;
        
    }
};


//{ Driver Code Starts.
int main() {
    // your code goes here
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges;
        map<pair<int, int>, int> mp;
        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            edges.push_back(temp);
            mp[{edges.back()[0], edges.back()[1]}] = edges.back()[2];
            mp[{edges.back()[1], edges.back()[0]}] = edges.back()[2];
        }

        Solution obj;
        vector<int> res = obj.shortestPath(n, m, edges);
        int ans = 0;
        for (int i = 2; i < res.size(); i++) {
            ans += mp[{res[i], res[i - 1]}];
        }
        if (ans == res[0]) {

        } else if (res.size() == 1 && res[0] == -1)
            ans = res[0];
        else
            ans = -2;
        cout << ans << endl;
        cout << "~" << endl;
    }
}

// } Driver Code Ends