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
class UnionFind{
    vector<int> parent;
    public:
      UnionFind(int n){
          parent.resize(n);
          for(int i=0;i<n;i++) parent[i]=i;
      }
    int find(int x){
        if(parent[x]==x) return x;
         return parent[x]=find(parent[x]);
    }
    void Union(int u,int v){
        int pu=parent[u];int pv=parent[v];
        if(pu!=pv) parent[pu]=pv;
    }
     
};
class Solution {
public:
    vector<int> spf;
    bool gcdSort(vector<int>& nums) {
        int maxnum=*max_element(begin(nums),end(nums));
        sieve(maxnum+1);
        UnionFind uf(maxnum+1);
        for(int x:nums){
            for(int f:getprimefactors(x))
                uf.Union(x,f);
        }
        vector<int> sortednums(nums);
        sort(sortednums.begin(),sortednums.end());
        for(int i=0;i<nums.size();i++){
            if(uf.find(nums[i])!=uf.find(sortednums[i]))
                return false;
        }
        return true;
    }
    void sieve(int n){
       spf.resize(n);
        for(int i=2;i<n;++i) spf[i]=i;
        for(int i=2;i*i<n;i++){
            if(spf[i]!=i) continue;
            for(int j=i*i;j<n;j+=i){
                if(spf[j]>i) spf[j]=i;
            }
        }
    }
        vector<int> getprimefactors(int n){
            vector<int> factors;
            while(n>1){
                factors.push_back(spf[n]);
                n/=spf[n];
            }
            return factors;
        }
};
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
     Solution S;
    vector<int> v={22,2,10,20,18,2,10,20,16,9};
    cout<<S.gcdSort(v);
    return 0;
 }
