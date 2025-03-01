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

## Making a Large Island

## Most Stones Removed with Same Row or Column

