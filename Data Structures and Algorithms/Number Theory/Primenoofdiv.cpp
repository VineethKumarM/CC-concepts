#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++); 
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
vil sqprimes;
ll getprimecount(ll l,ll r)
{
  ll cnt=0;
  ll rsqrt=sqrt(r);
  vector<bool> isprime(rsqrt+1,true);
  isprime[0]=isprime[1]=false;
  for(ll i=2;i<=rsqrt;i++)
  {
    if(isprime[i])
    {
      sqprimes.pb(i);
      for(int j=i*i;j<=rsqrt;j+=i)
       isprime[j]=false;
    }
  }
  vector<bool> rangeprm(r-l+1,false);
  for(ll p:sqprimes)
  {
    for(ll j=max(p*p,((l+p-1)/p)*p);j<=r;j+=p)
     rangeprm[j-l]=true;
  }
  if(l==0) rangeprm[0]=true;
  if(l==1) rangeprm[0]=true;
  for(ll i=0;i<=r-l;i++) if(!rangeprm[i]) cnt+=1;
   return cnt;
}
ll getpowercnt(ll l,ll r)
{
  ll count=0;
  for(ll p:sqprimes)
  {
    int cntl=0,cntr=0;
    int L=l,R=r;
    if(p<=sqrt(r))
    {
      if(L/p>0)
      {
       while(L>0)
       {
        cntl+=1;
        L/=p;
       }
      }
      if(R/p>0)
     {
        while(R/p>0)
        {
         cntr+=1;
         R/=p;
        }
     }
     
     if(cntl>=0 and cntr>1)
      count+=getprimecount(cntl+1,cntr+1);
      if(cntl<=1) count-=1;
    }
    else
    break;
  }
  return count;
}
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
      int l,r;cin>>l>>r;
     ll s1=getprimecount(l,r);
     ll s2=getpowercnt(l,r);
     cout<<s1+s2<<'\n';
     sqprimes.clear();
    }
    return 0;
}
