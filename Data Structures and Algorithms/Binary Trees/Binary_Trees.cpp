#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vii vector<vector<int>>
#define vs vector<string>
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
#define uns unsigned
#define ull unsigned long long int
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 10000
#define GlobalSpace 5
class Node{
    public:
    int data;
    Node *left;
    Node *right;
};
 Node *root=NULL;

Node* CreateNode()
{
    int x;cin>>x;
    Node* newnode=new Node();
    if(x==-1) return 0;
    
        newnode->data=x;
        newnode->left=CreateNode();
        newnode->right=CreateNode();
    
    return newnode;
}
void Preorder_Traversal(Node *headref)
{
    if(headref==NULL) return;
    cout<<headref->data<<" ";
    Preorder_Traversal(headref->left);
    Preorder_Traversal(headref->right);
}
void Postorder_Traversal(Node *headref)
{
    if(headref==NULL) return ;
    Postorder_Traversal(headref->left);
    Postorder_Traversal(headref->right);
    cout<<headref->data<<' ';
}
void Inorder_Traversal(Node *headref)
{
    if(headref==NULL) return;
    Inorder_Traversal(headref->left);
    cout<<headref->data<<' ';
    Inorder_Traversal(headref->right);

}
Node* GetNewNode(int data)
{
    Node *newnode=new Node();
    newnode->data=data;
    newnode->left=newnode->right=NULL;
    return newnode;
}
//Here by the recursion function we will implement the binaryseach using linked lists
//Here let us suppose that our recursive function will insert the given element at 
//at correct position and return the root pointer of tree
//Now the base condition of recursive function is that if the root pointer is null
//then we will create newnode and assign the value in root pointer
//Now the recurisve hypothesis is that 
//if(headref->data<data) then we have to position this data element in left subtree
//So it become thenewproblem with root value as headref->left 
//and we assume that the data will be placed in the correct position at left subtree and
//return the root pointer of that subtree
//so now we got a correct bst with all values positioned correctly and now
//we will assign the root pointer as left vaue of original root value
//same case works with if(headref->data>data)
//here make a note that we womt change any formal links only thing we will do is to add
//the new link
Node* Insert(Node *headref,int data)
{
    if(headref==NULL)
    {
        Node *newnode=GetNewNode(data);
        return newnode;
    }
    else if(data<=headref->data)
    {
         headref->left=Insert(headref->left,data);

    }
    else
    {
        headref->right=Insert(headref->right,data);
    }
    return headref;
}
Node* Insert_BST(Node *root,int data)
{
    if(root==NULL)
    {
        Node* newnode=GetNewNode(data);
        return newnode;
    }
    Node *child=root;
    Node* parent=root;
    while(child!=NULL)
    {
      parent=child;
      if(data<=child->data) child=child->left;
      else child=child->right;
    }
    if(data<=parent->data) parent->left=GetNewNode(data);
    else parent->right=GetNewNode(data);
    return root;
}
bool Search_BST(Node *root,int val)
{
    if(root==NULL) return false;
    if(root->data==val) return true;
    else
    {
        if(root->right!=NULL and root->data<=val) return Search_BST(root->right,val);
        else if(root->left!=NULL)  return Search_BST(root->left,val);
    }
    return false;
}
//Iterative approach of BST
Node* Search(Node *root,int val)
{
    if(root==NULL) return NULL;
    if(root->data==val) return root;
    Node* temp=root;
    while(temp!=NULL)
    {
        if(temp->data==val) return temp;
        else if(temp->data<val) temp=temp->right;
        else temp=temp->left;
    }
   return NULL;
}
//In this function we will print the binary search tree in same as graph in command prompt
//Let us divide the command prompt with space 5
//Since we approach this problem with a recursion
//Let us define a golbal space with 5
//At this position we will print the root
//Before we print we first print right value of root at root's position+global space
//Think if we have one root,onne left,one child
//In 2nd line we will print at 5th position in the above line from root;s 5th positionwe
//will add another 5 th pos then print right
//and same we will left tree
//As from the above example we will increase space by global space and print the right subterr part
//After prinring right subtree
//we come to new line
//then root must be printed with gap spae and global space
//we will iterate from global space to space and prnt " "
//then we come to next line
//and print the left subtree
void Print_BST(Node *root,int space)
{
   if(root==NULL) return;
   //Update space from root s position at space with global space
   space=space+GlobalSpace;
   //Print right subtree
   Print_BST(root->right,space);
   cout<<'\n';
   //Print spaces for root
   for(int i=GlobalSpace;i<=space;i++) cout<<' ';
   cout<<root->data;
   //After root data come to new line and print left subtree
   cout<<'\n';
   Print_BST(root->left,space);

}
int Height_BST(Node* root)
{
    if(root==NULL) return -1;
    return 1+max(Height_BST(root->left),Height_BST(root->right)); 
}
//Here we will traverse the binary search treee through breadth first traversal(BFS)
//In this bfs call we will traverse the tree level by level
//Print curr level function print the current level node
//Let us denote the current node was at height h from the root
//If this was h==0 then it means that we have reached the level from h height 
//then we will print the data
//So the two base conditions will be if(root==NULL) return;else if(level==0) cout<<root->data';
//Here we will first check whethere root was null or not in order to avoid segmenetation
//faults
//Then we recursively reach that node until the levle becomes 0 and we print left 
//element first and then right element as since theese are at same level
//Here we are printing the nodes which are at current level as all these level got same height
//so we will reach 0 by decrementing at ecah level and print the data
void Print_Curr_Level(Node *root,int level)
{
    if(root==NULL) return;
    else if(level==0) cout<<root->data<<' ';
    else
    {
        Print_Curr_Level(root->left,level-1);
        Print_Curr_Level(root->right,level-1);
    }
}
//BFS traversal
//this will caluclate the heigt of tree and pass each level to the above function
//iteratively
void BFS_Print(Node *root)
{
    int h=Height_BST(root);
    if(h==-1) return;
    for(int i=0;i<=h;i++)
    Print_Curr_Level(root,i);
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    root=Insert(root,8);
    Insert(root,1);
    Insert(root,9);
    Insert(root,6);
    Insert(root,9);
    Insert(root,11);
    Insert(root,5);
    Insert(root,3);
    Insert(root,13);
    Insert(root,10);
    Insert(root,2);
    Insert(root,15);
    Insert(root,14);
    // if(Search(root,14)) cout<<Search(root,14)->data;
    // else cout<<Search(root,14);
    //cout<<Height_BST(root);
   // Print_BST(root,3);
    BFS_Print(root);
   
    // root->right=NULL;
    // root->left=NULL;
    //root=CreateNode();
    
//    root=Insert(root,11);
//   root= Insert(root,6);
//     root=Insert(root,4);
//     root=Insert(root,5);

   // Preorder_Traversal(root);cout<<'\n';
    //Postorder_Traversal(root);cout<<'\n';
     //Inorder_Traversal(root);

     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 