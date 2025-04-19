//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

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


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i = 0;
        while (i++ < E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1, t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }

        Solution obj;
        cout << obj.spanningTree(V, adj) << "\n";

        cout << "~"
             << "\n";
    }

    return 0;
}

// } Driver Code Ends