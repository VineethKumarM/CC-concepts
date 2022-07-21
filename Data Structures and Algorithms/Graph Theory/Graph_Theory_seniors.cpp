#include<bits/stdC++.h>
using namespace std; 
#define ll long long int
#define ull unsigned long long int
#define vi vector<int>
#define vil vector<ll>
#define vb vector<bool>
#define vc vector<char>
#define vull vector<ull>
#define vf vector<float>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define uint_64t unsigned ll
#define int_64t  ll
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 10000
#define mod1 1e9+7
#define MAX 3000
vb vis;
vii graph;
vi val;
//Depth First Search Algorithm(DFS)
void dfs(int node)
{
    vis[node]=true;
    //cout<<node<<' ';
    for(auto &child:graph[node])
    {
        if(vis[child]==false)
          dfs(child);
    }
}
//Depth First Search To find an element exists or not
bool dfs_Find_val(int node,int find)
{
    vis[node]=true;
    if(val[node]==find) return true;
    for(auto &child:graph[node])
    {
        if(vis[child]==false){if(dfs_Find_val(child,find)) return true;}
    }
    return false;
}
void bfs(int node)
{
    vis[node]=true;
    queue<int> q;
    q.push(node);//Here we are pushing the current node into stack
    //cout<<node<<' ';
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        //Here we are using queue data structure as it pushes all the same level 
        //nodes and pops one after other
        for(auto &x:graph[t])
        {
            if(vis[x]==false) 
             {
                 //If the node yet visited then we are pushing into stack and making 
                 //the  visieted bool array as true as for that particular node
                 q.push(x);
                 vis[x]=true;
                 //cout<<x<<' ';
             }
        }
    }
}
//Problem of minimum distance from non flooding city
vi dist;
void bfs_min_dist(vi safenodes)
{
    queue<int> q;
    //If there is only one safenode then we can push that into queue and
    //we cab caucalte the minimum distance by bfs traversal
    // dist[node]=0;
    // q.push(node);
    // vis[node]=true;
    //But in case we are having safe nodes more than one then we will pass the whole array
    //to functino and push all the dsafe nodes before pushing firstnode childs
   // we will caluclate min distance for each safe node then we will cout the distance
   for(auto &x:safenodes)
   {
       dist[x]=0;
       q.push(x);
       vis[x]=true;
       //By pushing all the safe elements to the asssign we are only asssignng the 
       //values to itschild nodes for each safe node
       //because we are sure that min distance is 1 and making that visited node as true
    
   }
    while(!q.empty())
    {
        int t=q.front();
        //Most impoertant part of bfs is that we can always keep a track of parent nodes
        //So that they can be used in future
        q.pop();
        for(auto &x:graph[t])
        {
            if(vis[x]==false)
            {
                dist[x]=dist[t]+1;//Sinec for each safe node the child nodes distance is 1
                //from its parent node
                q.push(x);
                vis[x]=true;
            }
        }
        
    }
}
//Function to count number of leafnodes;
int  num_leafnodes=0;
void dfs_count_leaf(int node)
{
    vis[node]=true;
    int count=0;
    for(auto &x:graph[node])
    {
        if(vis[x]==false)
        {
            dfs_count_leaf(x);
            count++;
        }
    }
    if(count==0) num_leafnodes++;
}
//To find the number of connected components
int dfs_components(int n)
{
   int count=0;
    for(int i=1;i<n+1;i++)
    {
        if(vis[i]==false)
        {
            dfs(i);
            count++;
        }
    }
    return count;
}
//To find the no of subtrees taking that node as parent node
//From the recursion point of view
//We assume that this function return the total subterees of the child
//So we will itearte for each child of the parent then add the all subtrees of the child
//for the respective parent and atlast we will increment it by one 
//we will return the subtress of that node
vi ans;
int dfs_subtree(int node)
{
    vis[node]=true;
    for(auto &x:graph[node])
    {
        if(vis[x]==false)
        {
            ans[node]+=dfs_subtree(x);
            //Here we areadding all the subtree of child
        }
    }
    ans[node]+=1;
    //We are incrementing it by 1 since we are including that parent node also
    return ans[node];
}
int bfs_maxlevel_sum(int node)
{
    int ans=0;
    queue<int> q;
    q.push(node);
    vis[node]=true;
    while(!q.empty())
    {
        int n=q.size();
        int cur_lev_sum=0;
        //For caluclating currentlevl sum
        //Upto the current size of q it will push all the childs of current level parents
        //and pop all the parents and currelevel sum to caluclate all the currrlevel 
        //values of all parents
        //ans is encountered to keep track of the maximum value
        //This for loop is used to caluclating the current level sun
        for(int i=0;i<n;i++)
        {
            int t=q.front();
            vis[t]=true;
            cur_lev_sum+=val[t];//here before we are popping the parent we are summing \
    //curr level sum
            q.pop();
            //Here we are pushing the childs of from the same level parents
            for(auto &x:graph[t])
            {
                if(vis[x]==false)
                {
                    q.push(x);
                    vis[x]=false;
                }
            }
        }
        ans=max(ans,cur_lev_sum);
    }
    return ans;
}
//Function to find the cyclicity of 
bool dfs_cyclicity(int node)
{
    vis[node]=true;
    for(auto &child:graph[node])
    {
        if(vis[child]==true and child!=node)
         return true;
         else
          dfs(child);
    }
    return false;
}
vi vis_state;
bool f=false;
//For directed graph we can't use above algo as it will give the wrong answer
//Inorder to avoid we will declare visited array and state some states to the visited array
//State 0: not visited yet
//State 1:visited but it is under procee i.e., its childs are on call now
//State 2:fully visited and there is no child that is unvisited
//If we encounter any node that is state in 1 and it was the child present parent which is
//the child of state  1 node then we encounterd the cycle then we retunr true;
//if we want to find the number o cycle then maintain a  counter variable
void dfs_dir_cyclicity(int node)
{
    vis_state[node]=1;
    for(auto &child:graph[node])
    {
        if(vis_state[child]==1) f= true;
        else if(vis_state[child]==0) dfs_dir_cyclicity(child);
    }
    vis_state[node]=2;
}   
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;cin>>n;//Nodes
    graph.resize(n+1);
    vis.resize(n+1,false);
    int m;cin>>m;//Edges
    int k;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        //k=u; a temp variable to store any one node of the graph
        graph[u].pb(v);
        //graph[v].pb(u);For directed graph only one way is assigned
    }
   // int x;cin>>x;
   // val.resize(n+1);
//    int x;cin>>x;
//    vi safenodes(x);
//     for(int i=0;i<x;i++) cin>>safenodes[i];
//     dist.resize(n+1);
//     bfs_min_dist(safenodes);
//     for(int i=1;i<n+1;i++) cout<<dist[i]<<' ';
     //cout<<dfs_Find_val(1,17);
     //bfs(1);
   //  dfs_count_leaf(1);
 // cout<<dfs_components(10);
     //cout<<num_leafnodes;
    //  ans.resize(n+1,0);
    //  dfs_subtree(1);
    //  for(int i=1;i<n+1;i++) cout<<ans[i]<<' ';
    //   val.resize(n+1);
    //   for(int i=1;i<n+1;i++) cin>>val[i];
    //   cout<<bfs_maxlevel_sum(1);
    //cout<<dfs_cyclicity(1);5

     vis_state.resize(n+1,0);
    dfs_dir_cyclicity(1);
      cout<<f;
    //cout<<dfs_components(n);
 
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}
