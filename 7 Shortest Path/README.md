# Shortest Path

## Directed Acyclic Graph - Topological Sort
- Get topoSort answer in stack
- Take the nodes from stack and start relaxing edges
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=direct-acyclic-graph
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

## Undirected Acyclic Graph - Unit Weights - Plain BFS
- Plain BFS with relaxation of edges
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=shortest-path-in-undirected-graph-having-unit-distance
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

## Word Ladder 2

# Dijkstras Algorithm
- TC: E logV
- Can be done via Queue, PriorityQueue or Set

## Using Priority Queue
- Require a minHeap data structure
- Does not work for cycles and negative edge weights
- TC: E logV
- Why PQ: Saves some iterations
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=implementing-dijkstra-set-1-adjacency-matrix
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
- Set stores unique values and in sorted order (ascending order, the smallest at the top)
- Set can erase some elements to optimize the iterations
- Investing logN to delete an element and save some iterations later
- So can say much about which is better in terms of TC
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=implementing-dijkstra-set-1-adjacency-matrix
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
- Modify Dijksras to try to remember where are you coming from
- Use a parent array to track where a new node is pushed from in the PQ
https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=shortest-path-in-weighted-undirected-graph
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
https://www.geeksforgeeks.org/problems/shortest-path-in-a-binary-maze-1655453161/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=shortest-path-in-a-binary-maze
```cppp
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
https://www.geeksforgeeks.org/problems/path-with-minimum-effort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=path-with-minimum-effort
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
- Make decision based on stops rather than price
- No PQ required
https://www.geeksforgeeks.org/problems/cheapest-flights-within-k-stops/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=cheapest-flights-within-k-stops
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
https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=minimum-multiplications-to-reach-end
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

## 