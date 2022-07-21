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
A frog is crossing a river. The river is divided into some number of units, 
and at each unit, there may or may not exist a stone. The frog can jump on a stone, 
but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if
 the frog can cross the river by landing on the last stone. Initially, the frog is on 
 the first stone and assumes the first jump must be 1 unit.

If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. 
The frog can only jump in the forward direction.

_______________________________________Approach__________________________________________________________________

As we don't know at any staage through which step the frog can reach the we have to check all
possibilities..
For that we keep an hashmap for finding whether there is a stone at that position or not
and we keep a steps set for each stone which contains possible steps it can make from 
that stone.
 For example consider the stones array:
 stones  = [0,1,3,5,6,8,12,17]

 stone                 possible steps set

 0                       1
 1                       1,2(as 0->1 step made so possible steps now are it-1,it+1,it which are
                            0,2,1 we dont;t add 0)
                            Now we make every step from 1 findwhether stone is there.if it is
                            there we update the stones set for that stone
 3                        (1,2,3) 
                           [as 1+1==2(but no stone there at pos 2)
                             1+2 ==3 (so we have taken 2 steps now possible steps can be 1,2,3)]
                             1,2,3
 5

 6                           1,2,3,4 (set is considered as to avoid duplicate possible steps)

 8                          1,2,3,4

 12                        3,4,5
 
17                          4,5,6

So now we check whether size of steps set of last step is greater than >0 or not..
if it >0 it means there is a step possible from prevoious stone which made to the current stone
if its not ..it is not possible to reach the last step as we have checked all the possibilities
*/
bool canCross(vector<int>& stones) {
     int n=stones.size();
     vector<set<int>> steps(n);
     unordered_map<int,int> mp;
     for(int i=0;i<stones.size();i++) mp[stones[i]]=i;
     steps[0].insert(1);
     for(int i=0;i<n;i++){
        for(auto it:steps[i]){
            int targ=stones[i]+it;
            if(mp.find(targ)!=mp.end()){
                 if((it-1)!=0) steps[mp[targ]].insert(it-1);
                 steps[mp[targ]].insert(it);
                 steps[mp[targ]].insert(it+1);
            }    
        }
    }
    return steps[n-1].size()>0;
}
/*we can simply keeep hasmap<int,set<int>> by avoiding map and set in different containers
in the above approach.*/
bool canCross(vector<int> &stones){
     int n=stones.size();
     unordered_map<int,set<int>> steps;
     for(int i:stones) steps[i]={};
     steps[stones[0]].insert(1);
     for(int i=0;i<n;i++){
        for(auto it:steps[stones[i]]){
           int targ=stones[i]+it;
           if(steps.find(targ)!=steps.end()){
               if(it-1!=0) steps[targ].insert(it-1);
               steps[targ].insert(it);
               steps[targ].insert(it+1);
           }
        }
     }
   return steps[stones[n-1]].size()>0;
}
/*Given strings s1, s2, and s3, find whether s3 is 
formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration 
where s and t are divided into n and m non-empty substrings respectively, such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
Note: a + b is the concatenation of strings a and b.

______________________________________________Approach_______________________________________

if we see the question broadly then s3 should be of lenegth s1+s2 and every character in  s3
should come in the order of s1 and s2.

Naive approach:
Let us take an examle of 
    s1="aabcc"
    s2="dbbca"
    s3="aadbbcbca"

We keep a pointer over s1(i=0) and s2(j=0) and 3(k=0)
if s1[i]==s3[k] then we increment i++,k++
if s2[j]==s3[k] then we increment j++,k++,

so at the end of the iteration if k==s3.size() it means all the strings are in the same
order.
but this approach creates a problem when both s1[i]==s2[j]==s3[i+j-1] as we don;t know
whether to incremnt i pointer or j pointer,
                   
                   i pointer     j pointer     kpointer 
                   0              0            0
iteration 1:       1               0           1
                   2               0           2
                   2                1          3
                   
At this stafge we are not able to make anotherstep  s1[2]==s2[1]=s3[3]==b as we don;t knwow
which pointer to increment.So we need to increment i once...then check is it interleave
or not then  we increment j anc check futher
                             
                                        f(i,s1,j,s2,s3,k)
                             /                 |               \
                            /                  |                \ 
                    if(s1[i]==s3[k])     if(s2[j]==s3[k])       if none of the character matches
                     f(i+1,s1,j,s2,s3,k+1)  f(i,s1,j+1,s3,s3,k+1) return false;

Onbservation:we don't need to maintain k variable as it is always will be i+j

Given bellow rec+mem approach
*/
bool solve(int i,string &s1,int j,string &s2,string &s3,vector<vector<int>> &dp){
    if(i==s1.size() and j==s2.size()) return true;
    if(dp[i][j]!=-1) return dp[i][j];
    if(i<s1.size() and s1[i]==s3[i+j]){
        bool flag=solve(i+1,s1,j,s2,s3,dp);
        dp[i+1][j]=flag;
        if(flag) return dp[i][j]=true;
    }
    if(s2[j]==s3[i+j]){
        bool flag=solve(i,s1,j+1,s2,s3,dp);
        dp[i][j+1]=flag;
        if(flag) return dp[i][j]=true;
    }
    return dp[i][j]=false;
}
bool isInterLeavingString(string s1,string s2,string s3){
     if(s1.size()+s2.size()!=s3.size()) return false;
     vector<vector<int>> dp(s1.size()+1,vector<int>(s2.size()+1,-1)); 
     return solve(0,s1,0,s2,s3,dp);
}
/*
dp[i][j]=state whether the substring s1(0,i) and s2(0,j) can make interleave with s3(0,i+j)\

The dp table for the above case is as follows

            _      d       b        b          c         a
       
    _       T      F       F        F          F         F
            
    a      T      F        F        F           F         F
 
    a      T      T        T         T          T         F

    b      F      T        T          T          T        F

    c      F     F         T         T          T        T

    c      F      F        F         T          F       T

    dp[m][n] contains the answer
*/
bool isInterLeave(string s1,string s2,string s3){
    int m=s1.size(),n=s2.size();
    vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            if(i==0 and j==0) dp[i][j]=true;
            else if(i==0){
                dp[i][j]=(s2[j-1]==s3[i+j-1]) and dp[i][j-1];
            }else if(j==0){
                dp[i][j]=(s1[i-1]==s3[i+j-1]) and dp[i-1][j];
            }else{
                dp[i][j]=(s1[i-1]==s3[i+j-1] and dp[i-1][j]) or (s2[j-1]==s3[i+j-1] and dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}
int maxLengthofRepeatedSubarray(vector<int> &nums1,vector<int> &nums2){
      int m=nums1.size(),n=nums2.size();
      int res=0;
      vector<vector<int>> dp(m+1,vector<int>(n+1,0));
      for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(nums1[i-1]==nums2[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=0;
            res=max(res,dp[i][j]);
        }
      }
      return res;
}
/**/
int distinctEchoSubstring(string text){
    int n=text.size();
    set<string> s;
    for(int len=1;len<=n/2;len++){
        int cnt=0;
        for(int i=0,j=len;j<n;i++,j++){
            if(text[i]==text[j]) cnt++;
            else cnt=0;
            if(cnt==len){
                s.insert(text.substr(i+1,len));
                cnt--;
            }
        }
    }
    return s.size();
}
/*You are given an integer array nums. You want to maximize the number of points 
you get by performing the following operation any number of times:

Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete 
every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
Return the maximum number of points you can earn by applying the above operation
 some number of times.
 
 Let us consider the testcase 
                                       [3,4,2]                
                             /                  \                   \
                            /                     \                   \
                        3+[4(discarded),2(disc)]   4+[3(discarded),2]   2=[3(dicarded),4]
                        
                       3                              6                   6

    So the answer is 6;

Optimisation 1:Consider the case where the array contains duplicates.
     for example :[2,2,3,5,5,5,6,7]
     supoose we choose 2 then we are now to discard 3 and 1 
     but still we can take 2's as these aren't dicarded and chppsing the same  element
     won't increase discarding elements..as [same 3 and 1 are discarded now also]
The path is now compressed..We can simply rewirte the array as
[2,2,3,5,5,5,6,7]  ====>  [4,3,15,6,7]

Now we can try to solve the above problem as it was path compressed.

Optimisation2:As the statement said we cannot take x-1 x+1 values..the problem seems
like an maximum non-adjacent sum of elements..

We can basically convert above non-compressed array as freq table
     
       0     1    2     3     4     5     6    7    
freq   0     0    2     1     0     3     1    1   
At each stage we store freq[i] in nums[i]

Simply we can now apply max non-adijacent sum of elements algorithm but one change we don't add
simply freq[i] instead we add i*freq[i] value as due to optimisation 1
As we can seee the elements which aren;t there in the array got frequcnecy 0 whoch don't
contribute to the answer.
At last we return max value....

*/
int deleteAndEarn(vector<int> &nums){
    int n=*max_element(begin(nums),end(nums));
    vector<int> freq(n+1,0);
    for(int x:nums) freq[x]++;
    /*including the current element 
    excluding the current elemenr*/
    int incl=0,excl=0;
    for(int i=1;i<=10000;i++){
        int nincl=excl+freq[i]*i;
        int nexcl=max(excl,incl);
        incl=nincl;
        excl=nexcl;
    }
    return max(incl,excl);
}
/**/
int minCost(int cday,vector<int> &days,vector<int> &cost,unordered_map<int,bool> &isTravel){
    if(cday>days[days.size()-1]) return 0;
    if(isTravel.find(cday)!=isTravel.end()){
        int dayPass=minCost(cday+1,days,cost,isTravel)+cost[0];
        int weekPass=minCost(cday+7,days,cost,isTravel)+cost[1];
        int monthPass=minCost(cday+30,days,cost,isTravel)+cost[2];
        return min(dayPass,min(weekPass,monthPass));
    }else return minCost(cday+1,days,cost,isTravel);

}
int minCostTickets(vector<int> &days,vector<int> &cost){
    unordered_map<int,bool> mp;
    for(int i:days) mp[i]=true;
    return minCost(days[0],days,cost,mp);
}
int minCostTIckets(vector<int> &days,vector<int> &cost){
    vector<int> dp(396,0);
    unordered_map<int,bool> mp;
    for(int i:days) mp[i]=true;
    for(int i=365;i>=0;i--){
          if(i>days[days.size()-1]) continue;
          if(mp.find(i)!=mp.end()){
            dp[i]=min(dp[i+1]+cost[0],min(dp[i+7]+cost[1],dp[i+30]+cost[2]));
          }else dp[i]=dp[i+1];
    }
    return dp[days[0]];
}
int minDeleteSum(int m,string &s,int n,string &t){
    if(m==0){
        int ans=0;
        for(int i=0;i<n;i++) ans+=(t[i]-'a');
        return ans;
    }
    if(n==0){
        int ans=0;
        for(int i=0;i<m;i++) ans+=(s[i]-'a');
        return ans;
    }
    if(s[m-1]==t[n-1]){
        return minDeleteSum(m-1,s,n-1,t);
    }else return min(minDeleteSum(m-1,s,n,t),minDeleteSum(m,s,n-1,t));
}
int minASCIIdeleteSum(string &s,string &t){
     return minDeleteSum(s.size(),s,t.size(),t);
}
/*The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the 
sum of the elements at odd indices.

For example, the alternating sum of [4,2,5,3] is (4 + 5) - (2 + 3) = 4.
Given an array nums, return the maximum alternating sum of any subsequence of 
nums (after reindexing the elements of the subsequence).

A subsequence of an array is a new array generated from the original array by 
deleting some elements (possibly none) without changing the remaining elements' 
relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined 
elements), while [2,4,2] is not.

__________________________________________________Approach______________________________________

We try  to generate all subsequences...along with subseqeunce generation we keep a cur variable
which stores the index of current element in subsequence array.
Let us draw the recursive tree for test case 

                    [4,5,3]
        
        _+[5,3]                     4+[5,3]
     
     _+_+[3]    _+5+[3]           4+_+[3]           4+5+[3]

 -+-+-    -+-+3  _+5+3 _+5+_     4+_+_ 4+_+3     4+5+_      4+5+3

If we write all the subsequences in array format:
[-,-,-] Alt sum=0;
[3]   Als sum=3
[5,3] Alt sum=5-3=2
[5]  Alt sum=5
[4]  ALt sum=4
[4,3]  Alt sum=4-3
[4,5]   ALt sum=4-5
[4,5,3]  Alt sum=4+3-5=2

So as of broadly speaking we are generating all the subsequences but we don't need to generate
vector istead we can keep anindex variable and whenever the current element%2==0
then we add to the rec call(as even indexed) else we subtract from rec call
*/
long long maxAltSum(int idx,vector<int> &nums,int cur){
    if(idx>=nums.size()) return 0;
    long long ans=0,val=nums[idx];
    if(cur%2==0){
        ans=max(ans,maxAltSum(idx+1,nums,cur+1)+val);
    }else ans=max(ans,maxAltSum(idx+1,nums,cur+1)-val);
    ans=max(ans,maxAltSum(idx+1,nums,cur));
}
/*
Optimisation:As of storage is considered there are two chaniging variables 
idx and cur so we need to maintain 2d array dp[idx][cur].

But if we closely observe every time we are concerned with mod value with i.e.cur%2
so we can simply make dp[idx][0] and dp[idx][1] can be sufficient
*/
long long maxAltSumMemo(int idx,vector<int> &nums,int x,vector<vector<long long>> &dp){
    if(idx>=nums.size()) return 0;
    if(dp[idx][x]!=-1) return dp[idx][x];
    long long ans=0,val=nums[idx];
    if(x==0){
        dp[idx+1][1]=maxAltSumMemo(idx+1,nums,1,dp)+val;
        ans=max(ans,dp[idx+1][x]);
    }else{
        dp[idx+1][0]=maxAltSumMemo(idx+1,nums,0,dp)-val;
        ans=max(ans,dp[idx+1][x]);
    }
    dp[idx+1][x]=maxAltSumMemo(idx+1,nums,x,dp);
    ans=max(ans,dp[idx+1][x]);
    return dp[idx][x]=ans;
}
long long maxAlternatingSum(vector<int>& nums) {
       // return maxAltSum(0,nums,0);
       //vector<vector<long long>> dp(nums.size()+1,vector<long long>(2,-1));
       //return maxAltSumMemo(0,nums,0,dp);
}
//Tabulation
//endEven[i]=max subsequence alternating sum upto arr[0...i] if the current element is
//at ended at even
//endOdd[i]=max subsequence alternating sum upto arr[0...i] if the current element is
//at ended at odd
//note that endEven[i] may or may not include nums[i]
//endeven[i]=max(endeven[i-1],endodd[i-1]+val)
//endOdd[i]=max(endOdd[i-1],endeven[i-1]-val)
//If we try to draw the rec we can see the future of some indexes is same so we tru to maintain
//max sum
/*Let us try to draw the rec diagram for the test case  [7,3,4,2]

                           [7,3,4,2]
                    
            _+[3,4,2]                     7+[4,3,2]
    
    _+[4,2]       3+[4,2]              7+[3,2]         3(7-4=3)+[4,2]
     (i)           (ii)                  (iii)           (iv)
  
_+[2]   4+[2]     3+[2]  -1+[2]        7+[2]  4+[2]       3+[2]      3+4+[2]


If we observe the future of state (i) and (iv)
 State (i) futue _+[2],4+[2]
 State (iv) future 3+_+[2],3+4+[2]

They got the same future except that in state iv we already got sum 3 fromprevious values
but in state (i) we got sumto left ..
SInce they are getting same future both get same future sum value but state (iv) will
always be ahead of val =3 as we get from prev comoutayiom.
So we can take max of these states and completely can discard the other state(i)
so we solve for state(iv)  and we can discar state (iii)

Same goes state (ii) and state(iii)
              */
long long maxAlternatingSumTab(vector<int> &nums){
    vector<long long> endEven(nums.size(),0);
    vector<long long> endOdd(nums.size(),0);
    endEven[0]=nums[0];
    for(int i=1;i<nums.size();i++){
        long long val=nums[i];
        endEven[i]=max(endEven[i-1],endOdd[i-1]+val);
        endOdd[i]=max(endOdd[i-1],endEven[i-1]-val);
    }
    return max(endEven.back(),endOdd.back());
}
//space optimisation
long long maxAlternatingSumTab(vector<int> &nums){
    long long endEven=nums[0],endOdd=0;
    for(int i=1;i<nums.size();i++){
        long long val=nums[i];
        endEven=max(endEven,endOdd+val);
        endOdd=max(endOdd,endEven-val);
    }
    return max(endEven,endOdd);
}
/*
Alice and Bob take turns playing a game, with Alice starting first.

There are n stones arranged in a row. On each player's turn, they can remove either the 
leftmost stone or the rightmost stone from the row and receive points equal to the sum
 of the remaining stones' values in the row. The winner is the one with the higher score 
 when there are no stones left to remove.

Bob found that he will always lose this game (poor Bob, he always loses), so he decided
 to minimize the score's difference. Alice's goal is to maximize the difference in the score.

Given an array of integers stones where stones[i] represents the value of the ith stone 
from the left, return the difference in Alice and Bob's score if they both play optimally.


____________________________________________Approach_________________________________

Let us consider the test case [5,3,1,4,2]

i.Alice level                                    [5,3,1,4,2]


ii.Bob level          [3,1,4,2] (AliceScore[10])                           [5,3,1,4] (Ailce score[13])



iiiAlice level  [1,4,2]         [3,1,4]                                  [3,1,4]                 [5,3,1]
             Bob score(7)    bob score(8)                                Bob score(8)              Bobscore(9)

            .....                    ......                                    ......                  .......


Let us consider the situation at level ii.
At this stage alice got score..now its bob turn..two calls will be made...now bob is
playing optimally bob try to return max valeue among them as he wants to reduce the diff

Now again come to level1 now alice has two options score 
if he choosen 0th stonethen score will be x,if he chosen n-1 stone score wull be y
since alice want to maximise diff so he will return max among them

Below is the recursive approach with base cases:
if i==j only one element is there in that case both scores will be 0
if(i+1==j) then on;y two element so we will retyrn max b/w the stones
    

 */

int maxScore(int i,int j,vector<int> &stones,vector<int> &prefix){
    if(i==j) return 0;
    if(i+1==j) return max(stones[i],stones[j]);
    int stoneatI=prefix[j]-prefix[i]-maxScore(i+1,j,stones,prefix);
    int stoneatJ=prefix[j-1]-(i==0?0:prefix[i-1])-maxScore(i,j-1,stones,prefix);
    return max(stoneatI,stoneatJ);
}
//memorisatiom
int maxScoreMemo(int i,int j,vector<int> &stones,vector<int> &prefix,vector<vector<int>> &dp){
    if(dp[i][j]!=-1) return dp[i][j];
    if(i==j) return dp[i][j]=0;
    if(i+1==j) return dp[i][j]=max(stones[i],stones[j]);
    dp[i+1][j]=maxScoreMemo(i+1,j,stones,prefix,dp);
    int stoneatI=prefix[j]-prefix[i]-dp[i+1][j];
    dp[i][j-1]=maxScoreMemo(i,j-1,stones,prefix,dp);
    int stoneatJ=prefix[j-1]-(i==0?0:prefix[i-1])-dp[i][j-1];
    return dp[i][j]=max(stoneatI,stoneatJ);
}
//Tabulation
int maxScoreTab(vector<int> &stones){
    int n=stones.size();
    vector<int> prefix(n,0);
    prefix[0]=stones[0];
    for(int i=1;i<n;i++) prefix[i]+=(stones[i]+prefix[i-1]);
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) dp[i][j]=0;
            else if(g==1) dp[i][j]=max(stones[i],stones[j]);
            else{
                 int stoneatI=prefix[j]-prefix[i]-dp[i+1][j];
                 int stoneatJ=prefix[j-1]-(i==0?0:prefix[i-1])-dp[i][j-1];
                 dp[i][j]=max(stoneatI,stoneatJ);
            }
        }
    }
    return dp[0][n];
}
int stoneGameVII(vector<int> &stones){
    int n=stones.size();
    vector<int> prefix(n,0);
    prefix[0]=stones[0];
    for(int i=1;i<n;i++) prefix[i]+=(stones[i]+prefix[i-1]);
    return maxScore(0,n-1,stones,prefix);
}
/*Given an array of digits digits, return the largest multiple of three that
 can be formed by concatenating some of the given digits in any order. If there 
 is no answer return an empty string.

Since the answer may not fit in an integer data type, return the answer as a string.
 Note that the returning answer must not contain unnecessary leading zeros.
 
 _________________________________Approach_____________________________________________
 
 sort the array;
 if(sum%3==0) thenwe  can directly return the sorted array digitsin reverse order(greates value)
 if(sum%3==1)
     try to remove smallest element with  digits[i]%3==1
     if it is not found try to remove stwo mallest element withs digits[i]%3==2
if(sum%3==2)
   try to remove smallest element with  digits[i]%3==2
    if it is not found try to remove stwo mallest element withs digits[i]%3==1

At last whether ans[0]=='0' if it is then return "0" else return ans */
string removeRem(int rem1,int rem2,vector<int>& digits){
        bool flag=false;
        int n=digits.size();
        string ans="";
            for(int i=0;i<n;i++){
                if(digits[i]%3==rem1){
                    flag=true;
                    digits[i]=-1;
                    break;
                }
            }
            if(flag){
                for(int i=n-1;i>=0;i--) if(digits[i]!=-1) ans+=to_string(digits[i]);
            }else{
                vector<int> two(2,-1);
                for(int i=0;i<n;i++){
                    if(digits[i]%3==rem2){
                        if(two[0]==-1) {
                            two[0]=i;
                            digits[i]=-1;
                        }else{
                            two[1]=i;
                            digits[i]=-1;
                            break;
                        }
                        
                    }
                }
                  if(two[1]!=-1){
                for(int i=n-1;i>=0;i--) if(digits[i]!=-1) ans+=to_string(digits[i]);
              }
        }
          
        return ans.size()>0?(ans[0]=='0'?"0":ans):ans;
}
string largestMultipleOfThree(vector<int>& digits) {
        int sum=0,n=digits.size();
        sum=accumulate(begin(digits),end(digits),0);
        sort(begin(digits),end(digits));
        //cout<<sum<<' ';
        string ans="";
        if(sum%3==0){
           for(int i=n-1;i>=0;i--) ans+=to_string(digits[i]);
            return ans.size()>0?(ans[0]=='0'?"0":ans):ans;;
        }else if(sum%3==1){
           return removeRem(1,2,digits); 
        }else return removeRem(2,1,digits);
        
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
