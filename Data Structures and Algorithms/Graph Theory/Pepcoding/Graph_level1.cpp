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
class Edge {
public:
  int src = 0;
  int nbr = 0;
  int wt = 0;

  Edge(int src, int nbr, int wt) {
    this->src = src;
    this->nbr = nbr;
    this->wt  = wt;
  }
};
/*1. You are given a graph and a src vertex.
2. You are required to find and print all hamiltonian paths and cycles starting from src. The cycles must end with "*" and paths with a "."

Note -> A hamiltonian path is such which visits all vertices without visiting any twice. A hamiltonian path becomes a cycle if there is an edge between first and last vertex.
Note -> Print in lexicographically increasing order.*/
unordered_map<int,bool> mp;
void hamiltonian(int node,int osrc,vector<vector<Edge>> &graph,string osf){
    if(osf.size()==graph.size()-1){
        bool flag=false;
        for(auto &e:graph[node]){
          if(e.nbr==osrc) flag=true;
        }
        if(flag) osf+="*";
        else osf+='.';
        cout<<osf<<'\n';
        return;
    }
    mp[node]=1;
    for(auto &e:graph[node]){
        if(mp.find(e.nbr)==mp.end()) hamiltonian(e.nbr,osrc,graph,osf+to_string(e.nbr));
    }
    mp.erase(node);
}
unordered_map<int,bool> vis,stacked;
bool cycle_dfs(int node,vector<vector<Edge>> &graph){
    vis[node]=true;
    stacked[node]=true;
    for(auto &e:graph[node]){
      if(vis.find(e.nbr)==vis.end()){
         if(cycle_dfs(e.nbr,graph)) return true;
       }else if(stacked.find(e.nbr)!=stacked.end()) return true;
    }
    stacked.erase(node);
    return false;
}
bool cycle_bfs(int node,vector<vector<Edge>> &graph){
  queue<int> q;q.push(node);
  while(q.size()>0){
    int x=q.front();q.pop();
    if(vis.find(x)!=vis.end()) return true;
    vis[x]=true;
    for(auto &e:graph[x]){
      if(vis.find(e.nbr)==vis.end()) q.push(e.nbr);
    }
  }
  return false;
}
/*Bipartite Graph is a graph whose vertices can be divided into two disjoint and independent sets and that is every edge
connects a vertex to one in.
In simple terms we have to divide the vertices into two sets such that every egde in the graph should be across the two sets
and there should not be any edge b/w two vertices in the same set
Inorder to satisy bipartite graph should meet any of the following conditions:
1.Acyclic graph is always bipartite
2.If the graph is cyclic the cyclic graph size should always be even size.
3.Every component in the graph should be bipaatite inorder to call the graph as bipartite.*/
bool is_bipartite(int node,vector<vector<Edge>> &graph){
    queue<pair<int,int>> q;
    q.push(make_pair(node,0));
    vector<int> visited(graph.size()+1,-1);
    while(q.size()>0){
       auto p=q.front();q.pop();
       if(visited[p.first]!=-1){
           if(p.second!=visited[p.first]) return false;
       }else visited[p.first]=p.second;
       for(auto &e:graph[p.first]){
            if(visited[e.nbr]!=-1){
              q.push(make_pair(e.nbr,p.second+1));
            }
       }
    }
    return true;
}
void djikstra(int src,vector<vector<Edge>> &graph){
    priority_queue<pair<int,pair<int,string>>,vector<pair<int,pair<int,string>>>,greater<pair<int,pair<int,string>>>> pq;
    pq.push(make_pair(0,make_pair(src,to_string(src))));
    unordered_map<int,bool> vis;
    while(pq.size()>0){
      auto p=pq.top();pq.pop();
        if(vis.find(p.second.first)!=vis.end()) continue;
        vis[p.second.first]=true;
        cout<<p.second.first<<"via"<<p.second.second<<"@"<<p.first<<'\n';
        for(auto &e:graph[p.second.first]){
            if(vis.find(e.nbr)==vis.end())
               pq.push(make_pair(p.first+e.wt,make_pair(e.nbr,p.second.second+to_string(e.nbr))));
        }
    }
}
int mimimum_spanning_tree(vector<vector<Edge>> &graph){
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
   pq.push({0,0});/*We can take any vertex as src as the tree is spanning there will be atleast on edge from each node*/
   unordered_map<int,bool> vis;
   int sum=0;
   while(pq.size()>0){
       auto p=pq.top();pq.pop();
        if(vis.find(p.second)!=vis.end()) continue;
        vis[p.second]=true;
        sum+=p.first;
        for(auto &x:graph[p.second]){
            if(vis.find(x.nbr)==vis.end())
              pq.push(make_pair(x.wt,x.nbr));
        }
   }
   return sum;
}
/*Topological sort is a permutation of vertices for a directed acyclic graph where for all direct edges from u->v 
u appears before v in the graph
It is a postorder +stack*/
stack<int> st;
void dfs(int node,vector<vector<Edge>> &graph){
  vis[node]=true;
  for(auto &e:graph[node]){
      if(vis.find(e.nbr)==vis.end())
       dfs(e.nbr,graph);
  }
  st.push(node);
}
vector<int> topological_sort(vector<vector<Edge>> &graph){
  queue<int> q;
   for(int i=0;i<graph.size();i++){
      if(vis.find(i)==vis.end()) dfs(i,graph);
   }
   vector<int> ans;
   while(st.size()>0){
    ans.push_back(st.top());
    st.pop();
   }
   return ans;
}
void itertive_dfs(vector<vector<Edge>> &graph){
    stack<int> st;
    unordered_map<int,bool> vis;
    while(st.size()>0){
        auto x=st.top();st.pop();
        if(vis.find(x)!=vis.end()) continue;
        vis[x]=true;
        for(auto &e:graph[x]){ 
          if(vis.find(e.nbr)!=vis.end())
           st.push(e.nbr);
        }
    }
}

int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
