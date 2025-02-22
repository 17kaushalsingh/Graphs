# Dijkstras Algorithm

## Using Priority Queue
- Require a minHeap data structure
- Does not work for cycles and negative edge weights
- TC: E logV
- Why PQ: 
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=implementing-dijkstra-set-1-adjacency-matrix
```cpp
class Solution {
  public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex src.
    vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src) 
    {
        int n = adj.size();
        
        priority_queue<pair<int, int>> pq;
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
