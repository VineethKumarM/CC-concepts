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
/*https://leetcode.com/problems/distinct-subsequences/submissions/*/
/*Given two strings s and t, return the number of distinct subsequences of s which equals t.

A string's subsequence is a new string formed from the original string by deleting some (can be none) of the characters without disturbing the remaining characters' relative positions. (i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).

It is guaranteed the answer fits on a 32-bit signed integer.

 */
/*Base case is that when we are having s.size()==0 we hcannot get any susbsequence from it
so the dp[i][j]=0 if(i==0) and if the target stringsize is 0 then there is always a way exists
we can get by not picking any elemnt from the original string
Therefore it implies that dp[i][j]=0 if(j==0)
As we move forward we have two option if s[i]==s[j] or s[i]!=s[j] then
If(s[i]!=s[j]
 we will not take this oarticular character into our account and then we increment the charcter of mathing
 chacrcter for further matcjhing and keeping the present charcter of current string as constant
 dp[i][j]=dp[i-1][j]
 if(s[i]==s[j])
 then two cases arises where we take ths charceter into accoiunt and another case is that whene we havent 
 taken that character then dp[i][j]=dp[i-1][j-1]+dp[i-1][j] we will add both the cases sum*/
 long int dp[1001][1001];
     int solve(string s,string t)
     {
       for(int i=0;i<s.size();i++) for(int j=0;j<t.size();j++) 
       {if(i==0) dp[i][j]=0;
       if(j==0) dp[i][j]=1;}
         for(int i=1;i<=s.size();i++)
         {
             for(int j=1;j<=t.size();j++)
             {
                 if(s[i-1]!=t[j-1]) dp[i][j]=dp[i-1][j];
                 else 
                     dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
             }
         }
         return dp[s.size()][t.size()];
         
     }
    int numDistinct(string s, string t) {
        if(s.size()==t.size())
        {
            if(s==t) return 1;
            else return 0;
        }
        return solve(s,t);
        
        
    }
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 