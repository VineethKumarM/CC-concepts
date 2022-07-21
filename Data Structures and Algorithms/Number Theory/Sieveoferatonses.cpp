#include<bits/stdC++.h>
using namespace std;
const long long MAX_SIZE = 1000001;
const long long MAX = 1000000;
int spf[1000001];
  
vector<long long >isprime(MAX_SIZE, true);
vector<long long>prime;
vector <long long> SPF(MAX_SIZE);
bool p[9000001];//since it is declared globally all the values will be intialised with 0;
vector <int> pr;

//summof factors 
long long int sumoffactors( long long int n)
{
    long long int res=1;
    for(long int i=2;i<=sqrt(n);i++)
    {
       long long int csum=1;
          long long int cterm=1;
        while(n%i==0)
        {
            n=n/i;
            cterm*=i;
            csum+=cterm;
        }
        res*=csum;
    }
    if(n>=2)
     res*=n+1;
     return res;
}
//sum of factors in  O(log n)
void sumoffactorsp(long long int n)
{
   long long int cur=SPF[n];
   int cnt=1;
   long long int res=0,resf=1;

   int temp=1;
   while(n>1)
   {
       
        
       temp*=cur;
       res+=temp;
       n=n/SPF[n];
       if(cur==SPF[n])
       {
           
           cnt+=1;
           continue;
       }
      
      cout<<cur<<" "<<cnt<<endl;
      resf=resf*(1+res);
       cur=SPF[n];
       temp=1;
       cnt=1;
       res=0;
   }
        cout<<resf;
}
//Sievev of erathrsoens with n complexity
void nsieveofer(int n)
{
    isprime[0]=false;
    isprime[1]=false;
    for(long long int i=2;i<n;i++)
    {
        if(isprime[i])
        {
            prime.push_back(i);
            SPF[i]=i;
        }
        for(long long int j=0;j<sizeof(prime) && i*prime[j]<n && prime[j]<=SPF[i];j++)
        {
            isprime[i*prime[j]]=false;
            SPF[i*prime[j]]=prime[j];
        }
    }
    //for(int i=0;i<SPF.size();i++)
    // cout<<SPF[i]<<" "<<endl;
   
}
//Sieve of Erathrosenes Algorithm 

void sieveofer(int n)
{
    bool primep[n+1];
    memset(primep,true,n+1);
    for(int p=2;p*p<=n;p++)
    {
        if(primep[p])
        {
            for(int j=p*p;j<=n;j+=p)
             primep[j]=false;
        }
    }
    for(int i=0;i<100;i++)
      {
          if(primep[i])
            cout<<i<<" "<<endl;
      }
    /*int cnt=0;
    for(int i=2;i<n;i++)
    {
        if(prime[i])
        cnt+=1;
    }
    cout<<cnt;*/
}
//precomputation of smallest prime factor
void sieve()
{
  
    spf[1]=1;
    for(int i=2;i<MAX;i++)
       spf[i]=i;
       for(int i=4;i<MAX;i+=2)
         spf[i]=2;
         for(int i=3;i*i<=MAX;i++)
         {
             if(spf[i]==i)
             {
                 /*j is starting from i*i coz muliples of j less than i are already 
                 marked by numbers less than i*/
                 for(int j=i*i;j<MAX;j+=i)
                 {
                     //checks whether it is already marked or not
                     if(spf[j]==j)
                      spf[j]=i;
                 }


             }
         }
}
//Functuons returning a vector of prime factors
vector<int> getprimef(int n)
{
    vector <int> rev;
    while(n!=1)
    {
        int k=spf[n];
        rev.push_back(k);
        n=n/spf[n];
    }
    return rev;
}
//gcd with O(log max(a,b))
int gcd(int a,int b)
{
    if(b==0)
    return a;
    else
     return gcd(b,a%b);
}
/*To find lcm
  a*b=LCM(a,b)*gcd(a,b);*/
//Caluclating no coprime numbers to n from 1 to n using Euler totient Algorithm
int phi (int n)
{
   
  float result=n;
    for(int p=2; p*p<=n;p++)
    {
        if(n%p==0)
        {
            while(n%p==0)
             n/=p;
            result *= (1.0 - (1.0 / (float)p));

        }
        
        
    }
    if(n>1)
    // result*=(1.0-(1.0/(float)n));
     result *= (1.0 - (1.0 / (float)n));
     return  (int) result;
}
//finding kth prime
void findk()
{
    int max=9000001;
    p[0]=p[1]=true;
    for(int i=2;i<max;i++)
    {
        if(!p[i])
        {
            for(int j=i*i;j<max;j+=i)
             p[j]=true;
             pr.push_back(i);
        }
    }

}

int main()
{
 
       freopen("input.txt", "r", stdin); 
     freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    SPF[0]=0;
    SPF[1]=1;
   /*char s[]="Good Programmer";
   memset(s,'-',6);
       puts(s);
  */
   //nsieveofer(100);
  // nsieveofer(101);
   //cout<<sumoffactors(100)<<endl;;
   //sumoffactorsp(100);
   //sieve();
   //vector <int> p=getprimef(12245);
  // for(int i=0;i<p.size();i++)
   //  cout<<p[i]<<" ";
   // cout<<phi(97);
   findk();
     int k;cin>>k;
     cout<<pr[k-1];
     return 0;

}