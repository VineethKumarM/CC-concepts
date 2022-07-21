#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
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
/*Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
You must write an algorithm that runs in O(n) time.*/
int longest_consecutive_sequence(vi nums)
{
    unordered_map<int,bool> mp;
    for(auto val:nums) mp[val]=true;
    for(auto val:nums) if(mp.find(val-1)!=mp.end()) mp[val]=false;
    int max_l=0;
    for(auto val:nums)
    {
        if(mp[val]==false)
        {
            int tl=1;
            while(mp.find(val+tl)!=mp.end())
            tl++;
            max_l=max(max_l,tl);
        }
    }
   return max_l;
}
int main()
{
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;cin>>n;
    vector<vector<int>> costs(n,vector<int>(3,0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
        cin>>costs[i][j];
    }
    //cout<<min_cost_painting(costs);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}
