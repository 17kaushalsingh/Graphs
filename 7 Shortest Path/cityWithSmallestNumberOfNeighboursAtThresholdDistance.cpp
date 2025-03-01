//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++
class Solution 
{
  private:
    void floydWarshall(int n, vector<vector<int>> &mat)
    {
        for (int via=0; via<n; via++)
        {
            for (int i=0; i<n; i++)
            {
                for (int j=0; j<n; j++)
                {
                    if (mat[i][via] != INT_MAX && mat[via][j] != INT_MAX)
                        mat[i][j] = min(mat[i][j], mat[i][via] + mat[via][j]);
                }
            }
        }
    }
    
  public:
    int findCity(int n, int m, vector<vector<int>>& edges, int distanceThreshold) 
    {
        // create the adj_mat
        vector<vector<int>> mat(n, vector<int>(n, INT_MAX));
        
        for (int i=0; i<n; i++) mat[i][i] = 0;
        
        for (edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            mat[u][v] = wt;
            mat[v][u] = wt;
        }
        
        
        // perfor Floyd Warshall
        floydWarshall(n, mat);
        
        int ansCity = -1;
        int ansCnt = INT_MAX;
        for (int city=0; city<n; city++)
        {
            int cnt = 0;
            
            for (int adjCity=0; adjCity<n; adjCity++)
            {
                if (city == adjCity) continue;
                
                if (mat[city][adjCity] <= distanceThreshold)
                {
                    cnt++;
                }
            }
            
            if (cnt <= ansCnt)
            {
                ansCity = city;
                ansCnt = cnt;
            }
        }
        
        return ansCity;
    }
};


//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj;
        // n--;
        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }

        int dist;
        cin >> dist;
        Solution obj;
        cout << obj.findCity(n, m, adj, dist) << "\n";
    
cout << "~" << "\n";
}
}

// } Driver Code Ends