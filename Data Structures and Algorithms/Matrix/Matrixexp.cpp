/*
There are 2 ways to do.
1. Naive approach , Complexity O(M^3 * N)
2. Binary exponentiation , Complexity O(M^3 * logN)
where M = dimension of the square matrix.*/
#include<bits/stdC++.h>
using namespace std;
#define  ll long long int
#define fl(i,n) for(ll i=0;i<n;i++)
#define  N 101
#define a 1
#define b 2
const ll m=1e9+7;
ll arr[N][N], I[N][N];
ll f[a][N];

void mul(ll A[][N],ll B[][N],ll dim)
{
  ll res[dim+1][dim+1];
  fl(i,dim)
  { 
    fl(j,dim)
     {
      res[i][j]=0;
      fl(k,dim) res[i][j]+=((A[i][k]%m)*(B[k][j])%m)%m;
     }
  }
  fl(i,dim) fl(j,dim) A[i][j]=res[i][j];
}
void power(ll A[][N],int dim,int n)
{
    fl(i,dim) fl(j,dim)
    {
         if(i==j) I[i][j]=1;
        else I[i][j]=0;
    }
    //fl(i,n) mul(I,A,dim);
    //Using binary exponentiation Algorithm
    while(n)
    {
        if(n%2) {mul(I,A,dim);n--;}
         else
         {
          mul(A,A,dim);
          n/=2;
         }
    }

    fl(i,dim) fl(j,dim) A[i][j]=I[i][j];
}
void print(ll A[][N],ll dim)
{
    fl(i,dim)
    {
       fl(j,dim) cout<<arr[i][j]<<' ';
        cout<<endl; 
    }
}
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
    //    int dim,n;
    //    cin>>dim>>n;
    //    fl(i,dim) fl(j,dim) cin>>arr[i][j];
    //     power(arr,dim,n);
    //     print(arr,dim);
    //     cout<<endl;
    // 
    f[0][1]=1;
   f[0][1]=1;
    ll n;cin>>n;
      fl(i,2) fl(j,2)
      {
          if(i==0 && j==0)
           arr[i][j]=0;
           else
           arr[i][j]=1;
      }
      power(arr,2,n-1);
      
      mul(f,arr,2);
      cout<<f[0][1]<<endl;
    }
    int k1,k2;
    k1=1;k2=1;
    ll ans;
    //O(n approach)
    // for(ll i=3;i<=1000000000000;i++)
    // {
    //  ans=(k1+k2)%m ;
    //  k2=k1%m;
    //  k1=ans%m;
    // }
   // cout<<ans<<endl;
    return 0;
}