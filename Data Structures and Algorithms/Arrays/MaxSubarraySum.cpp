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
//Kadanes Algorithm
ll MaxSum(vil A,ll n)
{
    ll m_e_n=0,m_s_f=0;
    for(int i=0;i<n;i++)
    {
        m_e_n+=A[i];
        if(m_s_f<m_e_n) m_s_f=m_e_n;
        if(m_e_n<0) m_e_n=0;
    }
   return m_s_f;
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vil A{-2,-3,4,-1,-2,1,5,-3};
    cout<<MaxSum(A,A.size());
    return 0;
}