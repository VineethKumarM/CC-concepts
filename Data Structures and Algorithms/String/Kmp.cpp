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
/*The prefix function for this string is defined as an array pi  of length , where pi[i] is the length of the longest proper prefix of the substring  which is also a suffix of this substring.
 A proper prefix of a string is a prefix that is not equal to the string itself. By definition, pi[0]=0.*/
 /*Trivial Algorithm for finding the lps array of the string:*/
vector<int> prefix_func(string &s){
   int n=s.size();
   vector<int> pi(n,0);
   pi[0]=0;/*By definition*/
   for(int i=1;i<s.size();i++){
      for(int k=0;k<=i;k++){
         if(s.substr(0,k)==s.substr(i-k+1,k)) 
           pi[i]=k;
      }
   }
   return pi;
}
/*We can see above function is O(n^3) complexity....we need to optimise it*/
vector<int> prefix_function(string &s){
   int n=s.size();
   vector<int> pi(n);pi[0]=0;
   for(int i=1;i<s.size();i++){
      int j=pi[i-1];
      while(j>0 and s[i]!=s[j])
       j=pi[j-1];
      if(s[i]==s[j]) j++;
      pi[i]=j;
   }
   return pi;
}

int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s="aaccbaacaa";
    vector<int> pi=prefix_func(s);
    for(int i:pi) cout<<i<<' ';cout<<'\n';
    pi=prefix_function(s);
     for(int i:pi) cout<<i<<' ';cout<<'\n';
    return 0;
 }
