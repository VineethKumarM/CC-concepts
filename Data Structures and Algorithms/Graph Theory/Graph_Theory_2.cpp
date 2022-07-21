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
vii graph;
vi vis;
vi res;
vi indegree;
int n,m;
//Khan's Algorithm
//This algo is for directed graph
//In Khan's Algorithm we first choose all the nodes which has indegree equal to 0
//Then while(!q.empty()) we pop the current element and remove all edges by making inderee[child]--
//and if the indegree[child]==0 then we push the child into queue
//Before popping the current element in the queue we will push_back into res vector
void Topological_Sort(int n)
{
   queue<int> q;
   for(int i=1;i<=n;i++)
   if(indegree[i]==0) q.push(i);
   while(!q.empty())
   {
       int cur=q.front();
       q.pop();
       res.pb(cur);
       for(auto &child:graph[cur])
       {
          indegree[child]--;
          if(indegree[child]==0)
          q.push(child);
       }
   }
}
//The property of topological order is that when we represent the nodes in the topological orde
//then all the edges will be towards right
//i.e,,for any vertex v in the topological order all the children's position in res vector
//is always ind[node]<ind[child]
//so here we mapped the value of vector into its index value in the map
//check the remaining property
bool is_topological(vi v)
{
    unordered_map<int,int> mp;
    for(int i=0;i<v.size();i++)
    mp[v[i]]=i;
    for(int i=0;i<v.size();i++)
    {
        int node=v[i];
        if(graph[node].size())
        {
            for(auto &child:graph[node])
            {
                if(mp[child]<mp[node]) return false;
            }
        }
    }
    return true;
}
//Lexographically topological sort
//Since the topological sort is not unique in this problem we have to print the 
//the vector which is lexographically smaller if the topological sort exists else return fakse
//for the first condition we can use the priroity queue with greater int comparator
//so that minimum value will be at the top of the queue
//so we push back them in this order so that we can get lexographically smaller value
//if the graph contains any cyclicity then there will be no topological sort
//so to check that we can compare the res.size and n value
//if the sort order exists then they both will be equal therefore return res.size()==n
bool small_topological_sort(int n)
{
    //to get the min value at the top
    priority_queue<int,vector<int>,greater<int>> q;
    for(int i=1;i<=n;i++)
    if(indegree[i]==0) q.push(i);
    while(!q.empty())
    {
        //in case of priority queue top class exists not front
        int cur=q.top();
        q.pop();
        res.pb(cur);
        for(auto &child:graph[cur])
        {
            indegree[child]--;
            if(indegree[child]==0)
            q.push(child);
        }
    }
    //for checking valid topological sort order
    return res.size()==n;
}
bool visited[1001][1001];
int arr[1001][10001];
int dist[10001][1001];
vi dx={-1,0,1,0};
vi dy={0,1,0,-1};
bool is_valid(int x,int y)
{
    if(x<1 or x>n or y<1 or y>m) return false;
    if(visited[x][y]) return false;
   // if(visited[x][y] or arr[x][y]==0) return false;
    return true;

}
//grid_dfs is the dfs traversal through dfs where two cells are said to be connected if they 
//share any common sides
//so we check if is valid cell or not by the boundary conditions and is already visited or
//not and make the moves as left,right,down and up
void grid_dfs(int x,int y)
{
    visited[x][y]=true;
   // cout<<x<<' '<<y<<' '<<'\n';
    for(int i=0;i<4;i++)
    if(is_valid(x+dx[i],y+dy[i]))
     grid_dfs(x+dx[i],y+dy[i]);
}
int connected_components(int n,int m)
{
    int cnt=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    {
        if(arr[i][j] and visited[i][j]==0)
        {
            grid_dfs(i,j);
            cnt++;
        }
    }
    return cnt;
}
void bfs_grid(int x,int y)
{
    queue<pairi> q;
    cout<<x<<' '<<y<<'\n';
    q.push({x,y});
    dist[x][y]=0;
    visited[x][y]=true;
    while(!q.empty())
    {
        int curx=q.front().first;
        int cury=q.front().second;
        q.pop();
        for(int i=0;i<4;i++)
        {
            if(is_valid(curx+dx[i],cury+dy[i]))
            {
                int newx=curx+dx[i];
                int newy=cury+dy[i];
                dist[newx][newy]=dist[curx][cury]+1;
                visited[newx][newy]=true;
                q.push({newx,newy});
                cout<<newx<<' '<<newy<<'\n';
            }
        }
    }
}
//In this problem we are given a char grid in which p represnts path t represnts tree
//e represnts destination and s represnets starting node
//and we should return the minimum no of steps taken to reach the destination cell e from the
//starting cell
//here we will do the bfs traversal and we will maintain dist array to mainatain the distance
//increment level by level
char jung[31][31];
bool isvalid_cell(int x,int y)
{
    if(x<1 or x>n or y<1 or y>m) return false;
    if(visited[x][y] or jung[x][y]=='T') return false;
    return true;
}
int min_jungle_path(int x,int y)
{
    queue<pairi> q;
    visited[x][y]=1;
    dist[x][y]=0;
    q.push({x,y});
    while(!q.empty())
    {
        int curx=q.front().first;
        int cury=q.front().second;
        q.pop();
        for(int i=0;i<4;i++)
        {
            if(isvalid_cell(curx+dx[i],cury+dy[i]))
            {
                int newx=curx+dx[i];
                int newy=cury+dy[i];
                visited[newx][newy]=1;
                dist[newx][newy]=1+dist[curx][cury];
                q.push({newx,newy});
                if(jung[newx][newy]=='E') return dist[newx][newy];
                
            }
        }
    }
    return -1;
}
bool is_valid_knight_move(int x,int y)
{

    if(x<1 or x>n or y<1 or y>m) return false;
    if(visited[x][y]) return false;
    return true;
}
int dkx[]={-2,-1,1,2,2,1,-1,2};
int dky[]={1,2,2,1,-1,-2,-2,-1};
int min_knight_moves(int x,int y,int destx,int desty)
{
    queue<pairi> q;
    visited[x][y]=true;
    dist[x][y]=0;
    if(x==destx and y==desty) return dist[x][y];
    q.push({x,y});
    while(!q.empty())
    {
        int curx=q.front().first;
        int cury=q.front().second;
        q.pop();
        for(int i=0;i<8;i++)
        {
            if(is_valid_knight_move(curx+dkx[i],cury+dky[i]))
            {
                int newx=curx+dkx[i];
                int newy=cury+dky[i];
                dist[newx][newy]=1+dist[curx][cury];
                visited[newx][newy]=true;
                q.push({newx,newy});
                if(newx==destx and newy==desty) return dist[newx][newy];
            }
        }
    }
    return -1;
    
}
vii transpose;
vi order;
vi ssc;
vi taste;
void kosaraju_dfs1(int node)
{
    vis[node]=true;
    for(auto &child:graph[node])
    {
        if(vis[child]==0)
        kosaraju_dfs1(child);
    }
    order.pb(node);
}
void kosaraju_dfs2(int node)
{
    vis[node]=true;
    for(auto &child:transpose[node])
    {
        if(vis[child]==0)
         kosaraju_dfs2(child);
    }
    ssc.pb(node);
}
int solve_chefrun(int n)
{
    for(int i=0;i<n;i++) cin>>taste[i];
    int res=0;
    for(int i=0;i<n;i++)
    {
        int a=i;
        int b=(taste[i]+a+1)%n;
        graph[a].pb(b);
        transpose[b].pb(a);
    }
        for(int i=0;i<n;i++)
         if(vis[i]==0)
         kosaraju_dfs1(i);
         for(int i=0;i<n;i++) vis[i]=false;
         for(int i=order.size()-1;i>=0;i--)
         {
            
             if(vis[order[i]]==0)
             {
                  ssc.clear();
                 kosaraju_dfs2(order[i]);
             if(ssc.size()>1) 
                 res+=ssc.size();
             }
         }
    return res;
}
vi in,low;
vb onstack;
stack<int> st;
int cnt_scc=0;
int timer=1;
void Tarjans_scc(int node)
{
   vis[node]=true;
   onstack[node]=true;
   low[node]=in[node]=timer++;
   st.push(node);
   for(auto &child:graph[node])
   {
       if((vis[child]==true) and (onstack[child]==true))
       {
           low[node]=min(low[node],in[child]);
       }
       else
       {
           if(vis[child]==0)
           {
               Tarjans_scc(child);
               if(onstack[child]==true) low[node]=min(low[node],low[child]);
           }
       }
   }
   if(low[node]==in[node])
   {
       cnt_scc++;
       int u;
       while(1)
       {
           u=st.top();
           st.pop();
           onstack[u]=false;
           cout<<u<<" ";
           if(u==node) break;
       }
       cout<<'\n';
   }
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // cin>>n;
  cin>>n>>m;
    graph.resize(n+1);
    vis.resize(n+1);
    indegree.resize(n+1,0);
    transpose.resize(n+1);
    in.resize(n+1);
    low.resize(n+1);
    onstack.resize(n+1,0);
    int a,b;
    while(m--)
    {
      cin>>a>>b;
      graph[a].pb(b);
     // transpose[b].pb(a);
      //indegree[b]++;
    }
    // for(int i=1;i<=n;i++)
    //   if(vis[i]==0) kosaraju_dfs1(i);
    // for(int i=0;i<vis.size();i++) vis[i]=0;
    // for(int i=order.size()-1;i>=0;i--)
    // {
    //     if(vis[order[i]]==0)
    //     {
    //          ssc.clear();
    //          kosaraju_dfs2(order[i]);
    //          for(int j=0;j<ssc.size();j++) cout<<ssc[j]<<' ';
    //          cout<<'\n';
    //     }
    // } 
    for(int i=1;i<=n;i++)
    if(vis[i]==0)
    Tarjans_scc(i);
    cout<<cnt_scc;
    //taste.resize(n);
    //cout<<solve_chefrun(n);
//     cout<<small_topological_sort(n)<<'\n';
//     for(int i=0;i<res.size();i++) cout<<res[i]<<' ';
//    // res[4]=5;res[5]=4;
//     cout<<'\n';
//     cout<<is_topological(res);
    //   for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    //    cin>>jung[i][j];
       //cout<<connected_components(n,m);
    //    bfs_grid(1,1);
    //    cout<<dist[3][3]<<' ';
    //cout<<min_jungle_path(1,1);
    //cout<<min_knight_moves(1,1,2,3);
    //cout<<dist[3][3];
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 