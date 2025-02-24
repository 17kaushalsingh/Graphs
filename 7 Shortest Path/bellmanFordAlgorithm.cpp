//{ Driver Code Starts
#include <cstdio> // for freopen
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution {
  public:
    /*  Function to implement Bellman Ford
     *   edges: vector of vectors which represents the graph
     *   src: source vertex
     *   V: number of vertices
     */
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) 
    {
        int n = V;
        int m = edges.size(); // edges
        
        vector<int> dst(n, 1e8);
        dst[src] = 0;
        
        // n-1 times relaxation
        for (int i=0; i<n-1; i++)
        {
            for (int i=0; i<m; i++)
            {
                int u = edges[i][0];
                int v = edges[i][1];
                int wt = edges[i][2];
                
                if (dst[u] != 1e8 && dst[u] + wt < dst[v])
                {
                    dst[v] = dst[u] + wt;
                }
            }
        }
        
        // n-th relaxation to check for cycle
        for (int i=0; i<m; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            
            if (dst[u] != 1e8 && dst[u] + wt < dst[v]) return {-1};
        }
        
        return dst;
    }
};


//{ Driver Code Starts.

int main() {

    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        int N, m;
        cin >> N >> m;

        vector<vector<int> > edges;

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;

            vector<int> edge(3);
            edge[0] = u;
            edge[1] = v;
            edge[2] = w;
            edges.push_back(edge);
        }

        int src;
        cin >> src;
        cin.ignore();

        Solution obj;
        vector<int> res = obj.bellmanFord(N, edges, src);

        for (size_t i = 0; i < res.size(); i++) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}

// } Driver Code Ends