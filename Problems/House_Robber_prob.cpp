#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vb vector<bool>
#define vs vector<string>
#define vii vector<vector<int>>
#define vvcc vector<vector<char>>
#define vpii vector<pair<int,int>>
#define vvii vector<vector<int>>
#define vvbb vector<vector<bool>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
#define pairi pair<int,int>
#define umpcb unordered_map<char,bool>
#define umpib unordered_map<int,bool>
#define umpsb unordered_map<string,bool>
#define umpci unordered_map<char,int>
#define umpii unordered_map<int,int>
#define umpsi unordered_map<string,int>
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
int house_rob(vi houses){
    vi dp(houses.size());
    dp[0]=houses[0];
    dp[1]=max(houses[0],houses[1]);
    for(int i=2;i<houses.size();i++)
      dp[i]=max(dp[i-1],houses[i]+dp[i-2]);
      return dp[houses.size()-1];
}
/*Each house has a certain amount of money stashed. All houses at this place are arranged in a circle
Given an integer array nums representing the amount of money of each house, 
return the maximum amount of money you can rob tonight without alerting the police.*/
/*In this approach we will do two iterations to convert them into linear firt we will find 
the max profit only upto n-2 house without including the last house and in the second iteraytion
without inlcuding the first house so that in both the iteration we an take care of the constarinst
that adjacent gouse robberd cannot be roobeed'
At the end we will return the maximum of both the posiible values
We should take care the base conditions*/
int circle_house_rob(vi houses){
    if(houses.size()==1) return houses[0];
    if(houses.size()==2) return max(houses[0],houses[1]);
    int n=houses.size();
    vi dp(n);
    dp[0]=houses[0];
    dp[1]=max(houses[0],houses[1]);
    for(int i=0;i<n-1;i++)
      dp[i]=max(dp[i-1],houses[i]+dp[i-2]);
      int max1=dp[n-2];
      dp.clear();
      dp[1]=houses[1];
        dp[2]=max(houses[1],houses[2]);
    for(int i=0;i<n;i++)
        dp[i]=max(houses[i]+dp[i-2],dp[i]);
        int max2=dp[n-1];
        return max(max1,max2);
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