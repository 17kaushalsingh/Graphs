//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution 
{
  private:
    bool isValid(int row, int col, int maxRow, int maxCol)
    {
        return (row >= 0 && col >= 0 && row < maxRow && col < maxCol);
    }
    
    void dfs(int row, int col, vector<vector<int>>& grid, vector<vector<bool>> &isVisited, vector<pair<int, int>> &coordinates, int baseRow, int baseCol)
    {
        isVisited[row][col] = true;
        coordinates.push_back({row-baseRow, col-baseCol});
        
        // iterate on neighbours
        int dr[] = {1,-1,0,0};
        int dc[] = {0,0,1,-1};
        
        for (int i=0; i<4; i++)
        {
            int nrow = row + dr[i];
            int ncol = col + dc[i];
            
            // if valid and unvisited
            if (isValid(nrow, ncol, grid.size(), grid[0].size()) && !isVisited[nrow][ncol])
            {
                if (grid[nrow][ncol] == 1)
                {
                    dfs(nrow, ncol, grid, isVisited, coordinates, baseRow, baseCol);
                }
            }
        }
        
    }
    
  public:
    int countDistinctIslands(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<bool>> isVisited(n, vector<bool>(m, false));
        set<vector<pair<int, int>>> set;
        
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (!isVisited[i][j] && grid[i][j] == 1)
                {
                    vector<pair<int, int>> coordinates;
                    dfs(i, j, grid, isVisited, coordinates, i, j);
                    set.insert(coordinates);
                }
            }
        }
        
        int ans = set.size();
        
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
        cout << obj.countDistinctIslands(grid) << endl;
    
cout << "~" << "\n";
}
}
// } Driver Code Ends