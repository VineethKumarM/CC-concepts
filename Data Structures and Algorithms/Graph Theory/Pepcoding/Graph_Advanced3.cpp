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

/*________________________________________________________________________________________________

Given an m*n matrix mat, 
Originally, the 2D matrix is all 0 which means there is only sea in the matrix.
 The list pair has k operator and each operator has two integer A[i].x, A[i].y means 
 that you can change the grid mat[A[i].x][A[i].y] from sea to island. Return how many 
 island are there in the matrix after each operator.You need to return an array of size K.*/
/*___________________________________________Approach_______________________________________________

Eventually the question turns into dynamic edges where we are asked to find out the connnect components
at every stage of dynamic edge.
so for dfs will take O(v+e) complexity to find out the components at each stage which
results in complexity O(v+e)*e..
we can reduce the complexity to O(v+e) using dsu

we intialise the parent array with -1,rank with 0
any island with parent=-1 will be treated as new island and we increase the count of islands
we make parent[i]=i;
then we are going to merge with allones[can be retrived using parent array] 
if neighbor parent and cur cell oarent is different then we are going to merge them since we
merged two different islands we make curIsland--;
next iteration we try to do the same if both thier parent are equal then it does mean that
they are already merged and we are going to merge them again so we wont do anything
____________________________________________________________________________________________________
*/
int find(int x,vector<int> &parent){
    if(parent[x]==x) return x;
    else return parent[x]=find(parent[x],parent);
}
bool _union(int x,int y,vector<int> &parent,vector<int> &rank){
     int px=find(x,parent);
     int py=find(y,parent);
     if(px!=py){
        if(rank[px]>rank[py]) parent[py]=px;
        else if(rank[py]>rank[px]) parent[px]=py;
        else{
            parent[py]=px;
            rank[px]++;
        }
        return true;
     }
    return false;
}
vector<int> numIslands(int m,int n,vector<vector<int>> &ones){
    vector<int> parent(m*n,-1);
    vector<int> rank(m*n,0);
    vector<int> ans;
    int curIslands=0;
    vector<int> dx={-1,0,1,0,-1};
    for(int i=0;i<ones.size();i++){
         int row=ones[i][0],col=ones[i][1];
         /*cell no*/
         int cell=row*m+col;
         /*if the cur cell is already visited we can continue*/
         if(parent[cell]!=-1){
            ans.push_back(curIslands);
            continue;
         }
         /*then we are making self pareent*/
         parent[cell]=cell;
         /*considering it as a new Island*/
         curIslands++; 
         for(int j=0;j<4;j++){
           int nr=row+dx[j],nc=col+dx[j+1];
           if(nr<0 or nc<0 or nr>=m or nc>=n or parent[nr*m+nc]==-1) continue;
           /* we try to find whether merging happended or not*/
           bool flag=_union(cell,nr*m+nc,parent,rank);
           /*if it happened we mergred two diff islands we decrease curIslands--*/
           if(flag) curIslands--;
         }
         ans.push_back(curIslands);
    }
    for(int i=0;i<ans.size();i++) cout<<ans[i]<<' ';
    return ans;
}
/*
____________________________________________________________________________________________________

An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', 
or blank space ' '. These characters divide the square into contiguous regions.

Given the grid grid represented as a string array, return the number of regions.

Note that backslash characters are escaped, so a '\' is represented as '\\'.*/
/*
_________________________________________________________________________________________________
Approach:
Let us try to observe it with no of islands questions and assume slashes as connecting two points
           
           .____.____.____.
           | /  .    .  \ .
           .    .    .    .
           |  /    \   /
           .____.____.____.  

You can see that the the forward slash at (i,j) is connecting point (i,j+1) and (i+1,j)
and backwad slash connecting is connecting (i,j) and (i+1,j+1);
and we need to find the cycles in graph for regions
We can use krushkal algo for that and there is a region =1 which is rest of the region after counting
all cycles
Krushkal for cycle detection:if we are connecting two points which have
           */
int regionsBySlashes(vector<string> &grid){
    int n=grid.size()+1;
    vector<int> parent(n*n),rank(n*n,1);
    /*rest of the region*/
    int regions=1;
    for(int i=0;i<parent.size();i++) parent[i]=i;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==0 or j==0 or i==n-1 or j==n-1){
                int cell=i*n+j;
              if(cell!=0) _union(0,i*n+j,parent,rank);
            }
        }
    }
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            char ch=grid[i][j];
            if(ch=='/'){
                int c1=(i+1)*n+j,c2=i*n+j+1;
                regions+=(!_union(c1,c2,parent,rank));
            }else if(ch=='\\'){
                int c1=i*n+j,c2=(i+1)*n+j+1;
                regions+=(!_union(c1,c2,parent,rank));
            }
        }
    }
    return regions;
}
/*______________________________________________________________________________________________________
Eulerian Path is a path in which every edge is vsited extacly once.
Eulerian cicrcult is an eulerian path which start and ends on the same vertex.
Case 1:Graph is undirected:
 i.Eulerian Cicruit:
      All the vertices must have even indgree.
       
       -----node1----------(((((middle nodes)))))------------(node2)--
       |                                                              |
       |                                                              |
       |                                                              |
       |                                                              |
       ---------------------------------------------------------------
       We can asssume a graph like this where every node has even edges .if we assume node1 as source
       there is an exit edge and it will travel through all middle edges and enter into node2
       now the node2 should also have a exit edge whoch inturn enters into node1 thus having even indgree
       for each node.
    
    2.Eulerian Path:
       For the above graph although the middle edges must have one entry and one exit edge it is not
       the case with src and destination as they need not to have edge it can start at node1 ->middlenodes
       ->node2 and end here.
       Conditoion:(n-2) vertices must have even indegree and 2 edges can have odd indegree.(if these two also
       have even then itbecomes eulerian circuit which inturn becomes eulerian path)
       Note that exactly 2 nodes must have odd indgree .

Case 2:Directed Graph:
    1.Eulerian Circuit:
     The condition that is different from the undirected graph is undirected graph can make any edge
     from a vertex v as entry and exit edge but in directed graph for entry edge must be towards vertex'
     and exit edge must  be from the vertex.
     Condition:In directed graph indgree[vtx]=outdegrre[vtx] for every vtx

  2.Eulerian Path
    Exactly n-2 nodes should have indegree[vtx]=outdegree[vtx];
    exactly one node indgree[vtx]=outdgree[vtx]+1;
    exatcly one node outdegrre[vtx]=indgree[vtx]+1
____________________________________________________________________________________________________
*/
/*
You are given a list of airline tickets where tickets[i] = [fromi, toi]
 represent the departure and the arrival airports of one flight.
  Reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from "JFK", thus, 
the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.

For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
You may assume all tickets form at least one valid itinerary.
 You must use all the tickets once and only once.*/
 /*____________________________________________________________________________________________
 Approach:Eventually we are asked to find out the eulerian path and it is given the path exists
 
 Eulerian Path:A path in which every edge in the graph visited exactly once.
                 1<================>2
                 ||                 ||
                 ||                 ||
                 ||                 ||
                 ||                 ||
                 V|                 V|
                 3<=================>4
                  
Every node has indegree[node]=even there fore the path exits
Thr path can be 1->2->4->3->1->3->4->->2->1
every edge is traverse exactly one
if we try to mainatian a visited array for vetices then we wont't be able to visit all the edges
as 1->2->4->3..(3 stops here as 1 is already visited)
Instead of putting the vertices as visited we put edges as visited and avoid any edge visiting twice
for that we use map and a priority_queue [for lexo graphical purpise] as soon as we use the edge
we pop it from the pq
_____________________________________________________________________________________________________
*/ 
unordered_map<string,priority_queue<string,vector<string>,greater<string>>> graph;
void dfs(string &node,vector<string> &ans){
    while(graph[node].size()){
        string x=graph[node].top();graph[node].pop();
        dfs(x,ans);
        ans.push_back(x);
    }
    ans.push_back(node);
}
vector<string> findItinerary(vector<vector<string>> &tickets){
    for(auto &v:tickets) graph[v[0]].push(v[1]);
    vector<string> ans;string node="JFK";
    dfs(node,ans);
    reverse(begin(ans),end(ans));
    return ans;
} 
/*Given an m x n matrix, return a new matrix answer where answer[row][col] 
is the rank of matrix[row][col].

The rank is an integer that represents how large an element is compared to other elements.
 It is calculated using the following rules:

The rank is an integer starting from 1.
If two elements p and q are in the same row or column, then:
If p < q then rank(p) < rank(q)
If p == q then rank(p) == rank(q)
If p > q then rank(p) > rank(q)
The rank should be as small as possible.
The test cases are generated so that answer is unique under the given rules.*/
vector<int> rowMax;
vector<int> colMax;
int findParent(int x,vector<int> &parent){
    if(parent[x]<0) return x;
     return parent[x]=findParent(parent[x],parent);
}
void updateMat(vector<vector<int>> &arr,vector<vector<int>> &matrix){
    int m=matrix.size(),n=matrix[0].size();
    vector<int> parent(m+n,-1);
    for(int i=0;i<arr.size();i++){
        int row=arr[i][1],col=arr[i][2];
        int pRow=findParent(row,parent);
        int pCol=findParent(col+m,parent);
        if(pRow!=pCol){
            int maxRank=min(parent[pRow],min(parent[pCol],-1*(max(rowMax[row],colMax[col]))-1));
            parent[pCol]=pRow;
            parent[pRow]=maxRank;
        }
    }
    for(int i=0;i<arr.size();i++){
        int row=arr[i][1],col=arr[i][2];
        int p=findParent(row,parent);
        int rank=-1*parent[p];
        matrix[row][col]=rank;
        rowMax[row]=rank;
        colMax[col]=rank;
    }
}
vector<vector<int>> matrixRankTransform(vector<vector<int>> &matrix){
    int m=matrix.size(),n=matrix[0].size();
    rowMax.resize(m,0);
    colMax.resize(n,0);
    vector<vector<int>> grid;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            grid.push_back({matrix[i][j],i,j});
        }
    }
    sort(begin(grid),end(grid),[](const vector<int> &a,const vector<int> &b){
        return a[0]<b[0];
    });
    vector<vector<int>> arr;
    int lastValue=INT_MAX;
    for(int i=0;i<grid.size();i++){
        int val=grid[i][0];
        if(lastValue!=val){
            updateMat(arr,matrix);
            lastValue=val;
            arr.clear();;
        }
        arr.push_back(grid[i]);
    }
    updateMat(arr,matrix);
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++){
            cout<<matrix[i][j]<<' ';
        }
        cout<<'\n';
    }
    return matrix;
}
/*You are given two integer arrays, source and target, both of length n. 
You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] 
indicates that you are allowed to swap the elements at index ai and index bi (0-indexed)
 of array source. Note that you can swap elements at a specific pair of indices multiple 
 times and in any order.

The Hamming distance of two arrays of the same length, source and target, is the number
 of positions where the elements are different. Formally, it is the number of indices i for 
 0 <= i <= n-1 where source[i] != target[i] (0-indexed).

Return the minimum Hamming distance of source and target after performing any amount of 
swap operations on array source.*/
int minimumHammingDistance(vector<int> &source,vector<int> &target,vector<vector<int>> &allowedSwaps){
    int n=target.size();
    vector<int> parent(n);
    for(int i=0;i<n;i++) parent[i]=i;
    for(int i=0;i<allowedSwaps.size();i++){
        int x=allowedSwaps[i][0],y=allowedSwaps[i][1];
        int px=find(x,parent);
        int py=find(y,parent);
        if(px!=py){
            parent[py]=px;
        }
    }
    unordered_map<int,unordered_map<int,int>> mp;
    for(int i=0;i<n;i++){
        int root=find(i,parent);
        mp[root][source[i]]++;
    }
    int hamDist=0;
    for(int i=0;i<n;i++){
        int root=find(i,parent);
        if(mp[root].find(target[i])==mp[root].end()){
            hamDist++;
            continue;
        }
        if(mp[root][target[i]]<=0) hamDist++;
        else mp[root][target[i]]--;

    }
    return hamDist;
}
/*https://leetcode.com/problems/minimize-malware-spread/*/
/*
__________________________________________________Approach_______________________________________

Eventually the question is asking us to find out the max connected component size in
intials so that malware spread can be minimised.

we will find the component size of each node in the intial and try to return the index of the node
which has max malware spread.
Observation:One observation that should be kept in mind is that if we are given two intial nodes
which are affected by malware and they both belong to the same compnent then removing any node
in that component will never decrease the spread.
As if one node is present then there exists another nodes which spreads the malware.
                       
                       1---------------2
                       |               |
                       |               |
                       |               |
                       |               |
                       3---------------4---------5

Let us suppose node 1 and 5 are affected .Although if we remove node 1 the whole
component still be affected as node 5 is there.
The basic ds for grouping finding common parent is DSU.
This time we keeep a size array for finding out the group size .
We keep one more array for finding out no of infected nodes in the respcective component.
If it is greater than>1 then we no need to check the malware spread for this

Complexity Analysis:
Time complexity:O(n*n) -----------[we traverse graph for once]
Space complexity:O(n)-------------[for storing parent,size,infected]

____________________________________________________________________________________________________
*/
void unionBySize(int x,int y,vector<int> &parent,vector<int> &size){
    int px=find(x,parent);
    int py=find(y,parent);
    if(px!=py){
        if(size[px]>size[py]){
            parent[py]=px;
            size[px]+=size[py];
        }else{
            parent[px]=py;
            size[py]+=size[px];
        }
    }
}
int minMalwareSpread(vector<vector<int>> &graph,vector<int> &initial){
    int n=graph.size();
    vector<int> parent(n),size(n),infected(n,0);
    for(int i=0;i<n;i++){
        parent[i]=i;
        size[i]=1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j and graph[i][j]==1) unionBySize(i,j,parent,size);
        }
    }
    for(int i=0;i<initial.size();i++){
        int pi=find(initial[i],parent);
        infected[pi]++;
    }
    for(int i:infected) cout<<i<<' ';
    int ans=INT_MAX,maxSize=INT_MIN;
    for(int i=0;i<initial.size();i++){
        int pi=find(initial[i],parent);
        if(infected[pi]==1 and size[pi]>=maxSize){
           if(size[pi]==maxSize){
              ans=min(ans,initial[i]);
           }else ans=initial[i];
           maxSize=size[pi];
        }
    }
    return ans==INT_MAX?*min_element(begin(initial),end(initial)):ans;
}
/*https://leetcode.com/problems/minimize-malware-spread-ii/

_________________________________________Approach_________________________________________________

In the above question we make the inital node as unaffected for each node and try to count the max
size of components which remains unaffected after doing so.
This question is slight different from the above one.In this question we  remive all the edges
connected to the current node also.For example let us take the graph.

                       1---------------2----------6
                       |               |          |
                       |               |          |
                       |               |          |
                       |               |          |
                       3---------------4----------5

Let us suppose 1 is initally affected  if we remove the node 1 along with edgee the graph looks like

                                       2----------6
                                       |          |
                                       |          |
                                       |          |
                                       |          |
                       3---------------4----------5

Now we are asked to find out the maximum no of nodes that will be unaffected by removing the edges

If we build the graph and try to remove the edges it will lead to time complexity.

Optimisation:We try to bulild the graph of those nodes which were not affected and try to find the no
of components which are connected to the current affected node and their component size.
We sum all those component sizes and store it in a variable cursum.
Now we find the maximum of all these cursum's and return the node.
Algorithm:
==> We store all the inital nodes which were affected by malware initally.

==> We try to build the graph for those  nodes which weren't there in the malware graph.

==>Then we need to find the different components connected to the current node for all edgess with current
node.For that we mantain unnordered_map<int,set<int>> mp
Here we mantain set for avoiding duplicacy of parents as there may nodes exists for which they belong
to the same parent
                               4------------1----------------2
                               |            |
                               |            |
                               |            6
                               |            |
                               3------------5------------7

    Let us suppose node 1 is affected it has edges with 1->4 and 1->6 and 1->2
if we manually add we get 3 components but if we observe it carefully the 4 and 6 belong to
the same component so total components are 2 only.Inorder to avoid these we maintain set
by storing parent of each componet
parent[6]=3 and parent[4]=3 both belong to the same parent

===>Whenever we are checking the no.of components we should also check the node which the 
current affected node is connected should not present in the malware map as it is waste check
as there exist another node which affects the component

==>As in the above question here also we maintain one infected array to store the number of 
affected nodes in that component.If it is more than >1 then that component gets affected without 
this node as there is one more node which affects the whole component.

==>At last we return index which has max sum of all connected compoonent sizes.  i.e., which
affect more nodes in the graph.

*/
int minMalwareSpreadII(vector<vector<int>> &graph,vector<int> &initial){
    int n=graph.size();
    vector<int> parent(n),size(n,1),infected(n,0);
    for(int i=0;i<n;i++) parent[i]=i;
    unordered_map<int,int> malware;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            /*i!=j and graph[i][j]==1 and i and j should not be ther in the malware map*/
          if(i!=j and graph[i][j]==1 and malware.find(i)==malware.end() and malware.find(j)==malware.end())
              unionBySize(i,j,parent,size);
        }
    }
    /*we mantain all those parent's of connected component which will be affected for the current node*/
    unordered_map<int,set<int>> mp;
    for(int i=0;i<initial.size();i++){
        int node=initial[i];
        for(int j=0;j<graph[node].size();j++){
            /*if the node->j j is also initillay affecte then no need to check*/
            if(node!=j and graph[node][j]==1 and malware.find(j)==malware.end()){
                int p=find(j,parent);
                if(mp[node].find(p)==mp[node].end()){
                    mp[node].insert(p);
                    /*counting the affeected nodes in the current component**/
                    infected[p]++;
                }
            }
        }
    }
    int ans=INT_MAX,maxSize=-1;
    for(int i=0;i<initial.size();i++){
        int node=initial[i],cursize=0;
        for(auto it:mp[node]){
            /*if and only if the infected node has only one affecting node*/
             if(infected[it]==1) cursize+=size[it]; 
        }
        if(cursize>=maxSize){
            if(cursize==maxSize) ans=min(ans,node);
            else ans=node;
            maxSize=cursize;
        }
    }
    return ans==-1?*min_element(begin(initial),end(initial)):ans;
}

int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int m,n;cin>>m>>n;
    vector<vector<int>> matrix(m,vector<int>(n));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++) {
            cin>>matrix[i][j];
        }
    } 
    vector<int> initial={1,2};
    //cout<<minMalwareSpread(matrix,initial);
    //matrixRankTransform(matrix);
    return 0;
}
