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
 int table[256]={ Look_Up };
//Counting no of set bits;
//It will run as many times as there are set bits
int countset(int n)
{
    int cnt=0;
    while(n>0)
    {
        cnt++;
        n=n & (n-1);
    }
    return cnt;
}
//To identify whether a number is prime or not
bool ispower(int n)
{
    if(n<=0) return false;
    if((n & (n-1))==0) return true;
    else return false;
}
//Total sum of all pairs XOR
int xorsum(vector<int> v)
{
    int res=0;
    for(int i=0;i<31;i++)
    {
        int cnt0=0;
        int cnt1=0;
        for(int j=0;j<v.size();j++)
        {
            if((v[j] & (1<<i))==0) cnt1++;
            else cnt0++;
        }
        res+=((cnt0*cnt1)*(1<<i));
    }
   return res;
}
//Minimum no.of flips required to make a | b = c;
int minflips(int a,int b,int c)
{
    int ans=0;
    for(int i=0;i<32;i++)
    {
        bool x=false,y=false,z=false;
        if((a & (1<<i))) x=true;
        if((b & (1<<i))) y=true;
        if((c & (1<<i))) z=true;
        if(z==false)
        {
            if(x==true && y==true) ans+=2;
            else if(x==true || y==true) ans+=1;
        }
        else {if(x==false && y==false) ans+=1;}   
    }
    return ans;
}
//Finding the odd one out 
//since it is given all are 3 times so we have taken modulo 3;
int oddone(vector<int> & v)
{
    vector <int> f(32,0);
    for(int e: v)
    {
        for(int i=0;i<32;i++)
         if(e & (1<<i)) f[i]++;
    }
    int ans=0;
    for(int i=0;i<32;i++)
        if(f[i]%3) ans+=(1<<i);
  return ans;
}
// AND product of numbers from L to R range
int andprod(int l,int r)
{
    ll d=r-l;
    int res=0;
    ll f=1;
    for(int i=0;i<32;i++)
    {
        if(d > (f << i)) continue;
        else
        {
            if((l & (f << i)) && (r & (f << i)))
             res+=(f << i);
        }
    }
    return res;
}
//XOR of contiguos sub array
int xorsumsub(vi &v)
{
    int n=v.size();
    int res=0;
    int cnt=0;
    for(int i=1;i<=v.size();i++)
    {
        cnt=i*(n-i+1);
       if(cnt%2)
        res=res^v[i];
    }
    return res;
}
//Generating Subsets
void Subsets(int ar[],int n)
{

     int k1=2;
      int total=(1<<n);
      for(int k=1;k<=total;k++)
      {
        //For subsets of k lengh if total setbits=k then go to inner loop
     //   if(__builtin_popcount(k)==2)
      //  {
        for(int i=0;i<n;i++)
        {
          if(k & (1<<i)) cout<<ar[i]<<" ";
        }
       cout<<endl;
        }
      //}
}
//Checking the parity of a number 
//If we have odd no of 1's in binary number of n thrn it is the odd parity and returns 1
//and if it is even then it is even parity returns 0
bool checkparity(int n)
{
    //Here we will unset each bit of 1 to 0 for every step and reverse parity until n becomes 0
/*Initialize: n = 13 (1101)   parity = 0

n = 13 & 12  = 12 (1100)   parity = 1
n = 12 & 11 = 8  (1000)   parity = 0
n = 8 & 7 = 0  (0000)    parity = 1
*/    
    bool parity=0;

    while(n)
    {
        parity=!parity;
        n=n&(n-1);
    }
    return parity;
}
/*Consider that we want to find the parity of n = 150 = 1001 0110 (in binary).

1. Let’s divide this number into two parts and xor them and assign it to n: n = n ^ (n >> 4) = 1001 ^ 0110 = 1111.

Dissimilar bits result in a 1 bit in the result while similar bits result in a 0. We have basically considered all 8 bits to arrive at this intermediate result. So, effectively we have nullified even parities within the number.

Now repeat step 1 again until you end up with a single bit.
n = n ^ (n >> 2) = 11 ^ 11 = 00
n = n ^ (n >> 1) = 0 ^ 0 = 0
Final result = n & 1 = 0
*/
bool getparity(int n)
{
    int y=n^n>>1;
    y=y^(y>>2);
    y=y^(y>>4);
    y=y^(y>>8);
    y=y^(y>>16);
    if(y & 1)
     return 1;
     else
     return 0;
}
//get nth most MSB
int get2ndMSB(int n,int p)
{
    n|=(n>>1);
    n|=(n>>2);
    n|=(n>>4);
    n|=(n>>16);
    return((n+1)>>p);

}
//Checking parity using xor table .
//We will divide the total binary number into 8 chuunks and we wll xor them until we
//left with only 8 bits and we will precompute all parities of numbers from 0 to 255 
//from the already made look up table
int xorparity(int x)
{
 x=x^(x>>16);
 x=x^(x>>8);
 return table[x & 0xff];
}
//Parity of xor of two odd number gives even number parity
//Patity of xor of two even numbers give even number parity
//Parity of xor of one odd and one even parity numbers gives xor of odd parity
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cout<<minflips(253672,480319,829931);
     vector <int> v={1,2,3};
      //cout<<oddone(v);
      int l=1;int r=3;
      //cout<<andprod(9,10);
      //cout<<xorsumsub(v);
    //   int n;cin>>n;
    //   int arr[n];
    //   for(int i=0;i<n;i++) cin>>arr[i];
    //   Subsets(arr,n);
      // cout<<checkparity(11);
      /// int n=150;
      // cout<<(n^(n>>4));
     // cout<<getparity(150);
    
     //cout<<xorparity(1098283038);
    cout<<get2ndMSB(17281685,7);
    return 0;

}