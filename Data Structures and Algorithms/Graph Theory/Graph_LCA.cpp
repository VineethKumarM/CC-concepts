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
//this is the algoritm=hm for findingthe lowest common ancestor of both the  nodes 
//Some of the properties of the common ancestor  properties
//when both the nodes lie on the same path then the nodwe which is coming first will be
//the lowest common ancestor of both the nodes
//The lowest comon ancestor will alwasy lie on the shortest path for travelling from
//one node to another node
//problem with the naive approach is that it is taking the time complexity of O(n)
//Time complexity is more because when we are backtracking from the node we are backtarcking
//at a step of 1 for ecah node
//this make the complexity of O(n) when 1 node is at root and another root is at 
//leaf node and they are on the same path
//Inorder to avoid we can use binary lifting where we take complete n steps in
//logn time 
//for example if d is the differnce between the heights of  2 nodes and  let l be the 
//step that is taken
//then l is taken in such away that
//i)l<=d ii)l is max power of 2^m that is less than value of d
//At each step of d we are reducing d atleast 1/2 so the complexity of reaching is o(logn)
//time
//Inorder to reach the l distance in one step go we should know the parents of each node at that
//distance 
//for examble for a node n, we will make a table for 2^0,2^1,2^2,...upto 2^maxn
//where maxn=log2(n);
//For filling the table we can use the dp technique 
//since we want 2^ith parent of current node then 2^ith can be writtten as 2*(2^i-1)
//It impies that if we know the current node's 2^(i-1)th parent and then we can build 
//2^ith parent
//For example since the 2^(i)=(2*(2^(i-1))) then let the par be parent of (2^(i-1))th 
//node of the current node
//as 2^(i) th parent will be 2*(2^(i-1)) therdefore 2^ith will be 2^(i-1)th parent of 
//par node as it is twice from the given realtion
//since all the i-1 are already caluclated in the dp table then we can 
//construct the table
//Since there are max of logn needs to be stored the space complexity will be S(n*logn)
//f0r storing each node
//inorder to store 2^0th  parent we can make a dfs tree traversal
vii graph;
vi height;
int LCA[100][100];
vi vis;
int n,m;
//this function caluclates the height of each node from the parent
void dfs_height(int node,int d)
{
    vis[node]=true;
    height[node]=d;
    for(auto &child:graph[node])
    {
        if(vis[child]==0)
         dfs_height(child,d+1);
    }
}
//This allocates all the 2^0th parents to all nodes
//Note that this is the method of dfs traversal without using the visited array
//It may ask in interviews
//It keeps the parents track it will allow all the nodes except the parent
//because parent is already visited
void dfs(int node,int par)
{
    LCA[node][0]=par;
    for(auto &child:graph[node])
    {
        if(child!=par)
        dfs(child,node);
    }
}
//This is the initilasiatoon of dp table
void init(int n)
{
    //Dfs height caluclation
    dfs_height(1,0);
     int maxn=log2(n);
     //intiases all the values with -1 value    
    for(int i=0;i<=maxn;i++) for(int j=0;j<=n;j++) LCA[i][j]=-1;
    //This function assigns all the 0 parents
    dfs(1,-1);
    //Since the dp table shpuld he filled in col order we started with j then i
    //Let us define state of dp[i][j] as 2^j th parent of ith node
    //if we want to fing 2^j th parent we must know j-1th parent
    //If the 2^j-1 th parent is -1 then 2^j th parent will be also -1
    //the j loop runs from 1 to maxn
    for(int j=1;j<=maxn;j++) for(int i=1;i<=n;i++)
    {
        //checks the conditions for j-1 th parent
        if(LCA[i][j-1]!=-1)
        {
            //intermediate node of dp[i][j]
            //par will be dp[i][j-1] 2^(i-1)
            int par=LCA[i][j-1];
            //then LCA[i][j] will be 2^(j-1)th parent of par node
            LCA[i][j]=LCA[par][j-1];
        }
    }
}
int Lowest_Common_Ancestor(int a,int b,int n)
{
    //inorder to avoid the negative distance
    if(height[a]>height[b]) swap(a,b);
    int d=height[b]-height[a];
    int maxn=log2(n);
    //We are reducing the lowest node level until both the nodes come at same level
    while(d)
    {
          int maxd=log2(d);
          // we are assingning b maxd node for distance d 
          b=LCA[b][maxd];
          d-=(1<<maxd);
    }
    //if they are in the same path then they wil reach the same node
    //if both the nodes are at equal then return thr e node
    if(a==b) return b;
    //if they are not on the same path here the problem comes with the 
    //O(n) complexity
    //as we don't know at which distance from the level they are sharing the common
    //ancestor so we should traverse back at step length 1
    //This willa again turn it into O(n) complexity
    //here also we will use the binary concept poblem
    //as at max there will be 2^(maxn) nodes(as when the root are at leaf level
    //in different subtrees we tarverse from i=maxn and we will traverse back
    //If the maxn parents exist then we will update the value a=LCA[a][i] and if the value
    //at LCA[a][i]=-1 it means no such parent at that much height exists
    //then we reduce height 
    //With the LCA[a][i]!=-1 we should put another condition that LCA[a][i]!=LCA[b][i]
    //as we may  missout the nodes which are at back that are lower than that
    //as we are traversing from top
    //the exexurtion will step at the childs of lCA  a and b)
    //The present parent of a node will be LCA as the i=0 2^0 th parent is same 
    //the for loop stopexecuting
    //Note that it is recursive call after updating a value in between LCA and 
    //a the for loop executes again to minimiste until 2^0 th parent will be LCA
    for(int i=maxn;i>=0;i--)
    {
        if(LCA[a][i]!=-1 and (LCA[a][i]!=LCA[b][i]))
          a=LCA[a][i],b=LCA[b][i];
    }
    //here we retrun LCA[a][0]
    return LCA[a][0];
}
//Function for caluclating the distance between any two nodes of a tree using LCA
//we find the height of both nodes from trees and we subtract the height of LCA twice as 
//it was caluclated twicely for each node 1 time and we wont take into account that distance
//for caluclating the distance between two nodes
int getdistance(int a,int b,int n)
{
    init(n);
    int lca=Lowest_Common_Ancestor(a,b,n);
    return height[a]+height[b]-2*height[lca];
}

int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
     cin>>n>>m;
     graph.resize(n+1);
     vis.resize(n+1);
     height.resize(n+1);
     int a,b;
     while(m--)
     {
         cin>>a>>b;
         graph[a].pb(b);
         graph[b].pb(a);
     }
    // dfs_height(1,0);
    // cout<<height[5];
     //init(n);
     //<<LCA[8][1];
     //cout<<LCA[3][0];
     cout<<getdistance(9,6,n);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 