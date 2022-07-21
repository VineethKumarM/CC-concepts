#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vb vector<bool>
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
const int MAX=100;
const ull mod1=1e9+7;
int Binomial_Coefficient(int n,int k)
{
    int C[n+1][k+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=min(i,k);j++)
        {
          if(j==0 || j==i)
           C[i][j]=1;
           else
           C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    return C[n][k];
}
//Optimised Space Complexity with Order of O(k)
int Bin_Coefficient(int n,int k)
{
    int C[k+1];//Here only upto C[k+1] is necesaary simce we want the term upto there.
    memset(C,0,sizeof(C));
    C[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=min(i,k);j>0;j--)//Using the Pascaks triangle we will update eacg time from
        //the end of the array
         C[j]=C[j-1]+C[j];
    }
    return C[k];
}
//Space optimise and time optimised algo to claluclate nCr
ll Binom_Coeff(ll  n,ll r)
{
    ll res=1;
    if(r>n-r) r=n-r;
    for(int i=0;i<r;i++)
    {
        res*=(n-i);res/=(i+1);
    }
    return res;
}
//nCR mod p
ll nCrmodp(ll n,ll k,ll p)
{
    ll C[k+1];
    memset(C,0,sizeof(C));
    C[0]=1;
    for(ll i=1;i<=n;i++)
    {
        for(int j=min(i,k);j>0;j--)
        C[j]=(C[j-1]%p+C[j]%p)%p;
    }
    return C[k];
}
//nCr mod p can be calclated using the locus theorem by computing niCri where ni and ri is the
//respective digits in p-base representation
//Complexity of the below code is O(p^2*logpn) time
//We can reduce the time complexity to byprecomputating the pascals of trainagle p*p matrix 
//store it in 2d array
//Now we can get the values in O(1) time
//here ni and ri will alwats be less than p
//Precomputation of niCri upto order p*p matrix
int dp[1000][1000];
void precomp_Bin_Coeff(int p)
{
   for(int i=0;i<=p;i++)
   {
       for(int j=0;j<=p;j++)
       {
           if(j==0 || j==i)
            dp[i][j]=1;
            else
            dp[i][j]=(dp[i-1][j-1]+dp[i-1][j])%p;
       }
   }
}
ll nCrLucas(ll n,ll r,ll p)
{
    if(r==0) return 1;//Base case
    ll ni=n%p,ri=r%p;//Digit by digit approach thorough recursive call
    return(nCrLucas(n/p,r/p,p)*dp[ni][ri])%p;
    //return(nCrLucas(n/p,r/p,p)*nCrmodp(ni,ri,p)%p);
    //taking the last digit and cimputing 
    //remaining the result with multiolication of ncrmodp(ni,ri,p);
}
//nCr mod p using Fermats Little Theorem when p is prime and p>n
//Uner these two conditions we can find the nCr mod p using Fermat Little Theorem 
//By finding the modinverse of the number under division
ll Power_Modulo(ll a,ll n,ll p)
{
    a%=p;
    ll res=1;
    while(n)
    {
        if(n&1) res=(res*a)%p;
        a=(a*a)%p;
        n/=2;
    }
    return res;
}
ll Prime_Mod_Inverse(ll a,ll p)
{
    return Power_Modulo(a,p-2,p);
}
//Here two condition shiuld be taken care of 1.p should be prime and p>n
ll nCr_FermatMod_p(ll n,ll r,ll p)
{
    if(r==0) return 1;
    ll fact[n+1];
    fact[0]=1;
    for(int i=1;i<=n;i++) fact[i]=(i*fact[i-1])%p;
    return (fact[n]*(Prime_Mod_Inverse(fact[r],p)%p)*(Prime_Mod_Inverse(fact[n-r],p)%p)%p);
}
//Probability of 3 chosen numbers to be in AP from 1 to 2n+1 numbers
//Total possible triplets 2n+1C3
//Total possible triplets with AP=n*n;
//P(AP)=n*n/(2n+1C3)=3n/4(n*n)-1
float Prob_AP(ll n)
{
    float m=(float)n;
    return (3.0)*m/((4.0)*m*m-1);
}
// Partial dearrangements
// Partial dearrangements are the permutations of the n psition with k fixed positions
// If we are dearranging we should take care that k of n positions should be there at their 
// positions
// if k =0 none of them should be at their original positiin
// If k=1 fix onr of n positions dearrange the remaining terms
// They follow up a sequence called Recontres numbers
// D(n,k)=nCk*D(n-k,0); for any k>=0 where D(n,k) impiles dearrangements of n pos with k fixed positions
void Pre_Bin_Coeff(int C[][MAX],int n,int k)
{
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=min(i,k);j++)
        {
            if(j==0 || j==i)
             C[i][j]=1;
             else
             C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
}
int Recontre_Num(int C[][MAX],int n,int m)
{
    int dp[n+1][m+1]={0};
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if(j<=i)
            {
              if(i==0 and j==0)//Base Case
              dp[i][j]=1;
              else if(i==1 and j==0)//Base Case
               dp[i][j]=0;
               else if(j==0)
               dp[i][j]=(i-1)*(dp[i-1][0]+dp[i-2][0]);
               else
               dp[i][j]=C[i][j]*dp[i-j][0];
            }
        }
    }
   return dp[n][m];
}
//Printing Binomial Coeffiecients Table
void Print_binomial(int max)
{
    for(int m=0;m<=max;m++)
    {
       cout<<m<<' ';
        int binom=1;
        for(int x=0;x<=m;x++)
        {
           
           if(x!=0 and m!=0)
           binom=binom*(m-x+1)/x;
           cout<<binom<<" ";
        }
        cout<<'\n'; 
    }
}
//Horners Method for evaluating the poynomial Evaluation
//Here p array contains all the coefficients of x^n  starting from ax^n+a1x^n-1+......
int Poly_Horner(int p[],int n,int x)
{
    int res=p[0];
    for(int i=1;i<=n;i++)
    {
        res=(res*x)+p[i];
    }
    return res;
}
//Print Comboinationf of r elemnts from an array of size of n elements
//Method 1
int Combo_Recur(int arr[],int data[],int start,int end,int index,int r)
{
    if(index==r)
    {
        for(int j=0;j<r;j++) cout<<data[j]<<' ';
        cout<<'\n';
    }
    //end-i>=r-index By this condition we are ensuring the elements to be added are greater than
    //or equal to required elements
    //Once we reaced at end and no elemnts can be added this loop will break
    for(int i=start;i<end && end-i>=r-index;i++)
    {
        data[index]=arr[i];
        while(arr[i]==arr[i+1]) i++;
        Combo_Recur(arr,data,i+1,end,index+1,r);
    }
    return 0;
}
//Method 2
//By including and excluding that element
void Include_Exclude(int arr[],int n, int r,int data[],int index,int i)
{
    if(index==r)
    {
        for(int i=0;i<r;i++) cout<<data[i]<<' ';
        cout<<'\n';
    }
    if(i>=n) return ;
    data[index]=arr[i];
      while(arr[i]==arr[i+1]) i++;
    Include_Exclude(arr,n,r,data,index+1,i+1);//here we are adding the eleemnt and thus incrementing the
  
    //index
    Include_Exclude(arr,n,r,data,index,i+1);//Here we are not including that element and thus no increment
    //of index  
}
void Print_Combo_Recur(int arr[],int n,int r)
{
    int data[r];
    //if we have to handle the elemts and sort the array and call the function and in between
    ///two call add while(arr[i]==arr[i+1]) i++'
    sort(arr,arr+n);
   Combo_Recur(arr,data,0,n,0,r);
   //Include_Exclude(arr,n,r,data,0,0);
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //precomp_Bin_Coeff(13);
    int n=7,m=2;
   // int C[MAX][MAX];
    //Pre_Bin_Coeff(C,n,m);
    //cout<<Recontre_Num(C,n,m);
    //Print_binomial(10);
   // cout<<Prob_AP(10);
   //cout<<Binom_Coeff(10,2);
   int arr[5]={10,11,12,13,14};
   Print_Combo_Recur(arr,5,3);

    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}
