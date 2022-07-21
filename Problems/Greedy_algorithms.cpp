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
/*https://leetcode.com/problems/string-without-aaa-or-bbb/*/
/*There are generally 4 conditions that may occur.
a < 3 && b < 3
For this we simply print the string in any way we want as we will not get aaa or bbb as substring.
a >= 3 && b < 3
For this, we put b whenever the last 2 characters are aa as there may be a substring aaa.
a < 3 && b >= 3
For this, we put a whenever the last 2 characters are bb as there may be a substring bbb.
a >= 3 && b >= 3
For this, whenever we see aa as the last 2 characters, start printing b and whenever we see bb as the last 2 characters, start print a.*/
 string strWithout3a3b(int a, int b) {
        string s;
       while(a>0 or b>0)
       {
         if(s.size()>=2)
         {
           string temp="";
           temp=s[s.size()-1];
           temp+=s[s.size()-2];
            if(temp=="aa")
            {
              s+='b';
              b--;
            }else if(temp=="bb")
            {
              s+='a';
              a--;
            }else if(a>b)
            {
              s+='a';
              a--;
            }else
            {
              s+='b';
              b--;
            }
         }else
         {
           if(a>b)
           {
             s+='a';
             a--;
           }else
           {
             s+='b';
             b--;
           }
         }
       }
      return s;
    }
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}