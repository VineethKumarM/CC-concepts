#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
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
//Modulo power of(x,y,mod)
ll Powermodulo(ll x,ll y,ll mod)
{
    x%=mod;//Update x if it is more than mod
    ll res=1;
    x=x%mod;
    while(y)
    {
        if(y&1) res=(res*x)%mod;
        x=(x*x)%mod;
        y/=2;
    }
    return res;
}
//Complexity O(log m)
ll gcdextended(ll a, ll b,ll &x,ll &y)
{
    if(a==0)
    {
        x=0;y=1;return b;
    }
    ll x1,y1;
    ll gcd=gcdextended(b%a,a,x1,y1);
    x=y1-(b/a)*x1;
    y=x1;
    return gcd;
}

ll moduloinverse(ll a,ll m)
{
  ll x,y;
  ll g=gcdextended(a,m,x,y);
  if(g!=1) return -1;
  else
  {
      ll res=(x%m+m)%m;
      return res;
  }
}
//Modinverse through iterative approach
ll ModInverse(ll a,ll m)
{
    if(m==0) return a;
    ll y=0,x=1;
    while(a>1)
    {
        ll q=a/m;
        ll t=m;
        //Proceeding same as Euclids Algo
        m=a%m;a=t;
        t=y;
        y=x-(q)*t;
        x=t;
    }
    if(x<0) return x+m;
    return x;
}
//Case when m is prime using Fermats little Theorem
ll Primemodulo(ll a,ll m)
{
    ll gcd=__gcd(a,m);
    ll res=1;
    if(gcd!=1) return -1;
    else
    {
      ll res=Powermodulo(a,m-2,m);
      return res;
    }
}
//Division of modulo (a/b)%m using modulo Inverse 
ll moduloDivison(ll a,ll b,ll m)
{
    ll res=ModInverse(b,m);
    if(res==-1) return -1;
    else
    return (res*a)%m;
}
//Square Root Under modulo p
void squareroot(ll n,ll p)
{
    if(p%4!=3) cout<<-1;
    n%=p;
    ll x=Powermodulo(n,(p+1)/4,p);
    if((x*x)%p==n) cout<<x<<' ';
    x=p-x;
    if((x*x)%p==n) cout<<x<<' ';
    
}
ll order(ll b,ll p)
{
    if(__gcd(b,p)!=1) return -1;
    ll k=3;
    while(1)
    {
        if(Powermodulo(b,k,p)==1)
         return k;
         k++;
    }
}
ll convertx2e(ll x,ll &e)
{
    e=0;
    while(x%2==0)
    {
        e++;
        x/=2;
    }
    return x;
}
ll Stonelli(ll n,ll p)
{
    if(__gcd(n,p)!=1 || Powermodulo(n,(p-1)/2,p)==(p-1)) return -1;
    ll s,e;
    s=convertx2e(p-1,e);
    ll q;
    for(q=2;;q++)
    {
         if(Powermodulo(q,(p-1)/2,p)==p-1)
          break;
    }
    ll x=Powermodulo(n,(s+1)/2,p);
    ll b=Powermodulo(n,s,p);
    ll g=Powermodulo(q,s,p);
    ll r=e;
    return 0;
}
//Modulo multiplicatiom of large number
ll modulomult(ll a,ll b,ll mod)
{
    ll res=0;
    a%=mod;
    while(b)
    {
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b/=2;
    }
    return res;
}
//Computaion of large modulo m
ll largemodulo(string s,ll mod)
{
    ll res=0;
    for(ll i=0;i<s.size();i++)
    {
      res=(res*10+(ll) s[i]-'0')%mod;
      res+=1;
    }
     return res;
}
ull factorial(ull n)
{
    ull f=1;
    for(ull i=0;i<n;i++)
     f=(f*i)%mod1;
     return f;
}
//Computation of large (a^b) modulo m
ull Apowmodm(string s,ull b,ull mod)
{
    ull ans=largemodulo(s,mod);
    ull mul=ans;//Here we are storing mul as ans since in the expansion we have 
    //compute a%m at each stage of m
    for(ull i=1;i<b;i++)
     ans=(ans*mul)%mod;
     return mod;
}
//Computaion of large prime exponent values A^(B^C);
//Here mod should be prime
ull Primeexponent(ull a,ull b,ull c,ull mod)
{
   ull res=Powermodulo(b,c,mod-1);
   ull ans=Powermodulo(a,res,mod);
   return ans;
}
//Caluclation of no of divisors greater than a specified number
ll caluclatedivisors(ll a,ll b)
{
    ll n=(a-b);
    ll ans=0;
    for(ll i=1;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            if(i>b) ans++;//we should take values greater than b only because a%b will
            //range to 0,b-1 only where we cannot equate to b
            if((n/i)!=i && (n/i)>b)
            ans++;
        }
    }
    return ans;
}
//Possible values of x
ll Possiblex(ll a,ll b)
{
    if(b==a) return -1;
    if(a<b) return 0;
    ll ans=caluclatedivisors(a,b);
    return ans;
}
//Digsum of a a number 
//Here if a digit sum is multiple of 9 it is mainated until the last digit
//For 9k+p the last stage of single sum is p
ll digsum(ll n)
{
    if(n==0) return 0;
    if(n%9==0) return 9;
    return n%9;
}
//Sum of repeated digits
ll Repeatdigsum(ll n,ll p)
{
    ll sum=digsum(n);
    sum=sum*p;
    return digsum(sum);
}
//Value of y mod 2 rasied power
ull pow2mod(ull a,ull x)
{
    if(log(a)<x)
     return a;
     if(x>63) return a;
     return (a%(1<<x));

}
//unit digit of x ^y
ull unitdigit(ull x,ull y)
{
    x%=10;
    y%=4;//Because of last digit repeating cycle
    return ((ull)pow(x,y)%10);
}
//Subsequences of size three in an array whose sum is divisible by m problem
//using hashing and modulo technique
//Firstly, if thrice of a number is divisible by M then we will add {{N}choose{3}} to
//answer where N is frequency of that number.
//Secondly, if twice of some number A added with sum number B is divisible by M then we will add {{Freq[A]}choose{2}} * Freq[B] to the answer.
//Thirdly, if all the number A, B, C that sum up to S which is divisible by M then we will add Freq[A] * Freq[B] * Freq[C] to the answer.
//Complexity of the code is O(m^2)
ll CountSequence(vi A,ll n,ll m)
{
    vi h(m,0);//To staore the frequency of each value under modulo m
    ll ans=0;
    for(int i=0;i<n;i++)
    {
        A[i]=A[i]%m;
        h[A[i]]++;
    }
    for(int i=0;i<m;i++)
    {
        for(int j=i;j<m;j++)//Here j is starting from i because the previous elments cannot make up to make sum j
        {
            ll rem=(m-(i+j)%m)%m;//Required remainder to ad  to i and j to make sum divisible by m
            if(rem<j) continue;
            else if(i==j && rem==j) ans+=(h[i]*(h[i]-1)*(h[i]-2))/6;//Case 1 when all are equal
            else if(i==j) ans+=(h[i]*(h[i]-1)*h[rem])/2;//Given below are the three case where two of the values of i j and rem are equal and another one is remainder
            else if(i==rem) ans+=(h[i]*(h[i]-1)*h[j])/2;
            else if(j==rem) ans+=(h[j]*(h[j]-1)*h[i])/2;
            else  ans=ans+(h[i]*h[j]*h[rem]);//where i,j rem are differnet
        }
    }
    return ans;
}
//Distributing m items over n sze of circle from starting position of k
//Find position in circle where m th item to be deliverd
ll lastitem(ll m,ll n,ll k)
{
    if(m<=n-k+1) return m+k-1;//If no items to be distributed are less than remaining positions
    m-=(n-k+1);
    return m%n==0?n:m%n;//Return modulo;

}
//Baby Step Giant Step Algorithm
//a^k=b(mod)m
//Expressing k as i*n-j
//Calucalte all LHS values 
ll discretelog(ll a,ll b,ll m)
{
    ll n=(ll)sqrt(m)+1;
    unordered_map<ll,ll> value;//we will map each LHS value to its index value
    ll ans;
    for(int i=n;i>=0;i--)
     value[Powermodulo(a,i*n,m)]=i;
     for(ll j=0;j<n;j++)
     {
        ll cur=(Powermodulo(a,j,m)*b)%m;
        if(value[cur])//If any collision occurs because we stored the index value is there
        {
           ans=value[cur]*n-j;
           if(ans<m) return ans;//Checking if ans is less than m or not 
        }
     }
     return -1;
}
//Improved Optimisation of above method negotiating binary exponentiation and ordered maps
//Replacing counter varible to multiply each time when we increase p by 1 and counter
//variable for a to multiply when we increase q each time
//Use of unordered Map
//This function returns the minimum value of x which satisfies a^x%m=b%m
ull Improved_Discretelog(ull a,ull b,ull m)
{
    a%=m,b%=m;
    ull n=sqrt(m)+1;
    ull an=1;
    for(ull i=0;i<n;i++) an=(an*1LL*a)%m;
    unordered_map<ull,ull> values;
    for(ull q=0,curr=b;q<=n;q++)//Here qs range is  1 to n so why we are computing upto n
    {
        values[curr]=q;
        curr=(curr*1LL*b)%m;
    }
    for(ull p=1,cur=1;p<=n;p++)//checking for each posiible value
    {
        cur=(cur*1LL*an)%m;
        if(values.count(cur))
        {
            ull q=values[cur];
            ull ans=n*p-q;
            return ans;
        }
    }
    return -1;
}
//Incase if gcd(a,m)>1 then upon simplifying the original equation
//k*a^(x-1)=b mod(m)
ull GCD_Discretelog(ull a,ull b,ull m)
{
   a%=m;b%=m;
   ull k=1,add=0,g;
   while((g=__gcd(a,m))>1)
   {
       if(b==k) return 0;
       if(b%g) return -1;
       b/=g,m/=g,add++;
       k=(k*1ll*(a/g))%m;
   }
   ull n=sqrt(m)+1;
    ull an=1;
    for(ull i=0;i<n;i++) an=(an*1LL*a)%m;
    unordered_map<ull,ull> values;
    for(ull q=0,curr=b;q<=n;q++)
    {
        values[curr]=q;
        curr=(curr*1LL*b)%m;
    }
    for(ull p=1,cur=k;p<=n;p++)
    {
        cur=(cur*1LL*an)%m;
        if(values.count(cur))
        {
            ull q=values[cur];
            ull ans=n*p-q+add;//Here we are adding add to ans because we are computing for a^(x-1)=b mod(m) which 
            //is reduced by factor gcd 
            //So we should add to this ans in order to get the original equation
            return ans;
        }
    }
    return -1;
}
//Finding ‘k’ such that its modulus with each array element is same
ll Kmodulo(vil A,ll n)
{
    sort(A.begin(),A.end());
    ll d=A[n-1]-A[0];
    vil divisors;
    ll ans=0;
    for(ll i=1;i<=sqrt(d);i++)
    {
        if(d%i==0)
        {
            divisors.pb(i);
            if((d/i)!=i) divisors.pb(d/i);
        }
    }
    for(int i=0;i<divisors.size();i++)
    {
       
         ll temp=A[0]%divisors[i];
             ll check=1;
            for(ll j=1;j<n;j++)
            {
                if(A[j]%divisors[i]==temp)  check=1;
                else
                {
                    check=0;
                    break;
                }
            }
        
        if(check) {cout<<divisors[i]<<" ";ans+=1;}
    }
    return ans;
}
//Finding minimal zero
ll Findminzero(ll p)
{
    ll cur=1,prev=1,next=1,number=2;
    while(next)
    {
      next=(cur+prev)%p;
      prev=cur;
      cur=next;
      number+=1;
     
    }
    return number;
}
//Finding maxsub array under modulo m
ll MaxSubArr_mod(vil A,ll m)
{
    ll prefix=0,maxi=0;
    set<ll> S;
    for(int i=0;i<A.size();i++)
    {
        prefix=(prefix+A[i])%m;
        maxi=max(maxi,prefix);//Caluaclting maximum
        auto it=S.lower_bound(prefix+1);//here we are checking the lower bund of that number which
        //is just grater than prefix sum under modulo obtained so far
        if(it!=S.end())
         maxi=max(maxi,prefix-(*it)+m);//modulo operation
         S.insert(prefix);
    }
    return maxi;
}
//Triccks for Modular Divisiomm
//1.Using Modulo inverse
//Supoose if we have to find (nCr)%100000000007
ll ModDivison(ll n,ll r,ll mod)
{
    ll res=1;
    for(int i=1;i<=r;i++) res*=i;
    ll p=moduloinverse(res,mod);//Moulo Inverse caluclation
    ll ans=1;
    for(int i=0;i<r;i++)
     ans=(ans*(n-i))%mod;
     ans=(ans*p)%mod;
     return ans;
}
//Method 2
//This approach is used when b value is small
//This will work only in case when the denominator is a factor of numerator i.e. when a % b = 0 following the rule: 
//If b | a, then we can write (a/b) % p as (a % p*b)/b. 
//This rule proves useful for small values of b.
ll ModifiedModDiv(ll n,ll r,ll mod)
{
    ll res=1;
    for(int i=1;i<=r;i++) res*=i;
    mod*=res;//Here we are channging denominator
    ll ans=1;
    for(int i=0;i<r;i++)
     ans=(ans*(n-i))%mod;
     ans/=res;//Here we are again nullifying the effect to ans that we made in mod
     return ans;

}
//Count of integrs that satisifies the form x*x==1(modp)
//Approach if x satisfies the number then all the numbers of the form x+i*p does satisty
//where i is a multiple
ll CountPossiblex(ll n,ll p)
{
    ll ans=0;
    for(int i=1;i<p;i++)
    {
        if((i*i)%p==1)
        {
            ll last=i+(n/p)*p;
            if(last>n) last-=p;
            ans+=((last-i)/p+1);//1 added for the number itself
        }
        
    }
    return ans;
}
ull binpower(ull a,ull n)
{
    ull res=1;
    while(n>0)
    {
        if(n&1) res*=a;
        a*=a;
        n/=2;
    }
    return res;
}
//It has complexity of O(log n)
//From the concept of minima max9ima in derivative for maxproduct we should break into 2 and 3 only
//Case 1 when mod of 3=0 then simply we can break the integer into all 3 numbers
//Case 2 when mod is 1 in that case for ex:4 it is less than 5 2*2>3*1 so we take 4 from it and find 
//renaing power
//Case 3 when mod is 2 we simply multiply the nymber with 2 and 3
ll breakinteger_maxprod(ll n)
{
    if(n==2) return 1;
    if(n==3) return 2;
    ll ans=0;
    switch(n%3)
    {
        case 0:
           ans=binpower(3,n/3);
           break;
        case 1:
            ans=2*2*binpower(3,(n/3)-1);
            break;
        case 2:
            ans=2*binpower(3,n/3);
            break;
    }
    return ans;
}
//Finding mod of every number in range 1,m-1 incase if m is prime
vil PrimeRangeModInverse(ll m)
{
    vil inv(m+1);
    inv[1]=1;
    for(ll i=2;i<m;i++)
     inv[i]=m-(m/i)*inv[m%i]%m;
     return inv;
} 
//Finding gcd of Linear Congruence equation
vil Lceqn(ll a,ll b,ll n)
{
    ll g=__gcd(a,n);
    a/=g;n/=g;b/=g;
    ll inv=moduloinverse(a,n);
    vil xvalues;
    ll x=(b*inv)%n;
     xvalues.pb(x);
    for(ll i=1;i<g;i++)
    {
        ll p=x+i*n;
        xvalues.pb(p);
    }
    return xvalues;
}
//Caluclation of modified factorial taking out all ps multipe
//n!=1...(p-1)*1*(p+1).......2(P).....
//Here coefficients  of multiples of p are remained same in the multiplication
ull factmod(ull n,ull p)
{
    vul fact(p);
     fact[0]=1;
    for(ull i=1;i<p;i++)
     fact[i]=fact[i-1]*i%p;//To avoid recursion we precompute all the prime factorials
     ull res=1;
     while(n>1)
     {
         if((n/p)%2) res=p-res;//Here n/p beomes add so rem=-1 which impiles rem=p-1;
         res=res*fact[n%p]%p;//doing recursively
         n/=p;
     }
     return res;
}
//Multiplicity of p 
//Caluclation of n! modulo p 
//Here we have to use Legendres Formula
ull Multplcty_of_p(ull n,ull p)
{
    ull fact=1;
    for(int i=1;i<=n;i++) fact*=i;
    ull res=0;
    do
    {
        fact/=p;res+=fact;
    }while(fact);
    return res;
}
//Primitive Root of modulo n;
//Mathematically, g is a primitive root modulo n 
//if and only if for any integer a such that gcd(a,n)=1, there exists an
//g^k==a(mod n)
//k  is then called the index or discrete logarithm of a to the base g modulo n.
// g is also called the generator of the multiplicative group of integers modulo n.
ull Primitive_Root(ull p)
{
  ull ph=p-1,n=p;//Ph means totient function of p .Since p is prime phi will be p-1;
  vil fact;//Vector to store all the proper divisors
  //From langranage threoren we can coompute only prime ps and not their powers in n 
  for(ull i=1;i*i<=n;i++)
  {
      if(n%i==0)
      {
          fact.pb(i);
          while(n%i==0)
           n/=i;
      }
  }
  if(n>1) fact.pb(n);
  ull res;
  for(res=2;res<=p;res++)
  {
      bool safe=true;
      for(int t=0;t<fact.size();t++)
      safe &=Powermodulo(res,phi/fact[t],p)!=1;
      if(safe) return res;//fining smallest value as once we encoumter we will return the function
  }
  return -1;
}

int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // string s="12837979198390183";
    //cout<<largemodulo(s,11231341);
    //cout<<Primeexponent(3,9,4,19);
    //cout<<Possiblex(26,2);
   // cout<<Repeatdigsum(224,3);
   //cout<<pow2mod(112311,24);
   //vi A{1,2,4,3,1,3,4,5,6,7,8,99,2,16,4,2};
    //cout<<CountSequence(A,16,3);
    // cout<<discretelog(2,3,5);
    vil A{3,3,9,9,5};
    //cout<<Findminzero(7);
    //cout<<MaxSubArr_mod(A,7);
    //cout<<ModifiedModDiv(55555,5,mod1);
    //cout<<CountPossiblex(10,5);
    //cout<<breakinteger_maxprod(20);
   // vil xvalues=Lceqn(12,6,18);
    //for(int i=0;i<xvalues.size();i++) cout<<xvalues[i]<<' ';
    //cout<<factmod(17,11);
    //cout<<Multplcty_of_p(5,11);
    //cout<<Improved_Discretelog(7,3,5);
    //cout<<Primitive_Root(3);
    cout<<moduloinverse(3,7);
    return 0;
}
  