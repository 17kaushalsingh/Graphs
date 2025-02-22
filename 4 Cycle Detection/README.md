# Cycle Detection
- Try to visit all the children (neighbours) of a node which are not parents
- If such a node is already visited by someone else
- It means there is a cycle

## Undirected Graph Using BFS

https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
```cpp
class Solution {
  public:
    bool detectCycle(int node, vector<vector<int>> adj, vector<bool> &isVisited)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(node, -1));
        isVisited[node] = true;
    
        while(!q.empty())
        {
            auto front = q.front();
            q.pop();
    
            int frontNode = front.first;
            int parent = front.second;
    
            for (auto adjNode : adj[frontNode])
            {
                if (adjNode == parent) continue;
    
                if (isVisited[adjNode]) return true;
    
                q.push(make_pair(adjNode, frontNode));
                isVisited[adjNode] = true;
            }
        }
    
        return false;
    }

    bool isCycle(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        
        vector<bool> isVisited(n, false);
    
        for (int node=0; node<n; node++)
        {
            if (!isVisited[node])
            {
                if(detectCycle(node, adj, isVisited)) return true;
            }
        }
        
        return false;
    }
};
```

## Undirected Graph Using DFS
https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
```cpp
class Solution {
  public:
    bool detectCycle(int node, int parent, vector<vector<int>>& adj, vector<bool> &isVisited)
    {
        isVisited[node] = true;
    
        for (auto adjNode : adj[node])
        {
            if (adjNode == parent) continue;
    
            if (isVisited[adjNode]) return true; // cycle detected
            
            if (detectCycle(adjNode, node, adj, isVisited) == true) return true; // cycle detected
        }
    
        return false;
    }

    bool isCycle(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        
        vector<bool> isVisited(n, false);
    
        for (int node=0; node<n; node++)
        {
            if (!isVisited[node])
            {
                if(detectCycle(node, -1, adj, isVisited)) return true;
            }
        }
        
        return false;
    }
};
```

## Directed Graph Using DFS
- Use a path visited array
https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=detect-cycle-in-a-directed-graph
```cpp
class Solution 
{
  private:
    bool checkForCycle(int node, vector<vector<int>> &adj, vector<bool> &isVisited, vector<bool> &isPathVisited)
    {
        isVisited[node] = true;
        isPathVisited[node] = true;
        
        for (auto adjNode : adj[node])
        {
            if (!isVisited[adjNode])
            {
                if (checkForCycle(adjNode, adj, isVisited, isPathVisited)) return true;
            }
            
            if (isPathVisited[adjNode]) return true;
        }
        
        isPathVisited[node] = false;
        
        return false;
    }
    
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(vector<vector<int>> &adj) 
    {
        int n = adj.size();
        
        vector<bool> isVisited(n, false), isPathVisited(n, false);
        
        for (int i=0; i<n; i++)
        {
            if (!isVisited[i])
            {
                if (checkForCycle(i, adj, isVisited, isPathVisited)) return true;
            }
        }
        
        return false;
    }
};
```

## Directed Graph Usinf BFS (Kahns Algorithm OR Topo Sort)
- Check if the topoSort.size() == n_nodes
https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=detect-cycle-in-a-directed-graph
```cpp
class Solution 
{
  private:
    vector<int> getTopoSort(int n, vector<vector<int>> &adj)
    {
        vector<int> topo;
        
        vector<int> inDeg(n, 0);
        for (int i=0; i<n; i++)
        {
            for (auto adjNode : adj[i]) inDeg[adjNode]++;
        }
        
        queue<int> q;
        
        for (int i=0; i<n; i++) if (inDeg[i] == 0) q.push(i);
        
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            
            for (auto adjNode : adj[node])
            {
                inDeg[adjNode]--;
                
                if (inDeg[adjNode] == 0) q.push(adjNode);
            }
        }
        
        return topo;
    }
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(vector<vector<int>> &adj) 
    {
        int n = adj.size();
        
        vector<int> topoSort = getTopoSort(n, adj);
        
        return (topoSort.size() != n);
    }
```

## Eventual Safe States
- Everyone who is part of the cycle 
- And everyone who leads to a cycle can not be a safe node
- All others are safe nodes
https://www.geeksforgeeks.org/problems/eventual-safe-states/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=eventual-safe-states
```cpp
class Solution 
{
  private:
    bool dfs(int node, vector<int> adj[], vector<bool> &isVisited, vector<bool> &isPathVisited, vector<bool> &isSafeNode)
    {
       isVisited[node] = true;
       isPathVisited[node] = true;
       isSafeNode[node] = false;
       
       for (auto adjNode : adj[node])
       {
           if (!isVisited[adjNode])
           {
               if (dfs(adjNode, adj, isVisited, isPathVisited, isSafeNode)) return true;
           }
           
           else if (isPathVisited[adjNode]) return true;
       }
       
       isPathVisited[node] = false;
       isSafeNode[node] = true;
       return false;
    }
  public:
    vector<int> eventualSafeNodes(int V, vector<int> adj[]) 
    {
        int n = V;
        
        vector<bool> isVisited(n, false);
        vector<bool> isPathVisited(n, false);
        vector<bool> isSafeNode(n, false);
        
        for (int i=0; i<n; i++)
        {
            if (!isVisited[i]) dfs(i, adj, isVisited, isPathVisited, isSafeNode);
        }
        
        vector<int> safeNodes;
        for (int i=0; i<n; i++) if (isSafeNode[i]) safeNodes.push_back(i);
        
        return safeNodes;
    }
};
```
