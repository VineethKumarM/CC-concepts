#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>s
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
/*Buy and sell stocks*/
int buy_and_sell_stock1(vi v)
{
    int min_sofar=INT_MAX;
    if(v.size()<2) return 0;
    min_sofar=v[0];
    int ans=INT_MIN;
    for(int i=1;i<v.size();i++)
    {
        ans=max(ans,v[i]-min_sofar);
       min_sofar=min(v[i],min_sofar);
    }
    return ans<0?0:ans;
}
/*Since the infinite transactions allowed we will add all the profits when there is an
increase in the graph we will buy th*/
int buy_and_sell_stock2(vi v)
{
   int bd=0,sd=0,profit=0;
   for(int i=1;i<v.size();i++)
   {
       if(v[i]>=v[i-1]) sd++;
       else{
           profit+=v[sd]-v[bd];
           bd=sd=i;
       }
   }
   profit+=v[sd]-v[bd];
   return profit;
}
/*There is a fee for every selling and infinite transactions allowed.We should ouput the maximum profit possible
Let us suppose that the fee is Rs.3 and and the stocks given below.
Let us define two states
bs(bought state)=The maximum profit that can be obtained by having one extra buy
ss(sold state)=Tge maximum profit that can be obatined by having 0 extra buy
   
Stocks       10    15      20      16    18      22      20       22    20   23     25
 
bs         -10    -10     -10     -9     -9      -9      -9        -9
                                  |
                           (7-16=-9(max(-9,-10)))

ss          0      2       7      7      7       10      10        
                   |
               (15-10-3(fee)=2)

At last we will return the sold state profit
The approach will be same as buy and sell -stock problem1 but the only difference is fee matters here for every selling transaction
*/
int buy_and_sell_stock3(vi v,int fee)
{
    int bs=0,ss=0,profit=0;
    /*Base condition of bought state is when we have only one stock at that stage the profit will be -v[0] and sold state is 
    0*/
    bs=-v[0]; 
    for(int i=1;i<v.size();i++)
    {
        /*Here we have to update two states
        i.Bought state:
        Current bought state=max(last_bought_state,last_sold_state+cur_stock_cost)*/
        int temp_bs=max(bs,ss-v[i]);
        /*fee price fee will be charged for every selling transaction*/
        int temp_ss=max(bs+v[i]-fee,ss);
        bs=temp_bs;
        ss=temp_ss;
    }
    return max(bs,ss);

}
/*Best Time to Buy and Sell Stocks with Cool down - Infinite Transactions Dynamic Programming
1. You are given a number n, representing the number of days.
2. You are given n numbers, where ith number represents price of stock on ith day.
3. You are required to print the maximum profit you can make if you are allowed infinite transactions, but have to cooldown 
for 1 day after 1 transaction
i.e. you cannot buy on the next day after you sell, you have to cooldown for a day at-least before buying again.
Note - There can be no overlapping transaction. One transaction needs to be closed (a buy followed by a sell) before opening 
another transaction (another buy).
In this problem we will define 3 states  1)Bought State(with one extra buy) 2. Sold State(Selling State)   3.Cool down state(where we taken cool down)
                            
Stocks                    Bought State                                   Selling State                                Cool Down State

10                        -10(b1)                                           0                                              0    

15                        -10(b1)[max(-10,15)]                             5(s2b1)(s2-b1=5{max(0,5)})                      0

17                        -10(b1)                                          7(s3b1>s2b1)                                    5(b1s2c3)
       (As we cannot directly buy without cool down period)                    
20                        -10(b1>b1s2c3b4)                                 10(s4b1>s3b1)                                   7(s3b1c4>b1s2c3)

16                        -9(s3b1c4b4>b1)                                  10(s4b1>s5b1)                                  10(s4b1c5>s3b1s4)

18                        -8(s4b1c5b6>s2b1c4b4)                            10(s4b1>s3b1c4b4s5)                             10(s4b1c6==s4b1c5)

At last we will return the profit of sold state
*/
int buy_and_sell_stock4(vi v)
{
    int old_bs=-v[0];
    int old_ss=0;
    int old_cs=0;
    for(int i=1;i<v.size();i++)
    {
        int new_bs=max(old_bs,old_cs-v[i]);
        int new_ss=max(old_ss,v[i]+old_bs);
        int new_cs=max(old_cs,old_ss);
        old_bs=new_bs;
        old_cs=new_cs;
        old_ss=new_ss;
    }
    return old_ss;
}
/*1. You are given a number n, representing the number of days.
2. You are given n numbers, where ith number represents price of stock on ith day.
3. You are required to print the maximum profit you can make if you are allowed two transactions at-most.
Note - There can be no overlapping transaction. One transaction needs to be closed (a buy followed by a sell) 
before opening another transaction (another buy).
Here we are allowed atmost two transactions.Here we divide the problem into subprobles: left and right subproblem
At ith stock:
Left_subproblem:max_profit that can be obtained by allowing only one transaction upto ith stock(including ith stock) 
Right_subproblem:max-profit that can be obtained by alowing only one transacton from ith stock(including ith stock)
Note that we can buy and sell stock at the same day.

Stocks:    30   40    33   60    70    10    81      90

Left :     0    10    10   30    40    40    51      60
           s1     s2b1  s2b1  s4b1  s5b1  s5b1  s7b1   s8b1



Right:    80   80    80    80     80    80    9       0
          b6s8 b6s8 b6s8  b6s8   b6s9  b6s8  b7s8      b8


Total:    80    90    90   110    120   120   60     60

As we can that there are no overlap the two subproblems have been dealt separately at last we will return the maximum total profit

Note:There will be overlap when the graph have a overlapping point in that case there will be buy and sell will be on the same day
and that transaction will be cancelled and it will lead to only one transaction with max_profit
Overlapping point will be(It is highest point from left side and lowest point from right side.That point should satisfy both the conditions
simulatneously)
 */
int buy_and_sell_stock5(vi v)
{
    vi dp_left(v.size());
    vi dp_right(v.size());
    int least_stock_sofar=v[0];
    dp_left[0]=0;
    for(int i=1;i<v.size();i++)
    {
        int cur_profit=v[i]-least_stock_sofar;
        dp_left[i]=max(dp_left[i-1],cur_profit);
        least_stock_sofar=min(least_stock_sofar,v[i]);
    }
    int highest_stock_sofar=v[v.size()-1];
    dp_right[v.size()-1]=0;
    for(int i=v.size()-2;i>=0;i--)
    {
        dp_right[i]=max(dp_right[i+1],highest_stock_sofar-v[i]);
         highest_stock_sofar=max(highest_stock_sofar,v[i]);
    }
    int ans=-1;
    for(int i=0;i<v.size();i++)
    ans=max(ans,dp_left[i]+dp_right[i]);
    return ans;  
}
/*1. You are given a number n, representing the number of days.
2. You are given n numbers, where ith number represents price of stock on ith day.
3. You are given a number k, representing the number of transactions allowed.
3. You are required to print the maximum profit you can make if you are allowed k transactions at-most.
Note - There can be no overlapping transaction. One transaction needs to be closed (a buy followed by a sell) before 
opening another transaction (another buy).
Let us define a state called dp[i][j]  where it states the max-profit that can be obtained by having i transations and j stocks
allowed
Therefore,dp[i][j] can be obtained from these two states:
dp[i][j-1]=max_profit obtained by j-1 stocks from i transactions
dp[i-1][k]=max_profit obtained by i-1 transactions+one transaction of cur_stock(jth_stock)-kth stock where 0<=k<j
{As we had i-1 transactions we need one more transactions to make up i transaction so we keep on looping the max_profit that can be
obtained from this transaction from all k stocks(k<j as we cannot have invalid transaction.}We will take maximum of it)
Therefore dp[i][j]=max(dp[i][j-1],dp[i-1][k]+max_profit_from(jth_stock-kth_stock))*/
int buy_and_sell_stock6(vi v,int k)
{
    /*One edge case need to be consider if k>=v.size()/2 then it is same as infinite transactions
     */
    if(k>=v.size()/2) return buy_and_sell_stock2(v);
    vector<vector<int>> dp(k+1,vector<int>(v.size(),0));
    /*O(n^3) solution
    t=transactions d=days*/
    for(int t=1;t<=k;t++)
    {
        for(int d=1;d<v.size();d++)
        {
            int maxi=dp[t][d-1];
            for(int pd=0;pd<d;pd++)
            {
                /*ptilltm1=profit till t-1 transactions*/
                int ptilltm1=dp[t-1][pd];
                /*profit during tth transaction*/
                int ptth=v[d]-v[pd];
                maxi=max(maxi,ptilltm1+ptth);
            }
            dp[t][d]=maxi;
        }
    }
    /*Optimised O(n^2) 
      As the above solution is O(n^3) we can still optimise the above solution by avoiding the third innermost loop
      dp[i][j]=max(dp[i][j-1],dp[i-1][j-1]+v[j]-v[j-1]
                               dp[i-1][j-2]+v[j]-v[j-2]
                               dp[i-1][j-3]+v[i]-v[j-3]
                               :
                               ::
                               :::::)
        As we have to avod the extra loop for each comparision we can rearrange the second expression as
                              dp[i-1][j-k]-v[k]+v[j] where v[j] is constant
    So we will keep trak the max_value and at last we will compare
            dp[i][j]=max(dp[i][j-1],max_sofar+v[j](as v[j] is constant))

      */
    for(int t=1;t<=k;t++)
    {
        int max_sofar=INT_MIN;
        for(int d=1;d<v.size();d++)
        {
            /*for each values it update max_va;ue for each iteration from previous values*/
            max_sofar=max(max_sofar,dp[t-1][d-1]-v[d-1]);
            dp[t][d]=max(max_sofar+v[d],dp[t][d-1]);
        }
    }
    return dp[k][v.size()-1];
}
int main()
{
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //int n;cin>>n;
  // vector<vector<int>> costs(n,vector<int>(3,0));
   // for(int i=0;i<n;i++)
  /*  {
        for(int j=0;j<3;j++)
        cin>>costs[i][j];
    }*/
    vi v={10,15,20,18,22,20,22,20,23,25};
    cout<<buy_and_sell_stock6(v,2);
    //cout<<min_cost_painting(costs);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}
