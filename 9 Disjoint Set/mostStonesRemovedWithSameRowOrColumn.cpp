//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

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


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> adj;

        for (int i = 0; i < n; ++i) {
            vector<int> temp;
            for (int i = 0; i < 2; ++i) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }

        Solution obj;

        cout << obj.maxRemove(adj, n) << "\n";
    
cout << "~" << "\n";
}
}
// } Driver Code Ends