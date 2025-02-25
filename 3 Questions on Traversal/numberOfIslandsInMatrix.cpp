//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution 
{
  private:
  
    bool isValid(int row, int col, int maxRow, int maxCol)
    {
        return (row >=0 && row < maxRow && col >= 0 && col < maxCol);
    }
    
    void dfs(int row, int col, vector<vector<char>> &grid, vector<vector<bool>> &isVisited)
    {
        isVisited[row][col] = true;
        
        int delrow[] = {-1,-1,0,1,1,1,0,-1};
        int delcol[] = {0,1,1,1,0,-1,-1,-1};
        
        for (int i=0; i<8; i++)
        {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];
            
            if (isValid(nrow, ncol, grid.size(), grid[0].size()))
            {
                if (grid[nrow][ncol] == '1' && !isVisited[nrow][ncol])
                {
                    dfs(nrow, ncol, grid, isVisited);
                }
            }
        }
    }
    
  public:
    // Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) 
    {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<bool>> isVisited(m, vector<bool>(n, false));
        
        int numOfIslands = 0;
        
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (grid[i][j] == '1' && !isVisited[i][j])
                {
                    numOfIslands++;
                    dfs(i, j, grid, isVisited);
                }
            }
        }
        
        return numOfIslands;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> grid(n, vector<char>(m, '#'));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        Solution obj;
        int ans = obj.numIslands(grid);
        cout << ans << '\n';
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends