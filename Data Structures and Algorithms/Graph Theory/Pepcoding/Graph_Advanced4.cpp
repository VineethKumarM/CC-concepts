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
/*In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n, 
with one additional edge added. The added edge has two different vertices chosen from 1 to n,
 and was not an edge that already existed. The graph is represented as an array edges of
  length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi
   in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes. 
 If there are multiple answers, return the answer that occurs last in the input.*/
 /*
 __________________________________________Approach___________________________________________
 
 We can build the graph and try to find the edge that makes cycle.But it is given that we should rerurn
 the last edge that is making cycle in the graph
 For example Let us consider the case of edges=[[1,2],[1,3],[2,6],[6,5],[2,4],[4,5]]

                       1---------------2----------6
                       |               |          |
                       |               |          |
                       |               |          |
                       |               |          |
                       3               4----------5

   The graph looks like the above
 If we do a straight dfs 2->6 or 2->4 or 4->5 por 5->6 can be the edge which makes the graph cyclic
 But we know as from the order due to extra edge 4->5 we are getting cycle.
 So a simple dfs won;t work.

 ==>We can use the dsu inorder to find the cycle.Through dfs we can tell at which edge the cycle is
 occuring.
 Finding Cyclicity in graph:If we are connecting two nodes whcih hasve same parent that means
 that we are adding another path node1->node2 where already another path exists in the 
 graph.Basically we are making cycle in the graph.So we return the current edge
 based on the fact merging happened or not.
      
 */
int find(int x,vector<int> &parent){
   if(parent[x]==x) return x;
   return parent[x]=find(parent[x],parent);
}
bool _union(int x,int y,vector<int> &parent,vector<int> &rank){
   int px=find(x,parent);
   int py=find(y,parent);
   if(px!=py){
      if(rank[px]<rank[py]) parent[px]=py;
      else if(rank[px]>rank[py]) parent[py]=px;
      else{
         parent[py]=px;
         rank[px]++;
      }
      return true;
   }
   return false;
}
vector<int> findRebundantConnection(vector<vector<int>> &edges){
   int n=edges.size();
   vector<int> parent(n+1),rank(n+1,0);
   for(int i=0;i<=n;i++) parent[i]=i;
   for(int i=0;i<edges.size();i++){
       bool flag=_union(edges[i][0],edges[i][1],parent,rank);
       if(flag==false) return edges[i];
   }
   return {};
}
/*https://leetcode.com/problems/redundant-connection-ii/*/
/*
_____________________________________Approach____________________________________________________

The possibilities of violation of graph apart from tree are:
  i.A node has two parents
  ii.There exists a cycle in the graph
  iii.Both may exist

===> Assume the direction of graph as downwards.
Case i:
 Edges=[[1,2],[1,3],[2,4],[2,5],[3,6],[3,5]]

                                         1
                                       /   \
                                      2     3
                                    /  \    / \
                                    4     5    6

Case ii:
 Edges=[[1,2],[1,3],[2,4],[2,5],[3,7],[3,6],[6,1]]

                                         1<-------------|
                                       /   \            |
                                      2     3           |
                                    /  \    / \         |
                                    4   5   7  6--------|

In the above graph every node has one parent but it is not a graph as 6->1 edge makes it cyclic

Case iii:
 
 Edges[[2,3],[3,4],[1,2],[4,2],]

                                   1
                                     \    
                                      2
                                    /    \
                                   3------4

We try to find the indegrre and cyclicity in the graph
Note that cyclicity in directed graph cannot be found by dsu.We can only apply dsu when we know
that only when either one cycle is present or no cycle is present.
Case i:If we know that there is no cycle in the graph and we are getting indegree>=2 then we can return
the current edge as failing edge
Case ii:If we know there is no node which has idegree[1]>=2 then we can directly apply dsu
and find out the first edge.
Question becomes tricky in the third case:
 If we traverse edges we are getting at edge 3 the indegree[2]>=2 then we should return the edge
 But if we remove 1->2 edge the graph is still invalid as there is a cyle present in the graph.
 So there can be two possiblities in this case.
 The failng edge can be making the graph cyclic or making the indegree[2]>=2
 We should handle these 3 cases for getting correct answer.

_____________________________________________Algorithm______________________________________________

We will handle these 3 cases at once

==>First we try to find out the indegree and try to find two failing Edge cases.
Here we don;t store the no.of indegrees instead of this we store the index of the edge that made this
current node to have indegree[i]>=1
If the current node already has some +ve value it means it has two indgrees then
we store failingEdge1=i and failingEdge2=i;

==>Then we remove that falingEdge1 in the graph try to find through dsu whether cyclicity is present
in the graph after removing fedge1.
If it is present it means without fedge1 also graph is invalid so we return fegde2[case 3]
If the cyclicty is present then and no node has indegrre[node]>=2 then we directly return the 
cyclic edge

If the graph is acyclic after removing the fege1 then we return fedge1
___________________________________________________________________________________________________
*/
vector<int> findRebundantDirectConnection(vector<vector<int>> &edges){
    int n=edges.size();
    vector<int> parent(n+1),rank(n+1,0),indegree(n+1,-1);
    for(int i=1;i<=n;i++) parent[i]=i;
    int fEdge1=-1,fEdge2=-1;
    for(int i=0;i<edges.size();i++){
         if(indegree[edges[i][1]]==-1) indegree[edges[i][1]]=i;
         else{
            fEdge1=i;
            fEdge2=indegree[edges[i][1]];
            break;
         }
    }
    for(int i=0;i<edges.size();i++){
      /*if feged1==-1 then all the edges are considered*/
        if(i==fEdge1) continue;
        else{
           bool flag=_union(edges[i][0],edges[i][1],parent,rank);
           if(flag==false){
            /*if the fdege==-1 it means the graph has no indegree[node]>=2 so graph is invalid
            due to cyliciyty so we directly return the current cyclic edge  */
              if(fEdge1==-1) return edges[i];
               /*if cyle is present and fege!=-1 it means it has indegree>=2 and after removing
             fegde also we are getting cylity in that case we return fegdg2*/
              else return edges[fEdge2];
           }
        }
    }
    /*without the current edge the graph is acylic it means it is case ii so we return fedge1[last edge]*/
    return edges[fEdge1];
}
/*You are given an array of strings equations that represent relationships between
 variables where each string equations[i] is of length 4 and takes one of two different forms:
  "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different)
   that represent one-letter variable names.
Return true if it is possible to assign integers to variable names so as to satisfy
 all the given equations, or false otherwise.*/
bool equationPossible(vector<string> &equations){
   vector<int> parent(26),rank(26,1);
   for(int i=0;i<26;i++) parent[i]=i;
   for(string &s:equations){
       if(s[1]=='='){
         _union(s[0]-'a',s[3]-'a',parent,rank);
       }
   }
   for(string &s:equations){
      if(s[1]=='!'){
         int px=find(s[0]-'a',parent);
         int py=find(s[3]-'a',parent);
         if(px==py) return false;
      }
   }
   return true;
}
string findString(string &x,unordered_map<string,string> &parent,unordered_map<string,int> &rank){
    if(parent.find(x)==parent.end()){
       parent[x]=x;
       rank[x]=1;
       return x;
    } return x;
    return parent[x]=findString(parent[x],parent,rank);
}
void _unionString(string &x,string &y,unordered_map<string,string> &parent,unordered_map<string,int> &rank){
    string px=findString(x,parent,rank);
    string py=findString(y,parent,rank);
    if(px!=py){
      if(rank[px]>rank[py]) parent[py]=px;
      else if(rank[py]>rank[px]) parent[px]=py;
      else{
         parent[py]=px;
         rank[px]++;
       }
    }
}
bool senetenceSimilarity(vector<string> &s1,vector<string> &s2,vector<vector<string>> &pairs){
   if(s1.size()!=s2.size()) return false;
   unordered_map<string,string> parent;
   unordered_map<string,int> rank;
   for(auto v:pairs) _unionString(v[0],v[1],parent,rank);
   for(int i=0;i<s1.size();i++){
       if(s1[i]==s2[i]) continue;
       string px=findString(s1[i],parent,rank);
       string py=findString(s2[i],parent,rank);
       if(px!=py) return false;
   }
  return true;
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
