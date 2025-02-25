class Solution {
    public:
        int networkDelayTime(vector<vector<int>>& times, int n, int k) 
        {
            vector<vector<pair<int, int>>> adj(n+1);
    
            for (auto edge : times) adj[edge[0]].push_back({edge[1], edge[2]});
    
            vector<int> minTime(n+1, INT_MAX);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // time, node
    
            minTime[k] = 0;
            pq.push({0, k});
    
            while(!pq.empty())
            {
                int time = pq.top().first;
                int node = pq.top().second;
                pq.pop();
    
                for (auto it : adj[node])
                {
                    int adjNode = it.first;
                    int addTime = it.second;
    
                    if (addTime + time < minTime[adjNode])
                    {
                        minTime[adjNode] = addTime + time;
                        pq.push({addTime + time, adjNode});
                    }
                }
            }
    
            int ans = -1;
            for (int i=1; i<=n; i++) 
            {
                if(minTime[i] == INT_MAX) return -1;
                ans = max(ans, minTime[i]);
            }
            
            return ans;
        }
    };