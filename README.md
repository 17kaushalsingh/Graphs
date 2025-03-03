<details>
<summary> 1. Basic Terms and Representation of Graphs </summary>
</details>

<details>
<summary> 2. Traversals </summary>
</details>

<details>
<summary> 3. Questions On Traversals </summary>
</details>

<details>
<summary> 4. Cycle Detection </summary>

# Cycle Detection
- Try to visit all the children (neighbours) of a node which are not parents <br>
- If such a node is already visited by someone else <br>
- It means there is a cycle

## Undirected Graph Using BFS
### Problem Link
https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
### Code
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
### Problem Link
https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
### Code
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
### Problem Link
https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=detect-cycle-in-a-directed-graph
### Code
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
### Problem Link
https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=detect-cycle-in-a-directed-graph
### Code
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
- Everyone who is part of the cycle <br>
- And everyone who leads to a cycle can not be a safe node <br>
- All others are safe nodes
### Problem Link
https://www.geeksforgeeks.org/problems/eventual-safe-states/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=eventual-safe-states
### Code
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


</details>

<details>
<summary> 5. Bipartite Graphs </summary>

# Bipartite Graphs
- If you can color the graph with two colors such that no two adjacent nodes have the same color, then it is a bipartite graph  <br>
- A bipartite graph is a type of graph in which the set of vertices can be divided into two distinct groups (or partitions) such that no two vertices within the same group are adjacent <br>
- In other words, all edges in the graph connect a vertex from one group to a vertex in the other group <br>
- A bipartite graph can be colored with two colors such that no two adjacent vertices share the same color. This means we can divide the graph’s vertices into two distinct sets where: <br>
-- All edges connect vertices from one set to vertices in the other set <br>
-- No edges exist between vertices within the same set

## Properties of Bipartite Graphs:
- No Odd-Length Cycles: A graph is bipartite if and only if it does not contain a cycle of odd length <br>
- 2-Colorability: A bipartite graph can be colored using only two colors so that no two adjacent vertices have the same color <br>
- Matching and Maximum Matching: Bipartite graphs are useful in optimization problems, such as maximum matching in job assignment problems

## Checking for Bipartite Graph Using BFS
### Problem Link
https://www.geeksforgeeks.org/problems/bipartite-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=bipartite-graph
### Code
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
### Problem Link
https://www.geeksforgeeks.org/problems/bipartite-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=bipartite-graph
### Code
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


</details>

<details>
<summary> 6. Topological Sorting </summary>

# Topological Sorting
- Only exists for DAG (Directed Acyclic Graphs) <br>
- Any linear ordering of nodes such that <br>
- If there is an edge between u and v <br>
- u always appers before v in the sorted list <br>

## DFS Implementation
### Problem Link
https://www.geeksforgeeks.org/problems/topological-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=topological-sort
### Code
```cpp
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
```

## BFS Implementation Kahn's Algorithm
- use inDegree array
### Problem Link
https://www.geeksforgeeks.org/problems/topological-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=topological-sort
### Code
```cpp
class Solution 
{
  private:
    
  public:
    // Function to return list containing vertices in Topological order.
    vector<int> topologicalSort(vector<vector<int>>& adj) 
    {
        int n = adj.size();
        
        // get indegree of all the nodes
        vector<int> inDegree(n, 0);
        for (int u=0; u<n; u++)
        {
            for (auto v : adj[u])
            {
                //Edge: u --> v
                inDegree[v]++;
            }
        }
        
        // put all elements with inDegree 0 to queue
        queue<int> q;
        
        for (int i=0; i<n; i++) if (inDegree[i] == 0) q.push(i);
        
        // start processing the queue and put front elements with inDegree 0 in ans
        vector<int> topoSort;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            
            topoSort.push_back(node);
            
            for (auto adjNode : adj[node])
            {
                // Edge: node --> adjNode
                inDegree[adjNode]--;
                
                if (inDegree[adjNode] == 0) q.push(adjNode);
            }
        }
        
        return topoSort;
    }
```



## Course Scheduler I
### Problem Link
https://www.geeksforgeeks.org/problems/prerequisite-tasks/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=prerequisite-tasks
### Code
```cpp
class Solution 
{
  private:
    vector<int> getTopoSort(int n, vector<int> adj[])
    {
        vector<int> inDeg(n, 0);
        
        for (int i=0; i<n; i++)
        {
            for (auto adjNode : adj[i]) inDeg[adjNode]++;
        }
        
        queue<int> q;
        
        for (int i=0; i<n; i++) if (inDeg[i] == 0) q.push(i);
        
        vector<int> ans;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);
            
            for (auto adjNode : adj[node])
            {
                inDeg[adjNode]--;
                
                if (inDeg[adjNode] == 0) q.push(adjNode);
            }
        }
        
        return ans;
    }
    
  public:
    bool isPossible(int N, int P, vector<pair<int, int> >& prerequisites) 
    {
        vector<int> adj[N];
        
        for (int i=0; i<P; i++)
        {
            // Edge: [0 1] 1 --> 0.  u --> v
            int u = prerequisites[i].first;
            int v = prerequisites[i].second;
            
            adj[v].push_back(u);
        }
        
        vector<int> topo = getTopoSort(N, adj);
        
        return (topo.size() == N);
    }
};
```

## Course Scheduler II
### Problem Link
https://www.geeksforgeeks.org/problems/course-schedule/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=course-schedule
### Code
```cpp
class Solution
{
  private:
    vector<int> getTopoSort(int n, vector<int> adj[])
    {
        vector<int> inDeg(n, 0);
        
        for (int i=0; i<n; i++)
        {
            for (auto adjNode : adj[i]) inDeg[adjNode]++;
        }
        
        queue<int> q;
        for (int i=0; i<n; i++) if (inDeg[i] == 0) q.push(i);
        
        vector<int> ans;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);
            
            for (auto adjNode : adj[node])
            {
                inDeg[adjNode]--;
                
                if (inDeg[adjNode] == 0) q.push(adjNode);
            }
        }
        
        return ans;
    }
    
  public:
    vector<int> findOrder(int n, int m, vector<vector<int>> prerequisites) 
    {
        vector<int> adj[n];
        
        for (int i=0; i<m; i++)
        {
            int u = prerequisites[i][1];
            int v = prerequisites[i][0];
            
            adj[u].push_back(v);
        }
        
        vector<int> topo = getTopoSort(n, adj);
        
        if (topo.size() != n) return {};
        return topo;
    }
};
```


## Eventual Safe States
- Reverse the edges of the graph <br>
- Perform a basic Topo Sort, return topo vector of the reversed graph
### Problem Link
https://www.geeksforgeeks.org/problems/eventual-safe-states/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=eventual-safe-states
### Code
```cpp
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
```


## Alien Dictionary
- Represent chars as nodes of a graph <br>
- Figure out why a word appears before the other and create the graph basis that <br>
- Apply topologocal sort
### Problem Link
https://www.geeksforgeeks.org/problems/alien-dictionary/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=alien-dictionary
### Code
```cpp
class Solution 
{
private:
    // Helper function
    // checks if order is invalid when w1 is longer than w2 and w2 is a prefix of w1
    bool checkInvalidOrder(string &w1, string &w2) 
    {
        if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2) return true;

        return false;
    }
    
    vector<int> getTopoSort(int n, vector<int> adj[], vector<int> &inDeg, vector<bool> &exists) {
        queue<int> q;
        for (int i = 0; i < n; i++) 
        {
            if (inDeg[i] == 0 && exists[i]) q.push(i);
        }
        
        vector<int> topo;
        while (!q.empty()) 
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            
            for (int adjNode : adj[node]) 
            {
                inDeg[adjNode]--;
                if (inDeg[adjNode] == 0 && exists[adjNode]) q.push(adjNode);
            }
        }
        
        return topo;
    }
    
public:
    string findOrder(vector<string>& words) 
    {
        int n = words.size();
        
        // adjacency list and in-degree array
        vector<int> adj[26];
        vector<int> inDeg(26, 0);
        vector<bool> exists(26, false);  // Track which characters exist
        
        // Mark existing characters
        for (string word : words) 
        {
            for (char ch : word) exists[ch - 'a'] = true;
        }
        
        // Build graph from adjacent words
        for (int i = 0; i < n - 1; i++) 
        {
            string w1 = words[i];
            string w2 = words[i + 1];
            
            // Check invalid case: if w1 is longer and w2 is prefix of w1
            if (checkInvalidOrder(w1, w2)) return "";
            
            // Find first differing character
            int len = min(w1.size(), w2.size());
            
            for (int j = 0; j < len; j++) 
            {
                if (w1[j] != w2[j]) 
                {
                    int u = w1[j] - 'a';
                    int v = w2[j] - 'a';
                    adj[u].push_back(v);
                    inDeg[v]++;
                    break;
                }
            }
        }
        
        // Get topological sort
        vector<int> topo = getTopoSort(26, adj, inDeg, exists);
        
        // Check for cycle: if topo sort doesn't include all nodes with edges
        int count = 0;
        for (int i = 0; i < 26; i++) 
        {
            if (exists[i]) count++;
        }
        
        string ans = "";
        
        // Cycle detected
        if (topo.size() != count) return ans;

        // Construct result string
        for (int x : topo) 
        {
            if (exists[x]) 
            {
                ans += (char)(x + 'a');
            }
        }
        
        return ans;
    }
};
```



</details>

<details>
<summary> 7. Shortest Path </summary>

# Shortest Path

# Directed Acyclic Graph - Topological Sort
- Get topoSort answer in stack <br>
- Take the nodes from stack and start relaxing edges
### Problem Link
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=direct-acyclic-graph
### Code
```cpp
class Solution 
{
  private:
    void getTopoSort(int node, vector<pair<int, int>> adj[], vector<bool> &vis, stack<int> &st)
    {
        vis[node] = true;
        
        for (auto it : adj[node])
        {
            int adjNode = it.first;
            if (!vis[adjNode]) getTopoSort(adjNode, adj, vis, st);
        }
        
        st.push(node);
    }

  public:
    vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) 
    {
        // create the list from edges
        vector<pair<int, int>> adj[V];
        
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            adj[u].push_back({v, wt});
        }
        
        // get the topoSort ordering
        vector<bool> vis(V, false);
        stack<int> st; // topo sort stack
        
        for (int node=0; node<V; node++)
        {
            if (!vis[node]) getTopoSort(node, adj, vis, st);
        }
        
        vector<int> shortestDst(V, INT_MAX);
        int src = 0;
        shortestDst[src] = 0;
        while(!st.empty())
        {
            int node = st.top();
            st.pop();
            
            // start relaxing edges for neighbours
            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int wt = it.second;
                
                
                // going from node to adjNode if node is reachable
                if (shortestDst[node] != INT_MAX && shortestDst[node] + wt < shortestDst[adjNode])
                {
                    shortestDst[adjNode] = shortestDst[node] + wt;
                }
            }
        }
        
        for (int node=0; node<V; node++)
        {
            if (shortestDst[node] == INT_MAX) shortestDst[node] = -1;
        }
        
        return shortestDst;
    }
};
```

# Undirected Acyclic Graph - Unit Weights - Plain BFS
- Plain BFS with relaxation of edges
### Problem Link
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=shortest-path-in-undirected-graph-having-unit-distance
### Code
```cpp
class Solution {
  public:
    // Function to find the shortest path from source to all other nodes
    vector<int> shortestPath(vector<vector<int>>& adj, int src) 
    {
        int n = adj.size();
        
        queue<pair<int, int>> q; // node, dst
        vector<int> shortestDst(n, INT_MAX);
        
        shortestDst[src] = 0;
        q.push({src, 0});
        
        while(!q.empty())
        {
            int node = q.front().first;
            int dst = q.front().second;
            q.pop();
            
            for (auto adjNode : adj[node])
            {
                // if reachable at the current node and get a better way, relax the edge
                if (shortestDst[node] != INT_MAX && dst + 1 < shortestDst[adjNode])
                {
                    shortestDst[adjNode] = dst + 1;
                    q.push({adjNode, dst + 1});
                }
            }
        }
        
        for (int i=0; i<n; i++) if (shortestDst[i] == INT_MAX) shortestDst[i] = -1;
        
        return shortestDst;
    }
};
```

## Word Lader 1
### Problem Link
### Code

## Word Ladder 2
### Problem Link
### Code

# Dijkstras Algorithm
- TC: E logV <br>
- Can be done via Queue, PriorityQueue or Set

## Using Priority Queue
- Require a minHeap data structure <br>
- Does not work for cycles and negative edge weights <br>
- TC: E logV <br>
- Why PQ: Saves some iterations
### Problem Link
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=implementing-dijkstra-set-1-adjacency-matrix
### Code
```cpp
class Solution {
  public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex src.
    vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src) 
    {
        int n = adj.size();
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> shortestDst(n, INT_MAX);
        
        pq.push({0, src});
        shortestDst[src] = 0;
        
        while(!pq.empty())
        {
            int dst = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            for (auto it : adj[u])
            {
                int v = it.first;
                int wt = it.second;
                
                if (shortestDst[u] != INT_MAX)
                {
                    if (dst + wt < shortestDst[v])
                    {
                        shortestDst[v] = dst + wt;
                        pq.push({dst+wt, v});
                    }
                }
            }
        }
        
        return shortestDst;
    }
};
```

## Using Set
- Set stores unique values and in sorted order (ascending order, the smallest at the top) <br>
- Set can erase some elements to optimize the iterations <br>
- Investing logN to delete an element and save some iterations later <br>
- So can say much about which is better in terms of TC
### Problem Link
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=implementing-dijkstra-set-1-adjacency-matrix
### Code
```cpp
class Solution {
  public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex src.
    vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src) 
    {
        int n = adj.size();
        
        vector<int> shortestDst(n, INT_MAX);
        set<pair<int, int>> set;
        
        set.insert({0, src});
        shortestDst[src] = 0;
        
        while(!set.empty())
        {
            auto it = *(set.begin());
            int dst = it.first;
            int node = it.second;
            set.erase(it);
            
            for (auto it : adj[node])
            {
                int wt = it.second;
                int adjNode = it.first;
                
                if (dst + wt < shortestDst[adjNode])
                {
                    if (shortestDst[adjNode] != INT_MAX) set.erase({shortestDst[adjNode], adjNode});
                    
                    shortestDst[adjNode] = dst + wt;
                    set.insert({dst+wt, adjNode});
                }
            }
        }
        
        return shortestDst;
    }
};
```

## Printing Shortest Path
- Modify Dijksras to try to remember where are you coming from <br>
- Use a parent array to track where a new node is pushed from in the PQ
### Problem Link
https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=shortest-path-in-weighted-undirected-graph
### Code
```cpp
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
```

## Shortest Distance in Binary Maze
### Problem Link
https://www.geeksforgeeks.org/problems/shortest-path-in-a-binary-maze-1655453161/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=shortest-path-in-a-binary-maze
### Code
```cpp
class Solution 
{
  private:
    bool valid(int row, int col, int maxRow, int maxCol)
    {
        return (row >= 0 && row < maxRow && col >= 0 && col < maxCol);
    }
    
  public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source, pair<int, int> destination) 
    {
        int n = grid.size();
        int m = grid[0].size();
        
        int srcRow = source.first;
        int srcCol = source.second;
        
        int dstRow = destination.first;
        int dstCol = destination.second;
        
        vector<vector<int>> shortestDst(n, vector<int>(m, INT_MAX));
        queue<pair<int, pair<int, int>>> pq; // dst, (row, col)
        
        pq.push({0, {srcRow, srcCol}});
        shortestDst[srcRow][srcCol] = 0;
        
        while(!pq.empty())
        {
            auto it = pq.front();
            pq.pop();
            
            int dst = it.first;
            int row = it.second.first;
            int col = it.second.second;
            
            if (shortestDst[row][col] == INT_MAX) continue;
            if (row == dstRow && col == dstCol) break;
            
            int delrow[] = {1, -1, 0, 0};
            int delcol[] = {0, 0, -1, 1};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if (valid(nrow, ncol, n, m) && grid[nrow][ncol] == 1 && dst+1 < shortestDst[nrow][ncol])
                {
                    shortestDst[nrow][ncol] = dst+1;
                    pq.push({dst+1, {nrow, ncol}});
                }
            }
        }
        
        int ans = shortestDst[dstRow][dstCol];
        
        if (ans == INT_MAX) return -1;
        
        return ans;
    }
};
```

## Path with Minimum Effort
### Problem Link
https://www.geeksforgeeks.org/problems/path-with-minimum-effort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=path-with-minimum-effort
### Code
```cpp
class Solution 
{
  private:
    bool isValid(int row, int col, int n, int m)
    {
        return (row >= 0 && row < n && col >= 0 && col < m);
    }
    
  public:
    int MinimumEffort(int rows, int columns, vector<vector<int>> &heights) 
    {
        // effort: max(abs diff in two consecutive cells of the root)
        
        vector<vector<int>> minimumEffort(rows, vector<int>(columns, INT_MAX));
        // minEffort, row, col
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        
        minimumEffort[0][0] = 0;
        pq.push({0, {0, 0}});
        
        while(!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            
            int effort = it.first;
            int row = it.second.first;
            int col = it.second.second;
            
            // iterate on neighbours
            int delRow[] = {0, 0, -1, 1};
            int delCol[] = {-1, 1, 0, 0};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + delRow[i];
                int ncol = col + delCol[i];
                
                if (isValid(nrow, ncol, rows, columns))
                {
                    int newEffort = max(effort, abs(heights[row][col] - heights[nrow][ncol]));
                    
                    if (newEffort < minimumEffort[nrow][ncol])
                    {
                        minimumEffort[nrow][ncol] = newEffort;
                        pq.push({newEffort, {nrow, ncol}});
                    }
                }
            }
        }
        
        return minimumEffort[rows-1][columns-1];
    }
};
```



## Cheapest Flights Within K Stops
- Make decision based on stops rather than price <br>
- No PQ required
### Problem Link
https://www.geeksforgeeks.org/problems/cheapest-flights-within-k-stops/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=cheapest-flights-within-k-stops
### Code
```cpp
  public:
    int CheapestFLight(int n, vector<vector<int>>& flights, int src, int dst, int K)  
    {
        vector<pair<int, int>> adj[n];
        
        for (flight : flights)
        {
            int u = flight[0];
            int v = flight[1];
            int wt = flight[2];
            
            adj[u].push_back({v, wt});
        }
        
        queue<pair<int, pair<int, int>>> q; // stops, city, price
        vector<int> minPrice(n, INT_MAX);
        
        q.push({0, {src, 0}});
        minPrice[src] = 0;
        
        while(!q.empty())
        {
            auto it = q.front();
            q.pop();
            
            int stops = it.first;
            int city = it.second.first;
            int price = it.second.second;
            
            if (stops > K) continue;
            
            // if (city == dst) continue;
            
            for (auto it : adj[city])
            {
                int adjCity = it.first;
                int addPrice = it.second;
                
                if (price + addPrice < minPrice[adjCity])
                {
                    minPrice[adjCity] = price + addPrice;
                    q.push({stops+1, {adjCity, price + addPrice}});
                }
            }
        }
        
        int ans = minPrice[dst];
        if (ans == INT_MAX) return -1;
        return ans;
    }
};
```

## Minimum Multiplications to reach End
### Problem Link
https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=minimum-multiplications-to-reach-end
### Code
```cpp
class Solution 
{
  private:
    
  public:
    int minimumMultiplications(vector<int>& arr, int start, int end) 
    {
        int n = arr.size();
        
        vector<int> steps(100001, INT_MAX);
        queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; // seteps, val
        
        q.push({0, start});
        steps[start] = 0;
        
        while(!q.empty())
        {
            int step = q.front().first;
            int val = q.front().second;
            q.pop();
            
            if (val == end) return step;
            
            for (int i=0; i<n; i++)
            {
                int newVal = (val * arr[i]) % 100000;
                
                if (1 + step < steps[newVal])
                {
                    steps[newVal] = 1 + step;
                    q.push({1+step, newVal});
                }
            }
        }
        
        int ans = steps[end];
        
        if (ans == INT_MAX) return -1;
        return ans;
    }
};
```

## Number of Ways to Arrive at a Destination
- Have a ways array to count the num ways to arrive at a destination <br>
- == means a new path with same min dis/time <br>
- < means a new path with the better dis/time
### Problem Link
https://www.geeksforgeeks.org/problems/number-of-ways-to-arrive-at-destination/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=%2Fnumber-of-ways-to-arrive-at-destination
### Code
```cpp
class Solution 
{
    int mod = (int)(1e9 + 7);
  public:
    int countPaths(int n, vector<vector<int>>& roads) 
    {
        vector<vector<pair<int, int>>> adj(n);
        
        for (auto road : roads)
        {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }
        
        vector<long long int> minTime(n, INT_MAX);
        vector<long long int> ways(n, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // time, city
        
        minTime[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});
        
        while(!pq.empty())
        {
            long long int time = pq.top().first;
            int city = pq.top().second;
            pq.pop();
            
            for (auto it : adj[city])
            {
                int adjCity = it.first;
                long long int addTime = it.second;
                
                // new path with same time/dist
                if (time + addTime == minTime[adjCity])
                {
                    ways[adjCity] = (ways[city] + ways[adjCity]) % mod;
                }
                
                // new path with a better time/dist
                // OR first time a adjCity is being reached with this 'time'
                else if (time + addTime < minTime[adjCity]) 
                {
                    minTime[adjCity] = time + addTime;
                    pq.push({time + addTime, adjCity});
                    ways[adjCity] = ways[city];
                }
            }
        }

        return ways[n-1] % mod;
    }
};
```

## Network Delay Time
### Problem Link
https://leetcode.com/problems/network-delay-time/submissions/1553575181/
### Code
```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) 
    {
        vector<vector<pair<int, int>>> adj(n+1);

        for (auto edge : times) adj[edge[0]].push_back({edge[1], edge[2]});

        vector<int> minTime(n+1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // time, node

        minTime[k] = 0;
        pq.push({0, k});

        while(!pq.empty())
        {
            int time = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int addTime = it.second;

                if (addTime + time < minTime[adjNode])
                {
                    minTime[adjNode] = addTime + time;
                    pq.push({addTime + time, adjNode});
                }
            }
        }

        int ans = -1;
        for (int i=1; i<=n; i++) 
        {
            if(minTime[i] == INT_MAX) return -1;
            ans = max(ans, minTime[i]);
        }
        
        return ans;
    }
};
```

# Bellman Ford Algorithm
- Works for negative weight cycles and negative weights <br>
- Bellman is applicable only for DG <br>
- If undirected, represent it as directed with both way edges <br>
- TC: ExV <br>
- Step 1: Edges can be in any order <br>
- Step 2: Relax all edges in sequential order for n-1 times <br>
- Step 3: Relax: dst[u] + wt < dst[v] ==> update dst[v] <br>
- Step 4:If relaxation can be done for n-th time ==> Negative Weighted Cycle Detected <br>
- Why N-1? Each iteration updates dst of 1 node <br>
### Problem Link
https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=distance-from-the-source-bellman-ford-algorithm
### Code
```cpp
class Solution {
  public:
    /*  Function to implement Bellman Ford
     *   edges: vector of vectors which represents the graph
     *   src: source vertex
     *   V: number of vertices
     */
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) 
    {
        int n = V;
        int m = edges.size(); // edges
        
        vector<int> dst(n, 1e8);
        dst[src] = 0;
        
        // n-1 times relaxation
        for (int i=0; i<n-1; i++)
        {
            for (auto edge : edges)
            {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];
                
                if (dst[u] != 1e8 && dst[u] + wt < dst[v])
                {
                    dst[v] = dst[u] + wt;
                }
            }
        }
        
        // n-th relaxation to check for negative cycle
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            if (dst[u] != 1e8 && dst[u] + wt < dst[v])
            {
                return {-1};
            }
        }
        
        return dst;
    }
};
```

# Floyd Warshall Algorithm
- Multisource Shortest Path Algorithm <br>
- Finds shortest path from each node to every other node <br>
- Helps detect negative cycles as well <br>
- Works on Adjacency Matrix <br>
- TC: E<sup>3</sup>
- Step 1: Try to go via every path possible <br>
- Step 2: After getting the final dst array if dst[i][j] < 0 ==> Negative cycle
### Problem Link
https://www.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=implementing-floyd-warshall
### Code
```cpp
class Solution {
  public:
    void shortestDistance(vector<vector<int>>& mat) 
    {
        int n = mat.size();
        
        // mark diagonal nodes as 0
        // mark no edges as INT_MAX
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) 
            {
                if (i == j) mat[i][j] = 0;
                else if (mat[i][j] == -1) mat[i][j] = INT_MAX;
            }
        }
        
        for (int via=0; via<n; via++)
        {
            for (int i=0; i<n; i++)
            {
                for (int j = 0; j<n; j++)
                {
                    if (mat[i][via] != INT_MAX && mat[via][j] != INT_MAX)
                    {
                        mat[i][j] = min(mat[i][j], mat[i][via] + mat[via][j]);
                    }
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) 
            {
                if (mat[i][j] == INT_MAX) mat[i][j] = -1;
            }
        }
    }
};
```

## Find the City With the Smallest Number of Neighbours at a Threshold Distance
- Use Floyd Warshall
### Problem Link
https://www.geeksforgeeks.org/problems/city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=city-with-the-smallest-number-of-neighbors-at-a-threshold-distance
### Code
```cpp
class Solution 
{
  private:
    void floydWarshall(int n, vector<vector<int>> &mat)
    {
        for (int via=0; via<n; via++)
        {
            for (int i=0; i<n; i++)
            {
                for (int j=0; j<n; j++)
                {
                    if (mat[i][via] != INT_MAX && mat[via][j] != INT_MAX)
                        mat[i][j] = min(mat[i][j], mat[i][via] + mat[via][j]);
                }
            }
        }
    }
    
  public:
    int findCity(int n, int m, vector<vector<int>>& edges, int distanceThreshold) 
    {
        // create the adj_mat
        vector<vector<int>> mat(n, vector<int>(n, INT_MAX));
        
        for (int i=0; i<n; i++) mat[i][i] = 0;
        
        for (edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            mat[u][v] = wt;
            mat[v][u] = wt;
        }
        
        
        // perfor Floyd Warshall
        floydWarshall(n, mat);
        
        int ansCity = -1;
        int ansCnt = INT_MAX;
        for (int city=0; city<n; city++)
        {
            int cnt = 0;
            
            for (int adjCity=0; adjCity<n; adjCity++)
            {
                if (city == adjCity) continue;
                
                if (mat[city][adjCity] <= distanceThreshold)
                {
                    cnt++;
                }
            }
            
            if (cnt <= ansCnt)
            {
                ansCity = city;
                ansCnt = cnt;
            }
        }
        
        return ansCity;
    }
};
```

</details>

<details>
<summary> 8. Minimum Spanning Tree </summary>

# Minimum Spanning Tree (MST)
- Spanning Tree: Tree where N nodes and N-1 edges, and all nodes are reachable from each other <br>
- Minimum Spanning Tree: Spanning Tree with Minimum Sum of Edge Weights

## Prim's Algorithm
### Problem Link
https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=minimum-spanning-tree
### Code
```cpp
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
```

## Kruskel's Algorithm
- Sort alll the edges according to weight
### Problem Link
https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=minimum-spanning-tree
### Code
```cpp
class DisjointSet
{
private:
    vector<int> parent, rank, size;
    int n;

public:    
    DisjointSet(int n) 
    {
        this->n = n;

        parent.resize(n+1);
        rank.resize(n+1);
        size.resize(n+1);

        // initial configuration
        for (int i=0; i<=n; i++)
        {
            parent[i] = i; // each node is parent of itself
            rank[i] = 0; // each node is at rank 0
            size[i] = 1; // each node is single node component, and hence of size 0
        }
    }

    int findUltimateParent(int node)
    {
        if (parent[node] == node)
        {
            return node;
        }

        // path compression
        parent[node] = findUltimateParent(parent[node]);
        return parent[node];
    }

    void unionByRank(int u, int v)
    {
        // find ultimate parent of u and v
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // if already in the same component (already connected)
        if (ulp_u == ulp_v) return;

        // find rank of ulp_u and ulp_v
        int rank_ulp_u = rank[ulp_u];
        int rank_ulp_v = rank[ulp_v];

        // connect the smaller rank tree to larger rank tree

        // u gets attached to v
        if (rank_ulp_u < rank_ulp_v) parent[ulp_u] = ulp_v;

        // v gets attached to u
        else if (rank_ulp_u > rank_ulp_v) parent[ulp_v] = ulp_u;
 
        else
        {
            // both have same rank
            // attach anyone to other and increase rank of other
            parent[ulp_u] = ulp_v;
            rank[ulp_v]++;
        }
    }

    void unionBySize(int u, int v)
    {
        // find ultimate parent of u and v
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // if already in the same component (already connected)
        if (ulp_u == ulp_v) return;

        // find size of ulp_u and ulp_v
        int size_ulp_u = size[ulp_u];
        int size_ulp_v = size[ulp_v];

        // connect the smaller size tree to larger size tree

        // u gets attached to v
        if (size_ulp_u < size_ulp_v)
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }

        // v gets attached to u
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }

    bool areConnected(int u, int v)
    {
        return (findUltimateParent(u) == findUltimateParent(v));
    }

    int getRank(int node)
    {
        return rank[findUltimateParent(node)];
    }

    int getSize(int node)
    {
        return size[findUltimateParent(node)];
    }
};

class Solution 
{

  public:
    int spanningTree(int V, vector<vector<int>> adj[]) 
    {
        vector<vector<int>> edges; // weight, u, v
        for (int i=0; i<V; i++)
        {
            for (auto it : adj[i])
            {
                int u = i;
                int v = it[0];
                int wt = it[1];
                
                edges.push_back({wt, u, v});
            }
        }
        
        // sort all the edges according to weight
        sort(edges.begin(), edges.end());
        
        // add to the ds by making union
        DisjointSet ds(V);
        
        int mstSum = 0;
        for (auto edge : edges)
        {
            if (! ds.areConnected(edge[1], edge[2]))
            {
                ds.unionByRank(edge[1], edge[2]);
                mstSum += edge[0];
            }
        }
        
        return mstSum;
    }
};
```


</details>

<details>
<summary> 9. Disjoint Set </summary>

# Disjoint Set
- getParent[node]? Helps check if two nodes are part of the same component (in constant time) <br>
- Used mostly with Dynamic Graphs <br>
- Union by Rank TC - O(4 alpha) ~ constant <br>
- Union by Size: TC - O(4 alpha) ~ constant <br>

# Problems on DisjointSet

## Number of Provinces
- Find number of ultimate nodes
### Problem Link
https://www.geeksforgeeks.org/problems/number-of-provinces/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=number-of-provinces
### Code
```cpp
//User function Template for C++
class DisjointSet
{
private:
    vector<int> parent, size;
    int n;

public:    
    DisjointSet(int n) 
    {
        this->n = n;

        parent.resize(n+1);
        size.resize(n+1);

        // initial configuration
        for (int i=0; i<=n; i++)
        {
            parent[i] = i; // each node is parent of itself
            size[i] = 1; // each node is single node component, and hence of size 1
        }
    }

    int findUltimateParent(int node)
    {
        if (parent[node] == node)
        {
            return node;
        }

        // path compression
        parent[node] = findUltimateParent(parent[node]);
        return parent[node];
    }

    void unionBySize(int u, int v)
    {
        // find ultimate parent of u and v
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // if already in the same component (already connected)
        if (ulp_u == ulp_v) return;

        // find size of ulp_u and ulp_v
        int size_ulp_u = size[ulp_u];
        int size_ulp_v = size[ulp_v];

        // connect the smaller size tree to larger size tree

        // u gets attached to v
        if (size_ulp_u < size_ulp_v)
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }

        // v gets attached to u
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }

    bool areConnected(int u, int v)
    {
        return (findUltimateParent(u) == findUltimateParent(v));
    }
};

class Solution {
  public:
    int numProvinces(vector<vector<int>> adj, int V) 
    {
        DisjointSet ds(V);
        
        for (int i=0; i<V; i++)
        {
            for (int j=0; j<V; j++)
            {
                if (i != j && adj[i][j])
                {
                    if (! ds.areConnected(i, j)) ds.unionBySize(i, j);
                }
            }
        }
        
        int numProvinces = 0;
        for (int i=0; i<V; i++)
        {
            if (ds.findUltimateParent(i) == i) numProvinces++;
        }
        
        return numProvinces;
    }
};
```

## Number of Operations to Make Network Connected
### Problem Link
https://www.geeksforgeeks.org/problems/connecting-the-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=connecting-the-graph
### Code
```cpp
// User function Template for C++
class DisjointSet
{
private:
    vector<int> parent, rank, size;
    int n;

public:    
    DisjointSet(int n) 
    {
        this->n = n;

        parent.resize(n+1);
        rank.resize(n+1);
        size.resize(n+1);

        // initial configuration
        for (int i=0; i<=n; i++)
        {
            parent[i] = i; // each node is parent of itself
            rank[i] = 0; // each node is at rank 0
            size[i] = 1; // each node is single node component, and hence of size 1
        }
    }

    int findUltimateParent(int node)
    {
        if (parent[node] == node)
        {
            return node;
        }

        // path compression
        parent[node] = findUltimateParent(parent[node]);
        return parent[node];
    }

    void unionBySize(int u, int v)
    {
        // find ultimate parent of u and v
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // if already in the same component (already connected)
        if (ulp_u == ulp_v) return;

        // find size of ulp_u and ulp_v
        int size_ulp_u = size[ulp_u];
        int size_ulp_v = size[ulp_v];

        // connect the smaller size tree to larger size tree

        // u gets attached to v
        if (size_ulp_u < size_ulp_v)
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }

        // v gets attached to u
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }

    bool areConnected(int u, int v)
    {
        return (findUltimateParent(u) == findUltimateParent(v));
    }
};

class Solution 
{
  private:
    int getNumComponents(int n, vector<vector<int>>& edges, int &extraNodes)
    {
        DisjointSet ds(n);
        
        for (edge : edges)
        {
            if (! ds.areConnected(edge[0], edge[1]))
                ds.unionBySize(edge[0], edge[1]);
            else extraNodes++;
        }
        
        int num = 0;
        for (int i=0; i<n; i++)
        {
            if (ds.findUltimateParent(i) == i) num++;
        }
        
        return num;
    }
    
  public:
    int Solve(int n, vector<vector<int>>& edges) 
    {
        int extraNodes = 0;
        int ans = getNumComponents(n, edges, extraNodes) - 1;

        if (extraNodes >= ans) return ans;
        return -1;
    }
};
```

## Accounts Merge
- Use DisjointSet to represent persons <br>
- Use map to track and map emails to persons
### Problem Link
https://www.geeksforgeeks.org/problems/account-merge/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=account-merge
### Code
```cpp
class DisjointSet
{
   private:
    int n;
    vector<int> size, parent;
    
  public:
    DisjointSet(int n)
    {
        this->n = n;
        
        parent.resize(n+1);
        size.resize(n+1);
        
        for (int i=0; i<=n; i++)
        {
            parent[i] = i;
            size[i] = 0;
        }
    }
    
    int getParent(int node)
    {
        if (parent[node] == node) return node;
        return parent[node] = getParent(parent[node]);
    }
    
    void unionBySize(int u, int v)
    {
        int ulp_u = getParent(u);
        int ulp_v = getParent(v);
        
        if (ulp_u == ulp_v) return;
        
        if (size[ulp_u] <= size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];         
        }
    }
};

class Solution {
  public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) 
    {
        int n = accounts.size();
        
        DisjointSet ds(accounts.size());
        map<string, int> map;
        
        for (int i=0; i<n; i++)
        {
            vector<string> account = accounts[i];
            
            int m = account.size();
            
            for (int j=1; j<m; j++)
            {
                string email = account[j];
                if (map.find(email) == map.end()) // new email to be pushed in the map
                {
                    map[email] = ds.getParent(i);
                }
                
                else // email already in the map, merge it to its actual owner
                {
                    ds.unionBySize(i, map[email]);
                }
            }
        }
        
        // create the merged accounts
        vector<string> emails[n]; // emails belonging to the n-th node
        
        for (auto it : map)
        {
            string email = it.first;
            int node = it.second;
            node = ds.getParent(node); // update node to its parent node
            
            emails[node].push_back(email);
        }
        
        // create the final answer
        vector<vector<string>> ans;
        
        for (int i=0; i<n; i++)
        {
            vector<string> account = emails[i];
            
            int n = account.size();

            if (n != 0) // skip empty lists, process only those nodes that have some email ids
            {
                sort(account.begin(), account.end());
                
                vector<string> temp;
                temp.push_back(accounts[i][0]); // extract name of i-th node account holder
                
                for (string it : account)
                {
                    temp.push_back(it);
                }
                
                ans.push_back(temp);
            }
        }
        
        return ans;
    }
};
```

## Number of Islands II - Online Queries
### Problem Link
https://www.geeksforgeeks.org/problems/number-of-islands/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=number-of-islands
### Code
```cpp
class DisjointSet
{
  private:
    vector<int> parent, size;
  public:
    DisjointSet(int n)
    {
        parent.resize(n);
        size.resize(n);
        
        for (int i=0; i<n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }
    
    int getPar(int node)
    {
        if (node == parent[node]) return node;
        
        return parent[node] = getPar(parent[node]);
    }
    
    void unionBySize(int u, int v)
    {
        int ulp_u = getPar(u);
        int ulp_v = getPar(v);
        
        if (ulp_u == ulp_v) return;
        
        if (size[ulp_u] <= size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
    
    bool areConnected(int u, int v)
    {
        return (getPar(u) == getPar(v));
    }
};

class Solution 
{
  public:
    bool isValid(int row, int col, int n, int m)
    {
        return (row >= 0 && row < n && col >= 0 && col < m);
    }
    
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) 
    {
        vector<vector<int>> mat(n, vector<int>(m, 0));
        DisjointSet ds(n*m);
        
        vector<int> ans;
        int numIslands = 0;
        
        for (auto query : operators)
        {
            int row = query[0];
            int col = query[1];
            
            if (mat[row][col] == 1)
            {
                ans.push_back(numIslands);
                continue;
            }
            
            // mark as land
            mat[row][col] = 1;
            numIslands++;
            
            // do union with neighbours
            int dRow[] = {-1,0,1,0};
            int dCol[] = {0,1,0,-1};
            for (int i=0; i<4; i++)
            {
                int nrow = row + dRow[i];
                int ncol = col + dCol[i];
                
                if (isValid(nrow, ncol, n, m) && mat[nrow][ncol] == 1)
                {
                    int idx = row * m + col;
                    int nidx = nrow * m + ncol;
                    
                    if (! ds.areConnected(idx, nidx))
                    {
                        ds.unionBySize(idx, nidx);
                        numIslands--;                        
                    }

                }
            }
            
            ans.push_back(numIslands);
        }
        
        return ans;
    }
};
```

## Making a Large Island
- Connect the nodes using set <br>
- Try virtually replacing 0s to 1s
### Problem Link
https://www.geeksforgeeks.org/problems/maximum-connected-group/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=maximum-connected-group
### Code
```cpp
class DisjointSet
{
  private:
    vector<int> parent, size;
  public:
    DisjointSet(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        
        for (int i=0; i<n; i++) parent[i] = i;
    }
    
    int getPar(int node)
    {
        if (node == parent[node]) return node;
        return parent[node] = getPar(parent[node]);
    }
    
    int getSize(int node)
    {
        return size[getPar(node)];
    }
    
    void unionBySize(int u, int v)
    {
        int ulp_u = getPar(u);
        int ulp_v = getPar(v);
        
        if (ulp_u == ulp_v) return;
        
        if (size[ulp_u] <= size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution 
{
  private: 
    bool valid(int row, int col, int n)
    {
        return (row >= 0 && col >= 0 && row < n && col < n);
    }
    
  public:
    int MaxConnection(vector<vector<int>>& mat) {
        int n = mat.size();
        
        DisjointSet ds(n*n);
        
        for (int row=0; row<n; row++)
        {
            for (int col=0; col<n; col++)
            {
                if (mat[row][col] != 1) continue;
                
                // connect it with its neighbours
                int drow[] = {-1,1,0,0};
                int dcol[] = {0,0,1,-1};
                for (int i=0; i<4; i++)
                {
                    int nrow = row + drow[i];
                    int ncol = col + dcol[i];
                    
                    // if valid and 1
                    if (valid(nrow, ncol, n) && mat[nrow][ncol] == 1)
                    {
                        int idx = row * n + col;
                        int nidx = nrow * n + ncol;
                        
                        if (ds.getPar(idx) != ds.getPar(nidx))
                        {
                            ds.unionBySize(idx, nidx);
                        }
                    }
                }
            }
        }
        
        int ans = 1;
        
        // try virtually replacing a 0 by 1
        for (int row=0; row<n; row++)
        {
            for (int col=0; col<n; col++)
            {
                if (mat[row][col] == 0)
                {
                    set<int> set;
                    
                    // try connecting 4 directionally
                    int drow[] = {-1,1,0,0};
                    int dcol[] = {0,0,1,-1};
                    for (int i=0; i<4; i++)
                    {
                        int nrow = row + drow[i];
                        int ncol = col + dcol[i];
                        
                        // if valid and 1
                        if (valid(nrow, ncol, n) && mat[nrow][ncol] == 1)
                        {
                            set.insert(ds.getPar(nrow*n + ncol));
                        }
                    }
                    
                    int temp = 1;
                    for (auto it : set)
                    {
                        temp += ds.getSize(it);
                    }
                    
                    ans = max(ans, temp);
                }
            }
        }
        
        for (int idx=0; idx<n*n; idx++)
        {
            ans = max(ans, ds.getSize(idx));
        }

        return ans;
        
        
    }
};
```

## Most Stones Removed with Same Row or Column
- Treat the individual row/col as a node <br>
- No need to consider individual cell as node <br>
- No need to combine individual stones <br>
- Combine rows and cols as a whole
### Problem Link
https://www.geeksforgeeks.org/problems/maximum-stone-removal-1662179442/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=maximum-stone-removal
### Code
```cpp
class DisjointSet
{
private:
    vector<int> parent, size;
    int n;
    
public:    
    DisjointSet(int n) 
    {
        this->n = n;
        
        parent.resize(n+1);
        size.resize(n+1);

        // initial configuration
        for (int i=0; i<=n; i++)
        {
            parent[i] = i; // each node is parent of itself
            size[i] = 1; // each node is single node component, and hence of size 1
        }
    }

    int findUltimateParent(int node)
    {
        if (parent[node] == node)
        {
            return node;
        }

        // path compression
        parent[node] = findUltimateParent(parent[node]);
        return parent[node];
    }

    void unionBySize(int u, int v)
    {
        // find ultimate parent of u and v
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // if already in the same component (already connected)
        if (ulp_u == ulp_v) return;

        // find size of ulp_u and ulp_v
        int size_ulp_u = size[ulp_u];
        int size_ulp_v = size[ulp_v];

        // connect the smaller size tree to larger size tree

        // u gets attached to v
        if (size_ulp_u < size_ulp_v)
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }

        // v gets attached to u
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
  public:
    int maxRemove(vector<vector<int>>& stones, int n) 
    {
        int maxRow = 0;
        int maxCol = 0;
        
        for (vector<int> stone : stones)
        {
            maxRow = max(maxRow, stone[0]);
            maxCol = max(maxCol, stone[1]);
        }
        
        /*
        Total: maxRow + maxCol nodes
        Rows: 0 to maxRow-1
        Cols: maxRow to maxRow+maxCol-1
        */
        DisjointSet ds(maxRow+maxCol+1);
        map<int, bool> stoneNodes;
        for (vector<int> stone : stones)
        {
            int row = stone[0];
            int col = stone[1] + maxRow + 1;
            
            ds.unionBySize(row, col);
            stoneNodes[row] = true;
            stoneNodes[col] = true;
        }
        
        int numComponents = 0;
        
        for (auto it : stoneNodes)
        {
            int node = it.first;
            if (ds.findUltimateParent(node) == node) numComponents++;
        }
        
        int ans = stones.size() - numComponents;
        return ans;
    }
};
```

</details>

<details>
<summary> 10. Advanced Algorithms </summary>

# Advanced Algorithms

## Kosaraju's Algorithm (Strongly Connected Components)
- Only valid for Directed Graphs <br>
- Number of SCCs <br>
- Print the SCCs <br>
- Step1: Sort the nodes in order of finish time of DFS <br>
- Step2: Reverse the graph <br>
- Step3: Perform DFS in order of finish time (sorted nodes)

### Problem Link
https://www.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=strongly-connected-components-kosarajus-algo

### Code
```cpp
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
```


## Tarjan's Algorithm: Bridges in Graph
- Bridge is an edge removing which increases the number of components <br>
- Print all the bridges <br>
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

## Articulation Point in Graph
-  Any node whose removal (along with all the edges associated with it) breaks the graph into multiple components

### Problem Link
https://www.geeksforgeeks.org/problems/articulation-point-1/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=articulation-point

### Code
```cpp
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
```

</details>

<details>
<summary>  Revision Lectures </summary>
- Lec 26 <br>
- Lec 29, 30, 31 (Word Ladder problems)
</details>