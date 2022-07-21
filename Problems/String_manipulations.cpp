#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vb vector<bool>
#define vii vector<vector<int>>
#define vpii vector<pair<int,int>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
#define pairi pair<int,int>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
#define ull unsigned long long int
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 10000
const ll mod=1e9+7;
const ll size=2*(1e6+1);
const ll limit=1e10+7;
/*https://leetcode.com/problems/find-and-replace-pattern/*/
vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
      vector<string> ans; 
      for(int i=0;i<words.size();i++)
      {
          /*Here we maintain maps for both the pattern and word*/
          unordered_map<char,char> pat,word;
        bool flag=true;
          for(int j=0;j<pattern.size();j++)
          {
            if(pat.find(words[i][j])==pat.end())
              pat[words[i][j]]=pattern[j];
            if(word.find(pattern[j])==word.end())
              word[pattern[j]]=words[i][j];
            if(pat[words[i][j]]!=pattern[j] or word[pattern[j]]!=words[i][j])
            {
              flag=false;
              break;
            }
          }
        if(flag)
        ans.push_back(words[i]);
      }
      return ans;
    }
int main()
{
   // freopen("input.txt", "r", stdin); 
    //freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 