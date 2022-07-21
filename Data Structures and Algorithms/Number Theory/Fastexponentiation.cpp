 #include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++); 
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
#define vii vector<vector<int>>
#define viil vector<vector<ll>>
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
             ans[r][c]+=A[r][i]*B[i][c];
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
const ll mod=1e9+7;
ll exp(int a,int n)
{
    ll res=1;
    // for(int i=0;i<31;i++)
    // {
    //     if(n & (1<<i))
    //      res=res*a;
    //      a=a*a;
    // }
    while(n)
    {
        if(n%2)
         res=(res%mod*a%mod)%mod;
         a=(a%mod*a%mod)%mod;
         n/=2;//here we are not taking modulo for n because ther is no
  //property that expononent should also take mod ;a^x%mod!=a%mod^(x%mod)%mod
  //Propety for exponentiation is a^n%p=a^(n%phi(p));
  //not required but incase we have to do then use Eulers totient function
    }
    return res%mod;
}
//Calulating mod inverse with respect to mod m;
ll modinverse(ll a,ll m)
{
    return exp(a,m-2);
}
int main()
{   
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // cout<<exp(2,17);
    // int size,n;cin>>size>>n;
    // vii M(size,vector<int>(size));
    // for(int i=0;i<size;i++) {for(int j=0;j<size;j++) cin>>M[i][j];}
    // vii an=matrix_exp(M,n); 
    // for(int i=0;i<size;i++) 
    // {
    //     for(int j=0;j<size;j++)
    //      cout<<an[i][j]<<" ";
    //      cout<<endl;
    // }
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
    for(int r=0;r<2;r++)
    {
        for(int c=0;c<1;c++)
         {
             for(int i=0;i<2;i++)
              ans[r][c]+=mul_mod(b_n_1[r][i],b[i][c],mod1); 
         }
    }
   cout<<ans[0][0]<<'\n';
    }
    return 0;
}