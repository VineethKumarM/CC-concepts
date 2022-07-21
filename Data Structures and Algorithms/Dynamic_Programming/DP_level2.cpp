#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
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
/*Here we are given a matrix having cell costs in travelling from one cell to another cell
We have to return the min cost from top right to bottom of the grid
Here we travel from the bottom to up
dp[i][j] stores the min cost from the mat[i][j] to reach the end of the grid
So the problem is divided into 4 */
int min_cost_path(vector<vector<int>> mat)
{
   int m=mat.size(),n=mat[0].size();
   vector<vector<int>> dp(n,vector<int>(m,0));
   for(int i=n-1;i>=0;i--)
   {
      for(int j=m-1;j>=0;j--)
      {
        /*4 cases are here*/
        /*when it is at at the edge of the mat the min cost is dp[i][j]=mat[i][j];
        when it is at the last row since there is only on e way possible to move forward
        dp[i][j]=mat[i][j]=dp[i][j+1]
        when it is at column then there is only move dow
        dp[i][j]=dp[i-1][j]+mat[i][j]
        in all other ccases it chhoses from min(dp[i+1][j],dp[i][j+1])+mat[i][j]*/
        if(i==n-1 and j==m-1)
           dp[i][j]=mat[i][j];
          else if(i==n-1)
           dp[i][j]=dp[i][j+1]+mat[i][j];
          else if(j==m-1)
          dp[i][j]=dp[i+1][j]+mat[i][j];
          else
          dp[i][j]=min(dp[i+1][j],dp[i][j+1])+mat[i][j];
      }
   }
    return dp[0][0];
}
/*Here the gold path is given and we can start from any column and can collect the gold avaialbel in that cell
from the cell mat[i][j] we can go to mat[i+1][j+1] or mat[i][j+1] or mat[i-1][j+1]
return the max gold can be collected
Note that here  the smallest problem is at when we are in the last column
then the dp[i][j] is mat[i][j]
Here also 4 cases arises
and the main pointt is the travesal of dp array we traveese through the colum wise 
so we put the colum n loop on outer and row loppninner*/
int maxGold(int n, int m, vector<vector<int>> M)
    {
        // code here
        // int m=mat.size(),n=mat[0].size();
        int dp[n][m];
        for(int i=0;i<n;i++) dp[i][m-1]=M[i][m-1];  
        for(int j=m-2;j>=0;j--)
        {
            for(int i=0;i<n;i++)
            {
                int temp=-1;
                dp[i][j]=M[i][j];
                if(i-1>=0)
                temp=max(dp[i-1][j+1],temp);
                if(i+1<n)
                 temp=max(dp[i+1][j+1],temp);
                 temp=max(temp,dp[i][j+1]);
                 dp[i][j]+=temp;
                
            }
        }
        int ans=0;
        for(int i=0;i<n;i++)
        ans=max(ans,dp[i][0]);
        return ans;
  }
/*Subset Sum Problem*/
bool subset_sum(vector<int> v,int target)
{
   int n=v.size();
   vector<vector<bool>> dp(n+1,vector<bool>(target+1,0));
   for(int i=0;i<=n;i++)
   {
     for(int j=0;j<=target;j++)
     {
         if(i==0 and j==0)
          dp[i][j]=true;
          else if(i==0)
           dp[i][j]=false;
           else if(j==0)
           dp[i][j]=true;
           else{
             if(j<=v[i-1])
              dp[i][j]=dp[i-1][j] or dp[i-1][j-v[i-1]];
              else
              dp[i][j]=dp[i-1][j];
           }
     }
   }
   return dp[n][target];
}
/*Infinite coin change 
This is the combinations of coin change problem.We have coins 2,3,5and 7, and each of infinite supply
we have given a target amount.We have to find the no.of diff combinations of these coins such 
that they make up to the target amount.
Note that here we are given the combinations of coins. So 2,3,5 and 5,3,2 should be counted same as theses are 
the permutations
For this let us create a array of dp,where dp[j] stores the no.of different combiations of these coins that made up j target sum
So we proces the dp table from the i=0 so that we process the coins as 2,3,5 and 7.
If the present coin is 5 then all the combinations with 2 and 3 are already been counted so that occurentce comes as 2,3 and5
and avoids the permuation 5,3,2*/
int coin_change_comb(vector<int> coins,int amount)
{
    vector<int> dp(amount+1,0);
    for(int i=0;i<coins.size();i++)
    {
        for(int j=0;j<=amount;j++)
        {
            if(j==0) dp[0]=1;
            else if(j-coins[i]>=0)
             dp[j]+=dp[j-coins[i]];
        }
    }
    return dp[amount];
}
/*This is the permutaions questions where we count 235 and 352 as different
Inorder to approach this problem we change the tarver direction
as for each dp[j] we try to add the all the coins and find the posiible ways*/
int coin_change_perm(vector<int> coins,int amount)
{
  /*to increase int range*/
   vector<unsigned int> dp(amount+1);
   /*Outer loop for the target sum and inner loop we will check all the possibilities*/
   for(int j=0;j<=amount;j++)
   {
     for(int i=0;i<coins.size();i++)
     {
         if(j==0) dp[j]=1;
         else if(j-coins[i]>=0)
          dp[j]+=dp[j-coins[i]];
     }
   }
   return dp[amount];
}
/*0/1 knapsack problem
Here we are given a bag with maximum weight of W and have given an array of balls with their values
We should maximise the value of balls without excedding the bag weightage*/
int knapsack_0_1(int weight,vector<int> balls,vector<int> values)
{
     vector<vector<int>> dp(balls.size()+1,vector<int>(weight+1,0));
     for(int i=0;i<=balls.size();i++)
     {
       for(int j=0;j<=weight;j++)
       {
         if(i==0 or j==0)
          dp[i][j]=0;
          else if(j-balls[i-1]>=0)
           dp[i][j]=max(values[i-1]+dp[i-1][j-balls[i-1]],dp[i-1][j]);
           else dp[i][j]=dp[i-1][j];
       }
       
     }
     return dp[balls.size()][weight];
}
/*Here the aproach is sameas we  loop the weight outside and check for all possibilities*/
int infinite_knapsack(int weight,vector<int> balls,vector<int> values)
{
  vector<int> dp(weight+1,0);
  for(int j=1;j<=weight;j++)
  {
    for(int i=0;i<balls.size();i++)
    {
      if(j-balls[i]>=0)
        dp[j]=max(dp[j],values[i]+dp[j-balls[i]]);
    }
  }
  return dp[weight];
}
/*Let us take two 1d arrays dp0[] and dp1[] which impiles the n length appropriate strings which ends with 0 and n length appropriate
string which ends with 1 respectively
        0   1    2    3    4   5
dp0[0]  0   1    1    2   3   5
dp1[1]  0   1    2    3   5   8
Base values when n=0 or 1 is dp0[n]=dp0[n]=n;
when n is 2 for dp0[n] the only string are valid which ends with 1 with 1 lenght
so. dp0[n]=dp0[n-1];
for dp1[n] all the n-1 string are valid as we can keep 1 irrespective of the last character
dp1[n]=dp0[n-1]+dp1[n-1]
At last we will return both the strings which ends with 0 and 1
*/
int binary_strings_with_no_consecutive_0s(int n)
{
  vi dp0(n+1),dp1(n+1);
   dp0[0]=0;dp1[0]=0;dp0[1]=1;dp1[1]=1;
   for(int i=2;i<=n;i++)
   {
     dp1[n]=dp1[n-1]+dp0[n-1];
     dp0[n]=dp0[n-1];
   }
     return dp0[n]+dp1[n]; 
     /*By optimising the space complexity*/
     int oczeros=1;
     int ocones=1;
     for(int i=2;i<=n;i++)
     {
       int nczeros=ocones;
       int ncones=ocones+oczeros;
       ocones=ncones;
       oczeros=nczeros;
     }
     return ocones+oczeros;
}
/*in this  qstn we have two option either we can left space or we can have a building but the condition is that '
we cannot put two buildings side by side 
There is a road and we have to design buildings for left and right side
 such that it don't violates any of the above configurations*/
int building_problem(int n)
{
   int dp_b[n+1],dp_s[n+1];
   long long int mod=1e9+7;
   dp_b[0]=0,dp_s[0]=0,dp_b[1]=1,dp_s[1]=1;
   for(int i=2;i<=n;i++)
   {
     dp_b[i]=dp_s[i-1];
     dp_s[i]=(dp_b[i-1]+dp_s[i-1])%mod;
   }
   int ans=(dp_b[n]+dp_s[n])%mod;
   return (ans%mod*ans%mod)%mod;
}
/*Decoding a string
Here we are given mapping of letter to characters form a-1 b-2........................y-25 z-26
We are given a string of numeric characters we have to find the no.of ways we can decode the string with alphabetic so that different 
strings can be formed
For example:"12" can be written as "ab" or "l" as l==12
Constraints:
s[0]!=0 and 0<=s[i]<=9
Let us define a dp state as dp[i] which impliles the no.of ways we can decode the string
There will be 4 cases:
Case1:if(s[i-1]=='0' and s[i-2]=='0'(note that s[i-1] is present character) then there is no character mapped to 0 or we acn join this 0 to last charcter[for ex:10,20] as s[i-2]==0
so the dp[i]=0 in this case.
Case2:if(s[i-2]=='0' and s[i-1]!='0') then we can't join the present chaacter with its former character as(09 or 08) is not valid
only thing valid is that we can join present charcter to the i-1 lenght string
therfore ,dp[i]=dp[i-1]
case3:if(s[i-2]!='0' and s[i-1]=='0') then we there arises two cases 
   Case3.i)If s[i-2]=='1' or s[i-2]=='2' then we can form a charcter by joing the s[i-1] character as(20,10)
      therfore dp[i]=dp[i-2](after joining chacrter)
      here we can not get by singly appending the chacter as 0 is not mapped to any character dp[i] will be straigtly =0;
      Case2:if above case is not there dp[i]=0;
Case4:if s[i-2]!='0' and s[i-1]!='0' then before joiing the lasr twoc chaarcter s we have to check whether valuei s26 or not
n if it is dp[i]=dp[i-2]+dp[i-1]
else dp[i]=dp[i-1]
Base condition is :
 dp[0]=0;
 As s[0]!=0 dp[1]=1;
 dop[1]=1;*/
int decode_string(string s)
{
  int n=s.size();
  vi dp(n+1);
  dp[0]=1,dp[1]=1;
  for(int i=2;i<=n;i++)
  {
    if(s[i-2]=='0' and s[i-1]=='0')
       dp[i]=0;
    else if(s[i-2]=='0' and s[i-1]!='0')
      dp[i]=dp[i-1];
    else if(s[i-2]!='0' and s[i-1]=='0')
    {
      if(s[i-2]=='1' or s[i-2]=='2')
      dp[i]=dp[i-2];
      else dp[i]=0;
    }else if(s[i-2]!='0' and s[i-1]!='0')
    {
      if(stoi(s.substr(i-2,2))<=26)
       dp[i]=dp[i-1]+dp[i-2];
       else
       dp[i]=dp[i-1];
    }
  }
  return dp[n];
}
/*Let a be the number of subsequences of type(a^i) whcih ends with char a
Let ab be the number of subsequences of type(a^ib^j) which ends with char b
Let abc be the number of subsequences of type(a^ib^j^c^k) whcih ends with char c
Algorithm :
If the ith char is "a" then the current character can pair up with all prev_a states
or it won't pair up with a and it can come as single
For example let the prev pairs be a a(a1) a1
then now possible pairs are aa2 aa1a2 a1a2 a aa1 a1 and one extra a1
which leads to 2*a+1
if the current char b it can pair up with all a states before or ab states
for a states its should be pair a for ab it may or mayn't 2*ab+a
same goes for 2*abc+ab;
*/
int countSubsequence_ai_bj_ck(string &s){
   int n=s.size();
   int a=0,ab=0,abc=0;
   for(int i=0;i<n;i++){
       if(s[i]=='a') a=2*a+1;
       else if(s[i]=='b') ab=2*ab+a;
       else abc=2*abc+ab;
   }
   return abc;
}
vector<vector<int>> ans;
void solve(int count,vector<int> &osf,int A,int B){
    if(osf.size()==B) {
        ans.push_back(osf);
        return;
    }
    if(count>A) return;
    solve(count+1,osf,A,B);
    osf.push_back(count);
    solve(count+1,osf,A,B);
     osf.pop_back();
}
vector<vector<int> > combine(int A, int B) {
    vector<int> osf;
    solve(1,osf,A,B);
    return ans;
}
//vector<vector<int>> ans;
void solve(int ind,vector<int> &osf,vector<int> &A,int ssf,int B){
    if(ssf==B){
        ans.push_back(osf);
        return;
    }
    if(ind==A.size() or ssf>B) return;
    int x=ssf;
    while(ssf<B){
        osf.push_back(A[ind]);
        ssf+=A[ind];
    }
    while(osf.size()>0 and ssf!=x){
        solve(ind+1,osf,A,ssf,B);
       osf.pop_back();
       ssf-=A[ind];
    }
    solve(ind+1,osf,A,ssf,B);
}
vector<vector<int> > combinationSum(vector<int> &A, int B) {
    ans.clear();
    vector<int> osf;
    sort(A.begin(),A.end());
    solve(0,osf,A,0,B);
    sort(ans.begin(),ans.end());
    return ans;
}

int main()
{
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //vector<vector<int>> mat={{1,2,3},{1,2,3},{1,2,3}};
   // vi balls={1,2,3,4};
    //vi values={10,20,30,40};
    //cout<<infinite_knapsack(9,balls,values);
    //cout<<decode_string("21123");
    /*vector<int> A={8, 10, 6, 11, 1, 16};
    combinationSum(A,28);
    for(int i=0;i<ans.size();i++){
      for(int j=0;j<ans[i].size();j++){
        cout<<ans[i][j]<<' ';
      }
      cout<<'\n';
    }
  
*/
string s="abcabc";
cout<<countSubsequence_ai_bj_ck(s);
    //cout<<max_gold_path(mat);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}