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
/*You are given 2 integers N and M , N is the number of vertices, M is the number of edges
. You'll also be given ai and bi where ai and bi represents an edge from a vertex ai to a vertex bi.
You have to find the minimum number of edges you have to reverse in order to have atleast one path from vertex 1 to N, 
where the vertices are numbered from 1 to N.*/
/*This is 0/1 bfs where we can reduce the complexity using simple deque instead of priority queue in finding the shortest path
algorithm
We can observe one thing that the weights of the nodes are 0 or 1 so there exists only two wts wt+0,or wt+1 at any point of time in the queue
if any wt+2 is coming in pq then it means it has exhausted all wt+0 vertices as wt+1 vertices only leads to wt+2 vertices which means in
pq wt+0(which is smallest) has beeen exhausted!!*/
/*So we can replace the pq with a dq such that if the next node has wt+0 then it can be added at front if it has wt+1 it can be added at v
back*/
/*using priority queue*/
int minEdges_Djikstra(int nodes,int src,int targ,vector<vector<int>> &graph){
   vector<vector<pair<int,int>>> weightGraph(nodes+1);
   int n=graph.size();
   for(int i=0;i<graph.size();i++){
      weightGraph[graph[i][0]].push_back(make_pair(graph[i][1],0));
       weightGraph[graph[i][1]].push_back(make_pair(graph[i][0],1));
   }
   vector<bool> vis(nodes+1,false);
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
   pq.push({0,src});
   while(pq.size()>0){
      auto p=pq.top();pq.pop();
      if(p.second==targ) return p.first;
      if(vis[p.second]==true) continue;
      vis[p.second]=true;
      for(int i=0;i<weightGraph[p.second].size();i++){
         int node=weightGraph[p.second][i].first,wt=weightGraph[p.second][i].second;
         if(vis[node]==false) pq.push(make_pair(p.first+wt,node));
      }
   }
   return -1;
}
int minEdges_01_Bfs(int nodes,int src,int targ,vector<vector<int>> &graph){
   vector<vector<pair<int,int>>> weightGraph(nodes+1);
   int n=graph.size();
   for(int i=0;i<graph.size();i++){
      weightGraph[graph[i][0]].push_back(make_pair(graph[i][1],0));
       weightGraph[graph[i][1]].push_back(make_pair(graph[i][0],1));
   }
   vector<bool> vis(nodes+1,false);
   deque<pair<int,int>> dq;
   dq.push_back(make_pair(src,0));
   while(dq.size()>0){
      auto p=dq.front();dq.pop_front();
      if(p.first==targ) return p.second;
      vis[p.first]=true;
      for(int i=0;i<weightGraph[p.first].size();i++){
          int node=weightGraph[p.first][i].first,swaps=weightGraph[p.first][i].second;
          if(vis[node]==false){
             if(swaps==0) dq.push_front(make_pair(node,p.second+swaps));
             else dq.push_back(make_pair(node,p.second+1));
          }
      }
   }
   return -1;
}
/*Khans Algorithm:
Iterative way to find topological Sort
Note that there exists atleast one i such that indegree[i]==0 as the graph is directed acyclic graph*/
vector<int> Khans_Topological_Sort(vector<vector<int>> &graph){
   int n=graph.size();
   vector<int> indegree(n,0);
   for(auto &v:graph){
      for(int i:v) indegree[i]++;
   }
   queue<int> q;
   for(int i:indegree) if(i==0) q.push(i);
   vector<int> topSort;
   while(q.size()>0){
       auto i=q.front();q.pop();
       topSort.push_back(i);
       for(int j:graph[i]){
          indegree[j]--;
          if(indegree[j]==0) q.push(j);
       }
   }
   return topSort;
}
/*Alien Dictionary*/
string lexographical_Alien_Dictionary(vector<string> &words){
    int n=words.size();
    unordered_map<char,set<char>> mp;
    vector<int> indegree(26,-1);
    for(auto &s:words) for(char &ch:s) indegree[ch-'a']=0;
    int count=0;
    for(int i:indegree) count+=(i==0);
    for(int i=0;i<words.size()-1;i++){
        string cur=words[i],next=words[i+1];
        int j=0,k=0;
        bool flag=false;
        while(j<cur.size() and k<next.size()){
            if(cur[j]!=next[k]){
               mp[cur[j]].insert(next[k]);
               indegree[next[k]-'a']++;
               flag=true;
               break;
            }
            j++;k++;
        }
        /*To handle cases like {{"ab","abc"}} in this we can't decide lexo order in that case we should give preference to smalller lexo
        order and if the */
        if(flag==false and cur.size()>next.size()) return "";
    }
    queue<char> q;
    string lexoSort;
    for(int i=0;i<indegree.size();i++) if(indegree[i]==0) q.push(char('a'+i));
    while(q.size()>0){
        char ch=q.front();q.pop();
        lexoSort.push_back(ch);
        for(char it:mp[ch]){
           indegree[it-'a']--;
           if(indegree[it-'a']==0) q.push(it);
        }
    }
    /*checking all characters are there in the lexosort order if not no valid solutiom exists it returns ""*/
    if(count!=lexoSort.size()) return "";
    return lexoSort;
}
/*Kruskal Algorithm*/
int find(int x,vector<int> &parent){
   if(parent[x]==x) return x;
   else return parent[x]=find(parent[x],parent);
}
bool _union(int x,int y,vector<int> &parent,vector<int> &rank){
      int px=find(x,parent);
      int py=find(y,parent);
      if(px!=py){
          if(rank[px]>rank[py]) parent[py]=px;
          else if(rank[py]<rank[px]) parent[px]=py;
          else{
             parent[px]=py;
             rank[px]++;
          }
          return true;
      }
      return false;
}
/*Prims algorithm without pq
krushkal Algorithm*/
int minSpanningTree_Kruskal(int n,vector<vector<int>> &edges){
      sort(begin(edges),end(edges),[](const vector<int> &a,const vector<int> &b){
             return a[2]<b[2];
      });
      vector<int> parent(n);
      vector<int> rank(n,1);
      int weightSum=0;
      for(int i=0;i<parent.size();i++) parent[i]=i;
      for(int i=0;i<edges.size();i++){
          bool flag=_union(edges[i][0],edges[i][1],parent,rank);
          if(flag) weightSum+=edges[i][2];
      }
      return weightSum;
}
/*There are n construction sites in a town. We want to supply water for all the construction
 sites by building wells and laying pipes.

For each site i, we can either build a well inside it directly with cost wells[i-1], or pipe in water from another well to it. The costs to lay pipes between
sites are given by the 2d array cost, where each row of cost contains 3 numbers ai,bi and wi where wi is the cost to connect ai to bi. connections are bidirectional.

Return the minimum total cost to supply water to all the construction sites*/
/*Approach:
since we have two options whether we can dig the well or we can draw pipe from another well
we can observe that there must be atleast one well that need to be digged 
so we create at dummy node 0 and add an edge b/w o to node with weight wt of digging
then the question turns into minimum spanning tree*/
int minCostToSupplyWater(int n,vector<int> &wells,vector<vector<int>> &pipes){
   vector<vector<pair<int,int>>> graph(n+1);
   for(int i=0;i<pipes.size();i++){
      graph[pipes[i][0]].push_back(make_pair(pipes[i][1],pipes[i][2]));
      graph[pipes[i][1]].push_back(make_pair(pipes[i][0],pipes[i][2]));
   }
   for(int i=0;i<wells.size();i++){
      graph[0].push_back(make_pair(i+1,wells[i]));
      graph[i+1].push_back(make_pair(0,wells[i]));
   }
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
   vector<bool> vis(n+1,false);
   pq.push({0,0});
   int minWeight=0;
   while(pq.size()>0){
         auto x=pq.top();pq.pop();
         if(vis[x.second]) continue;
         minWeight+=x.first;
         vis[x.second]=true;
         for(auto p:graph[x.second]){
             if(vis[p.first]==false){
                pq.push(make_pair(p.second,p.first));
             }
         }
   }
   return minWeight;
}
/*You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.*/
int swimInWater(vector<vector<int>> &grid){
    int n=grid.size();
    vector<int> dx={-1,0,1,0,-1};
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;
    pq.push({grid[0][0],{0,0}});
    while(pq.size()>0){
       auto cur=pq.top();pq.pop();
       int minTime=cur.first,x=cur.second.first,y=cur.second.second;
       if(grid[x][y]<0) continue;
       if(x==n-1 and y==n-1) return minTime;
       grid[x][y]=-1;
       for(int i=0;i<4;i++){
         int nr=x+dx[i],nc=y+dx[i+1];
         if(nr<0 or nc<0 or nr>=n or nc>=n or grid[nr][nc]<0) continue;
         if(grid[nr][nc]>minTime) pq.push(make_pair(grid[nr][nc],make_pair(nr,nc)));
         else pq.push({minTime,{nr,nc}});
       }
    }
    return -1;
}
/*Mincost to connect all cities*/
int minCostToConnectCities(int n,vector<vector<int>> &edges){
   vector<vector<pair<int,int>>> graph(n);
   for(auto &v:edges){
      graph[v[0]].push_back({v[1],v[2]});
      graph[v[1]].push_back({v[0],v[2]});
   }
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
   pq.push({0,0});
   int minWeight=0;
   vector<bool> vis(n,false);
   while(pq.size()>0){
      auto p=pq.top();pq.pop();
      if(vis[p.second]==true) continue;
      minWeight+=p.first;
      vis[p.second]=true;
      for(auto &x:graph[p.second]){
         if(vis[x.first]==false) pq.push({x.second,x.first});
      }
   }
   return minWeight;
}
/*Kosaraju Algorithm for finding strongly connected components in the graph*/
/*Strongly Connected graph:A directed graph is strongly connected if there is a path b/w all pair of
vertices in the graph...i.e., in simple terms if we take a node then there must be a path to every 
other node in the graph from this node.
A strongly connected component of a directed graph is a maximal strongly connected subgraph.
[the scc should be as max as possible]
        
        0<--------- 3            6<------------7
        |           ^            |             ^
        |           |            |    y        |
        |     x     |            |             |
        V           |            V             |
        1---------->2----------->4------------>5
 
 We can see the above directed graph has 2 strongly connected components x and y
 you may notice from {0,1,2,3} we can reach all nodes even in the vertices of y but they will not be
 considered for a strongly connected graph as there is no path from {4,6,7,5} to any vertices of
 x.
 It is beacuse there is a problematic edge [2->4] which has one direction so we can travel in only one
 direction.
 so if we dfs from end first then all the ssc1 will be visited
 and if we dfs from start then all the ssc2 visited (here we dnt;visitit  y vertices as they are 
 already visited) 
In somehow we need to find this problematic edge
what kosaraju has ovserved that if we do dfs traversal from any node then the top of the stack will be
part of ssc1 of start node 
After dfs at 0=[6,7,5,4,2,3,1,0] at top 0 is there which is part of ssc1 of start node.
so we reverse the edge and we do dfs traversal from all st.tops which leads to one of the nodes
of every ssc in the graph.
If there will be no edge goimg outside of ssc as those parts are already visited
as we do dfs traverse in stack order.
As per kosaraju_dfs;
step1:do dfs from any random node store the nodes in postorder in stack.
push the node when we are backtracking
(note that upon dfs from any random node we may not reach all nodes so we need to do dfs from'
all the remaining nodes also)
2:reverse the edges of the graph
3.do dfs in the stack order and count connected components
*/
void kosaraju_dfs(int node,vector<bool> &vis,stack<int> &st,vector<vector<int>> &graph,bool flag){
   vis[node]=true;
   for(auto &x:graph[node]){
      if(vis[x]==false){
       kosaraju_dfs(x,vis,st,graph,flag);
      }
   }
   if(flag) st.push(node);
   return;
}
int countStronglyConnected_Kosaraju(int n,vector<vector<int>> &edges){
    vector<vector<int>> graph(n+1),revGraph(n+1);
    for(int i=0;i<edges.size();i++){
         graph[edges[i][0]].push_back(edges[i][1]);
         revGraph[edges[i][1]].push_back(edges[i][0]);
    }
    stack<int> st;
    vector<bool> vis(n+1,false);
    for(int i=1;i<=n;i++){
      if(vis[i]==false){
         kosaraju_dfs(i,vis,st,graph,true);
      }
    }
    int count_SC=0;
    vis.clear();
    for(int i=0;i<=n;i++) vis[i]=false;
    while(st.size()>0){
       int node=st.top();st.pop();
       if(vis[node]) continue;
       kosaraju_dfs(node,vis,st,revGraph,false);
       count_SC++;
    }
  //for(int i=1;i<=n;i++) if(vis[i]==false) count_SC++;
  return count_SC;
}
/*Mother Vertex is a vertex from which all other nodes can be visited.
we do a normal dfs traversal from a random  node .The node which is at top of the stack can be
mother vertex.if it cannot then there is no mother vertex at all.
Proof:
Let the stack be [7,8,1,2,3,4,5,6]
Let us analyse the 4 cases of possible mother  vertices ---(nros==rest of the stack)
Case 1:st.top() is mothervertex and nros is mothervertex
         In this case if st.top() is mothervertex anyway we are returing st,top()
Case 2:st.top() is mothervertex and nros is mothervertex
         we are handling this case already
Case 3:st.top() is not mothervertex and nros is not mothervertex 
            we are going to return -1
Case 4:st.top() is not mother vertex and nros is mothervertex
         This case aint posiible.
         Let us take st,top()=7 and nros=3;
         Two possibilities 7 and 3 has a path or not:
   If 3 and 7 has no oath then 3 cannot be mothervertex
   if 7->3 path existes then 7 will be also a mothervertex as all path exists from 3 then 7->3 also exists
   so 7 will be also a mothervertex
   if 3->7 path
      if we first do dfs on 3 then since 3->7 a path is there then 7 will be below than 3
      if we forst do dfs on 7 then since 7->3 path doesn'y exist then in this dfs traversal 3 will not be
      there it should be remaining nodes dfs and now eventually it will be on top of 3
      as we have already did dfs on 7*/
void motherVertex_dfs(int node,vector<bool> &vis,stack<int> &st,vector<vector<int>> &graph,bool flag){
    vis[node]=true;
    for(auto &x:graph[node]){
      if(vis[x]==false)
        motherVertex_dfs(x,vis,st,graph,flag);
    }
    if(flag) st.push(node);
    return;
}
int motherVertex(int n,vector<vector<int>> &edges){
   vector<vector<int>> graph(n+1);
   for(int i=0;i<edges.size();i++) graph[edges[i][0]].push_back(edges[i][1]);
   vector<bool> vis(n+1,false);
   stack<int> st;
   for(int i=1;i<=n;i++){
      if(vis[i]==false){
         motherVertex_dfs(i,vis,st,graph,true);
      }
   }
   for(int i=1;i<=n;i++) vis[i]=false;
   motherVertex_dfs(st.top(),vis,st,graph,false);
   for(int i=1;i<vis.size();i++) if(vis[i]==false) return -1;
   return st.top();
}
int main()
 {
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //vector<vector<int>> graph={{1,2},{3,2},{3,4},{7,4},{6,2},{5,6},{7,5}};
    //vector<string> words={{"wrt"},{"wrf"},{"er"},{"ett"},{"rftt"}};
    //lexographical_Alien_Dictionary(words);
     int m,n;cin>>m>>n;
  //   vector<int> wells(m);
    // for(int i=0;i<m;i++) cin>>wells[i];
     //vector<vector<int>> edges(n,vector<int>(3));
     //for(int i=0;i<n;i++) cin>>edges[i][0]>>edges[i][1]>>edges[i][2];
    // cout<<minCostToConnectCities(m,edges);
     //cout<<minSpanningTree_Kruskal(m,edges);
     //cout<<minCostToSupplyWater(m,wells,edges);
    //cout<<minEdges_Djikstra(7,1,7,graph)<<'\n';
    //cout<<minEdges_01_Bfs(7,1,7,graph)<<'\n';
    vector<vector<int>> edges(n,vector<int>(2));
    for(int i=0;i<n;i++) cin>>edges[i][0]>>edges[i][1];
    //cout<<countStronglyConnected_Kosaraju(m,edges);
    cout<<motherVertex(m,edges);
    return 0;
 }
