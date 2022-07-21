#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vvii vector<vector<int>>
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
#define ull unsigned long long int
#define ld long double
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 10000
int Longest_Valid_Parantheses(string s){
    stack<int> st;st.push(-1);
    int ans=0;
    for(int i=0;i<s.size();i++){
        if(s[i]=='('){
            st.push(i);
        }else{
            st.pop();
            if(st.size()==0){
                st.push(i);
            }else{
                int len=i-st.top();
                ans=max(ans,len);
            }
        }
    }
    return ans;
}
/*https://leetcode.com/problems/score-of-parentheses/submissions/*/
 int scoreOfParentheses(string s) {
       int count=0;
      stack<int> st;
      for(int i=0;i<s.size();i++)
      {
        if(s[i]=='(')
          st.push(0);
        else
        {
          int val=0;
          while(st.top()!=0) 
          {
            val+=st.top();
            st.pop();
          }
          val=max(2*val,1);
          st.pop();
          st.push(val);
        }
      }
        while(st.size()>0)
        {
          count+=st.top();
          st.pop();
        }
      return count;
    }
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 