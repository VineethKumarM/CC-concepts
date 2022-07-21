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
union abc{
    int a;
    char b;
    double c;
};
struct TreeNode{
     int val;  
     TreeNode* left;
     TreeNode* right; 
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
int solve(vector<int> &sweets,int k) {
    priority_queue<int> pq(begin(sweets),end(sweets));
    int res=0;
    while(k--){
        int x=pq.top();pq.pop();
        res+=x;
        pq.push(x/2);
    }
    return res;
}
int main()
{
   // freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //union abc var;
    //var.a=90;
    //cout<<var.a<<' '<<var.b<<' '<<var.c<<'\n';
    vector<int> v={1,2,1,3,4},wt={15,14,10,45,30};
  //  unboundedKnapsack(v.size(),wt,v,7);
    std::set<int> set {1, 2, 4, 5, 6};
    int number = 3;
    std::cout<<std::distance(set.begin(), set.lower_bound(number))<<std::endl;

    return 0;
} 