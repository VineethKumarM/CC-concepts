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
/*
Additive number is a string whose digits can form additive sequence.
A valid additive sequence should contain at least three numbers.
Except for the first two numbers, each subsequent number in the sequence
 must be the sum of the preceding two.
Given a string containing only digits '0'-'9', 
write a function to determine if it's an additive number.
Note: Numbers in the additive sequence cannot have leading zeros, 
so sequence 1, 2, 03 or 1, 02, 3 is invalid.
*/
/*Main thing in this problem is to select the lengths of two number so that the additivity is valid
so that we check recursively for further conditions
so for choosing the corect lenght of s1 and s2 we will use the backtracking 
First we will fix the size of s1 and s2 and check for remainging size and after all possibilites 
we increase the s1 sizea and do the same
We run two for loops for for both s1 and s2
in the recursive function we will pass 4 paramters ll n1,ll n2,remaining string and bool variable found
List of possibilities:
We will retunn true when we are left string whose size as 0 after checking all possibilities
recursively.
It may happen that the first two strings in the first call of rec function they may have 
exhausted whole string.in this case also we are left the string size is 0 but it should return false
as we got only two numbbers until now 
So to keep tarck of this thing we will pass thisflag varible with this function and we set false
to for the first class and for the remaining calls we set to true
and we return true if and only if flag==true and s.size()==0
Here we should make sure of another conditon is that we should avoid leadijg 0s in first two strings
and twp strings
for that we will convert the string to long long it and again convert the curent ll to string we
comapare the strings and if they have same size then continue else break from loop  check for
remaing strings
*/
/*here is the valid recursive function that checks recursively
whether a string is a valid additive number*/
bool valid(ll n1,ll n2,string s,bool flag){
    //return true only when flag is also true
    if(s.size()==0 and flag==true)
      return true;
      /*next stringto be presnet*/
      string n3=to_string(n1+n2);
      /*to avoid overflowss of substring we take the minimum of idx*/
      int idx=min(s.size(),n3.size());
      /*If both are equal then we return thr rec function*/
      if(n3==s.substr(0,idx))
         return valid(n2,stol(n3),s.substr(idx),true);
         /*else return false*/
        return false;
}
bool is_additive(string s){
    int n=s.size();
    for(int i=1;i<n-1;i++){
        /*conditions to be checked before string as we should take care leading zeroes*/
         ll n1=stol(s.substr(0,i));
          if(to_string(n1)!=s.substr(0,i))
            break;
        for(int j=i+1;j<n;j++){
            /*Here the substring starts from ith index it has length j-i*/
             ll n2=stol(s.substr(i,j-i));
          if(to_string(n2)!=s.substr(i,j-i))
            break;
            /*make anote that we pass remainibg substring at each iteration not the whole string*/
            bool found=valid(n1,n2,s.substr(j),false);
            if(found) return true;
        }
    }
    return false;
}
class Solution {
public:
  struct compare{
        bool operator()(const pair<int,string>&a, const pair<int,string>&b){
            if(a.first!=b.first) return a.first>b.first;
               return a.second<b.second;
            
        };
    };
    
    vector<string> topKFrequent(vector<string>& words, int k) {
      
        unordered_map<string,int> mp;
        for(int i=0;i<words.size();i++)
          mp[words[i]]++;
        vector<pair<int,string>> v;
        for(auto it:mp)
          v.push_back({it.second,it.first});
          sort(v.begin(),v.end(),compare());
        vector<string> ans;
          for(int i=0;i<k;i++) ans.push_back(v[i].second);
      return ans;
    }
};
/*https://leetcode.com/problems/rectangle-overlap/*/
bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
       if((rec1[2]<=rec2[0]) or (rec1[1]>=rec2[3]) or (rec1[0]>=rec2[2]) or (rec1[3]<=rec2[1]))
         return false;
      return true;
    }
int main()
{
    freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s="011";
     cout<<is_additive(s);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 