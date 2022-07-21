#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define Max 100000
//Sieve of Sundaran with O(n) complexity
void SieveofSundaran(int n)
{
    //Since the sieve of sundaran calucates all the prime numbers upto 2n+1
    //so we are reducing here to nnwe so it can print only n numbers
    int nnew=(n-1)/2;
    bool marked[nnew+1];
    memset(marked,false,sizeof(marked));
    for(int i=1;i<n;i++)
    {
        for(int j=i;(i+j+2*i*j)<=nnew;j++)
         marked[i+j+2*i*j]=true;
    }
    if(n>1) cout<<2<<'\n';
    for(int i=1;i<=nnew;i++)
    {
        if(marked[i]==false)
        cout<<2*i+1<<'\n';
    }
}
//Sieve of Sundaran with O(log n) time complexity
vector<int> primes;
void SieveSundaram()
{
    bool marked[Max/2+100]={false};
    for(int i=1;i<=sqrt(Max-1)/2;i++)
    for(int j=i*(i+1)<<1;j<=Max/2;j=j+2*i+1)
     marked[j]=true;
     primes.pb(2);
     for(int i=1;i<=Max/2;i++)
     if(marked[i]==false) 
      primes.pb(2*i+1);
}
bool IsSmith(int n)
{
    int pdigits=0;
     int temp=n;
    for(int i=0;primes[i]<=n/2;i++)
    {
      
        while(n%primes[i]==0)
        {
            int k=primes[i];
            n/=k;
            while(k)
            {
                pdigits+=(k%10);
                k/=10;
            }
        }
    }
    if(n!=1 && n!=temp)
    {
        while(n)
        {
            pdigits+=n%10;
            n/=10;
        }
    }
    int sod=0;
    while(temp)
    {
        sod+=temp%10;
        temp/=10;
    }
    return (sod==pdigits);
}
vi spf(Max,0);
void sieveofer()
{
    bool isprime[Max]={true};
    isprime[0]=isprime[1]=false;
    for(int i=2;i<=Max;i++)
    {
       if(spf[i]==0)
       {
           spf[i]=i;
           for(int j=2*i;j<Max;j+=i)
            if(spf[j]==0)
             spf[j]=i;
       }
    }
}
//O(nlogn) Time complexity
bool isSphenic(int n)
{
    set<int> s;
    while(n>1)
    {
        int sp=spf[n];
        int init=s.size();//checking total prime numbers for each iteration befor inserting
        s.insert(sp);//no two same factors are inserted
        if(s.size()==init || s.size()>3) return false;//if both sizes are equal then one prime factor is not inserted
        n/=sp;
    }
    return(s.size()==3);

}
//Finding kth prime factor
int findkthprimefactor(int n,int k)
{
    while(n>1)
    {
        if(k==1)
         return spf[n];
         k--;
         n/=spf[n];
    }
    return -1;
}
//mul_mod handles the overflow of integers
long long mul_mod(ll a,ll b,ll mod)
{
    ll res=0;
    while(b)
    {
        if(b & 1)
         res=(res+a)%mod;
          a=(a+a)%mod;
         b>>=1;
    }
    return res;
}
//Normal function f(x)=x^2+c here c mostky taken as c=1 but if we take some other 
//random c it will work faster sometimes and sometimes worse
ll func(ll x,ll c,ll mod)
{
    return (mul_mod(x,x,mod)+c)%mod;
}
//Polards Rho Algorithm for integer prime factorisation 
ll RhoAlgo(ll n)
{
    srand(time(NULL));//intialises seed  for producing random values
    if(n==1) return n;//no prime factors for 1
    if(n==2) return 2;//if n is even then one of the prime factor will be 2
    ll x=rand()%(n-2)+2;//Produces ant x b/.w(2,n-2)
    ll y=2;//at first y equals x
    ll c=rand()%n-2+1;//gaberates a random c in b/w(1,n-2)
    ll gcd=1;
    while(gcd==1)//if we found gcd other than 1
    {
        x=func(x,c,n)%n;
        y=func(y,c,n)%n;
        y=func(y,c,n)%n;
         gcd=__gcd(abs(x-y),n);
        if(gcd==n) return RhoAlgo(n);//if gcd ==n then we havent found any prime factor
        //so repeat the orocess
    }
    return gcd;

}
//Checking politeness of a number
ll C_oddprimefactors(ll n)
{
    while(n%2==0)
     n/=2;
     ll res=1;
     for(ll i=3;i<=n;i+=2)
     {
         if(n%i==0)
         {
            int cnt=0;
            while(n%i==0)
            {
                cnt+=1;
                n/=i;
            }
            res*=(1+cnt);
         }
     }
     if(n>2)
      res*=2;
      return res;
}
ll politeness(ll n)
{
    return C_oddprimefactors(n)-1;//Since representation od single number is not allowed
}
//Power of p in n! using Legendres formula without caluclating factorial
//Complexity O(logp N)
ll powerof_p(ll n,ll p)
{
    int res=0;
    ll temp=p;
    while(temp<=n)
    {
        res+=(n/temp);
        temp*=p;
    }
    return res;
}
//Finding all divisors im O(sqrtn) complexity
//Inorder to sort print the is case and store n/i values and then print the vector 
void divisors(ll n)
{
    for(int i=1;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            cout<<i<<' ';
            if(n/i!=i)
             cout<<n/i<<' ';
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // SieveofSundaran(10000);
    SieveSundaram();
    sieveofer();
   
//    for(int i=1;i<500;i++)
//     if(isSphenic(i)) cout<<i<<'\n';
   //cout<<findkthprimefactor(15,2);
//    cout<<RhoAlgo(10967535067);
//    cout<<'\n';
//    cout<<(10967535067)/RhoAlgo(10967535067);
  //cout<<politeness(90);
    //cout<<powerof_p(12,2);
    
    return 0;
}
