//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

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


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int V,x;
        cin>>V;
        
        vector<vector<int>> adj;
        
        for(int i=0; i<V; i++)
        {
            vector<int> temp;
            for(int j=0; j<V; j++)
            {
                cin>>x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }
        

        Solution ob;
        cout << ob.numProvinces(adj,V) << endl;
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends