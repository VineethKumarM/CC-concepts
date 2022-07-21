#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
#define ull unsigned long long int
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 500
//Finding nth fibonacci using recursive approach O(log n) time
vil fib(Maxx,0);
ll fibn(ll n)
{
    if(n==0) return 0;
    if(n==1 || n==2) return (fib[n]=1);
    if(fib[n]) return fib[n];
    ll k=(n&1)? (n+1)/2 : n/2;
    fib[n]=(n&1)? (fibn(k)*fibn(k)+fibn(k-1)*fibn(k-1)) : (2*fibn(k-1)+fibn(k))*fibn(k);   
    return fib[n];
}
bool Is_Perfectsquare(ll x)
{
    ll s=sqrt(x);
    return(s*s==x);
}
bool Is_Fibonacci(ll n)
{
    return (Is_Perfectsquare((5*n*n+4)) || Is_Perfectsquare((5*n*n-4)));
}
ll nearestFib(ll n)
{
  if(n==0 || n==1) return n;
  ll f0=0,f1=1,f3=1;
  while(f3<=n)
  {
      f0=f1;
      f1=f3;
      f3=f1+f0;
  }
  return f1;
}
//Representation of Fibonacci without using non neighbours in fibonacci
void PrintfibRep(ll n)
{
    while(n>0)
    {   
     ll f=nearestFib(n);
     cout<<f<<' ';
     n-=f;
    }
}
vil Fib(N);
int FiblessorEqual_n(ll n)
{
    Fib[0]=0;
    Fib[1]=1;
    int i;
     for(i=2; Fib[i-1]<=n;i++)
      Fib[i]=Fib[i-1]+Fib[i-2];
      return i-2;
}
//Binary Fibrepresentation of  a number n
char* Bin_FibRep(ll n)
{
    int ind=FiblessorEqual_n(n);
    char *code = (char*)malloc(sizeof(char)*(ind+3)); 
    int i=ind;
    while(n)
    {
        code[i]='1';
        n=n-Fib[i];
        i=i-1;
        while(i>=0 and Fib[i]>n)
        {
         code[i]='0';
         i=i-1;
        }
    }
    code[ind+1]='1';
    code[ind+2]=' ';
    
    return code;
}
//find position of n th multiple of a number in Fibonacci Sequence
int findpos(ll n,ll k)
{
  ull f0=0,f1=1,f2=1;
  for(int i=2;i<=Maxx;i++)
  {
      f2=f0+f1;
      f0=f1;
      f1=f2;
      if(f2%k==0)
      {
          return n*i;
      }
  }
   return -1;
}
//Finding gcd of nth and kth fibonocci numbers
//__gcd(fib(n),fib(k))=fib(__gcd(n,k));
ll fibgcd(ll n,ll k)
{
    return fibn(__gcd(n,k));
}
//Function to compute m terms of n-binocci numbers
void Nbinocci(ll n,ll m)
{

     vi nbin(m,0);
     nbin[n-1]=1;
     nbin[n]=1;
     for(int i=n+1;i<=m;i++)
       nbin[i]=2*(nbin[i-1])-nbin[i-n-1];
     for(int i=0;i<m;i++) cout<<nbin[i]<<' ';

}
//Caluclating factorial of all fibonocii numbers
//Since we already caluclated for the last terms
int mult(int x,int prevfact[],int &size)
{
    int carry=0;
    for(int i=0;i<size;i++)
    {
        int prod=x*prevfact[i]+carry;
        prevfact[i]=prod%10;
        carry=prod/10;
    }
    while(carry)
    {
        prevfact[size]=carry%10;
        carry/=10;
        size++;
    }
    return size;
}
//Caluclation of factorial from the last term
void factorial(int prevfact[],int &size,int prev,int n)
{
    for(int i=prev+1;i<=n;i++)
      size=mult(i,prevfact,size);
    for(int i=size-1;i>=0;i--)
    cout<<prevfact[i];
    cout<<'\n';
}
void printfibfact(int limit)
{
    if(limit<1) return;
    int a=1,b=1,c=a+b;
     cout<<1<<'\n'<<1<<'\n';
    int prevfact[Maxx];
    prevfact[0]=1;
    int size=1;
    while(c<limit)
    {
       factorial(prevfact,size,b,c);
       a=b;
       b=c;
       c=a+b;
    }

}
//Printing Fibonomial Triangle
int Fibp[N];
void prefib()
{
    Fibp[0]=0;Fib[1]=1;
    for(int i=2;i<N;i++)
      Fibp[i]=Fibp[i-1]+Fib[i-2];
}
void Fibnomial(int Fibn[][N],int Fibp[],int n)
{
    for(int i=0;i<=n;i++)
     Fibn[i][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            int k=j;
            while(k--)
            Fibn[i][j]*=Fibp[k];
            k=1;
            while((j+1)!=k)
            Fibn[i][j]/=Fibp[k++];
            cout<<Fibn[i][j]<<' ';
        }
        cout<<'\n';
    }

}
ll findindex(ll n)
{
    float fibo=2.078087*log(n)+1.672276;
    //For rounding the integer
    return round(fibo);
}
//Tail Recursive call to find nth fibonacci
//After iterating over n-1 steps we wil return b
//Time Compexity O(n) and Space Complexity O(n)
ll TailFib(ll n,ll a=0,ll b=1)
{
    if(n==0) return a;
    if(n==1) return  b;
    return TailFib(n-1,b,a+b);
}
//Finding Even Fibonocii Number Sum
ll Evenfibsum(ll limit)
{
    if(limit<2) return 0;
    ll ef1=0,ef2=2,sum=ef2+ef1;
    while(ef2<limit)
    {
      ll ef3=4*ef2+ef1;
      if(ef3>limit)
       break;
       ef1=ef2;
       ef2=ef3;
       sum+=ef3;
    }
    return sum;
}
//Complexity of the code given below is exponential
//We can reduce the time complexity to log(n) using dp or using the fact that En=F3n
//We can find nth fibonocci in log(n) time and thus Even fibonocii
ll Evenfib(ll n)
{
    if(n==0) return 0;
    if(n==1) return 2;
    return (4*Evenfib(n-1)+Evenfib(n-2));
}
//Finding no.of fibonocci numbers in the digits of nth fibonocii numbers
//using Binets formula
ll Fibdigits(ll n)
{
   if(n==1) return 1;
   ld d=(n*log10(phi)-(log10(5)/2));
   return ceil(d);
}
//Finding nth non-Fibonacci Number
ll Non_Fibonocci(ll n)
{
    ll prevprev=1,prev=2,curr=3;
    while(n>0)
    {
        prevprev=prev;
        prev=curr;
        curr=prev+prevprev;
        n-=curr-prev-1;//subtracting cnt of non-fiibonocci numbers from n

    }
    n+=curr-prev-1;//since n might have become negative we are adding the previous subtracted ones
    return n+prev;//here we are adding remaining n to prev number
}
//Counting possible sequences
ll Wayspos(string digit,ll n)
{
    int cnt[n+1];
    cnt[0]=1,cnt[1]=1;//To store values of subproblems

    for(int i=2;i<=n;i++)
    {
        cnt[i]=0;
        if(digit[i-1]>'0')
         cnt[i]=cnt[i-1];
         if(digit[i-2]=='1' || (digit[i-2]=='2' && digit[i-1]<'7'))
          cnt[i]+=cnt[i-2];
    }
    return cnt[n];
}
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //ll n=13;
    //cout<<fibgcd(15,30);
    //Nbinocci(3,8);
   // printfibfact(20);
   //prefib();
   int arr[N][N];
   //Fibnomial(arr,Fibp,4);
   //cout<<findindex(55);
   //cout<<TailFib(10,0,1);
     //cout<<Fibdigits(10);
      string s="1224";
      int n=s.size();
     cout<<Wayspos(s,n);
    return 0; 
}