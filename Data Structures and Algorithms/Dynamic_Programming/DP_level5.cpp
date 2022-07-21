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
int highwayBillBoard(int m,int n,vector<int> &boards,vector<int> revenue,int dist){
    vector<int> dp(n,0);
    dp[0]=revenue[0];
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            int cur_dist=boards[i]-boards[j];
            if(cur_dist>dist) dp[i]=max(dp[i],dp[j]);
        }
        dp[i]+=revenue[i];
    }
    return *max_element(begin(dp),end(dp)); 
    unordered_map<int,int> mp;
    for(int i=0;i<boards.size();i++) mp[boards[i]]=revenue[i];
    dp.resize(m,0);
    dp[0]=mp[0];
    for(int i=0;i<=m;i++){
        if(mp.find(i)==mp.end()) dp[i]=dp[i-1];
        else{
            if(i-dist-1>=0) dp[i]=max(dp[i-1],dp[i-dist-1]+mp[i]);
            else dp[i]=mp[i];
        }
    }
    return dp[m-1];
}
/*dp[i][j]=0 if mat[i][j]=0
else dp[i][j]=1+min(dp[i+1][j],min(dp[i+1][j+1],dp[i][j+1])*/
int largestSquareSubMatrix(vector<vector<int>> &matrix){
    int res=0;
    vector<vector<int>> dp(matrix.size(),vector<int>(matrix[0].size(),0));
    for(int i=matrix.size()-1;i>=0;i--){
        for(int j=matrix[0].size()-1;j>=0;j--){
            if(matrix[i][j]==0) dp[i][j]=0;
            else if(i==matrix.size()-1) dp[i][j]=matrix[i][j];
            else if(j==(matrix[0].size()-1)) dp[i][j]=matrix[i][j];
            else{
                dp[i][j]=1+min(dp[i+1][j],min(dp[i+1][j+1],dp[i][j+1]));
            }
            res=max(res,dp[i][j]);
        }
    }
    return res;
}
/*
_________________________________________________Approach________________________________________

dp[i]=min no.of steps to reach from i to end of the destination.

if(jumps[i]==0) dp[i]=INT_MAX;
we will calucate the min steps i to maxJump dp[i]=1+min(dp[i+1],dp[i+2],..dp[i+maxsteps]);
___________________________________________________________________________________________________
*/
int minJumps(vector<int> &jumps){
    int n=jumps.size();
    vector<int> dp(n,0);
    for(int i=n-1;i>=0;i--){
        int mini=INT_MAX,maxJumps=jumps[i];
        if(jumps[i]==0){
            dp[i]=INT_MAX;
            continue;
        }
        while(maxJumps--){
            if(i+maxJumps<n){
                mini=min(dp[i+maxJumps],mini);
            } 
        }
        dp[i]=mini;
    }
    return dp[0];
}
void minCostPrintPath(vector<vector<int>> &grid){
    int m=grid.size(),n=grid[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    for(int i=m-1;i>=0;i--){
        for(int j=n-1;j>=0;j--){
            if(i==m-1 and j==n-1) dp[i][j]=grid[i][j];
            else if(j==n-1) dp[i][j]=dp[i+1][j]+grid[i][j];
            else if(i==m-1) dp[i][j]=dp[i][j+1]+grid[i][j];
            else{
                dp[i][j]=grid[i][j]+min(dp[i+1][j],dp[i][j+1]);
            }
        }
    }
    cout<<dp[0][0]<<'\n';
    queue<pair<string,pair<int,int>>> q;
    q.push({"",{0,0}});
    while(q.size()>0){
        auto x=q.front();q.pop();
        int minNext=INT_MAX,i=x.second.first,j=x.second.second;
        if(i+1<m) minNext=min(minNext,dp[i+1][j]);
        if(j+1<n) minNext=min(minNext,dp[i][j+1]);
        bool flag=false;
        if(i+1<m and dp[i+1][j]==minNext){
            x.first+="H";
            q.push({x.first,{i+1,j}});
            x.first.pop_back();
            flag=true;
        }
        if(j+1<n and dp[i][j+1]==minNext){
               x.first+="V";
               q.push({x.first,{i,j+1}});
               x.first.pop_back();
               flag=true;
        }
        if(flag==false) {
            cout<<x.first<<'\n';
        }
    }
}
int maxGoldPath(vector<vector<int>> &grid){
    int m=grid.size(),n=grid[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    int res=INT_MIN;
    for(int j=n-1;j>=0;j--){
        for(int i=m-1;i>=0;i--){
            if(j==(n-1)) dp[i][j]=grid[i][j];
            else{
                if(i+1<m and j+1<n) dp[i][j]=max(dp[i+1][j+1],dp[i][j]);
                if(j+1<n) dp[i][j]=max(dp[i][j],dp[i][j+1]);
                if(i-1>=0 and j+1<n) dp[i][j]=max(dp[i-1][j],dp[i][j]);
                dp[i][j]+=grid[i][j];
            }
             if(j==0) res=max(res,dp[i][j]);
        }
    }
    queue<pair<string,pair<int,int>>> q;
    for(int i=0;i<m;i++) if(dp[i][0]==res) q.push({"",{i,0}});
    while(q.size()>0){
        auto x=q.front();q.pop();
        int i=x.second.first,j=x.second.second;
        int nextMax=INT_MIN;bool flag=false;
        if(i+1<m and j+1<n) nextMax=max(nextMax,dp[i+1][j+1]);
        if(j+1<n) nextMax=max(nextMax,dp[i][j+1]);
        if(i-1>=0 and j+1<n) nextMax=max(nextMax,dp[i-1][j+1]);
        if(i+1<m and j+1<n and dp[i+1][j+1]==nextMax){
             x.first+="d3";
             q.push({x.first,{i+1,j+1}});
             x.first.pop_back();
             flag=true;
        }
        if(j+1<n and dp[i][j+1]==nextMax){
            x.first+="d2";
            q.push({x.first,{i,j+1}});
            x.first.pop_back();
            flag=true;
        }
        if(i-1>=0 and j+1<n and dp[i-1][j+1]==nextMax){
            x.first+="d1";
            q.push({x.first,{i-1,j+1}});
            x.first.pop_back();
            flag=true;
        }
        if(flag==false) cout<<x.first<<'\n';
    }
} 
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
