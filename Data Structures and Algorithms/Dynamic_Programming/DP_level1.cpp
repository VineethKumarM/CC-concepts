#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
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
/*Fibonocii*/
int fibo_dp(int n)
{
    vector<int> dp(n+1);
    dp[0]=0,dp[1]=1;
    for(int i=2;i<=n;i++)
     dp[i]=dp[i-1]+dp[i-2];
}
/*Stair paths*/
int stair_dp(int n)
{
    vector<int> dp(n+1);
    dp[0]=1;
    for(int i=1;i<=n;i++)
   {
    if(i==1)
     dp[i]=dp[i-1];
     else if(i==2)
     dp[i]=dp[i-1]+dp[i-2];
     else
     dp[i]=dp[i-1]+dp[i-2]+dp[i-3];
   }
   return dp[n];
}
/*In case at each stage if we variable jumps*/
int stair_dp_variable(int n,vi steps)
{
  vi dp(n+1,0);
   dp[n]=1;
    for(int i=n-1;i>=1;i--)
    {
      int sum=0;
      int step=1;
      /*We will add all the possible steps from the current level to the possible steps we
      can make*/
      while(step<=steps[i-1] and step+i<=n)
        {
          sum+=dp[i+step];
           step++;
        }
        dp[i]=sum;
    }
    return dp[0];
}
int stair_dp_min_steps(int n,vi steps)
{
  /*As we are having some states which are having steps[i]=0*/
  vi dp(n+1,-1);
  dp[n]=0;
  for(int i=n-1;i>=1;i--)
  {
    if(steps[i]>0)
    {
        int mini=INT_MAX;
        for(int j=1;j<=steps[i];j++)
        {
          if(i+j<=n and dp[i+j]!=-1)
          mini=min(mini,dp[i+j]);
        }
        /*If in case it reaches to those stairs at which we cannot make any moves then
        we will put those values as - only*/
        if(mini!=INT_MAX)
        dp[i]=mini+1;
        else
        dp[i]=-1;
    }
  }
  return dp[0];
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}