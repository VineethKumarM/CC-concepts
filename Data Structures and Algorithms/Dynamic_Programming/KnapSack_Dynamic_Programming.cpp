#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vii vector<vector<int>>
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
//Knapsack 0/1 problem
//In this 0/1 type of knapsac either we can add fully or remove completerly
//We cannot add any fractionla items
int KnapSack(vi wt,vi val,int W,int n)
{
    //Base Condition is that n==0 or W==0 then return 0;
    //as we cannot process any step
    if(n==0 or W==0) return 0;
    //if the current index element's weight is less than max weight
    //then two cases exist
    //We will return the max value of both the cases
    if(wt[n-1]<=W)
    {
        //return the max value
        return max(val[n-1]+KnapSack(wt,val,W-wt[n-1],n-1),KnapSack(wt,val,W,n-1));
    }
    //if that is not the case since we cannot add that element we directly jump to 
    //its previous element
    else  return KnapSack(wt,val,W,n-1);  
}
//Above implementation is based on Recursion
//We define a matrix of dp based on constraints of maximum value
//We will make dp for those values which are changing
//Here we will intialise all values with -1;
vector<vector<int>> dp(1000,vector<int>(10001));
int   KnapSack_dp(vi wt,vi val,int n,int W)
{
    if(n==0 or W==0) return 0;
    //Since we already stored the max value possible at that step then we simply return
    //the max value as there is no need of recursion again
    if(dp[n][W]!=-1) return dp[n][W];
    //At each step before returning the function we are storing the data in dp matrix
    if(wt[n-1]<=W) return dp[n][W]=max(val[n-1]+KnapSack_dp(wt,val,n-1,W-wt[n-1]),KnapSack_dp(wt,val,n-1,W));
    else return dp[n][W]=KnapSack_dp(wt,val,n-1,W);
}
//Here inorder to avoid the stackoverflow we will tackle the problem with iteartive approach
//using the above table and the concept of top_down
//In this probelm we will make a top down table
//The element of the top_down matrix dp[i][j] the maximum profit that we can be made
//if the given value array size is i and the weight W
//Since we want ans for the maximuum profit if we have the array size of val is n
//and the Weight is W
//then we return the dp[n][W];
int Top_Down(vi wt,vi val,int n,int W)
{
  //if(n==0 or w==0) then we retun the 0
  //Here also we are doing the same as whwnver i(which means n here) or whenver 
  //j (means weight is here) we are intialsing with value 0)
   for(int i=0;i<n+1;i++) for(int j=0;j<W+1;j++) if(i==0 or j==0) dp[i][j]=0;
   //Now here we are staring with 0 value
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<W+1;j++)
        {
            //in normal step wt[n-1]<=W then two case will arise
            //Since we are calulating for an ith sized array and jth max weight 
            //if that wt of that index elemnt is smalller than max j weight 
            if(wt[i-1]<=j)
            //here also same above recursive implemnetation
            //max(val[n-1]+KnapSack(wt,val,W-wt[n-1],n-1),KnapSack(wt,val,W,n-1));
            //Since we are caluclating with respect to i and j wherever n and W is there 
            //we replace it with i and j respectively
            dp[i][j]=max(val[i-1]+dp[i-1][j-wt[i-1]],dp[i-1][j]);
            else
            dp[i][j]=dp[i-1][j];
        }
    }
    //Since we want maximum prodit  for n sized array and W max weight we return dp[n][W]
    return dp[n][W];
}
//In this problem  we have to tell whether a subset exists in a set such that 
//sum of elements in subset is equal to sum or not
//This problem is same as knapsack problem
//dp[i][j] denotes whether it is possible to get the sum j with i sized value array
//If i==0 and j==0 then we can get sum as 0 as null set sum is 0
//If i==0 and j!=0 then we can't get sum as j as our array size is 0 
//if i!=0 and j==0 then we can get a null set for any sized value such taht sum is 0;
bool Subset_Sum(vi val,int sum,int n)
{ 

    //base Condition
    for(int i=0;i<n+1;i++) for(int j=0;j<sum+1;j++)
    {
        if(i==0) dp[i][j]=false;
        if(j==0) dp[i][j]=true;
        if(i==0 and j==0) dp[i][j]=true;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<sum+1;j++)
        {
            //If val of the element is less than j then we will or with inclusion and exclusion results
            //such that maximum of both of them can be assigned to dp[i][j]
            //else we will go with the normal step dp[i][j]=dp[i-1][j];
           if(val[i-1]<=j) dp[i][j]=dp[i-1][j-val[i-1]] or dp[i-1][j];
            else dp[i][j]=dp[i-1][j];
        }
    }
    
    return dp[n][sum];
}
bool Equal_Sum_Partition(vi val,int sum,int n)
{
    //if the sum of all the elements in the array is odd then we cannot 
    //partition the array such that the total sum of both sum of subsets is an odd number
    //as well as they are equal
    //odd+oddd=even or even+even=even since they are eqaul sum of subsets
    //addition of both their sums will always give the even number
    if(sum%2) return false;
    else
    {
        sum/=2;//Here we have to find the sum/2 possible subset
    for(int i=0;i<n+1;i++) for(int j=0;j<sum+1;j++)
    {
        if(i==0) dp[i][j]=false;
        if(j==0) dp[i][j]=true;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<sum+1;j++)
        {
            if(val[i-1]<=j) dp[i][j]=dp[i-1][j-val[i-1]] or dp[i-1][j];
            else dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][sum];
    }
}
int Count_of_subsets_sum(vi val,int sum,int n)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<sum+1;j++)
    {
        //for false one 0 subsets
        //for true one 1 subsets
        if(i==0) dp[i][j]=0;
        if(j==0) dp[i][j]=1;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<sum+1;j++)
        {
            //Here we wll add both posiibilities
            if(val[i-1]<=j) dp[i][j]=dp[i-1][j-val[i-1]]+dp[i-1][j];
            else dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][sum];
}
int Minimum_Subset_Sum(vi val,int n)
{
    int sum=0;
    for(int i=0;i<n;i++) sum+=val[i];
    for(int i=0;i<n+1;i++) for(int j=0;j<sum+1;j++)
    {
        if(i==0) dp[i][j]=0;
        if(j==0) dp[i][j]=1;
    }
    for(int i=1;i<n+1;i++) for(int j=1;j<sum+1;j++)
    {
        if(val[i-1]<=j)
         dp[i][j]=dp[i-1][j-val[i-1]] or dp[i-1][j];
        else
         dp[i][j]=dp[i-1][j];
    }
    int ans;
    for(int i=sum/2;i>=0;i--)
     if(dp[n][i]) return ans=sum-2*i;
     return ans;
}
int Count_of_Subset_with_given_diff(vi val,int n,int sum,int diff)
{
    
    for(int i=0;i<n+1;i++) for(int j=0;j<sum+1;j++) 
    {
        if(i==0) dp[i][j]=0;
        if(j==0) dp[i][j]=1;
    }
    for(int i=1;i<n+1;i++) for(int j=1;j<sum+1;j++)
    {
        if(val[i-1]<=j) dp[i][j]=dp[i-1][j-val[i-1]]+dp[i-1][j];
        else dp[i][j]=dp[i-1][j];
    }
    return dp[n][diff];
}
//Target sum
// Target Sum Problem
// Given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

// Find out how many ways to assign symbols to make sum of integers equal to target S.
int Target_Sum(vi val,int n,int target)
{
    int sum=0;
    for(int i=0;i<n;i++) sum+=val[i];
    for(int i=0;i<n+1;i++) for(int j=0;j<sum+1;j++)
    {
        if(i==0) dp[i][j]=0;
        if(j==0) dp[i][j]=1;
    }
    for(int i=1;i<n+1;i++) for(int j=1;j<sum+1;j++)
    {
        if(val[i-1]<=j) dp[i][j]=dp[i-1][j-val[i-1]]+dp[i-1][j];
        else dp[i][j]=dp[i-1][j];       
    }
    //Since here we will partition the set into two subsets s1 and s2
    //s1 elements are with + and s2 with - 
    //Then the differnce should be target sum therefore same 
    return dp[n][(sum-target)/2];
}
// Unbounded Knapsack (Repetition of items allowed)
//  Given a knapsack weight W and a set of n items with certain value 
//  vali and weight wti, we need to calculate minimum amount that could 
//  make up this quantity exactly. This is different from classical Knapsack problem, 
//  here we are allowed to use unlimited number  of instances of an item.
int Unbounded_KnapSack(vi wt,vi val,int n,int W)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<W+1;j++)
     if(i==0 || j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<W+1;j++)
    {
        //In normal Knapsack after selecting the item we will consider the item as processed
        //and we will move to next elemnts as dp[i-1]
        //But since it can be processed again in case if we select them we won't
        //consider it as proceesed item we will write dp[i][j-wt[i-1]] not dp[i-1] in
        //if we won't select the item then we will do normal dp[i-1] as we consider 
        //in this case that item was proceessed
        if(wt[i-1]<=j) dp[i][j]=max(val[i-1]+dp[i][j-wt[i-1]],dp[i-1][j]);
        else dp[i][j]=dp[i-1][j];
    }
    return dp[n][W];
}
//Rod Cutting Problem
//  Given a rod of length n inches and an array of prices that contains prices 
//  of all pieces of size smaller than n. Determine the  maximum value obtainable 
//  by cutting up the rod and selling the pieces. 
int Rod_Cutting(vi price,int n)
{
    vi v;
    for(int i=0;i<n;i++) v.pb(i+1);
    //In most of the case the two loops are of same n
    //If the rod is not flexible then we can cut in only in certain no.of parts only
    //In that case the sizes may vary then we have ti loop as per the defined sizes
    for(int i=0;i<n+1;i++) for(int j=0;j<n+1;j++) if(i==0 || j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<n+1;j++)
    {
        if(v[i-1]<=j) dp[i][j]=max(price[i-1]+dp[i][j-v[i-1]],dp[i-1][j]);
        else dp[i][j]=dp[i-1][j];
    }
    return dp[n][n];
}
// Coin Change Problem Maximum Number of ways
// Given a value N, if we want to make change for N cents, and we have infinite supply
//  of each of S = { S1, S2, .. , Sm} valued coins, how many ways can we make the change? The order of coins doesn’t matter.
// Example:
// for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}. So output should be 4.
int Coin_Change(vi Coins,int Sum,int n)
{
    //For 0 coins and and non zero sum there is no way to get the sum 
    //so we will intialsie with 0
    //For any nonzero coins sized array inordeer to get the sum 0 dp[0][j]=0;
    //there is always a way of not choosing them 
    //we will intilise them with dp[i][0]=1;
    for(int i=0;i<n+1;i++) for(int j=0;j<Sum+1;j++)
    {
        if(i==0) dp[i][j]=0;
        if(j==0) dp[i][j]=1;
    }
    for(int i=1;i<n+1;i++) for(int j=1;j<Sum+1;j++)
    {
        //As in the case of  subset sum probelm once the eleemnt is proceessed we will 
       //consider it as processed elemnt since here we can chosse the same element at 
       //any no of times then if we choose the coin we wont change the state
       //we will chabge the state if and only if we havent chosen the coin 
       //as further case we wont chosse once we denied
        if(Coins[i-1]<=j) dp[i][j]=dp[i][j-Coins[i-1]]+dp[i-1][j];
        else dp[i][j]=dp[i-1][j]; 
    }
    return dp[n][Sum];
}
// Coin Change Problem Minimum Numbers of coins
// Given a value V, if we want to make change for V cents, 
// and we have infinite supply of each of C = { C1, C2, .. , Cm} 
// valued coins, what is the minimum number of coins to make the change?
// Example:
// Input: coins[] = {25, 10, 5}, V = 30
// Output: Minimum 2 coins required
// We can use one coin of 25 cents and one of 5 cents 
//Intiliasation: if array size is 0 and we have to represent the any j
//then theoretically it is not possible so mathematically we represent this case with
//infinit value 
//so we will intilaise dp[0][j]=INT_MAX-1;
//since in the main code we add 1 to each state and cheks for main value we are intialsing
//one minus value for INT_Max inorder to avoid overflow
//case2 if we have j==0 and a non zero sized array then there is always a way to represent 
//0 as we wont choose any element for this
//dp[i][0]=1; where i!=0
int Minimum_Coin_Change(vi coins,int sum,int n)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<sum+1;j++)
    {
        if(i==0) dp[i][j]=INT_MAX-1;
        if(j==0) dp[i][j]=0;
        //Here make anote that if array size is 0 and we are asked to represnt
        //0 then also the ans is INT_MAx value
        if(i==0 and j==0) dp[i][j]=INT_MAX-1;
    }
    //Here we expliity intialsie for 1 sized array elemntas we can easily for this
    //for any sum j,j%arr[0]==0 then the coins required are j/arr[0]
    //j%arr[0]!=0 then the value will be infinite value
    for(int j=1;j<sum+1;j++) if(j%coins[0]==0) dp[1][j]=j/coins[0]; else dp[1][j]=INT_MAX-1;
    for(int i=2;i<n+1;i++) for(int j=1;j<sum+1;j++)
    {
        //here we will assign minimum of both possibilitieas
        //we add 1 to whenever we chosses the element and 0 whenever it is not chosen
        //minimum of both these we will assign dp[i][j]
        if(coins[i-1]<=j) dp[i][j]=min(1+dp[i][j-coins[i-1]],dp[i-1][j]);
        //since we are adding 1 to dp of each state we reduced - 1there inorder to avoid overflow
        else dp[i][j]=dp[i-1][j];
    }  
    return dp[n][sum];
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vi wt,val;
    wt.pb(1);wt.pb(8);wt.pb(7);wt.pb(4);
    val.pb(1);val.pb(1);val.pb(100);val.pb(1);
    //cout<<Equal_Sum_Partition(val,8,4);
    //cout<<Top_Down(wt,val,4,9);
    //cout<<Count_of_Subset_with_given_diff(val,5,sum,temp);
    // cout<<Count_of_subsets_sum(val,11,5);
   // cout<<Target_Sum(val,5,3);
   //cout<<Unbounded_KnapSack(wt,val,4,14);
   //cout<<Rod_Cutting(val,5);
   vi coins;coins.pb(1);coins.pb(2);coins.pb(3);
   //cout<<Coin_Change(coins,4,3);
   cout<<Minimum_Coin_Change(coins,2,3);
       #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}