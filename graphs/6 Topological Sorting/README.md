# Topological Sorting
- Only exists for DAG (Directed Acyclic Graphs)
- Any linear ordering of nodes such that
- If there is an edge between u and v
- u always appers before v in the sorted list

## DFS Implementation
https://www.geeksforgeeks.org/problems/topological-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=topological-sort
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
https://www.geeksforgeeks.org/problems/topological-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=topological-sort
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
https://www.geeksforgeeks.org/problems/prerequisite-tasks/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=prerequisite-tasks
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
https://www.geeksforgeeks.org/problems/course-schedule/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=course-schedule
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
- Reverse the edges of the graph
- Perform a basic Topo Sort, return topo vector of the reversed graph
https://www.geeksforgeeks.org/problems/eventual-safe-states/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=eventual-safe-states
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
- Represent chars as nodes of a graph
- Figure out why a word appears before the other and create the graph basis that
- Apply topologocal sort
https://www.geeksforgeeks.org/problems/alien-dictionary/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=alien-dictionary
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

