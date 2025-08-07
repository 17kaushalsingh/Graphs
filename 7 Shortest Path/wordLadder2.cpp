//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends

//User function Template for C++

class Solution {
public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) 
    {
        set<string> set;
        for (string word : wordList) set.insert(word);
        
        queue<vector<string>> q;
        vector<string> usedOnLevel;
        int level = 0;
        
        q.push({beginWord});
        usedOnLevel.push_back(beginWord);
        
        vector<vector<string>> ans;
        while(!q.empty())
        {
            vector<string> vec = q.front();
            q.pop();
            
            // check if prev level is fully used
            if (vec.size() > level)
            {
                level++;
                
                for (string word : usedOnLevel) set.erase(word);
                usedOnLevel.clear();
            }
            
            string word = vec.back();
            
            if (word == endWord)
            {
                if (ans.size() == 0 || ans[0].size() == vec.size())
                {
                    ans.push_back(vec);
                }
            }
            
            for (int i=0; i<word.size(); i++)
            {
                char orgCh = word[i];
                
                for (char ch='a'; ch<='z'; ch++)
                {
                    word[i] = ch;
                    if (set.find(word) != set.end())
                    {
                        // add to sequence
                        vec.push_back(word);
                        
                        q.push(vec);
                        usedOnLevel.push_back(word);
                        
                        // remove for next word in same sequence length
                        vec.pop_back();
                    }
                }
                
                word[i] = orgCh;
            }
        }
        
        return ans;
    }
};


//{ Driver Code Starts.

bool comp(vector<string> a, vector<string> b)
{
    string x = "", y = "";
    for(string i: a)
        x += i;
    for(string i: b)
        y += i;
    
    return x<y;
}

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		vector<string>wordList(n);
		for(int i = 0; i < n; i++)cin >> wordList[i];
		string startWord, targetWord;
		cin >> startWord >> targetWord;
		Solution obj;
		vector<vector<string>> ans = obj.findSequences(startWord, targetWord, wordList);
		if(ans.size()==0)
		    cout<<-1<<endl;
		else
		{
		    sort(ans.begin(), ans.end(), comp);
            for(int i=0; i<ans.size(); i++)
            {
                for(int j=0; j<ans[i].size(); j++)
                {
                    cout<<ans[i][j]<<" ";
                }
                cout<<endl;
            }
		}
	
cout << "~" << "\n";
}
	return 0;
}
// } Driver Code Ends