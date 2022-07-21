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
//Caluclating Eulers Totient of (n) 
ull Totient(ull n)
{
    float result=n;
    for(int p=2;p*p<=n;p++)
    {
        if(n%p==0)//Checking Prime Divisors 
        {
            while(n%p==0) n/=p;//Taking all the primes of that divisor
            result*=(1.0-(1.0/(float)p));
            //result-=(result/p);We can avoid the above floating point calucaltion by this step
        }
    }
    if(n>1) result*=(1.0-(1.0/(float)n));
    return (ull) result;
}
//Optimised way to find f(n) for multiple queries using Sieve of Erathrosenes
vil primes;
void Sieve()
{
    ll n=100000;
    vb isprime(n);
    std::fill(isprime.begin(),isprime.end(),true);
    for(int i=2;i*i<=n;i++)
    {
      if(isprime[i])
      {
          primes.pb(i);
          for(int j=i*i;j<=n;j+=i) isprime[j]=false;
           
      }
    }
}
//ETf only iterarting over the primes reducing the unnecessary caluclation of iterating 
//over all the numbers upto sqrt(n)
ll ETF(ull n)
{
    ll res=n;
    for(int p:primes)
    {
      if(p*p>n) break;
      if(n%p==0)
      {
       res-=(res/p);while(n%p==0) n/=p;
      }
    }
    if(n>1) res-=(res/n);
    return res;
}
//Compute Eulers Totient Function to compute phi (N)form 1 to n-1
//Based on precomputing all values for each prime
vil Conpute_Totient(ull n)
{
   vil phin(n+1);
   for(int i=0;i<=n;i++) phin[i]=i;//Initialsing all its values with its index
   for(int p=2;p<=n;p++)
   {
       if(phin[p]==p)//If it wasnot computed then it is prime
       {
           phin[p]=p-1;//for prime phin[p]=p-1;
           for(int i=2*p;i<=n;i+=p)//Contributing this factor to all of its multiples
           //in which this prime factors is there
            phin[i]=(phin[i]/p)*(p-1);
       }
   }
    return phin;
}
ll Power_Modulo(ll a,ll n,ll m)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=(res*(1ll)*a)%m;
         a=(a*(1ll)*a)%m;
         n/=2;
    }
    return res;
}
//Finding Power Modulo
ll Primitive_Root(ll p)
{
    ll phini=p-1;
    ll n=phini;
    vil fact;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
         {
             fact.pb(i);//pushing only one prime factor
             while(n%i==0)
              n/=i;//Taking out all divisors
         }
    }
    if(n>1) fact.pb(n);
    for(int res=2;res<=p;res++)
    {
        bool ok=true;
        for(size_t i=0;i<fact.size() && ok;i++)
        {
            ok&=Power_Modulo(res,phini/fact[i],p)!=1;//here we are onlu checking fro, phi/p types
            //because the power of the p in phin is of no use
            //It can be proved
        }
        if(ok) return res;
    }
    return -1;
}
bool Issquare(ll n)
{
    double i=sqrt(n);
    if(i*i==n) return true;
    else return false;
}
bool Check_EulersIdentity(ll a,ll b)
{
    ll n=a*b;
    int i=0,j,k;
    while(i*i<=n)
    {
        int j=i;
        while(j*j+i*i<=n)
        {
            int k=j;
            while(j*j+i*i+k*k<=n)
            {
              ll t=k-(j*j+i*i+k*k);
              if(Issquare(t)) return true;
              else k++;
            }
            j+=i;
        }
        i+=1;
    }
    return false;
} 
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Sieve();
    //cout<<ETF(100);
    //vil phin=Conpute_Totient(101);
    //cout<<Totient(100);
    //cout<<phin[100];
   // cout<<Power_Modulo(2,3,5);
   cout<<Check_EulersIdentity(30,1);
    return 0;
}
