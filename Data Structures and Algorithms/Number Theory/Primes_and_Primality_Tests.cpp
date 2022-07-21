#include<bits/stdC++.h>
using namespace std; 
#define ll long long int
#define ull unsigned long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vull vector<ull>
#define vf vector<float>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define uint_64t unsigned ll
#define int_64t  ll
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 1000000
#define mod1 1e9+7
#define MAX 3000
ll binpower_mod(ll a,ll n,ll m)
{
    ll res=1;
    a%=m;//If a is greater than m then (m+k)=a this expansion will contain m multiples
    //So by taking mod we are reducing those caluclations
    while(n)
    {
        if(n&1) res=(res*a)%m;;
           a=(a*a)%m;
        n>>=1;
    }
    return res;
}
//Fermats Theoreem for finding primality test
//Time Complexity of the below method is O(klog n) time
bool Fermat_Test(ll n)
{
    if(n<=1 and n==4) return false;
    if(n<=3) return true;
    int k=5;
    while(k)
    {
        ll a=2+rand()%(n-4);
        if(__gcd(a,n)>1) return false;
        if(binpower_mod(a,n-1,n)!=1) return false;
        k--;
    }
    return true;
}
//Miller Rabin Test
//miller Rabin test is considered to be more accurate than fermats theoreem
//Becaue here we are checking two conditions 1.(a^(n-1)modn=1) since we derived from this
//expression only and the factors case
bool check_Composite(ll a,ll d,ll s,ll n)
{
    ll x=binpower_mod(a,d,n);//(a^d%n)
    if(x==1 || x==n-1) return false;//(checks a^d+1 || a^d-1 is divisible by n or not)
    //we are eqauting them to 1 and n-1 as (n-1+1) or (1-1) leads to zero
    for(int i=1;i<s;i++)
    {
        x=(ll)(x*x)%n;//Here we are squaring ecah time and only we have to check for
        //a^2sd+1 so only n-1
        if(x==n-1) return false;
    }
    return true;
}
bool Miller_Rabin_Test(ll n)
{
    if(n<1) return false;
    if(n==2 || n==3) return true;
    ll s=0;
    ll d=n-1;
    while(d%2==0)
    {
        d>>=1;
        s++;
    }
    //Iterating for 5 times for correctness
    for(int i=0;i<5;i++)
    {
        ll a=2+rand()%(n-3);
        if(check_Composite(a,d,s,n)) return false;
    }
    return true;
}
vil primes;
//Complexity of this code is O(nlog(log n)) time
void SieveofErathsrosenes()
{
    bool isprime[Maxx+5];
    memset(isprime,true,sizeof(isprime));
    isprime[0]=isprime[1]=false;
    for(int i=2;i*i<=Maxx;i++)
    {
       if(isprime[i])
       {
           for(int j=i*i;j<=Maxx;j+=i)
           isprime[j]=false;
       }
    }
    for(int i=0;i<Maxx;i++)
     if(isprime[i]) primes.pb(i);
}
//Sieve of Erathrosenes with linear time complexity o(n)
vi pr;
int lp[Maxx+5];
void Sieve_On_Comp()
{
    for(int i=2;i<=Maxx;i++)
    {
        if(lp[i]==0)
        {
            lp[i]=i;
            pr.pb(i);
        }
        for(int j=0;j<(int)pr.size() and pr[j]<=lp[i] and i*pr[j]<=Maxx;j++)
          lp[i*pr[j]]=pr[j];
    }
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cout<<Miller_Rabin_Test(97);
    Sieve_On_Comp();
    cout<<pr[25];
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}