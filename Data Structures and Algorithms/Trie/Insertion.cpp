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
struct TrieNode{
       TrieNode* child[26];
       bool isEnd;
};
TrieNode* root=new TrieNode();
void insert(string s){
      TrieNode* cur=root;
      for(int i=0;i<s.size();i++){
          if(cur->child[s[i]-'a']==NULL)
            cur->child[s[i]-'a']=new TrieNode();
            cur=cur->child[s[i]-'a'];
      }
      /*Here we should make it to true todenote that a word exist that ends with this last charcater */
      cur->isEnd=true;
}
bool search(string s){
    TrieNode* cur=root;
    for(int i=0;i<s.size();i++){
        if(cur->child[s[i]-'a']==NULL) return false;
        cur=cur->child[s[i]-'a'];
    }
    return cur->isEnd;
}
bool isprefix(string s){
    TrieNode* cur=root;
    for(int i=0;i<s.size();i++){
        if(cur->child[s[i]-'a']==NULL) return false;
        cur=cur->child[s[i]-'a'];
    }
    return cur->isEnd;
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<string> v(5);
    for(int i=0;i<5;i++) cin>>v[i];
    for(int i=0;i<5;i++) insert(v[i]);
    string s;cin>>s;cout<<search(s);
    return 0;
 }
