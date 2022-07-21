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
/*Custom comparator passing to a sort funtion*/
bool compare(int a,int b){
    /*the operator in b/w v[0] and v[1] should be passed here */
    return a>b;
}
/**/
class comparator{
    public:
    bool operator()(const vector<int> &a,const vector<int> &b){
        return a[0]>b[0];
    }
};
class comp{
    public:
    /*this is bit confusing part as the a and b is there as per the operator priority queue pushes and when we are popping out they come
    in reverse order
    Simply speaking it should be a reverse opertaor*/
    bool operator()(const pair<int,int> &a,pair<int,int> &b){
        return a.first+a.second<b.first+b.second;
    }
};
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //vi v={1,3,4,23};sort(begin(v),end(v),compare);
    //for(int i=0;i<v.size();i++) cout<<v[i]<<' ';
   // set<vector<int>,comparator> s;
    //s.insert({1,2});s.insert({2,3});s.insert({45,6,6});
    //for(auto it:s) {for(int i:it) cout<<i<<' ';cout<<'\n';}
    priority_queue<pair<int,int>,vector<pair<int,int>>,comp> pq;
    pq.push({1,2});pq.push({100,9});pq.push({-3,9});
    while(!pq.empty()) cout<<pq.top().first<<' '<<pq.top().second<<'\n',pq.pop();
    return 0;
 }
