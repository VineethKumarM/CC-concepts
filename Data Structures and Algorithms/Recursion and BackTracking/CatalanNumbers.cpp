#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
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
#define Maxx 10000
const ull mod1=1e9+7;
//Caluclatimg Catalan number for n
ull Catalan(ull n)
{
    if(n<=1) return 1;
    ull res=0;
    for(int i=0;i<n;i++)
     res+=Catalan(i)*Catalan(n-i-1);
   return res;
}
//Using dp technique to store the elemnents of an Catalan Table
ull CatalanDp(ull n)
{
    vil Catalan(n+1);
    Catalan[0]=1;Catalan[1]=1;
    for(int i=2;i<=n;i++)
    {
        Catalan[i]=0;
        for(int j=0;j<i;j++)
          Catalan[i]+=Catalan[j]*Catalan[i-j-1];
    }
    return Catalan[n];
}
//Finding Catalan Numbers UsingBinomial Coeffiecients
//Catn=(1/n+1)2nCn(Here C in binomial coeffiecient Form)
ull Bino_Catalan(ull n)
{
    ull k=n;
    n*=2;
    if(k>n-k) k=n-k;
    if(n==0) return 1;
    ull res=1;
    for(ull i=0;i<k;i++)
    {
        res*=(n-i);
        res/=(i+1);
    }
    return res/(k+1);
}

int main()  
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout<<Bino_Catalan(9);
    return 0;
}