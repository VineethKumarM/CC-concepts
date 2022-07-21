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
/*Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s

___________________________________Approach_______________________________________________

We use gap strategy to solve the problem:

                                      ABBCA

                      A|BBCA     AB|BCA    ABB|CA    ABBC|A
            
For given string dp[i][j] we try to give cut at every point we find minimum of all of them

==> dp[i][j]=dp[i][k]+dp[k+1][j]+1(we made a cut now)------>

One case we need to handle here is that what if the whole substring s[i..j] is a palindome
in that case we make straightly dp[i][j]=0 as no cuts need for dp[i][j];

so inorder to check we make a boolean isPalind table which tells whether s[i..j] is palindrome
or not in O(1) time

Algorithm for building isPalind table:

We use the same gap stategy inorder to solve this problem:

Gap values and their states----------

i.If the gap is 0 then it is referring to one character so isPalind[i][j]=true
ii.If the gap is 1 then substring contains two characters dp[i][j]=(s[i]==s[j])
iii.If the gap is >1 then inorder to become this substring a palindrome first and last
charcter should match and string in b/wthese two character should be a palindrome
The in b/w struing state is dp[i+1][j-1];
Therefore,dp[i][j]=(A[i]==A[j]) and dp[i+1][j-1]

After building the above table in our min cut algorithm we check if the current string is
already palind or not if it is we make it dp[i][j]=0;
otherwise we make a cut at each character from i to j-1 find min state
at last we return dp[0][n-1];

Space Complexity:O(n^2)
Time complexity:O(n^3)
 */
int minPalindromePartitioning(string &s){
    int n=s.size();
    vector<vector<bool>> isPalind(n,vector<bool>(n,false));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) isPalind[i][j]=true;
            else if(g==1) isPalind[i][j]=(s[i]==s[j]);
            else isPalind[i][j]=(s[i]==s[j]) and isPalind[i+1][j-1];
        }
    }
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(isPalind[i][j]) {
                dp[i][j]=0;
                continue;
            }
            int min_sf=INT_MAX;
            for(int k=i;k<j;k++) min_sf=min(dp[i][k]+dp[k+1][j],min_sf);
            dp[i][j]=1+min_sf;
        }
    }
    return dp[0][n-1];
}
/*
Above code tle since the time complexity is of O(N^3)
 we can reduce it to o(n^2) using suffix string partition
For example let us consider substribg from ABACABGG -->ACAB
in order to calulcate thsi dp[i][j] we are making a cut at evry char in
substring b/w i to j and calulcating min cuts for both left and right part

                                       ACAB
                                       
                                A|CAB   AC|AB   ACA|B

if the string is of more lenght we cut at each point and check
But the cutting each point won't be needed .As we want every part to be palindrome
cutting the above string at non-palind points won't contribute to our answer as it costs more 
cust.so we can simply cut at those points which are palind on one side

Prefix partitioning of this string :ABABACB
                                   ABABACB

                    A|BABACB         ABA|BACB      ABABA|CB

we are making cut at those points in which left string is palind

Same we can apply at suffixpartition   
                                   
                                   ACBAB

                        ABABAC|B     AC|BAB

            In the above case right part is palindrome...they only contribute oto the answer
*/
int minPalindromePartitioningOptmised(string &s){
    int n=s.size();
    vector<vector<bool>> isPalind(n,vector<bool>(n,false));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) isPalind[i][j]=true;
            else if(g==1) isPalind[i][j]=(s[i]==s[j]);
            else isPalind[i][j]=(s[i]==s[j]) and isPalind[i+1][j-1];
        }
    }
    vector<int> dp(n,0);
    dp[0]=0;
    for(int j=1;j<n;j++){
        if(isPalind[0][j]){
            dp[j]=0;
            continue;
        }
        int min_sf=INT_MAX;
        for(int i=j;i>=1;i--){
            if(isPalind[i][j])
             min_sf=min(min_sf,dp[i-1]);
        }
        dp[j]=1+min_sf;
    }
    return dp[n-1]; 
}
/*
Let us consider two string s1 and s3 and their first characters are r1 and r3
Subseunces of s1 are=C(_s2)+C(r1s2) 
_s2=subsequence without character r1 
r1s2=subsquence wit character r1

        s1                         s2

        C(_s2)                     C(_s4)
        C(r1s2)                    C(_s4)
        C(_s2)                     C(r3s4)
        C(r1s2)                    C(r3s4)
we generate all the subsequnces as above and match the both the string sets on left and right
 
 Following cases arise when we are doing cal:
      
        r1===r2                          r1!=r2
       case 4 will give 
       max answer                    max(1,2,3) cases
                                    above 3 cases can be written as lcs(S(r1s2),S(_s3))lcs(S(_s2),S(r2s3))

 dp[i][j]=1+dp[i+1][j+1] if s[i]==s[j]
 else dp[i][j]=max(dp[i+1][j],dp[i][j+1])
*/
int longestCommonSubsequence(string &s1,string &s2){
    int m=s1.size(),n=s2.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=m-1;i>=0;i--){
        for(int j=n-1;j>=0;j--){
            if(s1[i]==s2[j]) dp[i][j]=1+dp[i+1][j+1];
            else dp[i][j]=max(dp[i+1][j],dp[i][j+1]);
        }
    }
    return dp[0][0];
}
/*

We follow the same strategy as we followed for the above algorithm
           --------------- S(m)
          |
          |---------------S(c1m)
LPS(s)----
          |---------------S(mc2)
          |
           ---------------S(c1mc2)

c1 and c2 are the first and last characters of s respectively and m is the middle
part of the string by removing c1 and c2

Case1:c1==c2 if(c1==c2) the max lps(s) will come from 4 th case
      we can prove it by contraiction   
      dp[i][j]=2+dp[i+1][j-1]

Case2:c1!=c2 then the s(c1mc2) will never contribute to the answer
as c1!=c2 but all the strings in the set contains c1 and c2 as first and last character

So,the answer will be contribute by above 3 cases...
 S(m)+S(c1m)-->lps(c1m)
S(mc2)+S(m)--->lps(mc2)
so we can return max(lps(c1m),lps(mc2)) from both the cases

dp[i][j]=max(dp[i][j-1],dp[i+1][j])
dp[i][j-1]-->lps(c1m) case 
dp[i+1][j]=->lps(mc2) case
case2:c1!=c2  the above

We are going to use gap stratgy for implementing the algorithm

Important Note:dp[i][j] will never store substring of i j palindrome it stores the max 
length of subsequence i-j substring which is a palindrome in nature
Base cases:
dp[i][j]=1 in case gap==0
dp[i][j]=(s[i]==s[j])2:1   in case gap=1*/

int longestPalindromicSubsequence(string &s){
    int n=s.size();
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,g++){
            if(g==0) dp[i][j]=1;
            else if(g==1) dp[i][j]=(s[i]==s[j]?2:1);
            else dp[i][j]=(s[i]!=s[j]?max(dp[i+1][j],dp[i][j-1]):2+dp[i+1][j-1]);
        }
    }
    return dp[0][n-1];
}
/*
Given a string str of length N, you have to find number of palindromic subsequence
 (need not necessarily be distinct) which could be formed from the string str
*/
/*
 We follow the gap strategy to solve the porblem:

                -------------S(m)---->cp1
               |
               |------------S(c1m)-->cp2
               |
 CPS(c1mc2)----
               |
               |------------S(mc2)-->cp3
               |
                ------------S(c1mc2)-->cp4


               --------S(m)------->cp1
              |
              |
CPS(c1m)------
              |
              |
               -----------S(c1m)-->cp2


               --------S(m)------->cp1
              |
              |
CPS(mc2)------
              |
              |
               -----------S(mc2)-->cp2

where CPS(s)--count of palindromic subsequences of string s
cp-->count of palindromic subsequences of in set of S(m)
S(m)-->set of all subsequnces of string m


CPS(c1mc2)=cp1+cp2+cp3+cp4-------(i)
CPS(c1m)=cp1+cp2-----------------(ii)
CPS(mc2)=cp1+cp3-----------------(iii)

Let us try to caluclate respective value for strng "abca"
                                   
                                   "abca"

                    ----      a---       ---a      a---a
                    --c-      a--c-      --ca      a-ca
                    -b--      ab--       -b-a      ab-a
                    -bc-      abc-       -bca      abca
                    
                    cp1=2     cp2=1      cp3=1     cp4=3
            

Observations:
i.In case if c1 and c2 are equal we can observe that all subsequences thar are generated in
S(m) are generated S(c1mc2) but one extra palind sequence due to the null string
In case of S(m)=----(it is null so we don;t count)
In case of S(c1mc2)=a--a(since it is valid we count 1 more palindrome

Therefore CPS(c1mc2) =cp1+cp2+cp3+cp4
Case 1: c1==c2
       
       CPS(c1mc2) =cp1+cp2+cp3+cp4 
                  =cp1+cp2+cp3+cp1+1
                  =(cp1+cp2)+(cp1+cp3)+1   
                  =CPS(c1m)+CPS(mc2)+1-------------(from ii and iii above)
                
     CPS(c1mc2)=CPS(c1m)+CPS(mc2)+1

   DP state:   dp[i][j]=dp[i][j-1]+dp[i+1][j]+1

Case 2:c1!=c2

     CPS(c1mc2)  = cp1+cp2+cp3+cp4 
                 = cp1+cp2+cp3+0              ----(since c1mc2 type subsequcnces will 
                                                never be palind as c1!=c2)  

                =cp1+cp2+cp3-c1+c1            --------(Adding c1 and subtracting c1)

                =(cp1+cp2)+(cp3+cp1)-c1

                =CPS(c1m)+CPS(mc2)-c1

                =CPS(c1m)+CPS(mc2)-CPS(m)       ---(c1 is middle subtring palind count=CPS(m))

     CPS(c1mc2) =CPS(c1m)+CPS(mc2)-CPS(m)

    DP state:  dp[i][j]=dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1];

Base cases:
i.If gap is 0 then only one char present dp[i][j]=1
ii.If gap is 1 then two chars present if they are equal dp[i][j]=3 else dp[i][j]=2
iii.if gap is >1
  if(s[i]==s[j]) dp[i][j]=1+dp[i+1][j]+dp[i][j-1]

  else dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]

At last we return dp[0][n-1]
*/
int countPalindromicSubsequences(string &s){
    int n=s.size();
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) dp[i][j]=1;
            else if(g==1) dp[i][j]=(s[i]==s[j]?3:2);
            else{
                if(s[i]==s[j]) dp[i][j]=dp[i+1][j]+dp[i][j-1]+1;
                else dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
            }
        }
    }
    return dp[0][n-1];
}
int countPalindromicSubstrings(string &s){
    int n=s.size(),res=0;
    vector<vector<bool>> dp(n,vector<bool>(n,false));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) dp[i][j]=true;
            else if(g==1) dp[i][j]=(s[i]==s[j]);
            else dp[i][j]=(s[i]==s[j] and dp[i+1][j-1]);
            res+=(dp[i][j]);
        }
    }
    return res;
}
int lengthofLongestPalindromicSubstring(string &s){
    int n=s.size(),res=0;
    vector<vector<bool>> dp(n,vector<bool>(n,false));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) dp[i][j]=true;
            else if(g==1) dp[i][j]=(s[i]==s[j]);
            else dp[i][j]=(s[i]==s[j] and dp[i+1][j-1]);
            if(dp[i][j]) res=max(res,1+g);
        }
    }
    return res;
}
/* 
 We have to caluclate all the distinct subsequences of string s
  Let the string be  "ababc"
   
   .     a     b        a          b           c
    
   .    .      .        .          .           .
        a      a        a          a           a
               b        b          b           b
               ab       ab         ab          ab
    --------------------a-d        a           a
                        aa         aa          aa
                        ba         ba          ba
                        aba        aba         aba
        D---------------------------b-d          b
        D--------------------------ab-d         ab
                                   bb          bb
                                   abb         abb
                                   ab          ab
                                   aab         aab
                                   bab         bab
                                   abab        abab
                                               c
                                               ac
                                               bc
                                               abc
                                               ac
                                               aac
                                               aac
                                               bac
                                               abac
                                               bc
                                               abc
                                               bbc
                                               abbc
                                               abc
                                               aabc
                                               babc
                                               ababc


Above are the string which are generated from the naive approach.
We can observe that there are some duplicates in all the subsequences

Suppose there is string of length n then 2^n possible sequences are possible.
 
 i th sequnces comes from (i-1)th sequcences+(ith char+(i-1)sequences)
  dp[i]=dp[i-1]+dp[i-1]

Handling duplicacy:

Duplicacy arises when the same character that we have already processed appearing twice

For example if we observe 3rd character a which has already visited at i=1

Without a in the fist case there are dp[i-1] sequnces
in ith case   dp[i-1]+dp[i-1]+'a'
             without a + aftter adding a to all i-1 cases

now in 3rd character 'a' there are dp[i-1] sequences without 'a' and another dp[i-1] 
sequences with 'a'
but the dp[i-1] also contain the squences dp[first'a'index-1] sequences without
now in turn we are adding a to all those sequences which we have already added in first
'a' cases
for exapmle 
  
in the above case a is coming twice because we have added blank to a in first 'a' case and
again we are adding to the blank space which leads to duplicacy
  so
   dp[i]=dp[i-1]+dp[i-1]-mp[s[i]];
   At each stage we update mp[s[i]];

  */
int distinctSubsequences(string &s){
    int n=s.size();
    vector<int> dp(n+1,0);
    dp[0]=1;
    unordered_map<char,int> mp;
    for(int i=1;i<=n;i++){
        dp[i]=2*dp[i-1];
        dp[i]-=mp[s[i-1]];
        mp[s[i]]=dp[i-1];
    }
    return dp[n];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}
