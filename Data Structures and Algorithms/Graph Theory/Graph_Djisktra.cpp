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
#define vvpii vector<vector<pair<int,int>>>
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
vvpii graph;
vi dist;
//in this algorithm
void djikstra(int src,int n)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({src,0});
    for(int i=0;i<=n;i++) dist[i]=INT_MAX;
    dist[src]=0;
    while(!pq.empty()) 
    {
        int cur_n=pq.top().first;
        int cur_d=pq.top().second;
        pq.pop();
        for(auto &x:graph[cur_n])
        {
            if(cur_d+x.second<dist[x.first])
            {
                 dist[x.first]=cur_d+x.second;
                 pq.push({x.first,dist[x.first]});
            }
        }
    }
    for(int i=1;i<=n;i++) cout<<dist[i]<<' ';
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,m;
    cin>>n>>m;
    graph.resize(n+1);
    dist.resize(n+1);
    int a,b,w;
    while(m--)
    {
        cin>>a>>b>>w;
        graph[a].pb({b,w});
        graph[b].pb({a,w});
    }
   djikstra(1,n);
         #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 