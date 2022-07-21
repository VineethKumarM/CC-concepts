#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vb vector<bool>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
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
const ull mod1=1e9+7;
int arr[100003][4];
int dp[1000][4];
//Problem of Tasks
int Dpprob(int day,int ind)
{
    if(day==0) return 0;
    if(dp[day][ind]!=(-1)) return dp[day][ind];
    int ans=0;
    for(int i=0;i<3;i++)
    {
        if(i!=ind)
        ans=max(ans,Dpprob(day-1,i));
    }
    ans+=arr[day][ind];
    return dp[day][ind]=ans;
}
int arr1[10000];
int dp1[1000];
//Kadanes Algorithm using DP
int Kadanes_Algo(int n)
{
 dp1[0]=arr1[0];
 int ans=arr1[0];
 for(int i=1;i<n;i++)
 {
     dp1[i]=max(arr1[i],dp1[i-1]+arr1[i]);
     ans=max(ans,dp1[i]);
 }
 return ans;
}
//Longest Increasing Subsequence
int Longest_Inc_SubSequence(int n)
{
    dp1[0]=1;
    int maxi=1;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<=i-1;j++)
        {
            if(arr1[i]>arr1[j])
             dp1[i]=max(dp1[i],1+dp1[j]);
        }
        maxi=max(maxi,dp1[i]);
    }
   return maxi;
}
//String Algorithm
//Minimum cost to make the s1 to s2 using insertion,deletion and replacement with their 
//respective costs

void String_Algo()
{
    string s1,s2;cin>>s1>>s2;
    int ci,cr,cd;cin>>ci>>cr>>cd;
    int n=s1.size();
    int m=s2.size();
   for(int i=0;i<=n;i++)
   {
       for(int j=0;j<=m;j++)
       {
           if(i==0) dp[i][j]=(j*ci);
           else if(j==0) dp[i][j]=(i*cd);
           else if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1];
           else 
           {
               dp[i][j]=min(dp[i][j-1]+ci,min(dp[i-1][j]+cd,dp[i-1][j-1]+cr));
           }
       }
   }
   cout<<dp[n][m];
}
int dphr[100000];
//In this a house rob problem there are a vector houses from 1 to n
//Each house has some points
//Condition is that robber cannot rob the prvious and next house if he was robbing current house
//Find max no.of points he can rob
//Here the robber can start anywhere
int House_Rob(vi v)
{
   int n=v.size();
   dphr[0]=v[0];//Base Cases
   dphr[1]=max(v[0],v[1]);
   for(int i=2;i<n;i++)
   dphr[i]=max((v[i]+dphr[i-2]),(dphr[i-1]));//(For first brackket we are inclding
   //v[i] th element and adding i-2 th house and second bracket since we are no including
   //current house we have an option for i-1 house also,So we are simply finning max of
   //therse two values and assigning them to the dp[i])
   //Ex. 1 200 3 4 500 Ans is 700
   return dphr[n-1];
}
int main()
{
    
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // memset(dp,0,sizeof(dp));
    // int n;cin>>n;
    // for(int i=0;i<n;i++) cin>>arr1[i];
    //int p1=Dpprob(n,1),p2=Dpprob(n,0),p3=Dpprob(n,2);
    // int p4=max(p1,p2);
    //cout<<max(p4,p3);
    //cout<<Longest_Inc_SubSequence(n)<<'\n';
    //bool is[100000];
    //memset(is,true,sizeof(is));
    int n;cin>>n;vi v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    cout<<House_Rob(v);
   
 // String_Algo();
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}