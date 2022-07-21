#include<bits/stdC++.h>
using namespace std;
#define  ll long long int
#define vi vector<int>
#define fl(i,n) for(int i=0;i<=n;i++)
#define pb push_back
ll m=1000000001;
bool p[90000000];//since it is declared globally all the values will be intialised with 0;
vector <int> pr;
const ll maxn=1000000;
//finding kth prime
void findk()
{
    int max=90000000;
    p[0]=p[1]=true;
    for(int i=2;i<=sqrt(max);i++)
    {
        if(!p[i])
        {
            for(int j=i*i;j<max;j+=i)
             p[j]=true;
             
           
        }
    }
    for(int i=0;i<max;i++)
    {
        if(!p[i])
          pr.push_back(i);
    }

}
//Binary exponentiation to calulate a^n in O(logn) time

ll power(ll a,ll n)
{
    ll res=1;
    while(n)
    {
        if(n%2)
        {
         res*=a;
         n--;
        }
         else
           {
              a*=a;
              n/=2;
           }
    }
    return res;
}
//prime factorisation in O(logn) time
int arr[1000000];
void primef()
{
    int max=100001;
    for(int i=0;i<max;i++) arr[i]=-1;
    for(int i=2;i<max;i++)
    {
        if(arr[i]==-1)
        {
            for(int j=i;j<max;j+=i)
            {
            if(arr[j]==-1)
             arr[j]=i;
            }
        }
    }


}
ll phi(ll n)
{
    ll res=n;
    for(int i=2;i*i<=(n);i++)
    {
       if(n%i==0)
       {
           res/=i;
           res*=(i-1);
           while(n%i==0) 
            n/=i;
       }
    }
    if(n>1)
     res/=n,res*=n-1;
    return res;
}
//Totirnt function in O(Nlog(logn)) time usin sieve for n<10^6
//We will initialise phi[i]=i and for each prime number muk=ltiple  we will do i*(p-1)/p
int ph[1000000];
void init()
{
    for(ll i=0;i<maxn;i++) ph[i]=i;
    for(ll i=2;i<maxn;i++)
    {
        if(ph[i]==i)
        {
            for(int j=i;j<maxn;j+=i)
            {
              ph[j]/=i;
              ph[j]*=(i-1);
            }
        }
    }
}
//Summation of gcd(i,n) with Nlog(n){for precomputating phi array}+sqrt(n) complexity
ll gcdsum(ll n)
{
    ll res=0;
    for(ll i=1;i*i<=n;i++)
    {
        if(n%i==0)
        {
            ll d1=i;ll d2=n/i;
            res+=i*ph[n/i];
            if(d1!=d2)
              res+=n/i*ph[n/d2];
        }
    }
    return res;
}
//Sieve to generate all primes
vi primes;
int maxa=100001;
void sieve()
{
    vi ar(maxa+1,0);
    ar[0]=1;
    ar[1]=1;
    for(int i=2;i*i<=maxa;i++)
    {
        if(ar[i]==0)
        {
            for(int j=2*i;j<=maxa;j+=i)
              ar[j]=1;  
        }
    }
    fl(i,maxa)
    {if(ar[i]==0) primes.pb(i);}
      
}
//prime numbers genrator to print prime numbers b/w l and r
void primeg(ll l,ll r)
{
    if(l==1) l++;
    ll range=r-l+1;
    vi arrp(range,0);
    //arrp[0]=1;
    //arrp[1]=1;
    for(ll p:primes)
    {
        if(p*p<=r)
        {
            int i=(l/p)*p;
            if(i<l) i+=p;
            for(;i<=r;i+=p)
            {
            if(i!=p)
             arrp[i-l]=1;
            }

        }
    }
    fl(i,range)
    {
        if(arrp[i]==0)
        cout<<l+i<<endl;
    }
}
//Extended Euclidean algorthim a*x+b*y=gcd(a,b);
ll Egcd(ll a,ll b, ll &x,ll &y)
{
    if(b==0)
     {
         x=1;
         y=0;
         return a;
     }
     ll x1,y1;
     ll d=Egcd(b,a%b,x1,y1);
     x=y1;
     y=x1-(y1*(a/b));
     return d;

}
//LDE
bool find_any_solution(int a, int b, int c, int &x, int &y) {
 
	ll x0 , y0;
    int g = Egcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
 
    x = x0 * c / g;
    y = y0 * c / g;
 
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}
int main()
{
 
    //  freopen("input.txt", "r", stdin); 
    //  freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //init();

 // primef();
  //findk();
//   for(ll i=1000000;i<=1000200;i++)
//   { 
//       if(p[i]==0)
//       cout<<i<<endl;
//   }
    //cout<<p[100];
    //cout<<pr[24];
    //cout<<power(9,20);
    //int i=2;
    //int n=97;
    // while(n!=1)
    // {
    //     cout<<arr[n]<<" ";
    //     n=n/arr[n]; 
    // int mp=7;
    // ll ans=97;
    // int ans2=6; 
    // for(int i=1;i<4;i++)
    // {
    //  ans*=ans;ans2*=ans2;
    // }
    //  cout<<(ans+mp)%+mp<<" "<<(ans2+mp)%mp;;
    //cout<<ph[49887]<<endl;
   // cout<<phi(49887);
    //cout<<gcdsum(100000);
    //sieve();
    //ll l,r;
    //cin>>l>>r;
    //primeg(2,100);
    //init(2,100);
    //primeg(2,100);
    // ll x=0,y=0;
     //Egcd(57,81,x,y);
     //cout<<x<<' '<<y;
     primef();
     sieve();
     int t;cin>>t;
     while(t--)
     {
    int p;cin>>p;
    int arr1[p];
    int fact[1000001];
    for(ll i=0;i<1000001;i++) fact[i]=0;
    for(int i=0;i<p;i++) cin>>arr1[i];
    
     int ans1=0;
     for(int i=0;i<p;i++)
     {
      int n=arr1[i];
    
     while(n!=1)
     {
         int k=arr[n];
         int cnt=0;
         while(n%k==0)
         {
             n/=arr[n];
             cnt++;
         }
         //cout<<k<<" "<<cnt<<endl;
         if(cnt%2)
          fact[k]+=1;
          //cout<<k;
     }
         
     
     }
    //  for(int i=0;i<1000001;i++)
    // //   //ans+=min(p,p-fact[i]);
    // //   if(fact[i])
    // //   {
    // //       if(p-fact[i]>fact[i])
    // //        ans=ans+fact[i];
    // //        else
    // //        ans=ans+p-fact[i];
    // {
    //  if(fact[i])
    //     {
    //         if(p-fact[i]>fact[i])
    //         {
    //          //cout<<p<<fact[i];
    //          ans1+=fact[i];
    //         }
    //         else
    //         ans1+=p-fact[i];
    //     }
    // }
    // for(long long d:primes)
    // {
    //     if(fact[d])
    //     {
    //         if(p-fact[d]>fact[d])
    //         {
    //          //cout<<p<<fact[i];
    //          ans1+=fact[d];
    //         }
    //         else
    //         ans1+=p-fact[d];
    //     }
    // }
  cout<<primes[0];
     cout<<ans1<<endl;
    
     }
    return 0;
}
