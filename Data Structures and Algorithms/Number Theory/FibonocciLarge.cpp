#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define viil vector<vector<ll>>
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
#define mod1 1e9+7
ll mul_mod(ll a,ll b,ll mod)
{
  ll res=0;
  while(b)
  {
    if(b&1) res=(res+a)%mod;
    a=(a+a)%mod;
    b/=2;
  }
  return res;
}
viil mul_matrix(viil A,viil B)
{
    ll n=A.size();
    viil ans(n,vector<ll>(n));//All will be set to 0
    for(ll r=0;r<n;r++)
    {
        for(ll c=0;c<n;c++)
        {
            for(ll i=0;i<n;i++)
             ans[r][c]+=mul_mod(A[r][i],B[i][c],mod1);
        }
    }
    return ans;
}
//The complexity of matrix eponentiation is O(log n *r^3);
viil matrix_exp(viil M,ll n)
{
    ll r=M.size();
    viil res(r,vector<ll>(r));
    for(ll i=0;i<r;i++) res[i][i]=1;
    while(n)
    {
        if(n%2)
         res=mul_matrix(res,M);
         M=mul_matrix(M,M);
         n/=2;
    }
    return res;
}
int main()
{   
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll t;cin>>t;
    while(t--)
    {
    ll n;cin>>n;
    viil M(2,vector<ll>(2));
    M[0][0]=M[1][0]=M[0][1]=1;
    M[1][1]=0;
    viil b(2,vector<ll>(1));
    b[0][0]=1;b[1][0]=0;
    viil b_n_1=matrix_exp(M,n-1);
    viil ans(2,vector<ll>(1));
    for(ll r=0;r<2;r++)
    {
        for(ll c=0;c<1;c++)
         {
             for(ll i=0;i<2;i++)
              ans[r][c]+=mul_mod(b_n_1[r][i],b[i][c],mod1); 
         }
    }
   cout<<ans[0][0]<<'\n';
    }
    return 0;
}