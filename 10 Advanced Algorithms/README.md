# Advanced Algorithms

## Kosaraju's Algorithm (Strongly Connected Components)
- Only valid for Directed Graphs
- Number of SCCs
- Print the SCCs
### Algorithm
- Step1: Sort the nodes in order of finish time of DFS
- Step2: Reverse the graph
- Step3: Perform DFS in order of finish time (sorted nodes)
### Problem Link
https://www.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=strongly-connected-components-kosarajus-algo
### Code
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

## Tarjan's Algorithm: Bridges in Graph
- Bridge is an edge removing which increases the number of components
- Print all the bridges
### Algorithm
- Require: tInsertion[], tLow[] (apart from parents)
### Problem Link
https://leetcode.com/problems/critical-connections-in-a-network/submissions/1561315940/
### Code
```cpp
class Solution 
{
    int timer = 0;
private:
    void dfs(int node, int parent, vector<vector<int>> &adj, vector<bool> &vis, vector<int> &tInsertion, vector<int> &tLow, vector<vector<int>> &bridges)
    {
        vis[node] = true;

        tInsertion[node] = tLow[node] = timer;
        timer++;

        for (int adjNode : adj[node])
        {
            if (adjNode == parent) continue;

            if (!vis[adjNode])
            {
                dfs(adjNode, node, adj, vis, tInsertion, tLow, bridges);

                tLow[node] = min(tLow[node], tLow[adjNode]);

                // can node --> adjNode be a bridge
                if (tLow[adjNode] > tInsertion[node]) bridges.push_back({node, adjNode});
            }

            else
            {
                tLow[node] = min(tLow[node], tLow[adjNode]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
    {
        vector<vector<int>> adj(n);

        for (auto edge : connections)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<bool> vis(n, false);

        vector<int> tInsertion(n), tLow(n);

        vector<vector<int>> bridges;

        for (int i=0; i<n; i++)
        {
            if (!vis[i]) dfs(i, -1, adj, vis, tInsertion, tLow, bridges);
        }

        return bridges;
    }
};
```



# Articulation Point in Graphf