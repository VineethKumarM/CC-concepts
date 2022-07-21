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
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
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
class Pair{
    public:
    int li;
    int di;
    int val;
    Pair(int li,int di,int val)
    {
      this->li=li;
      this->di=di;
      this->val=val;
    }
};
class Compare{
    public:
    bool comparator(Pair& p1,Pair& p2)
    { 
            return p1.val<p2.val;
    }
};
void merge_lists(vii v)
{
    priority_queue<Pair,vector<Pair>,Compare> pq;
    for(int i=0;i<v.size();i++)
    {
        Pair p(i,0,v[i][0]);
        pq.push(p);
    }
    while(pq.size()>0)
    {
        cout<<pq.top().val<<'\n';
        pq.pop();
    }
}
int main()
{
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //intro();
   //vi v={3,2,1,5,6,4,8,7,9};
  //sort_nearly_sorted_array(v,3);
 vii v={{1,2},{7,9},{4,5},{6,7}};
 merge_lists(v);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}