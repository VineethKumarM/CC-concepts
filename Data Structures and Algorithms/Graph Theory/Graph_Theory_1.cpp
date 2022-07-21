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
int n,m;
vii graph(1000001);
vi vis(1000001);
void dfs(int node)
{
    vis[node]=true;
    //cout<<node<<' ';
    for(auto &x:graph[node]) if(vis[x]==0) dfs(x);
    return;
}
int dfs_no(int node)
{
    int cnt=0;
    vis[node]=true;
    cnt+=1;
    for(auto &x:graph[node]) if(vis[x]==0) cnt+=dfs_no(x);
    return cnt;
}
pairi solve()
{
    int cnt=0;
    ll ways=1;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==false)
        {
            cnt++;
            ways=(ways*dfs_no(i))%mod;
        }
    }
    return {cnt,ways};
}
int Connected_Componets()
{
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==false)
        {
            cnt++;
            dfs(i);
        }
    }
    return cnt;
}
vi shrt;
void Shortest_Path(int node)
{
     vis[node]=true;
     for(auto &x: graph[node])
     {
         if(vis[x]==0)
         {
             shrt[x]=1+shrt[node];
             Shortest_Path(x);
         }
     }
    return;
}
//Given a graph we have to identity whether it is a tree's topology
//For a graph to be tree there are two conditions
//1.The connected componets in graph must be equal to 1
//There should be no cycle in graph in order to become a tree
//1 condition can be checked by connected components function 
//and for 2nd condition to identify whether a cycle is present 
//if the graph has n edges and connected components are 1 then if the no of edges
//are m=n-1 then no cycle is present
//if there are two nodes and to connect them 1 edge requred for remaining n-2 nodes n-2+1 edges are required
bool Is_Tree_Topology(int n,int m)
{
    return m==n-1 and Connected_Componets()==1;
}
vi col;
//Bipartite graph is a special graph such that you can divide the vertex set into 2
//disjoint sets such that
//1>Each vertex belongs to exactly oone of 2 sets
//2.Each edges connects 2 verices of 2 different sets
//Approach to the problem:
//we will avoid the diving the graph into vertices into two parts and chceks whether it is 
//following or not
//Inorder to avoid that we will colour all the set1 elements as 0 colour and the remaining set2
//as 1 
//If we take a node then we color them as 0 and color all the connected edges with 1 
//and vice versa i.e, if the node of our color is 1 and if vis[child]=false then colour it
//with 0
//Through the recurive function we will approach the problem with dfs calls
//if we take a node and check for all its child whether they can be biparted by ech child
//and vis[child] is already chid and check if col[child]=col[node] then return false
//as they should be different
bool Is_Bipartite(int node,int c)
{
     vis[node]=true;
     col[node]=c;
     for(auto &x:graph[node])
     {
         if(vis[x]==0)
         {
             if(Is_Bipartite(x,c^1)==false) return false;
         }
         else
         {
             if(col[x]==col[node]) return false;
         }
     }
     return true;
}
bool Bugs()
{
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==false)
        {
          if(Is_Bipartite(i,0)==false);return false;
        }
    }
    return true;
}
//Property of cyclicity in graph is that ut provides two alternative paths to go
//from one node to another node
bool Is_Cycled(int node,int parent)
{
   vis[node]=true;
   for(auto &x:graph[node])
   {
       if(vis[x]==0)
       {
           //If we get any cycle for further childs in graph then we can directly return true
           //and no need of proceeding further
           if(Is_Cycled(x,node)==true) return true;
       }
       else
       {
           //If we found any ancestor of node that is the child of current node then the 
           //cycle is present in node
           if(x!=parent) return true;
       }
   }
   //After checking all the nodes if we haven't found any cycle then returen false as the cycle 
   //is non cycled one
   return false;
}
vi intime;
vi outtime;
int timer=1;
//in and outtimes of a node are the respective times of the entering and leaving of nodes
//Here we will set the current timer to cuurent node
//and we increment the timer value and process all childs of the current node
//after processing all the child then we will come to root of the current node
//as we are leaving the current node so we will assign the timer value after all processed 
//childs
//then we will asign outime[node]=time and return the function
void in_out(int node)
{
    vis[node]=true;
    //First the current timer will get assigned to the intime of node then we will 
    //timer value get updated
    intime[node]=timer++;
    for(auto &x:graph[node])
    {
        if(vis[x]==0) in_out(x);
    }
    outtime[node]=timer++;
}
//This function returns the boolean value if for the given two nodes 
//whether one node is a part of subtree of another node 
//If the current node is in subtree of another node the intime of the current node must 
//greater than the child as first parent will be visited then after the child
//and the outime of child must be less than outime of node as it has to backtrack from
//child to reach the root node  
bool is_subtreed(int n1,int n2)
{
    in_out(n1);
    if(intime[n1]<intime[n2] and outtime[n1]>outtime[n2]) return true;
    else return false;
}
//We have to find the longest path in tree which is also called as rakter of tree
//Novice Approachis that make dfs calls for each node and find the max path 
//Time complexoty of the above code is O(n*n)
//We can get the solution using only two dfs calls
//Step 1: make dfs call at anywhere in the graph then find max node which is at the ma
//maximum distance of the current node then this node will be one of the 
//edges of the diameter
//make dfs call from this node thn we will get the max distant from the node
//Here we will make two global variables and maxend and maxdistance and as soon as we get
//the maxnode and maxd we will update them
int maxd=-1,maxend=0;
void Longest_Path(int node,int d)
{
    vis[node]=true;
    if(d>maxd){ maxend=node;maxd=d;}
    for(auto &x:graph[node])
    {
     if(vis[x]==0)
     {
         Longest_Path(x,d+1);
     }
    }
}
//Subtree problem
//In this problem we have to find subtree size for each node
//For this we will fix a root node and we will start caluclating from that node and update
//each nodes subtree size from that node
//In-prder to approach these type of problems we will atrt from root node and we will store
//the values in a vector
//we will find the subtree[node]=1+subtree[all childs]
//if the node is already visited then it cannnot be the child of the current node and it must 
//be the parent of the current node
//in that we wont add subtree[node]
//At last before returning thr function we will store them in subtree vector
vi subtree;
int dfs_subtree(int node)
{
    vis[node]=true;
    int curr_size=1;
    for(auto &x:graph[node])
    {
        //If the node is already visited then we wony add them in curr_size as they are parents
        if(vis[x]==0)
        {
            curr_size+=dfs_subtree(x);
        }
    }
    subtree[node]=curr_size;
    return curr_size;
}
vi sssp;
void sssp_bfs(int node)
{
    vis[node]=true;
    queue<int> q;
    q.push(node);
    sssp[node]=0;
    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        for(auto &x:graph[cur])
        {
            if(vis[x]==0) 
            {
                q.push(x);
                sssp[x]=1+sssp[cur];
                vis[x]=1;
            }
        }

    }
}
//Prime path
//In this problem we are goven with two prime numbers and we have to convert
//from one prime number to another prime number and by changing the digits without violaing
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
void bfs(int node)
{
    vis[node]=true;
    queue<int> q;
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
                vis[x]=1;
            }
        }
    }
}
bool feasible_relations(int n,int m)
{
    graph.resize(n+1);
    vis.resize(n+1);
    int a,b;
    vpii v;
    string op;
    while(m--)
    {
        cin>>a>>op>>b;
        if(op=="=")
        {
            graph[a].pb(b);
            graph[b].pb(a);
        }
        else 
        {
            v.pb({a,b}); 
        }
    }
    for(int i=0;i<v.size();i++)
    {
        bfs(v[i].first);
        if(vis[v[i].second]==1) return false;
    }
   return true;
}
//count of nodes at distance d from source node 
int no_of_node_at_d(int node,int d)
{
     vis[node]=true;
     queue<int> q;
     q.push(node);
     int curr_dist=0;
     while(!q.empty() and curr_dist!=d)
     {
        int cur_node=q.front();
        q.pop();
        for(auto &x:graph[cur_node])
        {
            if(vis[x]==0)
            {
                q.push(x);
                vis[x]=1;
            }
        }
        curr_dist++;
     }
     return q.size();
}
// Pick an arbitrary vertex of the graph root and run depth first search from it.
 //Note the following fact (which is easy to prove):

// Let's say we are in the DFS, looking through the edges starting from vertex v. 
//The current edge (v,to) is a bridge if and only if none of the vertices to and 
//its descendants in the DFS traversal tree has a back-edge to vertex v or any of 
//its ancestors. Indeed, this condition means that there is no other way from v to to except for edge (v,to).
// Now we have to learn to check this fact for each vertex efficiently.
// We'll use "time of entry into node" computed by the depth first search.
// So, let tin[v] denote entry time for node v. 
//We introduce an array low which will let us check the fact for each vertex v. 
//low[v] is the minimum of tin[v], the entry times tin[p] for each node p that is 
//connected to node v via a back-edge (v,p) and the values of low[to] for each vertex to which is a direct descendant of v in the DFS tree:
// low[v]=min(tin[v],tin[p],low[to]) for all p for which (v,p) is a back edge for 
//all to for which (v,to) is a tree edge
// Now, there is a back edge from vertex v or one of its descendants to one of its ancestors if and only if vertex v has a child to for which low[to]≤tin[v]. If low[to]=tin[v], the back edge comes directly to v, otherwise it comes to one of the ancestors of v.
// Thus, the current edge (v,to) in the DFS tree is a bridge if and only if low[to]>tin[v].
//Here we will maintain a intime vector and low time vector
//The in time vector denotes the discovery time of node at which the node is visited
//and low array for a node deb=notes minimum low time node to which it is connected other than its
//parent
//low array is the minimum of 3 following values
//i)discovery time of the current node
//ii)low time of all its childs
//iii) if there is a backedge then the minimum of all discovery times of all the backedges
//so for each child we should we find minimum of all these 3 cases
//first we will check if the child is parent or not if the child is not parent then we will 
//continue and we will do nothing
//if the child of a node is already visited then it means that the node is an ancestor
//and it is abcakedge in this case we will find the minimum of all the nodes
//if the node is not yet visited then we will make arecursive call for all its childs then
//minimise all the low value of its further childs 
//and at the time of backtracking we will find the minimum of all the low times of all the child
//as stated earlier we will find all the low time of all children of current node and assign this 
//value as low[node]
//for bridges the condition is that in[node]<low[node] then it is a bridge 
//here note that if the in[node]==low[node] then also the current backedge cannot be the bridge
vi in,low;
int time_r=0;
int cbridge=0;
void dfs_tree(int node,int p)
{
    vis[node]=true;
    low[node]=in[node]=time_r;
    time_r++;
    for(auto &x:graph[node])
    {
        if(x==p) continue;
        if(vis[x])
        {
            //if the node is already visited then it is a backedge then we are minimising
            //the low[node] through all the intime of all backedges
            low[node]=min(low[node],in[x]);
        }
        else
        {
            //If that is not the case then the mimise all the low values of remaining childs
        // and asssign the minimum value of all those nodes
            dfs_tree(x,node);  
            if(in[node]<low[x]) cbridge++;
            low[node]=min(low[node],low[x]);
        }
    }
}
vpii vp;
bool hasbridge;
void one_way_road(int node,int p)
{
    vis[node]=true;
    in[node]=low[node]=timer++;
    for(auto &x:graph[node])
    {
        if(x==p) continue;
        else if(vis[x])
        {
            low[node]=min(low[x],low[node]);
            if(in[x]<in[node])
            vp.pb({node,x});
        }
        else
        {
            one_way_road(x,node);
            if(in[x]<low[node]) 
            {
               hasbridge=true;
               return; 
            }
            low[node]=min(low[x],low[node]);
            vp.pb({node,x});
             
        }
    }
}
// Pick an arbitrary vertex of the graph root and run depth first search from it. Note the following fact (which is easy to prove):

// Let's say we are in the DFS, looking through the edges starting from vertex v≠root. 
// If the current edge (v,to) is such that none of the vertices to or its descendants in 
// the DFS traversal tree has a back-edge to any of ancestors of v, then v is an articulation point. Otherwise, v is not an articulation point.

// Let's consider the remaining case of v=root. This vertex will be the point of articulation if and only if this vertex has more than one child in the DFS tree.

// Now we have to learn to check this fact for each vertex efficiently. We'll use "time of entry into node" computed by the depth first search.

// So, let tin[v] denote entry time for node v. We introduce an array low[v] which will let us check the fact for each vertex v. low[v] is the minimum of tin[v], the entry times tin[p] for each node p that is connected to node v via a back-edge (v,p) and the values of low[to] for each vertex to which is a direct descendant of v in the DFS tree:

// low[v]=min⎧⎩⎨tin[v]tin[p]low[to] for all p for which (v,p) is a back edge for all to for which (v,to) is a tree edge
// Now, there is a back edge from vertex v or one of its descendants to one of its ancestors if and only if vertex v has a child to for which low[to]<tin[v]. If low[to]=tin[v], the back edge comes directly to v, otherwise it comes to one of the ancestors of v.

// Thus, the vertex v in the DFS tree is an articulation point if and only if low[to]≥tin[v].
//The observations regarding bridge edges and cut points are
//1.The end points of a brigdge can be atrticulation points if and only if the degree of that node
//is atleast 2
//Every end node of backedge cannot be the articulation point 
//There are cutpoints which are not the endpoints of backedges
//We proceed the algo same as finding bridges and we will check for in[node]<=low[child]
//then that node s=is an articulation point
//from this algo the root will always be an articulatio point as all values are greater than or
//equal to in[node]<=low[chiild]
//But root node cannot be the articulation point all the time
//as if it contains cyclicity with root then it will never be an articuation point
//So the root will be articuation point if and only if the root has more than one child in the dfs
//tree
//So we will maintain a varaible chidren and as we do dfs from the children of root we will
//increment the children value and at end if(parent==-1 and children>1) then we will insert
//the element into cut_points
//Here we are directl not maintaing the count variable for articulation points
//because a node call may repeat several times as we are doing calls as many as there are children
//so we will maintain a set that avoids the duplicates
//we will insert the nodes and at last we will cout the set size
//Here we will maintain a intime vector and low time vector
//The in time vector denotes the discovery time of node at which the node is visited
//and low array for a node deb=notes minimum low time node to which it is connected other than its
//parent
//low array is the minimum of 3 following values
//i)discovery time of the current node
//ii)low time of all its childs
//iii) if there is a backedge then the minimum of all discovery times of all the backedges
//so for each child we should we find minimum of all these 3 cases
//first we will check if the child is parent or not if the child is not parent then we will 
//continue and we will do nothing
//if the child of a node is already visited then it means that the node is an ancestor
//and it is abcakedge in this case we will find the minimum of all the nodes
//if the node is not yet visited then we will make arecursive call for all its childs then
//minimise all the low value of its further childs 
//and at the time of backtracking we will find the minimum of all the low times of all the child
//as stated earlier we will find all the low time of all children of current node and assign this 
//value as low[node]
//for bridges the condition is that in[node]<low[node] then it is a bridge 
//here note that if the in[node]==low[node] then also the current backedge cannot be the bridge
//one thing that differs from the articulation point is equal to condition if remove vertex then
//we will remove all edges so we cannot travel from one component which is not the case with bridges
//when the both values are equal then there is cyclicity and if we remove that backedge then
//there is another way to reach that vertex
//But since we remove all connected edges then there is no way ti reach
//so for vectex v in[v]<=low[child] then v is an articulation point
//since this calls runs as many times as there are no.of childs then we will maintain
//we will maintain a set inorder to count the vertices
vi tin;
vi tlow;
set<int> cut_points;
void find_cutpoints(int node,int p=-1)
{
    vis[node]=true;
    tin[node]=tlow[node]=timer++;
    int children=0;
    for(auto &child:graph[node])
    {
        if(child==p) continue;
        else if(vis[child])
        {
            tlow[node]=min(tlow[node],tin[child]);
        }
        else
        {
            find_cutpoints(child,node);
            tlow[node]=min(tlow[child],tlow[node]);
            if(tin[node]<=tlow[child] and p!=-1)
            cut_points.insert(node);
            children++;
        }
    }
    if(p==-1 and children>1) cut_points.insert(node);
}
int main()
{
    freopen("Input.txt", "r", stdin); 
     freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    int a,b;
    graph.resize(n+1);
    vis.resize(n+1,false);
    shrt.resize(n+1,0);
    col.resize(n+1);
    intime.resize(n+1);
    outtime.resize(n+1);
    in.resize(n+1);
    low.resize(n+1);
    while(m--)
    {
        cin>>a>>b;
        graph[a].pb(b);
        graph[b].pb(a);
    }
    tin.resize(n+1);
    tlow.resize(n+1);
    find_cutpoints(1);
    cout<<cut_points.size();
    // sssp.resize(n+1);
    // sssp_bfs(1);
    // for(int i=1;i<=n;i++) cout<<sssp[i]<<" ";
    //cout<<feasible_relations(n,m);
    //   dfs_tree(1,0);
    // cout<<cbridge;
    //one_way_road(1,0);
    // if(hasbridge) cout<<0<<'\n';
    // else
    // {
    //     for(auto &x:vp)
    //     {
    //         cout<<x.first<<' '<<x.second;
    //         cout<<'\n';
    //     }
    // }
    // subtree.resize(n+1);
    // dfs_subtree(1);
    //for(int i=1;i<=n;i++) cout<<subtree[i]<<' ';

    // Longest_Path(1,0);
    // maxd=-1;
    // for(int i=0;i<=n;i++) vis[i]=false;
    // Longest_Path(maxend,0);
    // cout<<maxd<<" ";
    
     // pair p=distance(1);
    // cout<<p.first<<' '<<p.second;
    // dfs(1);
    //cout<<Connected_Componets();
    //Shortest_Path(1);
    //cout<<Is_Cycled(1,-1);
    //cout<<is_subtreed(2,3);
    ///for(int i=1;i<=n;i++) cout<<shrt[i]<<' ';
    // int t;cin>>t;
    // while(t--)
    // {
    //     cin>>n>>m;
    //     // graph.resize(n+1);
    //     // vis.resize(n+1);
    //     vis.clear();
    //     for(int i=1;i<=n;i++) {graph[i].clear();}
    //     int a,b;
    //     while(m--)
    //     {
    //         cin>>a>>b; 
    //         graph[a].pb(b);
    //         graph[b].pb(a);
    //     }
    //     pairi p=solve();
    //     cout<<p.first<<' '<<p.second<<'\n';
    // }
     unordered_map<string ,int> mp;
     string s;
     while(cin>>s)
     {
         if(mp.find(s)!=mp.end())
           mp[s]++;
           else mp[s]=1;
     }
     for(auto it:mp) cout<<it.first<<" "<<it.second<<'\n';
     
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 