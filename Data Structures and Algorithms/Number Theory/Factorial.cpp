#include<bits/stdC++.h>
#include<iomanip>
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
#define vpi vector<pair<int,int>>
#define vpli vector<pair<ll,ll>>
#define uint_64t unsigned ll
#define int_64t  ll
#define ull unsigned long long int
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n 
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define Maxx 10000
const int MAX=200;
const int mod1=1e9+7;
//Returns the largest power of p that divides the n!
int LargestPower(ull n,ull p)
{
    int x=0;
    while(n)
    {
        n/=p;//Herewe are taking all ps and dividing for further caluclation of n p^2 terms
        x+=n;//Here we are adding n of terms p id divisible  after diving by n
    }
    return x;
}
//Returns the largest power of p that divides n!
//here p can be composite number
int findpower(int n,int p)
{
    int x=0;
    int r=p;
    while(r<=n)
    {
        x+=n/r;
        r*=p;
    }
    return x;
}
vpi Prime_fact(ull n)
{
    vpi fact;
    for(ll i=2;i<=n;i++)
    {
        ll cnt=0;
        if(n%i==0)
        {
           
            while(n%i==0) {n/=i;cnt+=1;}
            fact.pb(make_pair(i,cnt));
        }
    }
    if(n>1) fact.pb(make_pair(n,1));
    return fact;
}
ull Largest_PowerComposite(int n,int p)
{
    int ans=INT_MAX;//Declaring ans ans as INT_MAX
    vpi v=Prime_fact(p);
    for(int i=0;i<v.size();i++)
    {
        ans=min(ans,findpower(n,v[i].first)/v[i].second);
        //Here ans is taken as minpowers of the prime factors of p
        //For ex;12 =4*3 largest power of 4 is 2 and for 3 it is 3
        //So minimum 2 will be taken as ans
    }
    return ans;
}
//Sum of divisors of factorials of number
vi allprimes;
void sieve(int n)
{
    vb isprime(n+1,true);
    for(int i=2;i*i<=n;i++)
    {
        if(isprime[i])
        {
           for(int j=i*2;j<=n;j+=i)
            isprime[j]=false;
        }
    }
    for(int i=2;i<=n;i++) if(isprime[i]) allprimes.pb(i);
}
//Binpower of(a^n)
int binpower(int a,int n)
{
    int res=1;
    while(n)
    {
        if(n&1) res*=a;
        a*=a;
        n/=2;
    }
    return res;
}
int sigmaofdivisors(int n)
{
    int res=1;
    sieve(n);
    for(int p=0;p<allprimes.size();p++)
    {
        int x=allprimes[p];
        int exp=LargestPower(n,x);
        res=res*((binpower(x,exp+1)-1)/(x-1));//Applying the summation of divisors formula
    }
    return res;
}
int PowerModulo(int a,int n,int p)
{
    int res=1;
    a%=p;
    while(n)
    {
        if(n&1) res=(res*a)%p;
        a=(a*a)%p;
        n/=2;
    }
    return res;
}
//optimised method 1 using sieve of erathrosenes
int modFact(int n,int m)
{
    if(n>=m) return 0;
    int res=1;
    vi primes;
    bool isprimes[n+1];
    memset(isprimes,true,sizeof(isprimes));
    for(int i=2;i*i<=n;i++)
    {
        if(isprimes[i])
        {
            for(int j=2*i;j<=n;j+=i)
             isprimes[j]=false;
        }
    }
    for(int i=2;i<=n;i++) if(isprimes[i]) primes.pb(i);
    for(int i:primes)
    {
        int exp=LargestPower(n,i);
        res=(res*PowerModulo(i,exp,m))%m;//Here we are taking exponent for each p^k factor in n
    }
    return res;
}
//Optimised method 2 for modfact using Wilson's Theorem
//Wilson theorem states that (p-1)!=-1 if p is prime
//This method is used when mod m is closer to n
//for 25!mod29 we now that 28!mod29 =-1 therfore multiply modinverse(26,29)*moinverse(27,29)
//*modinverse(28,29)
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
//Time complexity of this function is O(p-n)*log n
int Wilson_modfact(int n,int p)
{
    if(n>=p) return 0;
    int res=-1;//Impilin (p-1)!modp=-1;
    n+=1;//incrementing n with 1 to start finding its Modinverse
    while(p-n>0)//until the differnce becomes 0
    {
       res=(res*(moduloinverse(n,p)))%p;
       n++;
    }
    return res>0?res:res+p;
}
//Optimised method 3
//Here we can use  res*=n%p upto n encounters prime less than equal to n
//Once it encountes n prime then (res*(n))%p;
//By using AKS algo for primality test the time compleity is O(1o.5log n) time
//Double fatoraial
int doublefact(int n)
{
    int res=1;
    for(int i=n;i>=0;i-=2)
    {
        if(n==0 || n==1) return res;
        else
         res*=i;
    }
    return res;
}
//Tariling zeros in n!
//Since zeoes can be formed only by 2 and 5 and for each factorial the 5 are less than 
//2 s
//So the count of largest primes can be the trailing zeroes
int Count_trailzeroes(int n)
{
    int x=LargestPower(n,5);
    return x;
}
//Caluclating factorial of large numbers
int multiply(int x,vi &res,int size)
{
    int carry=0;
    for(int i=0;i<size;i++)
    {
        int prod=x*res[i]+carry;
        res[i]=prod%10;
        carry=prod/10;
    }
    while(carry)
    {
        res[size]=carry%10;
        carry/=10;
        size++;
    }
    return size;
}
vi LargeFact(int n)
{
    vi res(MAX);
    res[0]=1;
    int size=1;
    for(int i=2;i<=n;i++)
        size=multiply(i,res,size);
    //for(int i=size-1;i>=0;i--) cout<<res[i];   
    return res;
} 
//Caluclating Primorial Numbers
int Pmax=1000000;
vi SievePrimes;
void SieveSundaram()
{
    //Since Sieve of Sundaram Caluclates the primes upto 2*n+1
    //So we are reducing to n only
    bool mark[Pmax/2+1]={0};
    //Here we will mark the integers of form i+j+ij
    //and max is possible is sqrt(pmax-1)/2
    //j should be incremented by1 biy we are caluclating whole expresssion incremennt
    //and mark that j as false
    for(int i=1;i<=(sqrt(Pmax)-1)/2;i++)
    {
      for(int j=(2*i*(i+1));j<=Pmax/2;j+=2*i+1)
         mark[j]=true;
    }
    SievePrimes.pb(2);
    for(int i=1;i<=Pmax/2;i++)
    {
        if(!mark[i]) SievePrimes.pb(2*i+1);
    }
}
int Primorial(int n)
{
    int res=1;
    for(int i=0;i<n;i++) res*=SievePrimes[i];
    return res;
}
//Given a number x and we have to find first factorial such that i! wii be divisible by x
int FirstFact(int x)
{
    int new_x=x;
    int res;
    for(int i=2;i<x;i++)
    {
        new_x/=__gcd(i,new_x);
        if(new_x==1) {res=i;break;}
    }
    return res;
}
//Count numbers formed by given two digits with sum of the number having 2 digits 
int check(int x, int a, int b) 
{ 
    // sum of digits is 0 
    if (x == 0) 
        return 0; 
  
    while (x) { 
  
        // if any of digits in sum is 
        // other than a and b 
        if (x % 10 != a and x % 10 != b) 
            return 0; 
  
        x /= 10; 
    } 
  
    return 1; 
} 
int modInverse(int a, int m) 
{ 
    int m0 = m; 
    int y = 0, x = 1; 
  
    if (m == 1) 
        return 0; 
  
    while (a > 1) { 
  
        // q is quotient 
        int q = a / m; 
        int t = m; 
  
        // m is remainder now, process 
        // same as Euclid's algo 
        m = a % m, a = t; 
        t = y; 
  
        // Update y and x 
        y = x - q * y; 
        x = t; 
    } 
  
    // Make x positive 
    if (x < 0) 
        x += m0; 
  
    return x; 
} 
 const int N = 1000005; 
int fact[N];
void pregenfact()
{
    fact[0]=fact[1]=1;
    for(int i=2;i<=1000000;i++)
    fact[i]=(ll)fact[i-1]*i%mod1;
}
int InvMod[1000005];
void pregeninv_mod()
{
    InvMod[0]=InvMod[1]=1;
    int factorial=1;
    InvMod[1000000]=modInverse(fact[1000000],mod1);
    for(int i=999999;i>1;--i)
    InvMod[i]=((ll)InvMod[i+1]*(ll)(i+1))%mod1;
}
ll nCr(int n,int i)
{
    return (ll)fact[n]*(InvMod[n-i]%mod1)*(InvMod[i]%mod1);
}
ll Count_num(int n,int a,int b)
{
    pregenfact();
    pregeninv_mod();
    if(a==b) return check(a*n,a,b);
    int count=0;
    ll sum=0;
    for(int i=0;i<=n;i++)
    {
        
          if (check(i * a + (n - i) * b, a, b)) 
             count=(count+nCr(n,i))%mod1;
        
    }
    return count;
}
//function for printing the n composites
void print_Composite(int n)
{
    vi v=LargeFact(n+1);
    int q=0;
    // for(int i=2;i<2+n;i++)
    // {
      
    //    cout<<i;
    //    cout<<'\n';
    // }
}
//Inorder to avoid overfow conditions we are using mulmod function
ll mulmod(ll a,ll b,ll mod)
{
    ll res=0;
    a%=mod;
    while(b)
    {
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}
ll Count_Ways(ll n,ll m)
{
    sieve(1000000);//Caluclating all primes before
    //If the function calls are more than once just call the function in main at once
    ll ans=1;
    //Here we are statrting the index from 1
    for(int i=1;i<allprimes.size();i++)
    {
        //Caluclating power of prime 
        int power=Largest_PowerComposite(n,allprimes[i]);
        //It the current prime number power became 0 then
        //All other next primes no no=eed to be consideered as they are not going to divisible
        //by n
        if(power==0) break;
        ans=mulmod(ans,power+1,m)%m;//Here we are doing mod because in qstn it was given that
        //ans shild be mod of m
    }
    if((ans-1)%m<0) return (ans-1+m)%m;
     else return (ans-1)%m;
}
// vil factorial(int num1,int num2)
// {
//    vil ans;
//    ll facto=1;
//    for(int i=1;i<=num1;i++)
//    {
//       facto*=i;
//    }
//    ans.pb(facto);
//    for(int i=num1+1;i<=num2;i++)
//    {
//        facto*=i;
//        ans.pb(facto);
//    }
//    return ans;
// }
// void printformat(vil &result)
// {
//     int digits=result.back().str().size();
// }
//Finding the lasr digit after dividing A! by B!
//Factorial of any number always ends with 0,1,2,4,6
ll Last_Digit(ll a,ll b)
{
    if(a==b) return 1;//If both of them are equal
     else if(b-a>=5) return 0;//If their differnce greater than 5
     else
     {
         int variable=1;
         for(int i=a+1;i<=b;i++)
         variable=(variable*(i%10))%10;//Using modular multiplication
         return (ll)variable%10;
     }
}
//To get all primes smaller than n using wilsons theorem
void primes_Range_in_n(int n)
{
    int fact=1;
    for(int k=2;k<=n;k++)
    {
        fact*=(k-1);
        if((fact+1)%k==0) cout<<k<<' ';
    }
}
//Function to caluclate the factorial using stirling approxiamation
ll Stirling_Approx(int n)
{
    if(n==1) return 1;
    ll z;
    float e=2.71;
    z=sqrt(2*3.14*n)*pow((n/e),n);
    return z;
}
//Print composite numbers range of length n
void print_comp_range(ll n)
{
    ll fact=1;
    for(ll i=2;i<=n+2;i++) fact*=i;
    for(int i=2;i<=n+1;i++) cout<<fact+i<<'\n';
}
//Caluclating smallest number s such that n divides the s!
//Using binary search and prime factors
//Legendre func used to calucltae pow max of prime num in n1
// Lagrange’s Formula runs in O(Log N).
// Binary search is O(Log N).
// Calculating prime factors is O(sqrt(N))
// Iterating through prime factors is O(Log N).

// Time complexity becomes: O(sqrt(N) + (Log N)^3)
ull legendre(ull factor, ull num) 
{ 
    ull count = 0, fac2 = factor; 
    while (num >= factor) 
    { 
        count += num / factor; 
        factor *= fac2; 
    } 
    return count; 
} 
//Here map of prime factors
map<ull,int> prime_fact(ull num)
{
    map<ull,int> ans;
    for(ull i=2;i*i<=num;i++)
    {
          while(num%i==0) {ans[i]++; num/=i;}
      
    }
    if(num>1) ans[num]++;
    return ans;
}
//Checking if s! contains power prime of p divisor which is a prime factor of n
bool is_it_contain(map<ull,int> &factors,ull n)
{
    for(map<ull,int>::iterator it=factors.begin();it!=factors.end();it++)
    {
        if(legendre(it->first,n)<(it->second))
           return false;
    }
    return true;
}
ull bin_search(ull start,ull end,map<ull,int> &factors)
{
    ull mid=(start+end)/2;
    if(!(is_it_contain(factors,mid))) return bin_search(mid+1,end,factors);
     if(start==mid) return mid;
    
    return bin_search(start,mid,factors);
}
//Finding the smallest num
//We can also first fact function also
ull find_num(ull n)
{
    map<ull,int> factors=prime_fact(n);
    return bin_search(1,n,factors);
}
//Smallest number wg=hose factorial has atleat n digits
// Kamenetsky’s formula approximates the number
// of digits in a factorial by :
// f(x) = log10(((n/e)n) * sqrt(2*pi*n))

// Thus, we can pretty easily use the property of logarithms to ,
// f(x) = n*log10((n/e)) + log10(2*pi*n)/2 
ull Find_digits(ull n)
{
    if(n==0) return 1;
    if(n==1) return 1;
    double x=(n*log10((n/M_E)))+log10(2*M_PI*n)/2;
    return floor(x)+1;
}
ull  find_small_n(ull n)
{
    ull low=1;
    ull high=2*n;
    
    if(n<0) return -1;
    if(n<=1) return 1;
    //If low equals the n
    if(low==Find_digits(n)) return low;
    while(low<=high)
    {
        ull mid=(low+high)/2;
        if(Find_digits(mid)>=n && Find_digits(mid-1)<n)//If the mid lies in between mid and mid-1
        return mid;
        else if(Find_digits(mid)<n) low=mid+1;
        else high=mid-1;
    }
    return low;
}
//First npn zero digit of n!
// 
// Since we are asked about last non-zero digit, 
// we remove all 5's and equal number of 2's from
// factors of 14!.  We get following:

// 14! = 14 * 13 * 12 * 11 * 2 * 9 * 8 * 7 *
//                            6 * 3 * 2 * 1

// Now we can get last non-zero digit by multiplying
// last digits of above factors!
int dig[]={1, 1, 2, 6, 4, 2, 2, 4, 2, 8};
int lastnon_digit(int n)
{
    if(n<10) return dig[n];
    if((((n/10)%10)%2)==0)
     return (6*lastnon_digit(n/5)*dig[n%10])%10;
    else
     return (4*lastnon_digit(n/5)*dig[n%10])%10;
}
//Finding smallest number s! having atleast n zeroes
bool check(ull p,ull n)
{
   ull count=0,fact=5;
   while(p/fact)
   {
       count+=(p/fact);
       fact*=5;
   }
   return (count>=n);
}
ull num_having_nzeroes(ull n)
{
    ull low=0;
    ull high=5*n;
    if(check(low,n)) return low;
    while(low<high)
    {
        ull mid=(low+high)/2;
        if(check(mid,n)) high=mid;
        else
        low=mid+1;
    }
    return low;
}
//Count of Factorial that diveds x and not y
int Count_x_y_fact(int x,int y)
{
    return FirstFact(y)-FirstFact(x);
}
ull Count_of_Digits(ull n)
{
    if(n<0) return -1;
    if(n<=1) return 0;
    double digits=0;
    for(ull i=2;i<=n;i++)
    {
        digits+=log10(i);
    }
    return floor(digits)+1;
}
//Counting factorials in given range
int Count_fact(int low,int high)
{
    int fact=1;
    int cnt=1;
    while(fact<low)
    {
     cnt++;
     fact*=cnt;
    
    }
    int res=0;
    while(fact<=high)
    {
        fact*=cnt;
        cnt++;
        res++;
    }
    return res;
}

int main()
{
     freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // LargeFact(100);
    //print_Composite(10);
  //  SieveSundaram();
    //cout<<Count_num(11028,4,3);
    //cout<<InvMod[100000];
    // cout<<Last_Digit(2632,2634);
   // primes_Range_in_n(10);
    //cout<<Count_Ways(10,100);
    //cout<<Stirling_Approx(5);
    //print_comp_range(3);
   // cout<<find_num(100)<<'\n';
    //cout<<lastnon_digit(14);
  //cout<<FirstFact(100);
  //cout<<Count_x_y_fact(15,20);
  //cout<<FirstFact(25)-FirstFact(15);
  //cout<<Find_digits(120);
  cout<<Count_fact(2,720);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}