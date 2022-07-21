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
//This is an example of minimum spanning tree problem using Kruskal's Algorithm
//Minimum spaning tree or a minimum weight spanning tree for weighted,connected and and undir
//ected graph is a spanning tree with a weight less than or equal to  the weight of every 
//other spanning tree
//We should remove the edges in the graph such that graph is still connected and
//and it should have minimum cost of edges
//For this here we define a class with 3 attributes a,b to show the edge between a and b
//and there is weight variable for the value of the edge of the graph
//In this kruskal's Algorithm we used disjoint set union data structure for minimum spanning tree
//and for better complexity we used path compression techniques
//Step1:We will sort the edges as per their weights
//We will maintain a varible sum outside and we traverse by order of ascending order and 
//wwe encounter two edges which are not already connected then this must be minimum edge 
//that we should include in our final state as we haven't got any less wighted edge before this
//edge for connecting these componnents
//So we will add this weight to the sum as it counts to final state
//If we encounterd any edge that is already connected then there is no need to take this edge
//We simply can remove that edge as the graph is already connected by small weighted edges
//So we wont add this in our final sum value
class Edges{
    public:
    int a;
    int b;
    int w;
};
//Here we created a vector of user defined type edges
vector<Edges> edg(100000);
vi parent(100000,-1);
//As we are sorting the vector of edges we need to explicitly mention the comprartor
bool comp(Edges a,Edges b)
{
    if(a.w<b.w) return true;
    else return false;
}
//Path compression of find_set in disjoint_union data structure
int find_set(int a)
{
    if(parent[a]==-1) return a;
    else return parent[a]=find_set(parent[a]);
}
void union_set(int a,int b)
{
    a=find_set(a);
    b=find_set(b);
    if(a!=b) parent[b]=a;
    else return;
}
vi level;
vi vis;
vii graph;
vii par;
void dfs(int node,int d)
{
   vis[node]-true;
   level[node]=d;
   for(auto &child:graph[node])
   {
       if(vis[node]==false)
       {
           dfs(child,1+d);
       }
   }
}
//Novice Approach for finding the lowest common ancestor
//here we maintain a distamce array and we will check the levels of both the nodes
//Since we have tp backtrack in this novice approach we should maintain a parent vector of vectors
//that mainrains the info of the parent
//So we will select the node which is at greater level wrt to another node
//here we caluclate the level difference between two levels and we will keep backtracking 
//until the level difference between them becones 0
//once both the levels are reached then we will backtrack both thse nodes until
//each of their parent nodes becomes equal
//Once they become equal that parent[a] will be our lowest common ancestor of both the nodes
//we return the parent[a]
//This novice approach has the complexity of O(n) as if the tree is linear it has to back
//jump all the way from leaf to root in this approach
int Lowest_Common_Ancsetor(int a, int b)
{
   int d;
   //if the level[a] >level[b] swap(a,b) as we will doing the operation with a being at 
   //less height and b at lower height
   if(level[a]>level[b]) swap(a,b);
   //caluclated the level differnce
   d=level[b]-level[a];
   //here we will keep backtracking until the difference becomes 0
   while(d--) b=parent[b];
   //now as both the nodes are at same level before further backtracking both the nodes we
   //will keeep backtrack we check the condition whether they are in same path
   //if they are if same path then the node which is at lower level will be the common ancestor 
   //for both the nodes
   if(a==b) return b;
   while(parent[a]!=parent[b])
    a=parent[a],b=parent[b];
  return parent[a];
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,m;cin>>n>>m;
    // for(int i=0;i<m;i++)
    //  cin>>edg[i].a>>edg[i].b>>edg[i].w;
    //  sort(edg.begin(),edg.begin()+m,comp);
    //  int sum=0;
    //  for(int i=0;i<m;i++)
    //  {
    //     int x=find_set(edg[i].a);
    //     int y=find_set(edg[i].b);
    //     //Here we are chceking the parents of forth coming edges if they are in same connected
    //     //component then there is no need to add their edge weight value to the sum
    //     if(x!=y)
    //     {
    //         //Here we are adding the edge weight
    //         sum+=edg[i].w;
    //         //if they are not connnected then we will union both the values
    //         union_set(edg[i].a,edg[i].b);
    //     }
    //  }
    //  cout<<sum<<'\n';
    graph.resize(n+1);
    vis.resize(n+1);
    parent.resize(n+1);
    level.resize(n+1);
     int a, b;
    while(m--)
    {
          cin>>a>>b;
          graph[a].pb(b);
          //here we maintained a parent vector for storing all parents 
          parent[b]=a;
    }
    dfs(1,0);
    cout<<Lowest_Common_Ancsetor(9,5);
    //for(int i=1;i<=n;i++) cout<<parent[i]<<' ';
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 