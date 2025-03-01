//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution 
{
  private:
    bool isValid(int row, int col, int maxRow, int maxCol)
    {
        return (row >= 0 && row < maxRow && col >= 0 && col < maxCol);
    }
    
  public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        int m = grid[0].size();
        
        // take a queue and put all the 1s in it with distance as 0
        vector<vector<int>> dst(n, vector<int>(m, INT_MAX)); // INTMAX means the cell has not been reached
        
        queue<pair<pair<int, int>, int>> q;
        
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (grid[i][j] == 1)
                {
                    q.push({{i, j}, 0});
                    dst[i][j] = 0;
                }
            }
        }
        
        while(!q.empty())
        {
            int row = q.front().first.first;
            int col = q.front().first.second;
            int distance = q.front().second;
            q.pop();
            
            // start iterating on its neighbours
            int delrow[] = {-1,1,0,0};
            int delcol[] = {0,0,-1,1};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if (isValid(nrow, ncol, n, m) && dst[nrow][ncol] == INT_MAX)
                {
                    q.push({{nrow, ncol}, distance+1});
                    dst[nrow][ncol] = distance+1;
                }
            }
        }
        
        return dst;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        Solution obj;
        vector<vector<int>> ans = obj.nearest(grid);
        for (auto i : ans) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << "\n";
        }
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends