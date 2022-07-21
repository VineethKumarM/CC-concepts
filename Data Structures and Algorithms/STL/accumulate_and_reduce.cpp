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
/*Accumulate:
   An algorithm with linear time complexity O(n) that returns the result of accumulating
   all the values in the range [first,plus) plus init
   The default operation is to add the elements up but a different operation can be specified as binary_op
   
Reduce:
 An algorithm with linear time complexity O(n) that reduces the range [first,last),possibly permuted and aggregate in 
 unspecified manner,along with the initial value init over binary_op
 The default operation is to add the elements up but different operation can be specified*/
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<int> v={1,2,3,4,5,5};
    auto x=accumulate(v.begin(),v.end(),0);
    auto y=accumulate(begin(v),end(v),1,multiplies<>());
    //accumulate(begin(v),end(v),1,myfunc)
   //s cout<<x<<' '<<y<<' ';
    return 0;
 }
