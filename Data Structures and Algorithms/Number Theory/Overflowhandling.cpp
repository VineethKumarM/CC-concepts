#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++); 
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
const ll MOD=1e9+7;
uint_64t mulmod(uint_64t a,uint_64t b,uint_64t m)
{
    long double x;
    uint_64t r;
    uint_64t c;
    if(a>=m) a%=m;
    if(b>=m) a%=m;
    x=a;
    c=a*b/m;//floor value
    r=(int_64t)(a*b-m*c)%m;
    return r<0 ? r+m : r;
}
ll binpower(ll a,ll n,ll mod=MOD)
{
  ll res=1;
  while(n)
  {
    if(n & 1) res=((__int128)res*a)%mod;
    a=((__int128)a*a)%mod;
    n/=2;
  }
  return res;
}
//Here why are we taking mod with (a-b) instead of 1e9+7 because a-b can be as big as 1e12 which is causing overflow but 1e9+7 won’t cause overflow. I am not able to understand where I am wrong.

int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;cin>>t;
    while(t--)
    {
       ll a,b,n;cin>>a>>b>>n;
       if(a==b)
       {
         cout<<(binpower(a,n,a-b)+binpower(b,n,a-b))%MOD<<'\n';
       }
       else
       {
         ll d=(binpower(a,n,a-b)+binpower(b,n,a-b))%(a-b);
         cout<<(__gcd(d,a-b))%MOD<<"\n";
       }
    }
      
     return 0;
}