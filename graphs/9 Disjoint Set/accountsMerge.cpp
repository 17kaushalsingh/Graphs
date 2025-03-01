//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

// User function Template for C++

class DisjointSet
{
   private:
    int n;
    vector<int> size, parent;
    
  public:
    DisjointSet(int n)
    {
        this->n = n;
        
        parent.resize(n+1);
        size.resize(n+1);
        
        for (int i=0; i<=n; i++)
        {
            parent[i] = i;
            size[i] = 0;
        }
    }
    
    int getParent(int node)
    {
        if (parent[node] == node) return node;
        return parent[node] = getParent(parent[node]);
    }
    
    void unionBySize(int u, int v)
    {
        int ulp_u = getParent(u);
        int ulp_v = getParent(v);
        
        if (ulp_u == ulp_v) return;
        
        if (size[ulp_u] <= size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];         
        }
    }
};

class Solution {
  public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) 
    {
        int n = accounts.size();
        
        DisjointSet ds(accounts.size());
        map<string, int> map;
        
        for (int i=0; i<n; i++)
        {
            vector<string> account = accounts[i];
            
            int m = account.size();
            
            for (int j=1; j<m; j++)
            {
                string email = account[j];
                if (map.find(email) == map.end()) // new email to be pushed in the map
                {
                    map[email] = ds.getParent(i);
                }
                
                else // email already in the map, merge it to its actual owner
                {
                    ds.unionBySize(i, map[email]);
                }
            }
        }
        
        // create the merged accounts
        vector<string> emails[n]; // emails belonging to the n-th node
        
        for (auto it : map)
        {
            string email = it.first;
            int node = it.second;
            node = ds.getParent(node); // update node to its parent node
            
            emails[node].push_back(email);
        }
        
        // create the final answer
        vector<vector<string>> ans;
        
        for (int i=0; i<n; i++)
        {
            vector<string> account = emails[i];
            
            int n = account.size();

            if (n != 0) // skip empty lists, process only those nodes that have some email ids
            {
                sort(account.begin(), account.end());
                
                vector<string> temp;
                temp.push_back(accounts[i][0]); // extract name of i-th node account holder
                
                for (string it : account)
                {
                    temp.push_back(it);
                }
                
                ans.push_back(temp);
            }
        }
        
        return ans;
    }
};



//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<string>> accounts;

        for (int i = 0; i < n; i++) {
            vector<string> temp;
            int x;
            cin >> x;

            for (int j = 0; j < x; j++) {
                string s1;
                cin >> s1;
                temp.push_back(s1);
            }
            accounts.push_back(temp);
        }

        ///
        Solution obj;
        vector<vector<string>> res = obj.accountsMerge(accounts);

        for (int i = 0; i < res.size(); i++) {
            sort(res[i].begin(), res[i].end());
        }
        sort(res.begin(), res.end());
        cout << "[";
        for (int i = 0; i < res.size(); ++i) {
            cout << "[";
            for (int j = 0; j < res[i].size(); j++) {
                if (j != res[i].size() - 1)
                    cout << res[i][j] << ","
                         << " ";
                else
                    cout << res[i][j];
            }
            if (i != res.size() - 1)
                cout << "], " << endl;
            else
                cout << "]";
        }
        cout << "]" << endl;

        cout << "~"
             << "\n";
    }
}
// } Driver Code Ends