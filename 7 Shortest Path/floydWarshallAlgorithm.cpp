//{ Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function template for C++

class Solution {
  public:
    void shortestDistance(vector<vector<int>>& mat) 
    {
        int n = mat.size();
        
        // mark diagonal nodes as 0
        // mark no edges as INT_MAX
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) 
            {
                if (i == j) mat[i][j] = 0;
                else if (mat[i][j] == -1) mat[i][j] = INT_MAX;
            }
        }
        
        for (int via=0; via<n; via++)
        {
            for (int i=0; i<n; i++)
            {
                for (int j = 0; j<n; j++)
                {
                    if (mat[i][via] != INT_MAX && mat[via][j] != INT_MAX)
                    {
                        mat[i][j] = min(mat[i][j], mat[i][via] + mat[via][j]);
                    }
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) 
            {
                if (mat[i][j] == INT_MAX) mat[i][j] = -1;
            }
        }
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<vector<int>> matrix(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matrix[i][j];
            }
        }
        Solution obj;
        obj.shortestDistance(matrix);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "~"
             << "\n";
    }
    return 0;
}
// } Driver Code Ends