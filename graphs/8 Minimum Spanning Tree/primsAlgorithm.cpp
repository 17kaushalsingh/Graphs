class Solution 
{
  public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) 
    {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq; // wt, node, parent
        vector<int> vis(V, false);
        
        // initial config
        pq.push({0, 0, -1}); // -1 signifies the first node
        
        int mstSum = 0;
        vector<pair<int, int>> mstEdges;

        // process the queue
        while(!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            
            int wt = it[0];
            int node = it[1];
            int parent = it[2];
            
            if (parent == -1) // first node, not a part of MST
            {
                vis[node] = true;
            }
            
            if (!vis[node]) // this node/edge is not yet a part of mst, make it a part of mst
            {
                vis[node] = true;
                mstSum += wt;
                mstEdges.push_back({node, parent});
            }
            
            for (auto it : adj[node])
            {
                int adjNode = it[0];
                int adjWt = it[1];
                
                if (!vis[adjNode])
                {
                    pq.push({adjWt, adjNode, node});
                }
            }
        }
        
        return mstSum;
    }
};