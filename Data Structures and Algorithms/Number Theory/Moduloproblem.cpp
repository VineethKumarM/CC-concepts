#include<bits/stdC++.h>
using namespace std;
#define  ll long long int
#define fl(i,n) for(ll i=0;i<n;i++)
const ll  mod=1e9+7;
const int MAX=5e5+5;
const ll m=10000001;
ll F[1000001];
vector <vector<int>> divisors(MAX);
void prec()
{
for(int i=1;i<=MAX;i++)
{
     for(int j=i;j<=MAX;j+=i)
       divisors[j].push_back(i);
}
}
ll powerm(ll a,ll n,ll d)
{
  ll res=1;
  while(n)
  {
       if(n%2)
        {
             res=((res%d)*(a%d))%d;
             n--;
        }
        else
        {
             a=(a%d*a%d)%d;
             n/=2;
        }
  }
  return res;
}
/* This function is used to calucalte of gcd of two numbers which has larger difference using
 potential candidates and modulo arthimetic
*/
// ll gcd(ll a,ll b,ll n)
// {
//      if(a==b)
//       return powerm(a,n,mod)+powerm(b,n,mod);
//       ll num=a-b;
//       ll cand=1;
//       for(ll i=1;i*i<=num;i++)
//       {
//            if(num%i==0)
//            {
//             ll temp=(power(a,n,mod)+power(b,n,mod))%i;
//             if(temp==0) cand=max(cand,i);
//              temp=(power(a,n,mod)+power(b,n,mod))%(num/i);
//              if(temp==0)
//              cand=max(cand,n/i);
//            })%mod
//       }
//       ll k=cand % mod;
//      return k;
// }
ll power(ll a,ll n)
{
    ll res=1;
    while(n)
    {
        if(n%2)
        {
         res=(res*1ll*a)%mod;
         n--;
        }
         else
           {
              a=(a*1ll*a)%mod;
              n/=2;
           }
    }
    return res;
}
/* Calucalating  Binary coefficients using Modulo Inverse*/
ll BC(ll n, ll k)
{
     ll res=1;
     if(k>n)
      return 0;
      else
      {
           res=F[n];
         res=(res*1ll*power(F[k],m-2))%m;
          res=(res*1ll*power(F[n-k],m-2))%m;
          return res;  
      }

}
int main()
{
 
  F[0]=F[1]=1;
  for(int i=2;i<1000001;i++)
   F[i]=(i*F[i-1])%m;
     //freopen("input.txt", "r", stdin); 
   // freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    prec();
   int t;
   cin>>t;
   while(t--)
   {
     //    int n,m;
     //    cin>>n>>m;
     //    long long int res=0;
     //    for(int i=2;i<=n;i++)
     //    {
     //         int k=m-m%i;
     //         if(k>0)
     //         res+=lower_bound(divisors[k].begin(),divisors[k].end(),i)-divisors[k].begin();
     //         else
     //         res+=i-1;
     //    ll a,b,n;
     //    cin>>a>>b>>n;
     //    cout<<gcd(a,b,n);
     ll n,k;
 cin>>n>>k;
 cout<<BC(n,k);
        
        cout<<endl;

   }
  
   
     return 0;

}