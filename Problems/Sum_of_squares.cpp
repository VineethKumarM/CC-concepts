#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vb vector<bool>
#define vii vector<vector<int>>
#define vpii vector<pair<int,int>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
#define pairi pair<int,int>
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
#define Maxx 10000
const ll mod=1e9+7;
const ll size=2*(1e6+1);
const ll limit=1e10+7;
/*Fermat Theorem Approach:
This approach is based on the following statement, which is based on Fermat’s Theorem: 
“Any positive number n is expressible as a sum of two squares if and only if the 
prime factorization of n, every prime of the form (4k + 3) occurs an even number of times.” 
By making use of the above theorem, we can directly find out if the given number
 n can be expressed as a sum of two squares.
To do so, we simply find all the prime factors of the given number n, 
which could range from [2,\sqrt{n}] along with the count of those factors, by repeated division. 
If at any step, we find out that the number of occurrences of any prime factor of the form 
(4k + 3)occurs an odd number of times, we can return a false value.
If n itself is a prime number, it won’t be divisible by any of the primes 
in [2,\sqrt{n}]. Thus, we need to check if n can be expressed in the form of (4k + 3).
 If so, we need to return a false value, indicating that this prime occurs an odd number(1) of times.
Otherwise, we can return the true value. 
*/
bool is_sum_of_squares(int n)
{
    for(int i=2;i*i<=n;i++)
    {
        int cnt=0;
        if(n%i==0)
        {
            while(n%i==0)
            {
                n/=i;
                cnt++;
            }
            if((i%4==3) and (cnt%2)!=0) return false;
        }
    }
    return n%4!=3;
}
/*
   The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.
*/
string getPermutation(int n, int k) {
        int fact=1;
        vector<int> str;
        for(int i=1;i<n;i++)
        {
            fact*=i;
            str.push_back(i);
        }
        str.push_back(n);
        string res;
        k=k-1;
        while(1)
        {
            res+=to_string(str[k/fact]);
            str.erase(str.begin()+k/fact);
            if(str.size()==0) break;
            k%=fact;
            fact/=str.size();
        }
        return res;
    }
int main()
{
    // freopen("input1.txt", "r", stdin); 
    // freopen("output1.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s;
    for(int i=1;i<=4;i++) s.push_back((char)i);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}