#include<bits/stdC++.h>
#include<cstdint>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
const ll mod=1e9+7;
ll fib[1000];
void fibcode(ll n)
{
    int arr[100]={0};
   // cout<<arr[0]<<endl;
    int cnt=0;
    ll temp=n;
    for(ll i=99;i>=0;i--)
    {
        if(n>=fib[i])
        {
         arr[i-2]=1;
         if(temp==n)
          cnt=i-2;
          n=n-fib[i];
         //cout<<n<<endl;
        }
          
          if(n<0)
           break;   
    }
    for(int i=0;i<cnt+1;i++)
    cout<<arr[i];
    cout<<"1"<<endl;
}
//Fast doubling method
pair <ll,ll> fibn(ll n)
{
    if(n==0)
     return {0,1};
    auto p=(fibn(n>>1));
    auto c=(((p.first)%mod)*((2*p.second)%mod-(p.first)%mod))%mod;
    auto d=((p.second)%mod*(p.second)%mod)+(p.first%mod*p.first%mod)%mod;
    if(n&1)
     return {d,c+d};
     else
     return {c,d};

}
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;cin>>t;
    while(t--)
    {
      fib[0]=0;
      fib[1]=1;
      for(int i=2;i<1000;i++)
       fib[i]=(fib[i-1]%mod+fib[i-2]%mod)%mod;
      // cout<<fib[11]<<endl;
       
      // fibcode(18298399);
      pair <ll,ll> p;
      cout<<fibn(100).first<<" "<<fibn(10000).second;


    }
}