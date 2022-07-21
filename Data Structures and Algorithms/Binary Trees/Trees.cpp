#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vb vector<bool>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
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
const ull mod1=1e9+7;
int arr[100003][4];
int dp[1000][4];
//Node definition
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
//Creating the newnode
struct Node* newNode(int data)
{
    struct Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
//Here we are inserting the node into the tree
struct Node* insert(struct Node* root, int data)
{
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}
//Here is the inoder traversal of BST
void inorder_Traversal(struct Node* root)
{
    if (root != NULL) {
        inorder_Traversal(root->left);
        cout << root->data << " ";
        inorder_Traversal(root->right);
    }
}
//This Functions deletes the leaf of BST
struct Node* Delleaf(struct Node* root)
{
    if (root == NULL)
        return NULL;
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }
    root->left = Delleaf(root->left);
    root->right = Delleaf(root->right);
    return root;
}
//Here is the oreirder traversal of BST
void Preorder_Traversal(struct Node* node)
{
    if (node == NULL)
        return;
    cout << node->data << " ";
    Preorder_Traversal(node->left);
    Preorder_Traversal(node->right);
}
int main()
{
    struct Node* root = NULL;//Intialsing the root with null Pointer
    int n;
    cin>>n;
    while(n--)
    {
        int m;
        cin>>m;
        if(root==NULL)
        root = insert(root,m);
        else 
        insert(root,m);
    }
    Delleaf(root);
    Preorder_Traversal(root);
    cout<<endl;
    inorder_Traversal(root);
}