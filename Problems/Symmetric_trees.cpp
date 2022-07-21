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
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*This is the recurisve solution to judge whether a tree is symmetric or not
Since the approach is recursion based this code is little slow*/
bool ismirror(TreeNode *left,TreeNode* right)
    {
        if(!left and !right) return true;
        if(!left or !right) return false;
        if(left->val==right->val)
            return ismirror(left->left,right->right) and ismirror(left->right,right->left);
        else return false;
 }
 /*This is the itertative solution that uses two queues
 It is the optimised code rather than former*/
bool isSymmetric(TreeNode* root) {
       // if(root==NULL) return true;
      TreeNode *node1,*node2;
        queue<TreeNode *> q1;
        queue<TreeNode *> q2;
        q1.push(root);
        q2.push(root);
        while(!q1.empty() and !q2.empty())
        {
            node1=q1.front();q1.pop();
            node2=q2.front();q2.pop();
            if(!node1 and !node2) continue;
            if(!node1 or !node2) return false;
            if(node1->val!=node2->val) return false;
            q1.push(node1->left);
            q1.push(node1->right);
            q2.push(node2->right);
            q2.push(node2->left);
        }
        return true;
 }
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 