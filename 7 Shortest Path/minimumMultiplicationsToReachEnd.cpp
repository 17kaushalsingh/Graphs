//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution 
{
  private:
    
  public:
    int minimumMultiplications(vector<int>& arr, int start, int end) 
    {
        int n = arr.size();
        
        vector<int> steps(100001, INT_MAX);
        queue<pair<int, int>> q; // seteps, val
        
        q.push({0, start});
        steps[start] = 0;
        
        while(!q.empty())
        {
            int step = q.front().first;
            int val = q.front().second;
            q.pop();
            
            if (val == end) return step;
            
            for (int i=0; i<n; i++)
            {
                int newVal = (val * arr[i]) % 100000;
                
                if (1 + step < steps[newVal])
                {
                    steps[newVal] = 1 + step;
                    q.push({1+step, newVal});
                }
            }
        }
        
        int ans = steps[end];
        
        if (ans == INT_MAX) return -1;
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
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        int start, end;
        cin >> start >> end;
        Solution obj;
        cout << obj.minimumMultiplications(arr, start, end) << endl;
    
cout << "~" << "\n";
}
}

// } Driver Code Ends