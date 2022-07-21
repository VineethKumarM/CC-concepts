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
/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. 
You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
*/
/*at last all our elements are included we will add the difference for both the elements*/
int maxProfit(vector<int>& prices) {
        int sum=0;
        if(prices.size()==0 or prices.size()<2) return 0;
        for(int i=1;i<prices.size();i++)
        {
            if(prices[i]>prices[i-1])
            {
                sum+=prices[i]-prices[i-1];
            }
        }
        
        return sum;
    }
int solve(vii m)
{
   int ans=0;
    int cnt=0;
int ind=-1;
   while(true){
       for(int i=0;i<m[0].size();i++)
       {
             if(m[cnt][i]==1){
                 if(m[0].size()-i+1>ans){
                     ans=m[0].size()-i+1;
                     ind=cnt;
                     break;
                 }
             }   
       }
       cnt++;
       if(cnt>=m.size()) break; 
   }
   return ind;
}
/*Given a string s, determine if it is valid.

A string s is valid if, starting with an empty string t = "", you can transform t into s after performing the following operation any number of times:

Insert string "abc" into any position in t. More formally, t becomes tleft + "abc" + tright, where t == tleft + tright. Note that tleft and tright may be empty.
Return true if s is a valid string, otherwise, return false*/
bool isValid(string s) {
        stack<char> st;
      for(int i=0;i<s.size();i++)
      {
        if(s[i]=='c')
        {
          if(st.size()>=2)
          {
            if(st.top()=='b')
            {
              st.pop();
              if(st.top()=='a')
                st.pop();
              else return false;
            }else return false;
          }else
            return false;
        }else
          st.push(s[i]);
      }
      return st.size()==0;
    }
int main()
{
    // freopen("input.txt", "r", stdin); 
    // freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vii m={{0,1,1,1},{0,0,1,1},{1,1,1,1}};
    cout<<solve(m);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 