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
Given a string A, we may represent it as a binary tree by partitioning 
it to two non-empty substrings recursively.
Below is one possible representation of A = “great”:
    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
 
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node “gr” and swap its two children, it produces a 
scrambled string “rgeat”.

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that “rgeat” is a scrambled string of “great”.

Similarly, if we continue to swap the children of nodes “eat” and “at”, it produces a 
scrambled string “rgtae”.

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that “rgtae” is a scrambled string of “great”.
Given two strings A and B of the same length, determine if B is a scrambled string of S.

Let us take an example where a="pepcoder" and b="peerdcop"
                            
Suppose we cut at index 2 then 
                          
                          "pepcoder"                     "peerdcop"

                       "pe"      "coder"               "pe"     "erdcop"
        
so we check left part("pe") in "pepcoder" is scramble string of left part("pe") of "peerdcop"
and right part("coder") in "pepcoder" is scramble string of right part of "peerdcop" ("erdcop")
 Since we can swap both the left and right strings of current string so we need to check the
 current left is scramble of another right and current right is scramble string of another left

                 "pepcoder"                             "peerdcop"

               "pe"   "pcoder"                       "op"      "peerdc"

As the strings may have swapped we need o check this case also

To better understand consider this case 
                      "gr"                 "gr"
                    "g"  "r"  =====>    "r"  "g" ==========> "gr" and "rg" are scramble strings

Let us try to evaluate the case:              

          "gr"               "rg"

       "g"    "r"          "r"   "g"

If we consider only the above case it will give us that they are not scramble strings but they are

        "gr"                  "rg"

    "g"    "r"                "g"   "r"

We can see that after swapping we proved that they are scramble strings

Base Case:if both strings are equal then they are scramble strings
*/
bool isScrambleString(string a,string b){
    if(a==b) return true;
     bool flag=false;
    for(int k=1;k<a.size();k++){
       flag=isScrambleString(a.substr(0,k),b.substr(0,k)) and isScrambleString(a.substr(k),b.substr(k));//(left-left check and right-right check)
       if(flag) return true;
       //left-right check and right-left check
       flag=isScrambleString(a.substr(0,k),b.substr(b.size()-k,k)) and isScrambleString(a.substr(k),b.substr(0,b.size()-k));
       if(flag) return true;
    }
    return flag;
}
/*in the above rec function we are passing new substrings at each rec function(static variables) they cost 
us time complexity due to copying of strings at each stage 
To optimise we can have start and end indexes we can do operations on them without passings
the strings:(we can pass the one string through references which avoids copying)
we can't pass refernce varibales in above function as substring has to be new in 
each function call*/
bool isScramble(string &a,string &b,int as1,int ae1,int bs1,int be1){
     if(a.substr(as1,ae1-as1+1)==b.substr(bs1,be1-bs1+1)) return true;
     bool flag=false; 
     for(int i=0;i<ae1-as1;i++){
        //left-left and right-right check
         flag=isScramble(a,b,as1,as1+i,bs1,bs1+i) and isScramble(a,b,as1+i+1,ae1,bs1+i+1,be1);
         if(flag) return true;
         //left-right and right-left check
         flag=isScramble(a,b,as1,as1+i,be1-i,be1) and isScramble(a,b,as1+i+1,ae1,bs1,be1-i-1);
         if(flag) return true;
     }
     return false;
}
/*We can avoid passing start and end indexes as of common if we pass len varible
if the two strings has different len they won't be scramble strings
We pass a common len varibale*/
bool isScrambleII(string &a,string &b,int a1,int b1,int len){
    if(a.substr(a1,len)==b.substr(b1,len)) return true;
    bool flag=false;
    for(int k=1;k<len;k++){
        //left-left and right-right
       flag=isScrambleII(a,b,a1,b1,k) and isScrambleII(a,b,a1+k,b1+k,len-k);
       if(flag) return true;
       //left-right and right-left
       flag=isScrambleII(a,b,a1,b1+len-k,k) and isScrambleII(a,b,a1+k,b1,len-k);
       if(flag) return false;
    }
    return true;
}
/*Now we have reached all the rec optimisation now we can memorise the subproblems
that we have already solved 
here3 variable 
a1==starting  index of a1
b1=starting index of b1
len=len of string
dp[a1][b1][len] state whether "a"'s substring of length len witth index a1 is scrmble string of
"b"'s substring of length len len with index b1 is or not?
*/   
bool isScrambleIII(string &a,string &b,int a1,int b1,int len,int dp[31][31][31]){
        if(dp[a1][b1][len]!=-1) return dp[a1][b1][len];
         if(a.substr(a1,len)==b.substr(b1,len)) return dp[a1][b1][len]=true;
    bool flag=false;
    for(int k=1;k<len;k++){
       flag=isScrambleIII(a,b,a1,b1,k,dp) and isScrambleIII(a,b,a1+k,b1+k,len-k,dp);
       if(flag) return dp[a1][b1][k]=true;
       flag=isScrambleIII(a,b,a1,b1+len-k,k,dp) and isScrambleIII(a,b,a1+k,b1,len-k,dp);
       if(flag) return dp[a1][b1][len]=true;
    }
    dp[a1][b1][len]=false;
    return false;
}
bool isScramble(string a,string b){
    int dp[31][31][31];
     for(int i=0;i<=30;i++) for(int j=0;j<=30;j++) for(int k=0;k<=30;k++) dp[i][j][k]=-1;
        return isScrambleIII(a,b,0,0,a.size(),dp);
}
/*Tabulation 

So far we have discussed recursion part.Now the dp array is 3d we have observe each frame.
Let a="great" b="aterg"

                           a     t      e     r    g
    
                     g     0     0      0     0     1
                       
                     r     0     0      0     1     0
                      
 len=1               e     0     0      1     0     0

                     a     1     0      0     1     0
                      
                     t     0     1      0     0    0
                     


dp[i][j][1]--> since it has got len=1 only one cut possible i.e.,middle cut
              so we check A[i]=B[j] if it is then dp[i][j][1]=1 else dp[i][j][1]=0


                           a     t      e     r     g
    
                     g     0     0      0     1     NA
                       
                     r     0     0      1     0     NA
                      
 len=2               e     0     0      0     0     NA

                     a     1     0      0     0     NA
                      
                     t     NA    NA     NA     NA   NA

    
NA:not a valid state

let us try to observe how we have made the value at dp[0][3][2]

What the dp[0][3][1] signifies is that from the 0th index in a with length 2 substring is
scramble string of the substring from 3rd index of b with length 2
It means whether "gr"  "rg" scrambles or not

Left-left and right-right case:
                                    
                                "gr"   "rg"
                         "g"     "r"   "r"  "h"

                 r is compared with g    and  g compared with  r
    dp state        dp[0][3][1]         and  dp[1][4][1]   right part staring index increased

    dp[i][j][2]=     false          and     false


                                  "gr"     "rg"
                            "g"     "r"    "r"   "g"
                    left "rg" compared with right of "rg"   right "gr" compared with left "rg"

    dp state        dp[0][4][1]      and dp[1][3][1]    right part index occured in left part

     dp[i][j][2]     true         and true

     therefore dp[i][j][2]=true
     




                           a     t      e     r     g
    
                     g     0     0      0     NA     NA
                       
                     r     0     0      1     NA     NA
                      
 len=3               e     0     0      0     NA     NA

                     a     NA    NA      NA   NA     NA
                      
                     t     NA    NA     NA     NA    NA



            -----------------------------dp[0][2][3]-------------------------
            |                                                               |
            |                                                               | 
            k==1                                                           k==2
            |                                                               |
            |                                                               |
        dp[0][2][1] and dp[1][3][2](LL-RR)                                  dp[0][2][2] and dp[2][4][1]
        dp[0][4][1]  and dp[1][2][2](LR-RL)                                 dp[0][3][2]  and dp[2][1][1]



                           a     t      e     r     g
    
                     g     0     0      NA     NA     NA
                       
                     r     0     0      NA     NA     NA
                      
 len=4               e     Na     NA      NA     NA     NA

                     a     NA     NA    NA     NA    NA
                      
                     t     NA    NA     NA     NA    NA



We loop on k=1 k<len  at each stage

                         _______________dp[i][j][k] and dp[i+k][j+k][len-k] 
                        |
                        |
dp[i][j][len]-----------
                        |
                        |
                         ______________ dp[i][j+len-k][k]  and dp[i+k][j][len-k]




                           a     t      e      r      g
    
                     g     0     NA      NA    NA     NA
                       
                     r     NA     NA     NA    NA     NA
                      
 len=5               e     Na     NA    NA     NA     NA

                     a     NA     NA    NA     NA     NA
                      
                     t     NA    NA     NA     NA     NA


At last we return dp[0][0][n] stores the answer

Base cases:if len==1 check A[i]==B[j]

Complexity Analysis:
Time complexity:O(n^3)
Space complexity O(n^3)
 */
bool isScramble(string a,string b){
    int n=a.size();
    bool dp[n][n][n+1];
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<=n;k++) dp[i][j][k]=false;
    for(int len=1;len<=len;len++){
        for(int i=0;i+len<=n;i++){
            for(int j=0;j+len<=n;j++){
                if(len==1) dp[i][j][len]=(a[i]==b[j]);
                else{
                    for(int k=1;k<len and !dp[i][j][len];k++){
                        dp[i][j][len]=(dp[i][j][k] and dp[i+k][j+k][len-k]) or (dp[i][j+len-k][k] and dp[i+k][j][len-k]);
                    } 
                }
            }
        }
    }
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;  
 }
