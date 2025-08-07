//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution 
{
private:
    // Helper function
    // checks if order is invalid when w1 is longer than w2 and w2 is a prefix of w1
    bool checkInvalidOrder(string &w1, string &w2) 
    {
        if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2) return true;

        return false;
    }
    
    vector<int> getTopoSort(int n, vector<int> adj[], vector<int> &inDeg, vector<bool> &exists) {
        queue<int> q;
        for (int i = 0; i < n; i++) 
        {
            if (inDeg[i] == 0 && exists[i]) q.push(i);
        }
        
        vector<int> topo;
        while (!q.empty()) 
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            
            for (int adjNode : adj[node]) 
            {
                inDeg[adjNode]--;
                if (inDeg[adjNode] == 0 && exists[adjNode]) q.push(adjNode);
            }
        }
        
        return topo;
    }
    
public:
    string findOrder(vector<string>& words) 
    {
        int n = words.size();
        
        // adjacency list and in-degree array
        vector<int> adj[26];
        vector<int> inDeg(26, 0);
        vector<bool> exists(26, false);  // Track which characters exist
        
        // Mark existing characters
        for (string word : words) 
        {
            for (char ch : word) exists[ch - 'a'] = true;
        }
        
        // Build graph from adjacent words
        for (int i = 0; i < n - 1; i++) 
        {
            string w1 = words[i];
            string w2 = words[i + 1];
            
            // Check invalid case: if w1 is longer and w2 is prefix of w1
            if (checkInvalidOrder(w1, w2)) return "";
            
            // Find first differing character
            int len = min(w1.size(), w2.size());
            
            for (int j = 0; j < len; j++) 
            {
                if (w1[j] != w2[j]) 
                {
                    int u = w1[j] - 'a';
                    int v = w2[j] - 'a';
                    adj[u].push_back(v);
                    inDeg[v]++;
                    break;
                }
            }
        }
        
        // Get topological sort
        vector<int> topo = getTopoSort(26, adj, inDeg, exists);
        
        // Check for cycle: if topo sort doesn't include all nodes with edges
        int count = 0;
        for (int i = 0; i < 26; i++) 
        {
            if (exists[i]) count++;
        }
        
        string ans = "";
        
        // Cycle detected
        if (topo.size() != count) return ans;

        // Construct result string
        for (int x : topo) 
        {
            if (exists[x]) 
            {
                ans += (char)(x + 'a');
            }
        }
        
        return ans;
    }
};

//{ Driver Code Starts.

bool validate(const vector<string> &original, const string &order) {
    unordered_map<char, int> mp;
    for (const string &word : original) {
        for (const char &ch : word) {
            mp[ch] = 1;
        }
    }
    for (const char &ch : order) {
        if (mp.find(ch) == mp.end())
            return false;
        mp.erase(ch);
    }
    if (!mp.empty())
        return false;

    for (int i = 0; i < order.size(); i++) {
        mp[order[i]] = i;
    }

    for (int i = 0; i < original.size() - 1; i++) {
        const string &a = original[i];
        const string &b = original[i + 1];
        int k = 0, n = a.size(), m = b.size();
        while (k < n and k < m and a[k] == b[k]) {
            k++;
        }
        if (k < n and k < m and mp[a[k]] > mp[b[k]]) {
            return false;
        }
        if (k != n and k == m) {
            return false;
        }
    }
    return true;
}

int main() {
    string str;
    getline(cin, str);
    int t = stoi(str);
    while (t--) {
        getline(cin, str);
        stringstream ss(str);
        string curr;
        vector<string> words;
        while (ss >> curr)
            words.push_back(curr);

        vector<string> original = words;

        Solution ob;
        string order = ob.findOrder(words);

        if (order.empty()) {
            cout << "\"\"" << endl;
        } else {
            cout << (validate(original, order) ? "true" : "false") << endl;
        }
        cout << "~" << endl;
    }
    return 0;
}

// } Driver Code Ends