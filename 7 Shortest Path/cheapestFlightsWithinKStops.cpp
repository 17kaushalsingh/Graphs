//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
    int CheapestFLight(int n, vector<vector<int>>& flights, int src, int dst, int K)  
    {
        vector<pair<int, int>> adj[n];
        
        for (flight : flights)
        {
            int u = flight[0];
            int v = flight[1];
            int wt = flight[2];
            
            adj[u].push_back({v, wt});
        }
        
        queue<pair<int, pair<int, int>>> q; // stops, city, price
        vector<int> minPrice(n, INT_MAX);
        
        q.push({0, {src, 0}});
        minPrice[src] = 0;
        
        while(!q.empty())
        {
            auto it = q.front();
            q.pop();
            
            int stops = it.first;
            int city = it.second.first;
            int price = it.second.second;
            
            if (stops > K) continue;
            
            // if (city == dst) continue;
            
            for (auto it : adj[city])
            {
                int adjCity = it.first;
                int addPrice = it.second;
                
                if (price + addPrice < minPrice[adjCity])
                {
                    minPrice[adjCity] = price + addPrice;
                    q.push({stops+1, {adjCity, price + addPrice}});
                }
            }
        }
        
        int ans = minPrice[dst];
        if (ans == INT_MAX) return -1;
        return ans;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n; cin>>n;
        int edge; cin>>edge;
        vector<vector<int>> flights;
        
        for(int i=0; i<edge; ++i){
            vector<int> temp;
            for(int j=0; j<3; ++j){
                int x; cin>>x;
                temp.push_back(x);
            }
            flights.push_back(temp);
        }
        
        int src,dst,k;
        cin>>src>>dst>>k;
        Solution obj;
        cout<<obj.CheapestFLight(n,flights,src,dst,k)<<"\n";
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends