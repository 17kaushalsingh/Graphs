//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution 
{
  private:
    bool valid(int row, int col, int maxRow, int maxCol)
    {
        return (row >= 0 && row < maxRow && col >= 0 && col < maxCol);
    }
    
  public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source, pair<int, int> destination) 
    {
        int n = grid.size();
        int m = grid[0].size();
        
        int srcRow = source.first;
        int srcCol = source.second;
        
        int dstRow = destination.first;
        int dstCol = destination.second;
        
        vector<vector<int>> shortestDst(n, vector<int>(m, INT_MAX));
        queue<pair<int, pair<int, int>>> pq; // dst, (row, col)
        
        pq.push({0, {srcRow, srcCol}});
        shortestDst[srcRow][srcCol] = 0;
        
        while(!pq.empty())
        {
            auto it = pq.front();
            pq.pop();
            
            int dst = it.first;
            int row = it.second.first;
            int col = it.second.second;
            
            if (shortestDst[row][col] == INT_MAX) continue;
            if (row == dstRow && col == dstCol) break;
            
            int delrow[] = {1, -1, 0, 0};
            int delcol[] = {0, 0, -1, 1};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if (valid(nrow, ncol, n, m) && grid[nrow][ncol] == 1 && dst+1 < shortestDst[nrow][ncol])
                {
                    shortestDst[nrow][ncol] = dst+1;
                    pq.push({dst+1, {nrow, ncol}});
                }
            }
        }
        
        int ans = shortestDst[dstRow][dstCol];
        
        if (ans == INT_MAX) return -1;
        
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

        pair<int, int> source, destination;
        cin >> source.first >> source.second;
        cin >> destination.first >> destination.second;
        Solution obj;
        cout << obj.shortestPath(grid, source, destination) << endl;
    
cout << "~" << "\n";
}
}

// } Driver Code Ends