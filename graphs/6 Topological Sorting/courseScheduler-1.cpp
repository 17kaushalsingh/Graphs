//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution 
{
  private:
    vector<int> getTopoSort(int n, vector<int> adj[])
    {
        vector<int> inDeg(n, 0);
        
        for (int i=0; i<n; i++)
        {
            for (auto adjNode : adj[i]) inDeg[adjNode]++;
        }
        
        queue<int> q;
        
        for (int i=0; i<n; i++) if (inDeg[i] == 0) q.push(i);
        
        vector<int> ans;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);
            
            for (auto adjNode : adj[node])
            {
                inDeg[adjNode]--;
                
                if (inDeg[adjNode] == 0) q.push(adjNode);
            }
        }
        
        return ans;
    }
    
  public:
    bool isPossible(int N, int P, vector<pair<int, int> >& prerequisites) 
    {
        vector<int> adj[N];
        
        for (int i=0; i<P; i++)
        {
            // Edge: [0 1] 1 --> 0.  u --> v
            int u = prerequisites[i].first;
            int v = prerequisites[i].second;
            
            adj[v].push_back(u);
        }
        
        vector<int> topo = getTopoSort(N, adj);
        
        return (topo.size() == N);
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int N, P;
        vector<pair<int, int> > prerequisites;
        cin >> N;
        cin >> P;
        for (int i = 0; i < P; ++i) {
            int x, y;
            cin >> x >> y;
            prerequisites.push_back(make_pair(x, y));
        }
        // string s;
        // cin>>s;
        Solution ob;
        if (ob.isPossible(N, P, prerequisites))
            cout << "Yes";
        else
            cout << "No";
        cout << endl;

        cout << "~"
             << "\n";
    }
    return 0;
}
// } Driver Code Ends