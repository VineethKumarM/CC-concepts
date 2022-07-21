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
struct TreeNode{
     int val;  
     TreeNode* left;
     TreeNode* right; 
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*We can get preorder and postorder dfs from this algorithm*/
void iterative_dfs(TreeNode* root){
    unordered_map<TreeNode*,bool> vis;
    stack<TreeNode*> st;
    st.push(root);
    while(st.size()>0){
         TreeNode* cur=st.top();st.pop();
         if(vis.find(cur)!=vis.end()) continue;
         vis[cur]=true;
         cout<<cur->val<<' ';
         if(cur->left and vis.find(cur->left)==vis.end()) st.push(cur->left);
         if(cur->right and vis.find(cur->right)==vis.end()) st.push(cur->right);
    }
}
void iterative_dfs_inorder(TreeNode* root){
   TreeNode* cur=root;
   stack<TreeNode*> st;
   while(cur!=NULL or st.size()>0){
       while(cur!=NULL){
          st.push(cur);
          cur=cur->left;
       }
       cur=st.top();st.pop();
       cout<<cur->val<<' ';
       cur=cur->right;
   }
}
int main()
 {
    ios_base::sync_with_stdio(false);
    TreeNode* root=new TreeNode(0);
    root->left=new TreeNode(1);root->right=new TreeNode(2);
    root->left->left=new TreeNode(3);root->left->right=new TreeNode(4);
    root->right->left=new TreeNode(5);root->right->right=new TreeNode(6);
    iterative_dfs_inorder(root);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
