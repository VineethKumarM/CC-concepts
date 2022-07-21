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
vector<int> parent;
vector<int> pRank;
/*This naive_find algo has a complexity of O(n)*/
int naive_Find(int x){
       if(parent[x]==x) return x;
       return naive_Find(parent[x]);
}
/*since we are using naive find naive_union has also have the same complexity*/
void naive_Union(int x,int y){
     int px=naive_Find(x);
     int py=naive_Find(y);
     if(px!=py) parent[px]=py;
}

/*
We are going to path compress find_path and union two sets based on the rank.combining these two
optimisation we are going toreduce the complexity to O(1) for both union and rank*/
int pathCompress(int x){
    if(parent[x]==x) return x;
    return parent[x]=pathCompress(parent[x]);
}
/*
     Let us consider one set
   1<-2-<3-<4<-8 and another set as 5<-6-<7
   if we try to union these two the set 1 has more height than set 5 height
   if we union the 1 height wont be affected
   in case if both the heights are equal then any one of both sets will be increased
*/
void unionRank(int x,int y){
    int px=pathCompress(x);
    int py=pathCompress(y);
    if(pRank[px]>pRank[py]) parent[px]=py;
    else if (pRank[py]>pRank[px]) parent[py]=px;
    else{
        pRank[py]=px;
        pRank[px]++;
    }
}
/*____________________________________________________________________________________________________
 
 Advantage of DSU over DFS:
     Let us take an example where we are asked to count the no of connected components in the graph
if we are given the complete graph then for finding connected components it is better to apply
dfs over dsu(although both have approxiameatey same complexity)
But let us take the case where the graph is dynamic at we want to find the no of connected compnents
then dfs have time complexity O(v+e) where we can find with O(1) complexity in each case.
____________________________________________________________________________________________________
*/
int main()
 {
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,m;cin>>n>>m;
    parent.resize(n);
    pRank.resize(n);
    vector<vector<int>> edges(m,vector<int>(2));
    for(int i=0;i<m;i++) cin>>edges[i][0]>>edges[i][1];
    for(int i=0;i<n;i++) parent[i]=i;
    for(int i=0;i<m;i++) naive_Union(edges[i][0],edges[i][1]);
    for(int i=0;i<n;i++) cout<<parent[i]<<' ';cout<<'\n';
    for(int i=0;i<n;i++) parent[i]=i,pRank[i]=1;
    for(int i=0;i<m;i++) unionRank(edges[i][0],edges[i][1]);
    for(int i=0;i<n;i++) cout<<parent[i]<<' ';
    return 0;
 }
