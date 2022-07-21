#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>
using namespace std;
class Edge
{
public:
  int src = 0;
  int nbr = 0;

  Edge(int src, int nbr)
  {
    this->src = src;
    this->nbr = nbr;
  }
};
unordered_map<int,bool> vis,stacked;
bool solve(int node,vector<vector<Edge>> &graph){
    vis[node]=true;
    stacked[node]=true;
    for(auto &e:graph[node]){
      if(vis.find(e.nbr)==vis.end()){
         if(solve(e.nbr,graph)) return true;
       }else if(stacked.find(e.nbr)!=stacked.end()) return true;
    }
    stacked.erase(node);
    return false;
}
bool cycle(int node,vector<vector<Edge>> &graph){
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
int main() {
  int vtces;
  cin >> vtces;
  vector<vector<Edge>> graph(vtces, vector<Edge>());


  int edges;
  cin >> edges;

  for (int i = 0; i < edges; i++ ) {
    int u, v, w;
    cin >> u >> v >> w;

    graph[u].push_back(Edge(u, v));
    graph[v].push_back(Edge(v, u));
   

  }
    bool flag=false;
    for(int i=0;i<vtces;i++){
      if(vis.find(i)==vis.end()){
          if(solve(i,graph)){
            cout<<"true"<<'\n';
            break;
          }
      }
    }
    cout<<"false"<<'\n';
// write your code here
  return 0;
}