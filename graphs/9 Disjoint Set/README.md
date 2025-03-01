# Disjoint Set
- <b> getParent[node]? </b> Helps check if two nodes are part of the same component <b> (in constant time) </b>
- Used mostly with <b> Dynamic Graphs </b>
- <b> Union by Rank </b> TC - O(4 alpha) ~ constant
- <b> Union by Size </b>: TC - O(4 alpha) ~ constant 

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
- Use DisjointSet to represent persons
- Use map to track and map emails to persons
### problem Link
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
- Connect the nodes using set
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

