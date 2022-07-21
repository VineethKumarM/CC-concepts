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
#define MAX 100001
int table[256]={ Look_Up };
ll gcd(ll a,ll b)
{
    if(!a) return b;
    else
    return gcd(b%a,a);
}
/*Inorder to deal with large numbers of gcd with small numbers and a large number we will reduce the string 
large number to 0<num<=a such that it lies below small number  and we will take gcd then*/
ll reduce(ll a,string s)
{
    ll mod=0;
    for(int i=0;i<s.size();i++)
     mod=(mod*10+s[i]-'0')%a;
     return mod;
}
ll gcdlarge(ll a,string s)
{
    ll num=reduce(a,s);
     return gcd(a,num);
}
//Steins Algorithm or Binary gcd algorithm for finding gcd of two numbers a and b
//This Steins algorithm runs in O(n*n) where n represent no.of bits which is faster than normal
//gcd which takes O(log n) time
ll Binarygcd(ll a,ll b)
{
    if(a==0) return b;//if a==0 return b
    if(b==0) return a;
    int k;
    for(k=0;((a | b) && 1==0);++k)//Here we are taking out all the powers of 2 common to
                                    //both divisors
    {
      a>>=1;
      b>>=1;
    }
    //After implementing the above loop one of them should be the odd and other one is even
    //so we can take out all the 2 s in a or b 2's multiple cant be the gcd at this stage
     while((a & 1)==0)
     a>>=1;
     do
     {
       while((b & 1)==0)
       b>>=1;
       if(a>b) swap(a,b);
       b=b-a;//Here we are swapping them to make b non negative 
     }while(b!=0);

   return a<<k;
}
//Recursive approach of Binary gcd algorithm
ll gcd_binrec(ll a, ll b)
{
    if(a==0) return b;
    if(b==0) return a;
    if(~a & 1)//if  a is even
    {
        if(b & 1)//if b is odd
         return gcd_binrec((a>>1),b);//takeout all 2 multiples and return
         else
         return gcd_binrec(a>>1,b>>1)<<1;//here since both numbers contains 2^k so we are 
         //taking out all 2 s and leftshifting them to the final ans
    }
    if(~b & 1)//if b is even a is odd
     return gcd_binrec(b>>1,a);
     if(a>b)//if a is larger than b
     return gcd((a-b)>>1,b);//here we are right shiftinh brcause a-b is even and b is odd
     return gcd((b-a)>>1,a);
}
//Gcd of 2 numbers formed by repreating n for x and y times
//GCD(f(n,x) . f(n,y))=f(n,gcd(x,y));
//Minimum no.of moves function to make array 1
int minmoves(int arr[],int n)
{
    int flag=0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]==1)
        {
            flag=1;break;
        }
    }
     if(flag) return n-1;
    int minimum=INT_MAX;
    for(int i=0;i<n;i++)
    {
        int g=arr[i];
        for(int j=i+1;j<n;j++)
        {
            g=__gcd(g,arr[j]);
            if(g==1)
            {
                minimum=min(minimum,j-i);
                break;
            }
        
            
        }
    }
    if(minimum==INT_MAX) return -1;
    else return n+minimum-1;  
}
//Caluclation of gcd of floating numbers 
double gcdfloat(double a,double b)
{
    if(a<b)
    return gcdfloat(b,a);
    if(fabs(b)<0.001) return a;//here we are putting base case upto decimal points
    else
    return gcdfloat(b,a-floor(a/b)*b);

}
//Eulers Totient Function
// int phi(int n)
// {
//   int res=n;
//   for(int i=2;i*i<=n;i++)
//   {
//       if(n%i==0)
//       {
//           while(n%i==0)
//           n/=i;
//           res-=res/i;
//       }
//   }
//   if(n>1)
//   res-=res/n;
//   return res;
// }
//Incase we have to find all the totients from 1 to n use the approach like sieve of erathrosene
//maintain a vector and update the muktiples for each divisible prime
//Complexity of this code is O(log log n)
vi phi1_n(MAX,0);
vector<int> phi_1to_n(int n)
{
    
    phi1_n[0]=0;phi1_n[1]=1;
    for(int i=2;i<n;i++) phi1_n[i]=i;
    for(int i=2;i<n;i++)
    {
        if(phi1_n[i]==i)
        {
            for(int j=i;j<n;j+=i)
             phi1_n[j]-=phi1_n[j]/i;
        }
    }
    return phi1_n;
}
 vi phid(MAX,0);
//Finding totient using divisor sum property
//It has time complexity of about O(log n) which is litte worse than above implemnation
vector<int> phidiv(int n)
{
   
    phid[1]=1;
    for(int i=2;i<n;i++) phid[i]=i-1;
    for(int i=2;i<n;i++)
     for(int j=2*i;j<n;j+=i)
     phid[j]-=phid[i];//here we are subbtracting each divisor phi
     return phid;
      
}
vi sogp(MAX,0);
void sumofggcdpairs()
{
   
   //Iterating over all multiples of i==1
    for(int i=1;i<MAX;i++)
    {
        for(int j=2;i*j<MAX;j++)
         sogp[i*j]+=i*phid[j];
    }
    for(int i=2;i<MAX;i++) sogp[i]+=sogp[i-1];//caluclating the sum of all paris 
    //from 2 to n for sogp[n]
}
//Finding length of largest subsequence of which gcd>1
int largestgcdsubsequence(int arr[],int n)
{
    int ans=0;
    int maxe=*max_element(arr,arr+n);
    for(int i=2;i<=maxe;i++)
    {
        int count=0;
        for(int j=0;j<n;j++)
        {
            if(arr[j]%i==0)
            count++;
        }
        ans=max(ans,count);
    }
    return ans;
}
//Caluclating minimum dif upon adding a+k1*c and c+k2*d
ll middif(ll a,ll b,ll c,ll d)
{
  ll g=__gcd(a,b);
  ll p=abs(a-b);
  ll ans=min(p%g,g-(p%g));
  return ans;
}
/*
  If one number is 1, then it has no prime divisors, so answer is True. 
  Otherwise we have to find the GCD of these two numbers. If GCD is 1, 
  then they are co-prime. So answer is false. If GCD is > 1, then GCD 
  contains prime divisor, which divide x also (x as first number). If we have all unique prime divisor iff second number y / GCD has such unique prime divisor. We have to find uniqueness for pair (x, y/GCD) using recursion.
*/
  
//finding whether a number is divisible by all prime divisors of another problem
bool isdivisible(ll a,ll b)
{
    if(b==1) return true;
    ll gcd=__gcd(a,b);
    if(gcd==1) return false;
    //here we are dividing b with gcd so as to check remaing priem divisors are
    //divides   a or not
    return isdivisible(a,b/gcd); 
}
  
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //string s;cin>>s;
    //int a;cin>>a;
    //cout<<gcdlarge(a,s);
    //cout<<gcd_binrec(34,17);
    int A[5]={8,10,12,6,3};
  // cout<<minmoves(A,5);
  //double a=0.3979,b=0.9;
  //cout<<gcdfloat(a,b);
  //phidiv(MAX);sumofggcdpairs();
  cout<<isdivisible(120,75);
  return 0;
}