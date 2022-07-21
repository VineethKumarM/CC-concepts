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
vi parent;
int find_set(int node)
{
    if(parent[node]==node) return node;
    else
     return find_set(parent[node]);
}
void union_set(int a,int b)
{
    a=find_set(a);
    b=find_set(b);
    if(a==b) return;
    else
    parent[b]=a;
}
//Teachers Dilemma for choosing grp leaders
//This method give TLE we choose differnet methods
int find(int a)
{
    if(parent[a]<0) return a;
    else return find(parent[a]);
}
void Union(int a,int b)
{
     parent[a]+=parent[b];
     parent[b]=a;
}
//Path_Compression
int find_pathcompr(int a)
{
    if(parent[a]<0) return a;
    else return parent[a]=find_pathcompr(parent[a]); 
    //Iteratve approach
    // vi v;
    // while(parent[a]<0)
    // {
    //     v.pb(a);
    //     a=parent[a];
    // }
    // for(int i=0;i<v.size();i++)
    // parent[v[i]]=a;
}
void Union_pathCompr(int a,int b)
{
    if(parent[a]!=parent[b])
    {
        parent[a]+=parent[b];
        parent[b]=a;
    }
     return;
}
//Owl problem
int find_owl(int a)
{
    if(parent[a]<0) return a;
    else return parent[a]=find_owl(parent[a]);
}
void union_owl(int a,int b)
{
    if(parent[a]!=parent[b]) 
    {
        parent[a]=min(parent[b],parent[a]);
        parent[b]=a; 
    }
    return;
}
//Union by rank
vector<int> Rank;
int find_rank_parent(int a)
{
    if(parent[a]<0) return a;
    else return find_rank_parent(parent[a]);
}
void union_rank(int a,int b)
{
   a=find_rank_parent(a);
   b=find_rank_parent(b);
   if(a==b) return ;
   else
   {
       if(Rank[a]>Rank[b])
         {
             parent[b]=a;
             Rank[a]+=Rank[b];
         }
         else
         {
             parent[a]=b;
             Rank[b]+=Rank[a];
         }
   }
}
vector<int> solve(vector<int> &A) {
    unordered_map<int,priority_queue <int, vector<int>, greater<int>>> mp;
    for(int i=0;i<A.size();i++){
        if(mp.find(A[i])==mp.end()){
            mp[A[i]].push(i);
        }else{
            int ind=mp[A[i]].top();
            int val=A[ind]+1;
            A[ind]=val;
            mp[A[i]].pop();
           // if(mp[A[i]].size()==0) mp.erase(A[i]);
            mp[val].push(ind);
            mp[A[i]].push(i);
        }
    }
    return A;
}

int main()
{
    //freopen("Input.txt", "r", stdin); 
    // freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //int n,m;cin>>n>>m;
  //  parent.resize(n+1,-1);
  //  Rank.resize(n+1,1);
    
  //  while(m--)
    //{
        //int a,b;
      //  cin>>a>>b;
        //a=find(a),b=find(b);
        // if(a!=b)
        //  Union(a,b); 
   // }
    //int ans=1;
    // for(int i=1;i<=n;i++)
    // {
    //   if(parent[i]<0) ans*=abs(parent[i]);
    // }
    // cout<<ans;
//    cout<<find_set(9);
//    union_set(1,9);
//    cout<<find_set(1);
 // cout<<find_rank_parent(1);
 vector<int> A={1,2,1,2};
 A=solve(A);
 for(int i=0;i<A.size();i++) cout<<A[i]<<' ';
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 