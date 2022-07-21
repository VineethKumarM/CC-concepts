#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++); 
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
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
       int n,q;cin>>n>>q;
       vi v(n),prefix(n),suffix(n);
       for(int i=0;i<n;i++) cin>>v[i];
       prefix[0]=v[0];
       for(int i=1;i<n;i++) 
       {
         prefix[i]=__gcd(prefix[i-1],v[i]);
       }
      
       suffix[n-1]=v[n-1];
       for(int i=n-2;i>=0;i--)
       suffix[i]=__gcd(suffix[i+1],v[i]);
       while(q--)
       {
         int l,r;cin>>l>>r;
         if(l==1) cout<<suffix[r]<<'\n';
         else if(r==n) cout<<prefix[l-2]<<'\n';
         else
         cout<<__gcd(prefix[l-2],suffix[r])<<'\n';

       }
     
    }
      
     return 0;
}