//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

class Matrix {
  public:
    template <class T>
    static void input(vector<vector<T>> &A, int n, int m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d ", &A[i][j]);
            }
        }
    }

    template <class T>
    static void print(vector<vector<T>> &A) {
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[i].size(); j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }
};


// } Driver Code Ends

class Solution 
{
  private:
    bool isValid(int row, int col, int n, int m)
    {
        return (row >= 0 && row < n && col >= 0 && col < m);
    }
    
  public:
    int MinimumEffort(int rows, int columns, vector<vector<int>> &heights) 
    {
        // effort: max(abs diff in two consecutive cells of the root)
        
        vector<vector<int>> minimumEffort(rows, vector<int>(columns, INT_MAX));
        // minEffort, row, col
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        
        minimumEffort[0][0] = 0;
        pq.push({0, {0, 0}});
        
        while(!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            
            int effort = it.first;
            int row = it.second.first;
            int col = it.second.second;
            
            // iterate on neighbours
            int delRow[] = {0, 0, -1, 1};
            int delCol[] = {-1, 1, 0, 0};
            
            for (int i=0; i<4; i++)
            {
                int nrow = row + delRow[i];
                int ncol = col + delCol[i];
                
                if (isValid(nrow, ncol, rows, columns))
                {
                    int newEffort = max(effort, abs(heights[row][col] - heights[nrow][ncol]));
                    
                    if (newEffort < minimumEffort[nrow][ncol])
                    {
                        minimumEffort[nrow][ncol] = newEffort;
                        pq.push({newEffort, {nrow, ncol}});
                    }
                }
            }
        }
        
        return minimumEffort[rows-1][columns-1];
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    scanf("%d ", &t);
    while (t--) {

        int rows;
        scanf("%d", &rows);

        int columns;
        scanf("%d", &columns);

        vector<vector<int>> heights(rows, vector<int>(columns));
        Matrix::input(heights, rows, columns);

        Solution obj;
        int res = obj.MinimumEffort(rows, columns, heights);

        cout << res << endl;
    
cout << "~" << "\n";
}
}

// } Driver Code Ends