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
#define vs vector<string>
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
#define uns unsigned
#define ull unsigned long long int
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 10000
//Prime path
//In this problem we are given with two prime numbers and we have to convert
//from one prime number to another prime number and by changing the digits without violating
//the condition where the condition is that at each stage of change of number the
//number should be prime
//this problem can  be approached by graph theory
//First we will build the graph of primes and we will do bfs traversal inorder to have mi
//minimum distance
//We ill genarate all the 4 digit prime numbers ,store them in a vector,then we will build the graph
//In the adjaency list for a prime p we will connect this node to all the nodes 
//which differ by our current number by only one digit
//fo this we will run anested loop from i=0 to i<=prime.size() and j=i;j<=prime.size()
//and check the valid condition and if it satisifies then we will connect both the nodes
//here note that we are storing al prime numbers inorder to reduce time otherwise we have
//to rin loop for each i and j which increase time complexity
//and j loop is stating from i as if from prime[i] is genarted prime[j]
//then we will add these two numbers to their respective primes list
vii graph;
vi vis;
vi primes;
bool isprime(int n)
{
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0) return false;
    }
    return true;
}
void prime_gen()
{
    for(int i=1000;i<=9999;i++)
    {
        if(isprime(i)) primes.pb(i);
    }
}
bool isvalid(int a,int b)
{
    int cnt=0;
    while(a)
    {
        if(a%10!=b%10) cnt++;
        a/=10;b/=10;
    }
    return cnt==1;
}
void Build_Graph()
{
    for(int i=0;i<primes.size();i++)
    {
        for(int j=i;j<primes.size();j++)
        {
            int a=primes[i];
            int b=primes[j];
            if(isvalid(a,b))
            {
                graph[a].pb(b);
                graph[b].pb(a);
            }
        }
    }
}
vi dist;
void sr_bfs(int node)
{
    vis[node]=true;
    int cur_size=1;
    queue<int> q;
    dist[node]=0;
    q.push(node);
    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        for(auto &x:graph[cur])
        {
            if(vis[x]==0)
            {
             q.push(x);
             dist[x]=1+dist[cur];
             vis[x]=1;
            }
        }
    }
}

int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,m;cin>>n>>m;
    graph.resize(100001);
    vis.resize(100001);
    dist.resize(100001);
    prime_gen();
    Build_Graph();
    for(int i=0;i<=9999;i++) dist[i]=-1;
    sr_bfs(n);
    cout<<dist[m];
    
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 