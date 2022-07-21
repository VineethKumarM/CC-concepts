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
/*Given a string s and a dictionary of strings wordDict, return true if 
s can be segmented into a space-separated sequence of one or more dictionary words.
Note that the same word in the dictionary may be reused multiple times in the segmentation.

______________________________Appproach________________________________________________________

Naive approach is to solve recursively for all substrings and find whether the s can be segmeneted
or not.

Optimised approach:
  We use dp to avoid the extra computation of already solved problems.

  dp[i]===> states in how many ways we can segement substring s(0,i) with the given dict words..

Building dp array:
 dp[i]==>   0 1 2 3 4 5 6 7....i
From 0th index we check whether the substring s(j,i) is present in wordDict or not:
in case if it is present since we already segmented right part of it we need to know no of ways
segment the left part i.e., dp[j-1] ..as dp[j-1] is already precomputed..we add theways of dp[j-1]
to dp[i]
if it is not present we incremenet j keep on cheking for the next substring.
if the whole substring is itself present in s(0,i) in worddict then also we need to add dp[i]+=1;
*/
int wordBreak(string &s,vector<string> &wordDict){
    unordered_map<string,bool> mp;
    for(auto &x:wordDict) mp[x]=true;
    vector<int> dp(s.size(),0);
    for(int i=0;i<s.size();i++){
        for(int j=0;j<=i;j++){
            //if theright substring is present in wordDict
           if(mp[s.substr(j,i-j+1)]) {
            //if(j==0) it means whole string is present then we add+1
            //otherwie we add dp[j-1] ways to dp[i]
              dp[i]+=(j==0?1:dp[j-1]);
           }
        }
    }
    //at last we  return dp[s.size()-1] ways
  return dp[s.size()-1];

  //since we are asked to find out whether we can segment or not.. we can use simple bitset
  //301 is max size of string as per constrain
  //for bitset we need to know the dp size before hand
    bitset<301> dp1;
        for(int i=0;i<s.size();i++){
            for(int j=0;j<=i;j++){
                if(mp[s.substr(j,i-j+1)]){
                    if(j==0) dp1[i]=true;
                    else dp1[i]= dp1[i] or dp1[j-1];
                }
            }
        }
   return dp1[s.size()-1];
}
int optimisedWordBreak(string &s,vector<string> &wordDict){
    unordered_map<string,bool> mp;
    for(auto &s:wordDict) mp[s]=true;
    vector<int> dp(s.size()+1,0);
    dp[s.size()]=true;
    int n=s.size();
    for(int i=n-1;i>=0;i--){
        string temp="";
        for(int j=i;j<n;j++){
           temp+=s[j];
           if(mp.find(temp)!=mp.end()){
             if(j==n-1) dp[i]=true;
             else dp[i]=dp[i] or dp[j+1];
           }
           if(dp[i]) break;
        }
    }
    return dp[0];
}
/*1. Pepcoder is wishing to give offerings to all the temples along a mountain range. 
2. The temples are located in a row at different heights.
3. You have to find the minimum number of offerings such that these conditions are fulfilled - 
    -> If two adjacent temples are at different heights, then the temple which is situated 
    at greater height should receive more offerings.
    -> If two adjacent temples are at the same height, then their offerings relative to each
     other does not matter.

___________________________________________________Approach_____________________________________

As per the above constraints if we have given an x no of offerings then all its adjacent temples
which got lesser height than cur x should be offered <x no of offerings and for the temples
which got greater height should be given more than x.


for example..Let us consider this type of mountain:

                     / \
                    /   \
                   /     \
                  /       \
                           \
                            \
                             \
        if we try to give the  offering as based on heights i.e, we increase the offerings 
        as soon as we get greater height and decrease cur offering as soon as we get lesser height

Above approach won't work as of for the above case the offerings will be as follows:
                      4
                     / \
                (3) /   \ (3)
               (2) /     \ (2)
              (1) /       \ (1)
                           \ (0)
                            \ (-1)
                             \ (-2)

   As we can see the for the above case we started with min value as soon as we get greater value
   we are increasing and as soon as we get lesser height we decrease the offerings
   but through this approach we are getting negative offferings which are invalid ..
So we have to make sure that if we have given x offerings to height[i] then it should be able to
valid all the surrounnding height offerings and offering should be minimum.
for the above diagram the peak should be 6 as it satifisifies both the left and right.

We create a left array such that 
  if (height[i]>height[i-1]) left[i]=1+left[i-1];
  else left[i]=1;
As soon as we get greater height we assign 1 greateer than i-1 height 
ifthe height is equal or lesser we assign minimum value left[i]=1;

We create a right array such that
if(height[i]<height[i+1]) height[i]=1+height[i+1]
else heigt[i]=1;
As soon as we get greater height we assign 1 greateer than i-1 height 
ifthe height is equal or lesser we assign minimum value left[i]=1;
Now at this stage we knwo both max depression at left and max depression at right for index[i]
so we assign offerinsg=max(left[i],right[i]) so that we don't get any invalid condition
and we kept left[i]=1 and right[i]=1 in all other cases so that we get minimum value.
So we add all these max values.
*/
int minTempleOfferings(vector<int> &height){
    int n=height.size(),minOfferings=0;
    vector<int> larr(n,0),rarr(n,0);
    larr[0]=1;
    for(int i=1;i<n;i++){
        if(height[i]>height[i-1]){
            larr[i]=1+larr[i-1];
        }else larr[i]=1;
    }
    rarr[n-1]=1;
    for(int i=n-2;i>=0;i--){
        if(height[i]>height[i+1]){
            rarr[i]=1+rarr[i+1];
        }else rarr[i]=1;
    }
    for(int i=0;i<n;i++) minOfferings+=max(larr[i],rarr[i]);
    return minOfferings;
}
/*
Given a string s. In one step you can insert any character at any index of the string.
Return the minimum number of steps to make s palindrome.
A Palindrome String is one that reads the same backward as well as forward.

________________________Approach______________________________________________________________

We try to find out the longest palindromic subsequnce...then all the remaining charcters need
to be added again to make it palindrome..
n-lps(0,n-1)=min no of inertions to make a string palindrome
*/
int minInsertionsToMakePalindrome(string &s){
    int n=s.size(),maxLen=0;
    vector<vector<bool>> dp(n,vector<bool>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) dp[i][j]=1;
            else if(g==1) dp[i][j]=(s[i]==s[j]);
            else dp[i][j]=(s[i]==s[j]) and dp[i+1][j-1];
            if(dp[i][j]) maxLen=max(maxLen,j-i+1);
        }
    }
    return s.size()-maxLen;
}
/*An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.

Given an integer n, return the nth ugly number.

__________________________________________________Approach_____________________________________________

Let us try to listout the multiples of 2 3 5.

  2 :   2  4 6  8 10 12 14 16 18 20  ........................
  3 :   3  6  9  12 15 18 21 24 27 .........................
  5 :  5 10 15 20 25 30 35 40 45 50 .......................

We keep pointer i=2,j=3 k=5 and we try to move the windows

ug1 =1,ug2 =min(2,3,5)=2;
ug3 =min(4,3,5)=3   ug4=min(4,6,5)=4 ug5=min(6,6,5)=5 ug6=min(6,6,10)=6;
 ug7=min(8,9,10)=8 (Note that 6 came in bith pointers so we incremented both pointers in those
 two tables to avoid duplicay)
 ..................................
 ....................................

 As we keep on building we will be face the values as i=14,j=15,k=15
 Now if we try to assign ugx=min(14,15,15)=14 it gives the wrong answer as 14 is not an ugly number
 
 Observation:
   At each stage we are putting min(2*x,3*y,5*z) as an ugly number where x,y,z are numbers>=1;
   if we want all the numbers to be ugly we need to make sure that x,y,z should be ugly 
   numbers as then only multiplying them with any 2,3,5 won't affect ugliness as we 
   multiplying with vaid numbers.
So we want x,y,z, to be unique..if we try to observe x,y,z values we should have already
added in our dp array x,y,z<2*x,2*y,2*z...since we arruve at 2*(x,y,z) stage it means
we already had crossed x,y,zadded them in dp table so we can keep pointers on these values
for multiplying as with 2,3,5 as each number is valid mulytiplyinh with (2,3,5) wont affect

dp[0]=1..
we keep i=0,j=0,k=0;
dp.push_back min(2*dp[1].3*dp[j],5*dp[k])
noe we have added one min value..
we increment pointer for the value whohc got min value
 if(2*dp[i]==minValue) i++;
if(3*dp[j]==minValue) j++;
if(5*dp[k]==minValue) k++;

Note that herre wehaven't used else if as we have seeen we can get 
2*dp[i]==minvalue and 3*dp[j]==minvalue  ..posiibke case:[6,6,10]

in this case we need to avoid duplicacy so we incremented both pointers

   */
int nthUglyNumber(int n){
    vector<int> dp;
    dp.push_back(1);
    int i=0,j=0,k=0;
    while(dp.size()<n){
       int minValue=min(2*dp[i],min(3*dp[j],5*dp[k]));
       dp.push_back(minValue);
       if(2*dp[i]==minValue) i++;
       if(3*dp[j]==minValue) j++;
       if(5*dp[k]==minValue) k++;
    }
    return dp[n-1];
}
/*We follow the same approach:
A super ugly number is a positive integer whose prime factors are in the array primes.

Given an integer n and an array of integers primes, return the nth super ugly number.

The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

__________________________________________________________Approach______________________________

This time we keep a pointers array for stroring the pointers for ech time.
Then we find min value among all the poinnter multiples..and we add to dp array the min balue
and we increment all the min value pointers.

Now at each iteration we doing over k loop .Therefore,
Time complexity:O(n*k) Space Complexity:O(n)

We need to optimiise the above approach:
instead of keeping pointers array and checking min value we can use priority _queue
which stores {cur_value,{multiplier,pointer_index}} and we keep a map to avoid duplicacy
We giev custom order so that top of the pq will be smallest..
as soon as we get duplicate value we remove the value increment pointer and try to add it again
in pq.

Space optimisation:We can avoid map as duplicacy will be only at last .
so we compare pq.top() with dp[dp.size()-]
*/
int superUglyNumber(int n,vector<int> &primes){
    vector<long long> dp;
    dp.push_back(1);
    priority_queue<pair<long long,pair<int,int>>,vector<pair<long long,pair<int,int>>>,greater<pair<long long,pair<int,int>>>> pq;
    for(int i:primes) pq.push({i,{i,0}});
    unordered_map<int,bool> mp;
    mp[1]=true;
    while(dp.size()<n){
        //duplicacy case
        while(dp[dp.size()-1]==pq.top().first) {
            auto x=pq.top();pq.pop();
            x.second.second+=1;//incrementing the pointer
            x.first=x.second.first*dp[x.second.second];
            pq.push(x);
        }
        auto x=pq.top();pq.pop();
        dp.push_back(x.first);
        mp[x.first]=true;
        x.second.second+=1;
        x.first=x.second.first*dp[(x.second.second)];
        pq.push(x);
    }
    return dp[n-1];
}
/*We stack glasses in a pyramid, where the first row has 1 glass, the second row has 2 glasses,
 and so on until the 100th row.  Each glass holds one cup of champagne.

Then, some champagne is poured into the first glass at the top. 
 When the topmost glass is full, any excess liquid poured will fall equally to the glass 
 immediately to the left and right of it.  When those glasses become full, any excess champagne
  will fall equally to the left and right of those glasses, and so on.  
(A glass at the bottom row has its excess champagne fall on the floor.)

For example, after one cup of champagne is poured, the top most glass is full.  
After two cups of champagne are poured, the two glasses on the second row are half full.  
After three cups of champagne are poured, those two cups become full - there are
 3 full glasses total now.  After four cups of champagne are poured, the third row has 
 the middle glass half full, and the two outside glasses are a quarter full, as pictured below.
 
_____________________________________________Approach____________________________________________


        Ideal Champange Tower                                  Can be converted to dp table
             
              __                                                __
            __  __                                              __ __
          __  __  __                                            __ __ __
        __  __  __  __                                          __ __ __ __
      __  __  __  __  __                                        __ __ __ __ __

So if dp[i][j]>1.0 thnen we equally distribute left drink ti dp[i+1][j],dp[i+1][j+1]

*/
double champagneTower(int poured,int row,int col){
    vector<vector<double>> dp(row+1,vector<double>(col+1,0));
    for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            if(dp[i][j]>1.0){
                double left=dp[i][j]-1.0;
                dp[i][j]=1.0;
                dp[i+1][j]+=(left/2.0);
                dp[i+1][j+1]+=(left/2,0);
            }
        }
    }
    return dp[row][col];
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
