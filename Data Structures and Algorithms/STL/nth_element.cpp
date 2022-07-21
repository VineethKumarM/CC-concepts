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
/*nth_element is partial sorting that arranges elements in [first,last)(excluding last) such that:
   a.The element at n_th position is the one which_should be at that position if we sort the list
   b.It does not sort the list just all the elements which precede the nth element are not greater than the it and all the
     element after it are not less than it
   c.It is implemented using intro sort*/
   /*This partial sort can be used to find kth largest element with complexity O(n)*/
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vi v={1,2,3,3,3,4,4};
    //nth_element(v.begin(),v.begin()+v.size()/2,v.end());
    nth_element(v.begin(),v.begin()+v.size()/2,v.end(),greater<int>());
    for(int i=0;i<v.size();i++) cout<<v[i]<<' ';
    return 0;
 }
