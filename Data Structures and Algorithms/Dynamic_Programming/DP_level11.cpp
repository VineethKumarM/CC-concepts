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
Given two strings s1 and s2, return the 
lowest ASCII sum of deleted characters to make two strings equal.

Naive Approach:
 Naive approach is to generate all the subsequences of s1 and s2 and we try to equal
 them and find the cost of making that subsqeunce i.e,. (cost of deleteing remaining
 characters).

 Optimisation:


                             ------------S(r1,r2)---cost(c1+c2)---(i)
                            |
                            |
                            |------------S(c1r1,r2)---cost(c2)------(ii)
 f(s1,s2)------f(c1r1,c2r2)-
                            |-------------S(r1,c1r2)----cost(c1)-----(iii)
                            |
                            |
                             -----------S(c1r1,c2r1)----cost=0-------(iv)


Case 1:if c1==c2
     The minimum comes from 4 th type of subsequences as we are getting extra cost innecessarily in
     above 3 subsequnces wihch won't be the case in iv
     We can prove that like we did in the lcs algo

Case 2:if c1!=c2
          Then no set in iv contains answer as all the subseqeunces aee of type
          c1S(r1) c2S(r2) and we are given c1!=c2 so they won;t beequla
          Above 3 cases can be combined as
          
          min(c1+f(r1,c2r2),c2+f(c1r1,r1))
So the dp[i][j]
   if(s[i]==s[j]) dp[i][j]=dp[i+1][j+1]'
   else dp[i][j]=min(a[i]+dp[i+1][j],b[j]+dp[i][j+1]);

*/
int minimumDeleteSum(string &a,string &b){
    int m=a.size(),n=b.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i=m;i>=0;i--){
        for(int j=n;j>=0;j--){
            if(i==m and j==n) dp[i][j]=0;
            else if(j==n) dp[i][j]+=(dp[i+1][j]+a[i]);
            else if(i==m) dp[i][j]+=(dp[i][j+1]+b[j]);
            else {
                if(a[i]==b[j]) dp[i][j]=dp[i+1][j+1];
                else dp[i][j]=min(a[i]+dp[i+1][j],b[j]+dp[i][j+1]);
            }
        }
    }
    return dp[0][0];
}
/*Given two strings word1 and word2, return the minimum number of 
steps required to make word1 and word2 the same.
In one step, you can delete exactly one character in either string.*/

int minDistance(string &word1,string &word2){
     int m=word1.size(),n=word2.size();
     vector<vector<int>> dp(m+1,vector<int>(n+1,0));
     for(int i=m-1;i>=0;i--){
        for(int j=n-1;j>=0;j--){
              if(word1[i]!=word2[j]) dp[i][j]=max(dp[i+1][j],dp[i][j+1]);
              else dp[i][j]=1+dp[i+1][j+1];
        }
     }
     return (m+n)-2*dp[0][0];
}
/*Given an integer array nums, find the contiguous subarray 
(containing at least one number) which has the largest sum and return its sum.
A subarray is a contiguous part of an array.

Naive Approach:naive apporach is to generate all sub arrays find maximum sum among all of them
Time complexity:is O(n^2)

Optimised Approach:Every element has a choice whether to be a part of the sequence
or it can start its own seqeunce.

Suppose the array elements are:
             
             4   3   -2   6  -14   7  -1   4   5   7   -10    2   9   -10     -5    -9   6

         Current Best                                  Overall Best
          4
          7-(43)
          5(43-2)
          11(43-26)
          -3(4,3,-2,6,-14)
          7(7)
          ...
          .....


Now if we obsrve the case of 7 it has two choices 
    It can be part of the prev sequence (cur_sum=will be 4)
    It can start generating its own sequence (cur_sum will be 7)

    Optomal choice is to start sequence of its owm


*/
int maximumSubarraySum(vector<int> &arr){
    int cur_sum=arr[0],msf=arr[0];
    for(int i=1;i<arr.size();i++){
        //checking optimal choice
        if(cur_sum+arr[i]>arr[i]) cur_sum+=arr[i];
        else cur_sum=arr[i];
        msf=max(msf,cur_sum);
    }
    return msf;
}
/*Given an integer array arr and an integer k, modify the array by repeating it k times.

For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].

Return the maximum sub-array sum in the modified array. 
Note that the length of the sub-array can be 0 and its sum in that case is 0.

As the answer can be very large, return the answer modulo 109 + 7.


Let us take two cases:
Case 1:k==1
     This is the simple case we can just apply kadanes Algo for finding max subarray sum

Case ii: k>1
  
  Let us consider the elements are [a,b,c,d,e,f,g]
 
  Let us consider two cases for this case:
   case i)If the total array sum is <0
            a,b,c,d,e f,a,b,c,d,e,f.............a,b,c,d,e,f
                _____________________________________

            If we consider abive part is having greate sum.This case can't be the answer
        as we already given sum<0 therefore if all the whole array come's in b/w
        our maximum subarray then it has always has optimal choice to avoid the whole array
        elements in it as many times as posssible.

      For this case maximum subarray sum can be found by concatening array only one time
      as adding one more time would never change the answer
      so apply kadanes on [a,b,c,d,e,f,g,a,b,c,d,e,f,g];

    
  Case ii)If the total array sum is >0
          
           a,b,c,d,e f,a,b,c,d,e,f.............a,b,c,d,e,f
                _____________________________________

        Let us consider the cases where the array can give max subarray
           [a,b,c,d,e,f,g]
                ______
        Let us suppose that the subarray will be of above pattern.We can prove that this case can't
        be the case 

        Only the below case can give answer
              [a,b,c,d,e,f,g,a,b,c,d,e,f,g]
                   ___________________
        In this type array start from one index and end at the same index from start of new array

  If we consider above case as max sum the sum=c+d+e
  If we consider belwo case as max sum the sum =c+d+e+f+g+a+b+c+d+e
                                               =c+d+e+(total array sum)>0

                                    case 2> case 1

    we simply apply kadanes algo on [a,b,c,d,e,f,g,a,b,c,d,e,f,g]
    add max_sum+(k-2)*(total sum)  as we try to merge as many array as possible as sum>0 which
    is unlike in above case 1
*/
long long kadanesAlgo(vector<int> &arr){
    long long cur_sum=0,max_sum=0;
    for(int i=0;i<arr.size();i++){
        if(cur_sum+arr[i]>arr[i]) cur_sum+=arr[i];
        else cur_sum=arr[i];
        max_sum=max(max_sum,cur_sum);
    }
    return max_sum;
}
int kConcatenationMaxSum(vector<int> &arr,int k){
    if(k==1) return kadanesAlgo(arr);
    long long sum=0,cur_sum=0;
    for(int i:arr) sum+=i;
    int n=arr.size();
    for(int i=0;i<n;i++) arr.push_back(arr[i]);
    cur_sum=kadanesAlgo(arr);
    if(sum<0) return cur_sum;
    return (cur_sum%mod+((k-2)%mod*(sum%mod))%mod)%mod;

}
/* Given an array, find the subarray (containing at least k numbers) which has the largest sum. 

 let us consider the array elements are 
                           [2,3,-4,5,5,6,7,3,4] and given k=4;

Let us suppose if the max sub array ends at ith index then we need to add (i-k+1...i) elements
as the subarray should be greater than k 
it gives exactk sum.Let it be sumK;
then we will add max subaarray sum that ends [i-k]
for atleast k size sum  atleastK=msf[i-k]+sumk

For finding max sum subaaray that ends with i-k index we can use kadanes algo
At each i we find max of all these two values..we will retujrn the ans;
*/
int maxSumSubarrayWithAtleastSizeK(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> max_sf(n,0);
    int cur_sum=0;
    //kadanes'algo
    for(int i=0;i<n;i++){
        if(cur_sum+arr[i]>cur_sum) cur_sum+=arr[i];
        else cur_sum=arr[i];
        max_sf[i]=cur_sum;
    }
    int ksum=0,p=k,ans=0;
    while(p--) ksum+=arr[p-1];
    //ksum woill be first k elements sum
    ans=max(ans,ksum);
    for(int i=k;i<n;i++){
        //we add the current index i delete i-k as ksum is exact k elements sum
      ksum+=(arr[i]-arr[k]);
      ans=max(ans,ksum);
      //for atleast k sum we add max_sum so far index at i-k
      int atleastk=ksum+max_sf[i-k];
      //max ans among these two values
      ans=max(ans,atleastk);
    }
    //return ans at last
    return ans;
}

int main()
 {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
