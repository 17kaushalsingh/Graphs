//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution 
{
  public:
    vector<vector<char>> fill(vector<vector<char>>& mat) 
    {
        int n = mat.size();
        int m = mat[0].size();
        
        // mark Os on the boundary
        // -1 not visited
        // 0 not on boundary or connected to it
        // 1 on boundary or connected to it
        vector<vector<int>> onBoundary(n, vector<int>(m, -1));
        
        queue<pair<int, int>> q;
        
        for (int i=0; i<n; i++)
        {
            if (mat[i][0] == 'O')
            {
                onBoundary[i][0] = 1;
                q.push({i,0});
            }
            else onBoundary[i][0] = 0;
            if (mat[i][m-1] == 'O')
            {
                onBoundary[i][m-1] = 1;
                q.push({i,m-1});
            }
            else onBoundary[i][m-1] = 0;
        }
        
        for (int j=0; j<m; j++)
        {
            if (mat[0][j] == 'O')
            {
                onBoundary[0][j] = 1;
                q.push({0,j});
            }
            else onBoundary[0][j] = 0;
            if (mat[n-1][j] == 'O') 
            {
                onBoundary[n-1][j] = 1;
                q.push({n-1,j});
            }
            else onBoundary[n-1][j] = 0;
        }
        
        while(!q.empty())
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            int delrow[] = {1,-1,0,0};
            int delcol[] = {0,0,-1,1};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                // if valid and unvisited
                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && onBoundary[nrow][ncol] == -1)
                {
                    if (mat[nrow][ncol] == 'O')
                    {
                        q.push({nrow, ncol});
                        onBoundary[nrow][ncol] = 1;
                    }
                    else onBoundary[nrow][ncol] = 0;
                }
            }
        }
        
        // All Os not connected with boundary are converted to X
        // All Os on the bouundary remain 0s
        vector<vector<char>> ans(n, vector<char>(m, 'X'));
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (mat[i][j] == 'O' && onBoundary[i][j] == 1) ans[i][j] = 'O';
            }
        }
        
        return ans;
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> mat(n, vector<char>(m, '.'));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> mat[i][j];

        Solution ob;
        vector<vector<char>> ans = ob.fill(mat);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << ans[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "~"
             << "\n";
    }
    return 0;
}
// } Driver Code Ends