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
/*A trie is a n-array tree where each parent can have n number of childs*/
struct TreeNode{
       char ch;
       TreeNode* child[26];
       int wordend;
};
/*Above Structure is a basic trie structure having 26 children 
The above structure is basically a dictionary
Root Properties of Trie;
it doesn't have the char and wordend will always be 0 but it has 26 child pointers
*/
/*Uses of trie
1.It can be used in dictionary (to store words and to search words)
2.The time complexity of search store and remove of a word in a dictionary is of O(word length time)
3.it is very good in finding prefixes 
4.Ordered and structured data strucutre*/
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}


