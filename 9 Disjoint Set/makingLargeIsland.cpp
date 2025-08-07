//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

// User function Template for C++
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



//{ Driver Code Starts.
int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> grid(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        Solution obj;
        cout << obj.MaxConnection(grid) << "\n";
        cout << "~" << endl;
    }
}

// } Driver Code Ends