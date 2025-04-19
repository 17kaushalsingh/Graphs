//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

`
// } Driver Code Ends
// User function Template for C++

class Solution 
{
  private:
    bool isValid(int row, int col, int maxRow, int maxCol)
  {
      return (row >= 0 && col >= 0 && row < maxRow && col < maxCol);
  }
  
  public:
    int numberOfEnclaves(vector<vector<int>> &grid) 
    {
        int n = grid.size();
        int m = grid[0].size();
        
        // any land cell on the boundary can lead to a jump off the grid
        // which means any land cell 4 directionally connected to it can also lead to a jump
        
        vector<vector<int>> landCellOnBoundary(n, vector<int>(m, -1));
        // -1 means not visited
        // 0 means not connected with boundary
        // 1 means connected with boundary
        
        queue<pair<int, int>> q;
        
        for (int i=0; i<n; i++)
        {
            // left col
            if (grid[i][0] == 1)
            {
                q.push({i, 0});
                landCellOnBoundary[i][0] = 1;
            }
            else landCellOnBoundary[i][0] = 0;
            
            // right col
            if (grid[i][m-1] == 1)
            {
                q.push({i, m-1});
                landCellOnBoundary[i][m-1] = 1;
            }
            else landCellOnBoundary[i][m-1] = 0;
        }
        
        for (int j=0; j<m; j++)
        {
            // top row
            if (grid[0][j] == 1)
            {
                q.push({0, j});
                landCellOnBoundary[0][j] = 1;
            }
            else landCellOnBoundary[0][j] = 0;
            
            // bottom row
            if (grid[n-1][j] == 1)
            {
                q.push({n-1, j});
                landCellOnBoundary[n-1][j] = 1;
            }
            else landCellOnBoundary[n-1][j] = 0;
        }
        
        while(!q.empty())
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            // iterate on neighbours
            int dr[] = {-1,1,0,0};
            int dc[] = {0,0,1,-1};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + dr[i];
                int ncol = col + dc[i];
                
                // if valid and unvisited
                if (isValid(nrow, ncol, n, m) && landCellOnBoundary[nrow][ncol] == -1)
                {
                    if (grid[nrow][ncol] == 1)
                    {
                        q.push({nrow, ncol});
                        landCellOnBoundary[nrow][ncol] = 1;
                    }
                    
                    else landCellOnBoundary[nrow][ncol] = 0;
                }
            }
        }
        
        int ans = 0;
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (grid[i][j] == 1 && landCellOnBoundary[i][j] != 1) ans++;
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
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        Solution obj;
        cout << obj.numberOfEnclaves(grid) << endl;
    
cout << "~" << "\n";
}
}
// } Driver Code Ends