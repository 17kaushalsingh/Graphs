//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution 
{
    int mod = (int)(1e9 + 7);
  public:
    int countPaths(int n, vector<vector<int>>& roads) 
    {
        vector<vector<pair<int, int>>> adj(n);
        
        for (auto road : roads)
        {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }
        
        vector<long long int> minTime(n, INT_MAX);
        vector<long long int> ways(n, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // time, city
        
        minTime[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});
        
        while(!pq.empty())
        {
            long long int time = pq.top().first;
            int city = pq.top().second;
            pq.pop();
            
            for (auto it : adj[city])
            {
                int adjCity = it.first;
                long long int addTime = it.second;
                
                // new path with same time/dist
                if (time + addTime == minTime[adjCity])
                {
                    ways[adjCity] = (ways[city] + ways[adjCity]) % mod;
                }
                
                // new path with a better time/dist
                // OR first time a adjCity is being reached with this 'time'
                else if (time + addTime < minTime[adjCity]) 
                {
                    minTime[adjCity] = time + addTime;
                    pq.push({time + addTime, adjCity});
                    ways[adjCity] = ways[city];
                }
            }
        }

        return ways[n-1] % mod;
    }
};

//{ Driver Code Starts.

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int u, v;

        vector<vector<int>> adj;

        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }

        Solution obj;
        cout << obj.countPaths(n, adj) << "\n";
    
cout << "~" << "\n";
}

    return 0;
}
// } Driver Code Ends