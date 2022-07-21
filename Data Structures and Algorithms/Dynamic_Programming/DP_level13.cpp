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
/*On an n x n chessboard, a knight starts at the cell (row, column) and 
attempts to make exactly k moves. The rows and columns are 0-indexed, so 
the top-left cell is (0, 0), and the bottom-right cell is (n - 1, n - 1).

A chess knight has eight possible moves it can make, as illustrated below.
 Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.
Each time the knight is to move, it chooses one of eight possible moves 
uniformly at random (even if the piece would go off the chessboard) and moves there.
The knight continues moving until it has made exactly k moves or has moved off the chessboard.
Return the probability that the knight remains on the board after it has stopped moving.*/
/*__________________________________________________________________________________________________________

Approach:
   We mantaining two dp table containing the cur state and next state probabilities
We iterate  over each cell and the probability of the cell through which we can move from this cell
as next[i+dx][j+dy]+=cur[i][j]/(8.0); 
at last we make cur=next and made next to 0.0 as new state for nrxt iteration*/
double knightProbability(int n,int k,int row,int column){
    vector<vector<double>> cur(n,vector<double>(n,0.0));
    vector<vector<double>> next(n,vector<double>(n,0.0));
    vector<int> dx={-1,-2,-2,-1,1,2,2,1};
    vector<int> dy={-2,-1,1,2,2,1,-1,-2};
    cur[row][column]=1.0;
    for(int move=0;move<k;move++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(cur[i][j]==0) continue;
                for(int x=0;x<8;x++){
                    int nr=i+dx[x],nc=j+dy[x];
                    if(nr>=0 and nr<n and nc>=0 and nc<n){
                       next[nr][nc]+=(cur[i][j]/(8.0));
                    }
                }
            }
        }
        //for next iteration
        cur=next;
        fill(next.begin(),next.end(),vector<double>(n,0.0));
    }
    double totalProb=0;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) totalProb+=cur[i][j];
    return totalProb;
}
/*1. You are given two strings S1 and S2.
2. You have to find the number of unique ways in which you can transform S1 to S2.
3. Transformation can be achieved by removing 0 or more characters from S1, such that the 
sequence formed by the remaining characters of S1 is identical to S2.

for example :Let us take two strings s="aaabc" t="abc"
There are 3 a's in source string one a in target .
Therfore we have to select 2 a's from 3 a's .No.of ways will be 3C2=3
Those can be:  i) a..bc
               ii).a.bc
               iii)..abc
               Dotted characters are deleted

let us try to draw the recursive diagram:

                                        "xaabc","abc"
                                           |
                                           |
                                      "aabc","abc"  {since the first characters won't match there is no other
                                         /        \               way we have to delete the string}
                                       /           \
                                      /             \
                                     /               \
                              "abc","abc"          "abc","bc"

If the characters match then two cases arise: 
    i.The current character can be removed turning the sub problem to "abc","abc"
    ii.The current character remains and it matches with first character "abc","bc"

Overall the dp state is build as follows over s(c1+r1),t(c2+r2)

if(c1==c2) f(s,t)=f(r1,t)+f(r1,r2)
else f(s,t)=f(r1,t);
*/
int distinctTransformations(string &s,string &t,int i,int j){
    if(i==s.size()){
        if(j<t.size()) return 0;
        else return 1;
    }else if(j==s.size()) return 1;
    int totalWays=0;
    if(s[i]!=t[j]){
        totalWays=distinctTransformations(s,t,i+1,j);
    }else{
        totalWays+=distinctTransformations(s,t,i+1,j);
        totalWays+=distinctTransformations(s,t,i+1,j+1);
    }
    return totalWays;
}
int distinctTransformations(string &s,string &t){
    int m=s.size(),n=t.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=m;i>=0;i--){
        for(int j=n;j>=0;j--){
            if(j==n) dp[i][j]=1;
            else if(i==m) dp[i][j]=0;
            else{
                if(s[i]!=t[j]) dp[i][j]=dp[i+1][j];
                else dp[i][j]=dp[i+1][j]+dp[i+1][j+1];
            }
        }
    }
    return dp[0][0];
}
/**/
int numericKeyPad(int k){
    vector<vector<int>> dp(k+1,vector<int>(10,0));
    vector<vector<int>> neighbors={{0,8},{1,2,4},{1,2,3,5},{2,3,6},{1,4,5},{2,4,5,6,8},{3,5,6},{4,7,8},{5,7,8,9,0},{6,8,9}};
    for(int i=1;i<=k;i++){
        for(int j=0;j<=9;j++){
            if(i==1) dp[i][j]=1;
            else{
               for(int k=0;k<neighbors[j].size();k++) dp[i][j]+=dp[i-1][k];
            }
        }
    }
    int sum=0;
    accumulate(begin(dp[k]),end(dp[k]),sum);
    return sum;
}
/*1. You are given a string containing only 0's and 1's.
2. You have to find the length of substring which is having maximum difference 
of number of 0s and number of 1s i.e (Number of 0's - Number of 1's).
3. If there are all 1's present in the given string, then print '-1'.*/
int maxDiffZerosandOnes(string &s){
    int csf=0,msf=0;
    for(int i=0;i<s.size();i++){
        int val=s[i]=='0'?1:-1;
        if(csf+val>val) csf=csf+val;
        else csf=val;
        msf=max(msf,csf);
    }
    return csf;
}
/*Given an integer array nums and two integers firstLen and secondLen, 
return the maximum sum of elements in two non-overlapping subarrays with 
lengths firstLen and secondLen.

The array with length firstLen could occur before or after the array with length
 secondLen, but they have to be non-overlapping.

A subarray is a contiguous part of an array

_________________________________________________Approach________________________________________

naive approach is to traverse all the subarray and find maximum among all of them

Optimised:
  Let us define two dp states dp1 and dp2 as follows
   dp1[i]:is the maximum sum subarray of size x from [0...i] 
   dp2[i]:is the maximum sum subarrya of size y from [i..n-1]
So.At each index we know the left max subarray sum i.e,, dp1[i] and right subarray sum dp2[i]
 Therefore res=max(dp1[i]+dp2[i+1],res)

As atleast x size needed i starts from x and to the right there must be y size it will end on
n-y;
for(int i=x-1;i<n-y;i++) res=max(res,dp1[i]+dp2[i+1]);

We considered the case where x comes first then y ...but we also need to cosnider another case
where y comes first and x comes then.
We return max among these two.
*/
int maxSumTwoNoOverlap(vector<int> &nums,int x,int y){
       int n=nums.size(),res=0;
       vector<int> dp1(n,0),dp2(n,0);
       int cursum=0;
       for(int i=0;i<n;i++){
        //size<x case
           if(i<x){
              cursum+=nums[i];
              dp1[i]=cursum;
           }else{
              cursum+=(nums[i]-nums[i-x]);
              dp1[i]=max(cursum,dp1[i-1]);
           }
       }
       cursum=0;
       for(int i=n-1;i>=0;i--){
          if(i+y>=n){
            /*size <y*/
            cursum+=nums[i];
            dp2[i]=cursum;
          }else{
            cursum+=(nums[i]-nums[i+y]);
             dp2[i]=max(cursum,dp2[i+1]);
          }
      }
      //x-->y case i starting from x-1 and ends on n-y-1
      for(int i=x-1;i<n-y;i++) res=max(res,dp1[i]+dp2[i+1]);
      fill(dp1.begin(),dp1.end(),0);
      fill(dp2.begin(),dp2.end(),0);
      cursum=0;
      for(int i=0;i<n;i++){
         if(i<y){
            cursum+=nums[i];
            dp1[i]=cursum;
         }else{
            cursum+=(nums[i]-nums[i-y]);
            dp1[i]=max(dp1[i-1],cursum);
         }
      }
      cursum=0;
      for(int i=n-1;i>=0;i--){
          if(i+x>=n){
             cursum+=nums[i];
             dp2[i]=cursum;
          }else{
             cursum+=(nums[i]-nums[i+x]);
             dp2[i]=max(cursum,dp2[i]);
          }
      }
      //y-->x case
      for(int i=y-1;i<n-x;i++) res=max(res,dp1[i]+dp2[i]);
      return res;
}
/*Given an integer array nums and an integer k, find three non-overlapping subarrays of length k 
with maximum sum and return them.
Return the result as a list of indices representing the starting position of each interval (0-indexed). 
If there are multiple answers, return the lexicographically smallest one.

_______________________________________________________Approach_________________________________________

We follow the same approach as we done for two overlapping subarray...
we avoid two calls as k is same for both the arrays

Valid middle subarray inidces(starting) range will be [k,n-2*k]

At each index i we know the sum of middle subarray sum as preifx[i+k-1]-preifx[i-1]
left max will be dp1[i-1]
right max subarrau will be dp2[i+k]
so we know the max value of subarray for current index..
We update the index as soon as we get the max value....in this way we can find middleInd

once we find middleInd we can now tell what is left max value dp1[middleInd-1](leftsum)
rightsum will be dp2[i+k](rightsum)

Since we want lexographically smallest indices we find the first subarray throight prefix
array which has value left sum..as soon as we find we break it
similaryly we start searching the first index from middleInd+k subarray which ot subarray 
sum as rightsum..as sonne as we find we break it.

*/
vector<int> maxSumofThreeSubarray(vector<int> &nums,int k){
    int n=nums.size(),cursum=0;
    vector<int> prefix(n,0),dp1(n,0),dp2(n,0);
    for(int i=0;i<n;i++){
        if(i<k){
            cursum+=nums[i];
            dp1[i]=cursum;
        }else{
            cursum+=(nums[i]-nums[k]);
            dp1[i]=max(dp1[i-1],cursum);
        }
        prefix[i]=(i==0)?nums[i]:nums[i]+prefix[i-1];
    }
    for(int i=n-1;i>=0;i--){
        if(i+k>=n){
            cursum+=nums[i];
            dp2[i]=cursum;
        }else{
            cursum+=(nums[i]-nums[i+k]);
            dp2[i]=max(dp2[i+1],cursum);
        }
    }
    int maxSum=0,firstInd=-1,middleInd=0,lastInd=-1,leftsum=0,rightsum=0;

    for(int i=k;i<=n-2*k;i++){
        int val=dp1[i-1]+prefix[i+k-1]-prefix[i-1]+dp2[i+k];
        if(val>maxSum){
            middleInd=i;
            leftsum=dp1[i-1];//leftsum stroing
            rightsum=dp2[i+k];//rightsum
            maxSum=val;
        }
    }
    //searching for first occurence of leftsum
    for(int i=k-1;i<middleInd;i++){
        if(i==(k-1)){
            if(prefix[i]==leftsum){
                firstInd=0;
                break;
            }
        }else{
            if(prefix[i]-prefix[i-k]==leftsum){
                firstInd=i-k+1;
                break;
            }
        }
       
    }
    //searching for first occurenece of rightsum after middleInd+k elements
    for(int i=middleInd+2*k-1;i<n;i++){
        if(prefix[i]-prefix[i-k]==rightsum){
            lastInd=i-k+1;
            break;
        }
    }
    return {firstInd,middleInd,lastInd};
}
/*
We will consider two cases whether the current element can be part of answer or it wont
if the current element is part of answer then all the k elements must be included in the answer
as we are considering the subarray and it should be continuos so we have to add them.
if it is included then we recursive call for i+k index for m-1 subarrays
if it is excluded then we recusrive call for i+1 index for m subsets

*/
int maxMNonOverlapSubarrays(int idx,int m,int k,vector<int> &nums,vector<int> &prefix,vector<vector<int>> &dp){
    if(m==0 or idx>=nums.size()) return 0;
    if(dp[idx][m]!=-1) return dp[idx][m];
    int exclude=0+maxMNonOverlapSubarrays(idx+1,m,k,nums,prefix,dp);
    int include=prefix[idx]+maxMNonOverlapSubarrays(idx+k,m-1,k,nums,prefix,dp);
    return dp[idx][m]=max(exclude,include);
 }
 int maxMNonOverLapSub(vector<int> &nums,int m,int k){
    int n=nums.size();
    vector<int> prefix(nums.size(),0);
    int sum=0;
    for(int i=0;i<k;i++) sum+=nums[i];
    prefix[0]=sum;
    for(int i=k,j=0;i<n;i++,j++){
        sum+=(nums[i]-nums[j]);
        prefix[i-k+1]=sum;
    }
    vector<vector<int>> dp(n,vector<int>(m+1,-1));
    return maxMNonOverlapSubarrays(0,m,k,nums,prefix,dp);
 }
 /*An integer array is called arithmetic if it
  consists of at least three elements and if the difference between any 
  two consecutive elements is the same.
For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
Given an integer array nums, return the number of arithmetic subarrays of nums.
A subarray is a contiguous subsequence of the array.

__________________________________________________Approach____________________________________________

We define dp[i] as number of arthimetic slices which are ending with nums[i];
Since it is a subarray we
if(nums[i]-nums[i-1]==nums[i-2]-nums[i-1]) the n current element can be part of ap of dp[i-1]
as it can be the next elemeent so we added 1+dp[i-1]
else dp[i]=0;

*/
 int arthimeticSlices(vector<int> &nums){
    int n=nums.size();
    vector<int> dp(n,0);
    int ans=0;
    for(int i=2;i<n;i++){
        if(nums[i]-nums[i-1]==nums[i-2]-nums[i-1]){
            dp[i]=1+dp[i-1];
            ans+=dp[i];
        }
    }
    return ans;
 }
 /*Given an integer array nums, return the number of all the arithmetic subsequences of nums.

A sequence of numbers is called arithmetic if it consists of at least three elements and 
if the difference between any two consecutive elements is the same.

For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
A subsequence of an array is a sequence that can be formed by removing some elements
 (possibly none) of the array.

For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
The test cases are generated so that the answer fits in 32-bit integer.

_____________________________________________Approach______________________________________________

Naive approach is to solve through recursive approach by stating whether the element can be a part of
ap subsequence or it cannot be....

Optimised approach:
We keep an array of hasmap that stores 
mparray[i]={common_difference,no.of ap;s}
basically what it means it stores the no.of aps whose common difference is cd which ends at nums[i]

Let us try to put value for the current sequene
           
        4     |    2        |     3         |     5       |      2   |     6      |     7      |     9
              | (-2,1)      |  (-1,1)       |  (1,1)      |          |            |            |
              |             |  (1,1)        |  (3,1)      |          |            |            |
              |             |               |   (2,1)     |          |            |            |
              |             |               |             |          |            |            |
              |             |               |             |          |            |            |
              |             |               |             |          |            |            |
              |             |               |             |          |            |            |


    For 2: common diff   no.of aps
            -2            1
            0             1
            -1            2----------(iii)
            -3            1

In the thrid case no.of aps are 2,Let us see how:

The nu,ber on left sie is 3 so the cd=2-3=-1
Bit we can see that in hashmap of 3 there is also one more ap which ends with 3 with common
difference -1
So,now the aps for 2 will be
  i.3,2(with cd -1)
  ii.4,3,2(with cd -1 4,3 are from hashmap 3)
Since for the valid ap size >=3 we add prevoius aps ending on J to our answer as they have ap size>=2
adding current i it to them amke aps have size>=3 which are valid.

As soon as we find there is same common difference in hasmap of j we add no of apps on j
and add j count to current hashmap
mp[i][cd]=mp[j][cd]+1.....(1 is added last j and i make a new ap with same cd)

Overlfow case:
As we try to find out the common difference it may happen cd>=INT_MAX or cd>=INT_MIN
in those cases 3rd element cannot be there as all nums[i] are in integers next element 
will have greater than int_MAx which leads to overflow case/
 For example numbers are: -2^30 2^30 
  then cd will be 2^31
  then third element will be 2^30+2^31 which is an overflow case no nums[i] can  fit this large
  number.
 */
 int arthieticSlicesII(vector<int> &nums){
    int ans=0,n=nums.size();
    vector<unordered_map<int,int>> mp(n);
    for(int i=1;i<nums.size();i++){
        for(int j=0;j<i;j++){
            long cd=(long)nums[i]-(long)nums[j];
            //overflow case
            if(cd<=INT_MIN or cd>=INT_MAX) continue;
            //aps ending on J
            int apsEndingonJ=mp[j][cd];
            //we try to add them in ans
            ans+=apsEndingonJ;
            //for current hashmap i we try to add 1+apsendig 0n j
            mp[i][cd]+=(apsEndingonJ+1);
        }
    }
    return ans;
 }
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
