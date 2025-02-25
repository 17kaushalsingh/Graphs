# Bipartite Graphs
- If you can color the graph with two colors such that no two adjacent nodes have the same color
- Then it is a bipartite graph
- A bipartite graph is a type of graph in which the set of vertices can be divided into two distinct groups (or partitions) such that no two vertices within the same group are adjacent.
- In other words, all edges in the graph connect a vertex from one group to a vertex in the other group.
- A bipartite graph can be colored with two colors such that no two adjacent vertices share the same color. This means we can divide the graph’s vertices into two distinct sets where:
- All edges connect vertices from one set to vertices in the other set.
- No edges exist between vertices within the same set.

## Properties of Bipartite Graphs:
- No Odd-Length Cycles: A graph is bipartite if and only if it does not contain a cycle of odd length.
- 2-Colorability: A bipartite graph can be colored using only two colors so that no two adjacent vertices have the same color.
- Matching and Maximum Matching: Bipartite graphs are useful in optimization problems, such as maximum matching in job assignment problems.

## Checking for Bipartite Graph Using BFS
https://www.geeksforgeeks.org/problems/bipartite-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=bipartite-graph
```cpp
class Solution {
  public:
    bool isBipartite(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        
        queue<pair<int, int>> q; // node, color
        vector<int> color(n, -1);
        // -1 not visited
        // 0 red
        // 1 black
        
        q.push({0,0});
        color[0] = 0;
        
        while(!q.empty())
        {
            int node = q.front().first;
            int col = q.front().second;
            q.pop();
            
            for (auto adjNode : adj[node])
            {
                if (color[adjNode] == -1) // not yet touched
                {
                    int ncolor;
                    (col == 0) ? (ncolor = 1) : (ncolor = 0);
                    q.push({adjNode, ncolor});
                    color[adjNode] = ncolor;
                }
                
                else if (color[adjNode] == col) return false;
            }
        }
        
        return true;
    }
};
```

## Checking for Bipartite Graph Using DFS
https://www.geeksforgeeks.org/problems/bipartite-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=bipartite-graph
```cpp
class Solution 
{
  private:
    bool dfs(int node, int col, vector<vector<int>> &adj, vector<int> &color)
    {
        color[node] = col;
        
        for (auto adjNode : adj[node])
        {
            if (color[adjNode] == -1)
            {
                int ncolor = (col == 0) ? 1 : 0;
                if (dfs(adjNode, ncolor, adj, color) == false) return false;
            }
            
            if (color[adjNode] == col) return false;
        }
        
        return true;
    }
  public:
    bool isBipartite(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        vector<int> color(n, -1);
        
        for (int i=0; i<n; i++)
        {
            if (color[i] == -1)
            {
                if (dfs(i, 0, adj, color) == false) return false;
            }
        }
        
        return true;
        
    }
};
```
