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
/*Given an input string (s) and a pattern (p), implement wildcard pattern
 matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
*/
/*
  We have to determine whether the current string matches the pattern or not

We build a dp table considering the following 3 cases depending upon pattern character

Consider two strings: s="baabab"  b="ba*a?"

dp[i][j] states that whether the string from i to end of the string in pattern matches 
the whole string starting from j

for example dp[3][4] is whether "a?" matches "ab" or not

So we build the dp table as follows:

Case1: If the pattern character is an alpha character then we check whether
current pattern character matches with string character.
   if it matches with the character dp[i][j]=dp[i+1][j+1] (match remainining string)
   else dp[i][j]=false (as first characters itself not matching)
   
   dp[i][j]=(pattern[i]==s[j]) and dp[i+1][j+1]

Case 2:if the pattern character is an ? then we can match current character with any string 
  in s so we can directly jump to the question whether remaining string matched or not
    dp[i][j]=dp[i+1][j+1];


Case3:This is an important case.
  for * character it can match any sequence of charcters of the string which has got length 0 or more

  For example at dp[2][2] string p will be "*a?" and s will be "abab"
          
          "*a?"         "abab"

* and b can becan be 
           *         remaining p      remaining s     dp state
        __________________________________________________________

         ""(blank)       "a?"            "abab"      dp[i+1][j]
         "a"             "a?"             "bab"      dp[i+1][j+1]
         "ab"            "a?"              "ab"      dp[i+1][j+2]
         "aba"           "a?"               "a"      dp[i+1][j+3]
         "abab"          "a?"                ""      dp[i+1][j+4]

* can take all those characterers and we left with remaing problem which we have already solved 
in pur previous computation as the dp is building from backwards

We have to take or from the next row in case our current character is "*"
Now checking the prevous loop again again make it to O(n^3) complexuty:

Optimistaion:
i.We can make a flag variable that stores the prevoius state or values as precomputation
ii.
  We can observe one thing dif we want to calucalte dp[i][j] when it is *
  the dp[i]][j+1] contains or value  from the previous row
  as dp[i][j+1] is also computed using the same process and one more value
  we should consider is dp[i+1][j] (case when * is blank)

therefore dp[i][j]=(dp[i+1][j] or dp[i][j+1]); when p[i]="*"

Base Cases:
i.We make a dp table that is greater than length of string  s size which stores the blank
at the last character.
ii.Let m=p.size(),n=s.size();
dp[m][n]=true as blank matches blank
dp[m][j]=false as blank don't match any non empty character
dp[i][n]{
    if(p[i]=='*) dp[i][n]=dp[i+1][n] (case of * we simply asiign down value asthere is nor right value)
    else dp[i][n]=false
}
Complexity Analysis:
Time complexity:O(n^2)
Space Complexity:O(n^2)
*/
int wildcardMatching(string s,string pattern){
    int m=pattern.size(),n=s.size();
    vector<vector<bool>> dp(m+1,vector<bool>(n+1,0));
    for(int i=m;i>=0;i--){
        for(int j=n-1;j>=0;j--){
           if(i==m and j==n) dp[i][j]=true;
           else if(i==m) dp[i][j]=false;
           else if(j==n){
               if(pattern[i]=='*') dp[i][j]=dp[i+1][j];
               else dp[i][j]=false;
           }else{
               char ch=pattern[i];
               if(ch=='?') dp[i][j]=dp[i+1][j+1];
               else if(ch=='*') dp[i][j]=dp[i+1][j] or dp[i][j+1];
               else dp[i][j]=(pattern[i]==s[j]) and dp[i+1][j+1];
           }
        }
    }
   return dp[0][0];
}
/*
Given an input string s and a pattern p, 
implement regular expression matching with support for '.' and '*' where:
'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).
_____________________________________Apporach______________________________________________

We have to determine whether the character matches or not

We build the dp table consider the 3 cases depending upon the pattern character

dp[i][j]=states that whether the string from 0 to i in pattern matches with string from
0 to j in string s
let us take example s="mississippi"  pattern="mis*i.*p*i"

dp[3][4]==states whether the string "mis" matches with "mis*"

Case i:If the character is alphabet then we check p[i-1]==s[j-1] 
  if they are equal check the remainig part dp[i-1][j-1]
  else dp[i][j]=false;

case ii:if the character is '.' then it can match any character dp[i][j]=dp[i-1][j-1](rem string)

Case iii: Let us simply oberve all the string that can be formed if we gar an asteric char

                                  "mis*"
 
                   "mi"                       "mis"   "miss"   "misss"  "missss"   "misssss" ..........and so on

dp[i][j] if the character p[i-1]=='*' we are marching towards to some big probelms
and in each case we are to deal with new string for which we haven.t solved..
If we do it from brute force it will lead us to time complexity.

*One obervation is that "mis*" the s can remain blank which leads to the case "mi" *

Optimisation:
 
 let us work on strings "miss"  and "mis*"
                
                "mis*"           "miss"
                _________________________
                 
                 "mi"             "miss"
                 "mis"            "miss"
                 "miss"           "miss"
                 "misss"          "miss"

    
let us try to work on two another string "misi" "mis*"

                "mis*"           "misi"
                _________________________
                 
                 "mi"             "misi"
                 "mis"            "misi"
                 "miss"           "misi"
                 "misss"          "misi"


We can observe that if we added a charcter at the end of the charcter for example "mis"(one s added)

and if the last character won't match with last character of string ("mis" and "misi" s!=i)
 then all the strings whcih can be added can be discarded as they will never be equal
 (for example "miss"!=misi and misss!=misi)

 In case they were mathed("mis","miss") we check on remainng string("miss*","miss")

Above "mis*" can be broken into two states
                                        
                                        "mis*"

                            (left case)   "mi"        "mis(s*)"(one s added and it has another star means we can add or remove futher)

                                                  "miss"       "miss(s*)"
                                                            
                                                            "misss"         "misss(s*)"(all the cases that we have genrated here)


For checking left case at dp[i][j]=dp[i-2][j] same as checking "mi" with "miss" as we have already
solved the problem as i is lower

for checking right case:we can check the last characters of both the string 
  if they match "miss*" and "miss" s and s were matched. the remaining problem "mis*" and "mis"
  which we have already solved in the case dp[i][j-1]

   If they won't match we can straightlt all the further cases as we have already all those upocooming
   cases won;t contribute as last characters haven;t matched.

on summary if the p[i-1]=="*"
  dp[i][j]=dp[i][j] or dp[i-2][j] (case where we havn;t added any char)
  dp[i][j]=dp[i][j-1]

Trvial case:
What if wegot ".*" then we no need to check whether the last character matches because . mathces
with any single character we can simply write as dp[i][j]=dp[i-2][j] or dp[i][j-1];

Base case:
if i==0 and j==0 dp[i][j]=true
else if(i==0) dp[i][j]=false (non empyty string with blank pattern)
else if(j==0){
    if(p[i-1]=='*) dp[i][j]=dp[i-2][j](*star case)
    else dp[i][j]=false
}      
else we consider all those cases  
*/
int regularExpressionMatching(string &s,string &p){
    int m=p.size(),n=s.size();
    vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            if(i==0 and j==0) dp[i][j]=true;//blank with blank
            else if(i==0) dp[i][j]=false;//non empty string with blank pattern
            else if(j==0){
                if(p[i-1]=='*') dp[i][j]=dp[i-2][j];//star cases
                else dp[i][j]=false;//we can make straightly false
            }else{
               char ch=p[i-1];
               //* case
               if(ch=='*'){
                   dp[i][j]=dp[i-2][j];//common
                   char prev=s[i-2];
                   if(prev=='.' or prev==s[j-1]) dp[i][j]=dp[i][j] or dp[i][j-1];
               }else if(ch=='.'){//dot
                 dp[i][j]=dp[i-1][j-1];
               }else if(ch==s[j-1]){//last two mathced
                 dp[i][j]=dp[i-1][j-1];
               }else {//haven't matched
                 dp[i][j]=false;
               }
            }
        }
    }
    return dp[m][n];
}
/*
let us take an example where s1="pqabcxy" s2="xyzabcp"
dp[i][j]=will store the lonest common suffix for string s1(0-i) and s2(0-j)

              -   x    xy      xyz        xyza      xyzab       xyzabc       xyzabcp

         _   0    0     0       0         0          0           0           0
    
         p   0    0     0       0         0          0           0           1(p mathces with last suffix)
 
        pq   0    0     0       0         0         0           0           0
        
       pqa   0    0     0       0         1         0            0          0

       pqab  0    

      pqabc  0
        
     pqabcx  0

    pqabcxy  0

We have considered all the substrings while we comparing with suffixes of all sub strings s2
For example:"pqabcx" "xabcy"  in ordering all the strings "pqabc" "xabc" and the large substring
is 3 we hae arrived at the answer by comparing the above strings 
The longest susbtring will be part of one ofsuffix string
We return the max of all the table
Let us build the dp table

s1 =>(s1')c1 s2==>(s2')c2
 if c1==c2 dp[i][j]=1+dp[i-1][j-1]
 else c1!=c2  dp[i][j]=0 beacuse the last characters haven;t matched the whole value gets to 0
*/
int longestCommonSubstring(string &s1,string &s2){
   int m=s1.size(),n=s2.size();
   vector<vector<int>> dp(m+1,vector<int>(n+1,0));
   int res=-1;
   for(int i=1;i<=m;i++){
     for(int j=1;j<=n;j++){
         if(s1[i-1]==s2[j-1]) dp[i][j]=1+dp[i-1][j-1];
         else dp[i][j]=0;
         res=max(res,dp[i][j]);
      }
   }
   return res;
}
int longestRepeatingSubsequence(string &s){
   int n=s.size();
   vector<vector<int>> dp(n+1,vector<int>(n+1,0));
   for(int i=n-1;i>=0;i--){
     for(int j=n-1;j>=0;j--){
        if(s[i]==s[j] and i!=j) dp[i][j]=1+dp[i+1][j+1];
        else dp[i][j]=max(dp[i+1][j],dp[i][j+1]);
     }
   }
   return dp[0][0];
}
/*
Let us try to draw the recursive tree for the s1="ahellobye" s2="amezooe"

                            "ahellobye"   "amezooe"
                                 

                              "hellobye"  "mezooe"


           "ellobye" "ezooe"       "hellobye" "ezooe"     "ellobye" "mezooe"


             _    a    m    e     z     o    o    e

        _    0    1    2    3     4     5    6    7

        a    1    0    1    2     3     4    5    6

        h    2    1    2    2     3     4    5    6  

        e    3    3    2    2     3

        l    4

        l    5

        o    6

        b    7

        y    8

        e   9


    dp[i][j] stores the minimum operations needed to convert the string s1(0,i-1) to s2(0,j-1)
  
if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1] remaining string s1(0,i-2) s2(0,j-2)
   
   Let us consider dp[4][3]

                           "amez" "ahe"

                  "ame" "ah"    "amez" "ah"        "ame" "ahe"
                  dp[i-1][j-1]   dp[i][j-1]          dp[i-1][j]
                     (replace)    insert              delete
                                  ("ameze","ahe")       z deleted
                                   e-e matched          solve for("ame",ahe)
                                   solve("amez","ah")
                      
  dp[i][j]=1+min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]));

*/
int editDistance(string &s1,string &s2){
    int m=s1.size(),n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=0;i<=m;i++) dp[i][0]=i;
    for(int j=0;j<=n;j++) dp[0][j]=j;
    for(int i=1;i<=m;i++){
      for(int j=1;j<=n;j++){
         if(s1[i-1]==s2[j-1])  dp[i][j]=dp[i-1][j-1];
         else dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
       }
    }
    return dp[m][n];
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
