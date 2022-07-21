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
/*_________________________________________________________________________________________________
In this bellMan_Ford we are going to return shortes path b/w a source vertex to all other nodes
in which negative weights is possible.
<--------------------------------------------------------------------------------------------------->
Observation:We cannot define the shortest weight path for negative weighted cyclic graph.
Negative weighted cyclic graph:the toytal edge weight sum upon one cycle is negative for this graph
Let us assume a case where there is negative cycle in the graph and try to find the shortest path
1----7----->(((cycle)))[-10]-----------20----->3
we can see that if we do one cycle over the graph to reach 3 from 1 
weightSum=7+(-10)+20=(-17)
but if we do cycling once again the totalweight sum reduces...and sp on...
so  it leads to infinite cycling in the negative graph.
So we cannot define shortest path weight in these type of graph
?-----------------------------------Why (n-1) times---------------------------------------------?
from the dry run we can observe at ith iteration all the nodes which are having at max i lenght from
source get all the shortest weight path sum{kind of dp a=pproach dp[i] we know we try to build
the answer for dp[i+1]
So we need to find the maxPath lenght node iterations for the last node to get their shortestPath weights
?--------------------------What is maxPathlenght-----------------------------------------------?
Let us divide the whole graph into 2 types
i.Linear Graph ii.Non-linear graph
i.Linear Graph:In this case the max lenght for the last node is at n-1 where there is a single
edge b/w two nodes
ii.Non-Linear Graph:In this case there might be cycle which has maxPath lentght>n
But we already know the cyclic part of graph cannot be negative so it must be +ve..
So if we do the cycle we are actually getting extra cost as one cycle always leads to +ve
So if there is any shortest weigted path it must be of linear in whihc max length n-1 edges
So in both cases after n-1 iteration both graphs shortest path weights will be sorted...
Time complexity:O(V*E)
____________________________________________________________________________________________________*/
vector<int> bellMan_Ford(int src,int n,vector<vector<int>> &edges){
    vector<int> dist(n+1,INT_MAX);
    dist[src]=0;
    for(int i=0;i<n-1;i++){
        for(auto &v:edges){
            if(dist[v[0]]!=INT_MAX and dist[v[0]]+v[2]<dist[v[1]])
             dist[v[1]]=dist[v[0]]+v[2];
        }
    }
    for(int i=2;i<=n;i++) cout<<dist[i]<<' ';
    return dist;
}
/*_________________________________________________________________________________________________
To detect we do exactly bellMan_Ford  but we do one more iteration at last
As for non-negative weight cylic graph the dist vector will have the minimum value of shortest path
after n-1 iteration.But for negative graph it keep on updating as we keep on increasing itreatipn
so at nth iteration if any value is updating in dist it means the graph is negative wighted cyclic
________________________________________________________________________________________________-*/
bool negative_Weight_Cycle(int n,vector<vector<int>> &edges){
    vector<int> dist(n,INT_MAX);
    dist[0]=0;
    for(int i=0;i<n;i++){
        for(auto &v:edges){
            if(dist[v[0]]!=INT_MAX and dist[v[0]]+v[2]<dist[v[1]])
             dist[v[1]]=dist[v[0]]+v[2];
        }
    }
    for(auto &v:edges){
        if(dist[v[0]]!=INT_MAX and dist[v[0]]+v[2]<dist[v[1]])
         return true;
    }
    return false;
}

/*____________________________________________________________________________________________________

Articulation Points:It is a vertex in graph whose removal from the graph increases its number of
connected components.
We need following arrays for this algorithm:
Discovery Array:It keeps track at time at which a particula node v visited 
Low array:It keeps the lowest discovery value node which the current node can reach upon removing
the whole path currnt node had travelled.

       1-----------4---------5
       |           |         |
       |           |         |
       |           |         |
       2-----------3---------6

Let us do dfs from 1 then dfs traversal will be 1(1)->3(2)->4(3)->5(4)->6(5)
low[4]=1; because although it we remove path 1->3->4 the 4 can still reach node 1 which has min_disc value
----------------------------------------Algorithm----------------------------------------------------
We try to build above two arrays in a single dfs traversal
we intiliase the low and disc for current node with current time value
Upon iteration over dfs we check 3 condition
C1:If the current node is parent then we continue;
C2:if the current node is visited then it must have lowest discovery time and we are gettting 
path to that node so low[node]=min(low[node],low[x]);
C3:if the current node is unvisited then we do dfs traversal on the neigbor upon backtracking
we update low[node]=min(low[node],low[x]);

Current node will be an articluation point if any of its neighbor low value is less than or equal
to current node's discovery value i.e., disc[node]<=low[x]
Basically what low[x] impiles is the minimum discovery node without the current path
if it is greater than disc[node] then it cannot reach the node again without the current path
which indirectly means if the current node is removed then the graph gets disconnected as current node
and any of its less discovery values cannot be reached which increases in connected components,thus
the definition of articulation point.so current node will be an artuclation point.
--->We keep a bool array for articulation points thus no duplicates arrive
--->The given algo will not work for src node as no node will have low value less than src node as
dfs starts from source.
Inorder to achive that we maintain count of dfs calls from src node if it is >=2 then it willl be articluation
point.if its not then all the nodes will be visisted which restrict to count to 1
---->Most important observation is that when we are getting already visited neighbor we are updating
low[node] with disc[x] while when we are baktracking after doing dfs call over unvisited visited
we are updating low[node] with low[x] value
if(vis[x]==true) low[node]=min(low[node],low[x]);
else dfs(x)->low[node]=min(low[node],low[x]);
--->Reason:
 If we observe by doing dfs call for above graph 1->2->3->4->5->6
 at 6 the 3 is  a visited neightbor whichg has low[3]=1
 if we try to update low[6]=min(low[6],low[3])=1 which means there is a path from 6->1 without the
 current path 
 The path will be 6-3->4->1 here 3->4 should be removed but it has followed
 Basically if we update with low value the path will cross the npath which needs to be removed
 but if we update it with disc[3] then the edge will reach 3 it never crosses.
 So we should update it with low[6]=min(low[6],disc[3]);
 _____________________________________________________________________________________________________
*/
void dfs(int node,int parent,vector<bool> &vis,vector<bool> &isArtPoint,vector<int> &disc,vector<int> &low,vector<vector<int>> &graph,int &time){
      vis[node]=true;
      disc[node]=time;
      low[node]=time;
      time++;
      int count=0;
      for(auto &x:graph[node]){
          if(x==parent){
           continue;
          }else if(vis[x]==true){
              low[node]=min(low[node],disc[x]);
          }else {
            count++;
            dfs(x,node,vis,isArtPoint,disc,low,graph,time);
             low[node]=min(low[node],low[x]);
             if(parent==-1){
                if(count>=2) isArtPoint[node]=true;
             }else{
                if(disc[node]<=low[x]) 
                  isArtPoint[node]=true;
             }
          }
      }
    return;
}
int articulationPoints(int n,vector<vector<int>> &edges){
   vector<vector<int>> graph(n+1);
   for(auto &v:edges){
      graph[v[0]].push_back(v[1]);
      graph[v[1]].push_back(v[0]);
   }
   vector<int> disc(n+1),low(n+1);
   vector<bool> vis(n+1,false),isArtPoints(n+1,false);
   int time=1;
   dfs(1,-1,vis,isArtPoints,disc,low,graph,time);
   int artPoints=0;
   for(int i=1;i<=n;i++) artPoints+=(isArtPoints[i]);
   return artPoints;
}
void dfsBridge(int node,int parent,int &time,vector<bool> &vis,vector<int> &low,vector<int> &disc,vector<vector<int>> &graph,vector<vector<int>> &ans){
    vis[node]=true;
    low[node]=disc[node]=time;
    time++;
    for(auto &x:graph[node]){
        if(x==parent) continue;
        else if(vis[x]==true) low[node]=min(low[node],disc[x]);
        else{
            dfsBridge(x,node,time,vis,low,disc,graph,ans);
            low[node]=min(low[x],low[node]);
            if(disc[node]<low[x]) ans.push_back({node,x});
        }
    }

}
vector<vector<int>> edgeBridges(int n,vector<vector<int>> &edges){
    vector<vector<int>> graph(n);
    for(auto &v:edges){
        graph[v[0]].push_back(v[1]);
        graph[v[1]].push_back(v[0]);
    }
    vector<int> disc(n),low(n);
    vector<bool> vis(n,false);  
    vector<vector<int>> ans;
    int time=0;
    dfsBridge(0,-1,time,vis,low,disc,graph,ans);
    return ans;
}
/*https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/*

_____________________________________Approach_____________________________________________________
Here we can observe that type 3 edges are most optimal edge for both Alice and Bob as this edge allows
both Alice and Bob to travel.
So we are going to sort the array bases on the type .Type 3 will come first
we are going to add these edges in our graph and after this if any type of duplicate edge comes
{can be alice or bob type} we can remove that edge as we already added this edge
we keep count of vertices that are connected and after all edge traversal if the count for both
alice and bob is n then we are able to connect the graph for both so we are going to return edgeremove
count else we return -1(as we are not able to connect them)
_____________________________________________________________________________________________________
*/
int find(int x,vector<int> &parent){
    if(parent[x]==x) return x;
    else return parent[x]=find(parent[x],parent);
}
bool _union(int x,int y,vector<int> &parent,vector<int> &pRank){
    int px=find(x,parent);
    int py=find(y,parent);
    if(px!=py){
        if(pRank[px]>pRank[py]) parent[px]=py;
        else if(pRank[py]>pRank[px]) parent[py]=px;
        else{
            parent[py]=px;
            pRank[px]++;
        }
        return true;
    }
    return false;
}
int maxEdgeRemoval(int n,vector<vector<int>> &edges){
    sort(begin(edges),end(edges),[](const vector<int> &a,const vector<int> &b){
            return a[0]>b[0];
    });
    vector<int> parentA(n+1),pRankA(n+1,1),parentB(n+1),pRankB(n+1,1);
    for(int i=1;i<=n;i++) {
        parentA[i]=i;
        parentB[i]=i;
    }
    int countAlice=1,countBob=1,edgeRemove=0;
    for(int i=0;i<edges.size();i++){
        if(edges[i][0]==1){
            if(_union(edges[i][1],edges[i][2],parentA,pRankA)) countAlice++;
            else edgeRemove++;
        }else if(edges[i][0]==2){
             if(_union(edges[i][1],edges[i][2],parentB,pRankB)) countBob++;
             else edgeRemove++;
        }else{
            bool edgeAlice=_union(edges[i][1],edges[i][2],parentA,pRankA);
            bool edgeBob=_union(edges[i][1],edges[i][2],parentB,pRankB);
            if(edgeAlice) countAlice++;
            if(edgeBob) countBob++;
            if(edgeAlice==false and edgeBob==false) edgeRemove++;
        }
        cout<<countAlice<<" "<<countBob<<'\n';
    }
    
   return (countAlice==n and countBob==n)?edgeRemove:-1;
}
int main()
 {
    freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // int n,m;cin>>n>>m;
  //  vector<vector<int>> edges(m,vector<int>(3));
//for(int i=0;i<m;i++) cin>>edges[i][0]>>edges[i][1]>>edges[i][2];
    //bellMan_Ford(1,n,edges);
    //cout<<negative_Weight_Cycle(n,edges);
   // cout<<articulationPoints(n,edges);
   //cout<<maxEdgeRemoval(n,edges);
    cout<<pow(10,-2);
    return 0;
 }
