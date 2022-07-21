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
/*Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.
It is guaranteed that there is always possible to find a binary search tree with the given requirements for the given test cases.
A binary search tree is a binary tree where for every node, any descendant of Node.left has a value strictly less than Node.val, 
and any descendant of Node.right has a value strictly greater than Node.val.
A preorder traversal of a binary tree displays the value of the node first, then traverses Node.left, then traverses Node.right.*/
int minimumTotal(vector<vector<int>>& triangle) {
       for(int i=1;i<triangle.size();i++)
       {
           for(int j=0;j<triangle[i].size();j++)
           {
               int sum=0;
               if(j==0) 
               {
                   sum=triangle[i][j]+triangle[i-1][j];
               }
               else if(j==(triangle[i].size()-1))
               {
                   sum=triangle[i][j]+triangle[i-1][triangle[i-1].size()-1];
               }
               else
               {
                  int mini=min(triangle[i-1][j],triangle[i-1][j-1]);
                  sum=triangle[i][j]+mini;
               }
               triangle[i][j]=sum;
               //cout<<sum;
           }
       }
        int mini=INT_MAX;
      for(int i=0;i<triangle[triangle.size()-1].size();i++)
      {
        mini=min(mini,triangle[triangle.size()-1][i]);
      }
        return mini;
    }
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<vector<int>> triangle;
    triangle.pb({1});
    triangle.pb({2,3});
    triangle.pb({3,4,5});
    cout<<minimumTotal(triangle);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 