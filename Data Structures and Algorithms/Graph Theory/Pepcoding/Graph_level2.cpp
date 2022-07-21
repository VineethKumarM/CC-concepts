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
/*Given an m*n binary matrix mat, return the number of distinct island.
An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected)\
 to equal the other.*/
vector<pair<int,char>> dx={{-1,'U'},{0,'R'},{1,'D'},{0,'L'},{-1,'Z'}};
void path(int row,int col,vector<vector<int>>&graph,string &psf){
     graph[row][col]=0;
     for(int i=0;i<4;i++){
        int nr=row+dx[i].first,nc=col+dx[i+1].first;
         if(nr<0 or nc<0 or nr>=graph.size() or nc>=graph[0].size() or graph[nr][nc]==0) continue;
         psf+=(dx[i].second);
         path(nr,nc,graph,psf);
         psf+='Z';
     }
    psf+='Z';
}
int distinct_islands(vector<vector<int>> &graph){
    int m=graph.size(),n=graph[0].size();
    set<string> s;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
           if(graph[i][j]==1){
             string p="x";
             path(i,j,graph,p);
             p+="Z";
             s.insert(p);
           }
        }
    }
    return s.size();
}
/*Given an m*n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.
We use reverse bfs here*/
vector<vector<int>> min_distance_1_0(vector<vector<int>> &graph){
    vector<int> dir={-1,0,1,0,-1};
    queue<pair<int,int>> q;
    for(int i=0;i<graph.size();i++){
        for(int j=0;j<graph[0].size();j++){
            if(graph[i][j]==0) q.push(make_pair(i,j));
            else graph[i][j]*=(-1);
            //cout<<graph[i][j]<<' ';
        }
    }
    while(q.size()>0){
        auto p=q.front();q.pop();
        for(int i=0;i<4;i++){
            int nr=p.first+dir[i],nc=p.second+dir[i+1];
            if(nr<0 or nc<0 or nr>=graph.size() or nc>=graph[0].size() or graph[nr][nc]>=0) continue;
            graph[nr][nc]=(1+graph[p.first][p.second]);
            q.push(make_pair(nr,nc));
        }
    }
    return graph;
}
/*Rotten Oranges
You are given an m * n matrix containing 0, 1 or 2 , where 0 represents an empty cell, 1 represents a fresh orange,
 2 represents rotten orange. Every hour, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
Print the minimum number of hours that must elapse until no cell has a fresh orange.

In case if all the oranges can't become rotten print -1*/
int orangeRotting(vector<vector<int>> &graph){
    queue<pair<int,int>> q;
    vector<int> dir={-1,0,1,0,-1};
    int m=graph.size(),n=graph[0].size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(graph[i][j]==2) q.push(make_pair(i,j));
        }
    }
    int time=0;
    while(q.size()>0){
        int sz=q.size();
        for(int i=0;i<sz;i++){
            auto x=q.front();q.pop();
            for(int j=0;j<4;j++){
                int nr=x.first+dir[j],nc=x.second+dir[j+1];
                if(nr<0 or nc<0 or nr>=m or nc>=n or graph[nr][nc]!=1) continue;
                graph[nr][nc]=2;
                q.push(make_pair(nr,nc));
            }
        }
        if(q.size()>0) time++;
    }
    bool flag=false;
    for(int i=0;i<m;i++) for(int j=0;j<n;j++) flag|=(graph[i][j]==1);
    return flag?-1:time;
}
/*Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land,
 find a water cell such that its distance to the nearest land cell is maximized, and return the distance.
  If no land or water exists in the grid, return -1.

The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0)
 and (x1, y1) is |x0 - x1| + |y0 - y1|.
*/
int maxDistance_land(vector<vector<int>> &grid){
    queue<pair<int,int>> q;
    vector<int> dir={-1,0,1,0,-1};
    int m=grid.size(),n=grid[0].size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]==1) {
                /*reinitialise it to 0 otherwise we add 1+graph[i][j] whcih leads to 1 extra max due to 1*/
                grid[i][j]=0;
                q.push({i,j});
            }
            else grid[i][j]=-1;
        } 
    }
    /*maxd=-1 as if no land or water exists it returns -1 not 0*/
    int maxd=-1;
    while(q.size()>0){
        auto x=q.front();q.pop();
        for(int i=0;i<4;i++){
            int nr=x.first+dir[i],nc=x.second+dir[i+1];
            if(nr<0 or nc<0 or nr>=m or nc>=n or grid[nr][nc]>=0) continue;
            grid[nr][nc]=1+grid[x.first][x.second];
            q.push({nr,nc});
            maxd=max(maxd,grid[nr][nc]);
        }
    }
    return maxd;
}
/*You are given an n x n binary matrix grid where 1 represents land and 0 represents water.

An island is a 4-directionally connected group of 1's not connected to any other 1's. 
There are exactly two islands in grid.

You may change 0's to 1's to connect the two islands to form one island.

Return the smallest number of 0's you must flip to connect the two islands.*/
vector<int> dir={-1,0,1,0,-1};
void shortestBridge_dfs(int row,int col,vector<vector<int>> &grid,queue<pair<int,int>> &q){
    if(row<0 or col<0 or row>=grid.size() or col>=grid[0].size() or grid[row][col]!=1)
     return;
     grid[row][col]=-1;
     q.push({row,col});
     for(int i=0;i<4;i++)
      shortestBridge_dfs(row+dir[i],col+dir[i+1],grid,q);
}
int shortestBridge(vector<vector<int>> &grid){
     int m=grid.size(),n=grid[0].size();
     queue<pair<int,int>> q;
     for(int i=0;i<m;i++){
        bool flag=false;
        for(int j=0;j<n;j++){
            if(grid[i][j]==1) {
                shortestBridge_dfs(i,j,grid,q);
                flag=true;
            }
        }
        if(flag) break;
     }
     int dist=0;
     while(q.size()>0){
         int sz=q.size();
         for(int i=0;i<sz;i++){
            auto x=q.front();q.pop();
            for(int j=0;j<4;j++){
                int nr=x.first+dir[j],nc=x.second+dir[j+1];
                if(nr<0 or nc<0 or nr>=m or nc>=n or grid[nr][nc]==-1) continue;
                if(grid[nr][nc]==1) return 1+dist;
                grid[nr][nc]=-1;
                q.push(make_pair(nr,nc));
            }
         }
         dist++;
     }
     return dist;
}
/*Bus Routes
You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.*/
int numBusesToDestinatoon(vector<vector<int>> &routes,int source,int target){
    unordered_map<int,vector<int>> busRoutes;
    for(int i=0;i<routes.size();i++){
        for(int j=0;j<routes[0].size();j++){
            busRoutes[routes[i][j]].push_back(i);
        }
    }
    unordered_map<int,bool> vis_routes,vis_buses;
    int numBuses=0;
    queue<int> q;q.push(source);
    vis_routes[source]=true;
    while(q.size()>0){
        int sz=q.size();
        for(int i=0;i<sz;i++){
            int x=q.front();q.pop();
            if(x==target) return numBuses;
            for(int j=0;j<busRoutes[x].size();j++){
                int route=busRoutes[x][j];
                if(vis_routes.find(route)==vis_routes.end()){
                    for(int k=0;k<routes[route].size();k++){
                        if(vis_buses.find(routes[route][k])==vis_buses.end()){
                            q.push(routes[route][k]);
                            vis_buses[routes[route][k]]=true;
                        }
                    }
                    vis_routes[route]=true;
                }
            }
        }
        numBuses++;
    }
    return -1;
}
/*Another solution*/
int numBusesToDestination(vector<vector<int>> &routes,int source,int target){
    unordered_map<int,vector<int>> mp;
         for(int i=0;i<routes.size();i++){
             for(int j:routes[i]) mp[j].push_back(i);
         }
         queue<pair<int,int>> q;q.push({source,0});
         unordered_set<int> vis={source};
         while(!q.empty()){
            int bus_stop=q.front().first,buses_sf=q.front().second;q.pop();
             if(bus_stop==target) return buses_sf;
             for(int i:mp[bus_stop]){
                 for(int j:routes[i]){
                     if(vis.find(j)==vis.end()){
                         vis.insert(j);
                         q.push(make_pair(j,buses_sf+1));
                     }
                 }
                 routes[i].clear();
             }
         }
      return -1;
}
/*sliding puzzle*/
int slidingPuzzle(vector<vector<int>> &board){
    string root="",target="123450";
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            root+=(to_string(board[i][j]));
        }
    }
    vector<vector<int>> swapIndex={{1,3},{0,2,4},{1,5},{0,4},{3,1,5},{2,4}};
    unordered_map<string,int> mp;
    queue<pair<string,pair<int,int>>> q;
    int zero=0;
    for(int i=0;i<root.size();i++) if(root[i]=='0') zero=i;
    q.push({root,{zero,0}});mp[root]=true;
    while(q.size()>0){
          string x=q.front().first;int ind=q.front().second.first,swaps=q.front().second.second;
          q.pop();
         if(x==target) return swaps;
         for(int i=0;i<swapIndex[ind].size();i++){
             swap(x[ind],x[swapIndex[ind][i]]);
             if(mp.find(x)==mp.end()){
                mp[x]=true;
                q.push({x,{swapIndex[ind][i],swaps+1}});
             }
             swap(x[ind],x[swapIndex[ind][i]]);
         }
    }
    return -1;
}
/*Minimum Number of swaps to sort an array*/
int minSwaps(vector<int> &arr){
    vector<pair<int,int>> temp;
    for(int i=0;i<arr.size();i++) temp.push_back({arr[i],i});
    sort(begin(temp),end(temp));
    int res=0;
    vector<bool> vis(arr.size(),false);
    for(int i=0;i<arr.size();i++){
        if(vis[i]==true or temp[i].second==i) continue;
        int cLen=0,j=i;
        while(vis[j]==false){
            vis[j]=true;
            j=temp[j].second;
            cLen++;
        }
        res+=(cLen-1);
    }
    return res;
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // int m,n;cin>>m>>n;
    //vector<vector<int>> graph={{1,2,3},{4,0,5}};
     //cout<<slidingPuzzle(graph);
    //cout<<numBusesToDestinatoon(graph,1,6);
    vector<int> arr={2,3,1,4,6,5};
    cout<<minSwaps(arr);
    return 0;
 }
