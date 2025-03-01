//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

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



//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n,m,k; cin>>n>>m>>k;
        vector<vector<int>> a;
        
        for(int i=0; i<k; i++){
            vector<int> temp;
            for(int j=0; j<2; j++){
                int x; cin>>x;
                temp.push_back(x);
            }
            a.push_back(temp);
        }
    
        Solution obj;
        vector<int> res = obj.numOfIslands(n,m,a);
        
        for(auto x : res)cout<<x<<" ";
        cout<<"\n";
    
cout << "~" << "\n";
}
}

// } Driver Code Ends