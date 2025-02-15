//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  private:
    bool isValid(int row, int col, int maxRow, int maxCol)
    {
        return (row >= 0 && row < maxRow && col >= 0 && col < maxCol);
    }
    
    bool allOrangesRotten(int orangesRotten, int initialFreshOranges)
    {
        return (orangesRotten == initialFreshOranges);
    }
    
  public:

    int orangesRotting(vector<vector<int>>& mat) 
    {
        int n = mat.size();
        int m = mat[0].size();
        int initialFreshOranges = 0;
        
        // 0 means no oranage
        // 1 means fresh
        // 2 means rotten
        vector<vector<int>> isVisited(n, vector<int>(m, 0)); 
        
        queue<pair<pair<int, int>, int>> q;
        
        // put all the oranges which are initially rotten
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (mat[i][j] == 1) initialFreshOranges++;
                
                if (mat[i][j] == 2)
                {
                    q.push(make_pair(make_pair(i, j), 0));
                    isVisited[i][j] = 2;
                }
            }
        }
        
        int ans = 0;
        
        int orangesGettingRotten = 0;
        // start processing until the queue is empty
        while(!q.empty())
        {
            auto front = q.front();
            q.pop();
            
            int row = front.first.first;
            int col = front.first.second;
            int time = front.second;
            
            ans = max(ans, time);
            
            int delrow[] = {-1,1,0,0};
            int delcol[] = {0,0,-1,1};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if (isValid(nrow, ncol, n, m))
                {
                    if (mat[nrow][ncol] == 1 && isVisited[nrow][ncol] != 2)
                    {
                        q.push(make_pair(make_pair(nrow, ncol), time+1));
                        isVisited[nrow][ncol] = 2;
                        orangesGettingRotten++;
                    }
                }
            }
        }
        
        if (allOrangesRotten(orangesGettingRotten, initialFreshOranges)) return ans;
        else return -1;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> mat(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> mat[i][j];
            }
        }
        Solution obj;
        int ans = obj.orangesRotting(mat);
        cout << ans << "\n";

        cout << "~"
             << "\n";
    }
    return 0;
}
// } Driver Code Ends