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
using u64=uint64_t;
//using u128 =__int128_t;
const ll m=1e9+7;
vi primes;
int maxa=100001;
bool is__prime[1000000];
//Generating all primes
void sieve()
{
    int max=1000000;
    is__prime[0]=false;
    is__prime[1]=false;
    for(int i=2;i*i<max;i++)
    {
        if(is__prime[i])
        {
            for(int j=i*i;j<max;j+=i)
             is__prime[j]=false;
        }
    }
    for(int i=0;i<max;i++) {if(is__prime[i]) primes.pb(i);}
}
//Optimisation using blocked sieve

int cntprime(int n)
{
    const int S=10000;
    vi prime;
    int res=0;
    int nsqrt=sqrt(n);
    vector<char> is_prime(nsqrt+1,true);
    for(int i=2;i<=nsqrt;i++)
    {
        if(is_prime[i])
        {
             prime.pb(i);
             for(int j=i*i;j<=nsqrt;j+=i)
             is_prime[j]=false;
        }
    }
  //  for(int i=0;i<nsqrt;i++){if(is_prime[i]) prime.pb(i);}
    vector<char> block(S);
    for(int k=0;k*S<=n;k++)
    {
        fill(block.begin(),block.end(),true);
        int start=k*S;
        for(int p:prime)
        {
           int start_indx=(start+p-1)/p;
           int j=max(start_indx,p)*p-start;
           for(;j<S;j+=p)
              block[j]=false;
        }
       if(k==0)
       block[0]=block[1]=false;
       for(int i=0;i<S && start+i<=n;i++)
        if(block[i]) cout<<i<<endl;
        cout<<endl;
    }
  return res;  
}
//Generating Prime numbers in [L,R] range using Segmwnted Sieve Range
vil sqprimes;
vector<bool> SegmentedSieve(ll L,ll R)
{
    ll rsqrt=sqrt(R);
    
    vector<bool> isprm(rsqrt+1,true);
    for(ll i=2;i<=rsqrt;i++)
    {
         if(isprm[i])
         {
             sqprimes.pb(i);
             for(ll j=i*i;j<=rsqrt;j+=i)
             isprm[j]=false;
         }
    }
    vector<bool> rangeprm(R-L+1,true);
       for(ll p:sqprimes)
       {
           for(ll j=max(p*p,(L+p-1)/p*p);j<=R;j+=p)
              rangeprm[j-L]=false;
       }    

    if(L==0)
    rangeprm[0]=false;
   for(int i=0;i<=R-L;i++) if(rangeprm[i]) cout<<i+L<<'\n';
   return rangeprm;
}
//Generating All prime with  linear complexity
//Used only upto 1e7 
vector<int> primegen(ll n)
{
  vi pr;
  vi spf(n+1,0);
  for(int i=2;i<=n;i++)
  {
    if(spf[i]==0)
    {
      spf[i]=i;
      pr.pb(i);
    }
    for(int j=0;j<pr.size() && pr[j]<=spf[i] && i*pr[j]<=n;j++)
       {spf[i*pr[j]]=pr[j];
         cout<<i*pr[j]<<" ";
       }
       cout<<endl;
  }
  return pr;
}
ll binpower(ll a,ll b,ll n)
{
    if(b==0)
    return 1;
    ll res=binpower(a,b/2,n);
    if(b%2)
    return res*res*a;
    else
    return (res*res)%n;
}
//Fermats Primality Test
bool isprime(ll n,int itr=5)
{
  if(n==4)
   return n==2|| n==3;
   for(int i=0;i<itr;i++)
   {
     ll a=2+rand() %(n-3);
     if(binpower(a,n-1,n)!=1)
       return false;
   }
   return true;

}
u64 binpowerl(u64 base, u64 e, u64 mod)
{
  if(e==0)
   return 1;
   u64 result=1;
   base%=mod;
   while(e)
   {
     if(e&1)
      result=(u64)result*base %mod;
      base=(u64)base*base%mod;
     e>>=1;
   }
   return result;
}
bool check_composite(u64 a,u64 d,int s,u64 n)
{
   u64 x=binpowerl(a,d,n);
   if(x==1 || x==n-1)
    return false;
    for(int i=1;i<s;i++)
    {
       x=(u64)x*x%n;
       cout<<x<<endl;
       if(x==n-1)
       return false;
    }
    return true;
}
bool MillerRabin(u64 n,int iter=5)
{
  if(n<4)
   return n==2 || n==3;
   u64 d=n-1;
   int s=0;
   while((d&1)==0)
   {
     s++;
     d>>=1;
   }
   for(int i=0;i<iter;i++)
   {
     int a=2+rand() % (n-3);
     if(check_composite(a,d,s,n))
       return false;
   }
   return true;
}
//Femats Factorisation Method O(p-q) method 
int Fermat(int n)
{
  int a=ceil(sqrt(n));
  int b1=a*a-n;
  int b=round(sqrt(b1));
  while(b*b!=b1)
  {
    a+=1;
    b1=a*a-n;
    b=round(sqrt(b1));
  }
  return a-b;
}
int main()
{
    
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cout<<cntprime(100000000);
   // ll l=1000;ll r=1000000;
    //vector<bool> p=SegSievnopregen(l,r);
    //vector<bool> p=SegmentedSieve(l,r);
   // for(int i=l;i<r;i++)
      //if(p[i]) cout<<i<<endl;
      //cout<<MillerRabin(113)<<endl;
      //int n=19;
     // cout<<Fermat(n)<<" "<<n/Fermat(n)<<endl;
     SegmentedSieve(100,200);
     for(ll p:sqprimes) cout<<p<<' ';
    
    return 0;
}    
