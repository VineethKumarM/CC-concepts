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
struct TreeNode {
     int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
/*Level by level ordeer Traversal*/
vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root==NULL) return ans;
          queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            int max=q.size();
            vector<int> level;
            for(int i=0;i<max;i++)
            {
                TreeNode* node=q.front();
                q.pop();
                if(node->left!=NULL) q.push(node->left);
                if(node->right!=NULL) q.push(node->right);
                level.push_back(node->val);
            }
            ans.push_back(level);
        }
        return ans;
}
/*This is the construction of tree based on preorder and inorder traversal
Process:
Root node will be the first element of preorder tarversal
Left and right subtree will be constructed upon the ledt and right elements of 
root element in inorder tree
We will solve this problem using recursion*/
/*Here we maintain a global variable idx=0 as we keep on incrementing its value for
each recursion as we keep puttimg the values in the same order as inorder traversal from the
recorsion
Note that right tree starts buoilding only when whole left subtree is completed*/
int ind=0;
unordered_map<int,int> mp;
TreeNode* solve(vector<int> pre,vector<int> in,int lb,int ub)
{
    /*as we are changing the lb and ub values if(lb>ub) return NULL*/
        if(lb>ub) return NULL;
        /*Here we create the new memory for node*/
        TreeNode *res=new TreeNode();
        /*assign elemnt of preorder*/
        res->val=pre[ind++];
        /*if lb and ub are equal the it is the leaf chhild then return the function with this node pointer
        */
        if(lb==ub) return res;
        /*search this res->value in the inorder traversal and solve for remaining array
        //One important to note that here we used map instead of linear search as linear search
        will cost of O(n) complexiity and this total recursive call will cost of O(n^2) inorder to avoid that
        we have used linear search*/
        int mid=mp[res->val];
        res->left=solve(pre,in,lb,mid-1);
        res->right=solve(pre,in,mid+1,ub);
        return res;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i=0;i<preorder.size();i++) mp[inorder[i]]=i;
        TreeNode *root=solve(preorder,inorder,0,preorder.size()-1);
        return root;
}
 TreeNode* insert(TreeNode* root,int data)
   {
       if(root==NULL){root=new TreeNode();root->val=data;return root;}
       else if(root->val<data) root->left=insert(root->left,data);
       else root->right=insert(root->right,data);
       return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.size()==0) return NULL;
        TreeNode *root;
        root=insert(root,nums[0]);
        for(int i=1;i<nums.size();i++) 
        {
            insert(root,nums[i]);
        }
        return root;
    }
/*zig -zag traversal of binary tree*/
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root==NULL) return ans;
        queue<TreeNode *> q;
        q.push(root);
        bool flag=true;
        while(!q.empty())
        {
            int max=q.size();
            vector<int> level;
            for(int i=0;i<max;i++)
            {
                TreeNode *node=q.front();
                q.pop();
                if(node->left!=NULL) q.push(node->left);
                if(node->right!=NULL) q.push(node->right);
                level.push_back(node->val);
            }
            if(!flag) reverse(level.begin(),level.end());
            ans.push_back(level);
            flag=!flag;
        }
        return ans;
    }
/*flattening of binary tree*/
   void flatten(TreeNode* root) {
        if(root==NULL) return ;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty())
        {
            TreeNode *cur=st.top();
            st.pop();
            if(cur->right!=NULL) st.push(cur->right);
            if(cur->left!=NULL) st.push(cur->left);
            if(!st.empty()) cur->right=st.top();
            cur->left=NULL;
        }
    }
int min_1(vector<vector<int>>& triangle,int cur_x,int cur_y,int n,int m)
    {
        if(cur_x>n or cur_y>m) return 0;
        return max(triangle[cur_x-1][cur_y-1]+min_1(triangle,cur_x+1,cur_y+1,n,m),triangle[cur_x-1][cur_y-1]+min_1(triangle,cur_x,cur_y+1,n,m));
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        int n=triangle.size();
        int m=triangle[n-1].size();
        return min_1(triangle,1,1,n,m);      
    }
/*Count of nodes in a complete binary tree*/
int Leftheight(TreeNode *root)
    {
        if(root==NULL) return 0;
        return 1+Leftheight(root->left);
    }
     int Rightheight(TreeNode *root)
    {
        if(root==NULL) return 0;
        return 1+Rightheight(root->right);
    }
    int countNodes(TreeNode* root) {
        if(root==NULL) return 0;
        int left=Leftheight(root);
        int right=Rightheight(root);
        if(left==right)
        {
            return (1<<left)-1;
        }
        return 1+countNodes(root->left)+countNodes(root->right);
    }
/**/
/*Constructing the binary tree from inorder traversa;=l and postorder traversal
using recursion */
unordered_map<int,int> mp;
   TreeNode* buildTree_rec(vector<int> inorder,vector<int> postorder,int start,int end,int index)
   {
       if(start>end) return NULL;
       TreeNode *root=new TreeNode(postorder[index]);
       int inorderIndex=mp[postorder[index]];
       root->right=buildTree_rec(inorder,postorder,inorderIndex+1,end,index-1);
      root->left=buildTree_rec(inorder,postorder,start,inorderIndex-1,index-(end-inorderIndex)-1);
       return root;
   }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
           int n=inorder.size();
        if(n==0) return NULL;
        for(int i=0;i<n;i++) mp[inorder[i]]=i;
        return buildTree_rec(inorder,postorder,0,n-1,n-1);
        
    }
/*Soted array to height balanced bst*/
/*As the tree shoud be balance the middle element of nums array will be the root and letf part
of that nums will be lefttree and right willl be right subtree*/
TreeNode* build_tree(vector<int> nums,int start,int end)
   {
       if(start>end) return NULL;
       int mid=(start+end)/2;
       TreeNode *root=new TreeNode(nums[mid]);
       root->left=build_tree(nums,start,mid-1);
       root->right=build_tree(nums,mid+1,end);
       return root;
   }
   /*To check whether a tree is balanced or not*/
bool ans=true;
    int isbalanced(TreeNode* root)
    {
        if(root==NULL) return 0;
        if(!ans) return 0;
        int l=isbalanced(root->left);
        int r=isbalanced(root->right);
        if(abs(l-r)>1) ans=0;
        return max(l,r)+1;
    }
    bool isBalanced(TreeNode* root) {
        if(root==NULL) return true;
        ans=true;
       isbalanced(root);
        return ans;
    }
/*Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.
Note that the root node is at depth 1.
The adding rule is:
Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
cur's original left subtree should be the left subtree of the new left subtree root.
cur's original right subtree should be the right subtree of the new right subtree root.
If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.*/
//https://leetcode.com/problems/add-one-row-to-tree/
//Here we will keep thhe list of nodes in previouslevel then we add the rows
 TreeNode* addOneRow(TreeNode* root, int val, int depth) {
       if(depth==1)
       {
         TreeNode* node=new TreeNode(val);
         node->left=root;
         return node;
       }
      queue<TreeNode*> q;
      q.push(root);
      queue<TreeNode*> temp;
      while(depth-->1)
      {
        int size=q.size();
        temp=q;
        for(int i=0;i<size;i++)
        {
          TreeNode *node=q.front();
          q.pop();
          if(node->left!=NULL)
            q.push(node->left);
          if(node->right!=NULL)
            q.push(node->right);
        }
      }
      q=temp;
      while(q.size()>0)
      {
        TreeNode *node=q.front();
        q.pop();
        TreeNode* temp=node->left;
        TreeNode* newnode=new TreeNode(val);
        node->left=newnode;
        newnode->left=temp;
        newnode=new TreeNode(val);
        temp=node->right;
        node->right=newnode;
        newnode->right=temp;
      }
      return root;
    }
      
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cout<<"Hello World!";
    //TreeNode *root=NULL;
    vector<vector<int>> ans;
    ans.pb({1});
    ans.pb({2,3});
    ans.pb({4,5,6});
    //cout<<ans[2].size();
    cout<<minimumTotal(ans);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 