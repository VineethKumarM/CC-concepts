#include<bits/stdC++.h>
using namespace std;
#define  ll long long int
#define vi vector<int>
#define fl(i,n) for(int i=0;i<=n;i++)
#define pb push_back
const ll mod=1e9+7;
ll mulmod(ll a, ll b,ll c){
    ll x = 0,y=a%c;
    while(b > 0){
    if(b%2 == 1){
        x = (x+y)%c;
       // cout<<x<<" ";
    }
    y = (y*2LL)%c;
    //cout<<y<<" ";
    b /= 2;
   // cout<<b<<" "<<endl;
    }
    return x%c;
}
ll binpower(ll a,ll n,ll m)
{
    ll res=1;
    while(n)
    {
        if(n%2)
        {
         res=mulmod(res,a,m);
         n--;
        }
         else
           {
              a=mulmod(a,a,m);
              n/=2;
           }
    }
    return res%m;
}
bool isprime(ll n, int it=5)
{
    if(n<4)
    return n==2 || n==3;
    for(int i=1;i<=5;i++)
    {
      ll a=2+rand()%(n-3);
      ll res=binpower(a,n-1,n);
      if(res!=1) return false;
    }
    return true;

}
//Miller Rabin primality test
/*Considered to be more efiicient and strict version than fermats primality list
It gives strong probable primes with 75% probability 
Here we will check if n divides atleast one of the factors of the number a^n-1
First we wiill start with (a^d-1)(a^d+1)
Then we will  iterate it with its square until we get (a^(2^(s)*d)-1)(a^(2^(s)*d)+1)
Although it gives more acuracy than fermats priliminary test it is also non deterministic
approach only
*/
ll checkcomposite(ll n,ll a,ll d,ll s)
{
   ll x=binpower(a,d,n);
   if(x==1 || x==n-1)
   return false;
   for(int i=1;i<s;i++)
   {
       x=mulmod(x,x,n);
       if(x==n-1)
       return false;
   }

  return true;
}
bool isprimem(ll n,int it=5)
{
    if(n<4)
     return n==2 || n==3;
     ll d=n-1;
     ll s=0;
     while((d & 1)==0)
     {
         d>>=1;
         s++;
     }
     fl(i,it)
     {
      ll a=2+rand()%(n-3);
      if(checkcomposite(n,a,d,s))
       return false;
     }
     return true;

}
/*Miller showed that it is possible to make the algorithm deterministic by only 
 checking all bases ≤O((lnn)2). Bach later gave a concrete bound, it is only 
 necessary to test all bases a≤2ln(n)2.
 For 32 bit integer checking for 2,3,5,7 is enough
 For 64 bit integer checking for first 12 primes is enough
 So people have invested quite a lot of computation power into finding lower bounds */
int main()
{
    
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cout<<mulmod(2,100,100000000);
    // int t;
    // cin>>t;
    // while(t--)
    // {
    //     ll n; cin>>n;

    // cout<<isprime(n);
    // }
    cout<<isprimem(11);
    cout<<endl;
    cout<<isprime(12111);
    return 0;
}