class Solution {
    public:
        int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
        {
            // create set for searching words in list
            // set also works as vis array for bfs
            set<string> set;
            for (string word : wordList) set.insert(word);
    
            queue<pair<string, int>> q;
            q.push({beginWord, 1});
            set.erase(beginWord);
            int ans = 0;
    
            while(!q.empty())
            {
                auto it = q.front();
                string word = it.first;
                int len = it.second;
                q.pop();
    
                if (word == endWord)
                {
                    ans = len;
                    break;
                }
    
                // try changing every char of word
                for (int i=0; i<word.size(); i++)
                {
                    char orgCh = word[i];
    
                    for (char ch='a'; ch<='z'; ch++)
                    {
                        word[i] = ch;
    
                        if (set.find(word) != set.end())
                        {
                            q.push({word, len+1});
                            set.erase(word);
                        }
                    }
    
                    word[i] = orgCh;
                }
            }
    
            return ans;
        }
    };