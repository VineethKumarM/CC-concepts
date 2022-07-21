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
/*Approach: 
We traverse given string. For every character encounter, we do the following:
1) Initialize counts of different subsequences caused by different combination of ‘a’. Let this count be aCount.
2) Initialize counts of different subsequences caused by different combination of ‘b’. Let this count be bCount.
3) Initialize counts of different subsequences caused by different combination of ‘c’. Let this count be cCount.
4) Traverse all characters of given string. Do following for current character s[i] 
    If current character is ‘a’, then there are following possibilities : 
    a) Current character begins a new subsequence. 
    b) Current character is part of aCount subsequences. 
    c) Current character is not part of aCount subsequences. 
    Therefore we do aCount = (1 + 2 * aCount);
If current character is ‘b’, then there are following possibilities : 
    a) Current character begins a new subsequence of b’s with aCount subsequences. 
    b) Current character is part of bCount subsequences. 
    c) Current character is not part of bCount subsequences. 
    Therefore we do bCount = (aCount + 2 * bCount);
If current character is ‘c’, then there are following possibilities : 
    a) Current character begins a new subsequence of c’s with bCount subsequences. 
    b) Current character is part of cCount subsequences. 
    c) Current character is not part of cCount subsequences. 
    Therefore we do cCount = (bCount + 2 * cCount);
5) Finally we return cCount;
Explanation of approach with help of example: 
aCount is the number of subsequences of the letter ‘a’.
Consider this example: aa.
We can see that aCount for this is 3, because we can choose these possibilities: (xa, ax, aa) (x means we did not use that character). Note also that this is independent of 
characters in between, i.e. the aCount of aa and ccbabbbcac are the same because both have exactly 2 a’s.
 
Now, adding 1 a, we now have the following new subsequences: each of the old subsequences, each of the old subsequences 
+ the new a, and the new letter a, alone. So a total of aCount + aCount + 1 subsequences.
 
Now, let’s consider bCount, the number of subsequences with some a’s and then some b’s. in ‘aab’,
 we see that bCount should be 3 (axb, xab, aab) because it is just the number of ways we can 
 choose subsequences of the first two a’s, and then b. So every time we add a b, the number of ways increases by aCount.
 
Let’s find bCount for ‘aabb’. We have already determined that aab has 3 subsequences, so certainly we still have those. 
Additionally, we can add the new b onto any of these subsequences, to get 3 more. Finally, we have to count the subsequencthat are made without using any other b’s, 
and by the logic in the last paragraph, that is just aCount. So, bCount after this is just the old bCount*2 + aCount;
 
cCount is similar. */
int subsequences_aibjck(string s)
{
    int a=0;
    int ab=0;
    int abc=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='a')
          a=2*a+3;
          else if(s[i]=='b')
          ab=2*ab+a;
          else if(s[i]=='c')
          abc=2*abc+ab;
    }
    return abc;
}
/*Loop for all elements in arr[] and maintain two sums incl and excl where 
incl = Max sum including the previous element and excl = Max sum excluding the previous element.
Max sum excluding the current element will be max(incl, excl) and max sum including the current
 element will be excl + current element (Note that only excl is considered because elements cannot be adjacent).
At the end of the loop return max of incl and excl.

Approach:If we try to draw all the possibile subsets of this problem then you can observe 
at the level l there is one option for inclusion but two options for exclusion
but we take max of these exclusions as the future of both these trees will be same
so we go with the max                  
Example:  */
int max_sum_non_adjacent_elements(vi v)
{
    int inc=0;
    int exc=0;
    for(int i=0;i<v.size();i++)
    {
        int ninc=exc+v[i];
        int nexc=max(inc,exc);
        inc=ninc;
        exc=nexc;
    }
    return max(inc,exc);
}
/*1. You are given a number n, representing the number of houses.
2. In the next n rows, you are given 3 space separated numbers representing the cost of 
painting nth house with red or blue or green color.
3. You are required to calculate and print the minimum cost of painting all houses without painting
 any consecutive house with same color.
 Naive Approach: The simplest approach to solve the given problem is to generate all possible ways of 
 coloring all the houses with the colors red, blue, and green and find the minimum cost among all the possible 
 combinations such that no two adjacent houses have the same colors. 
Time Complexity: (3^N)
Auxiliary Space: O(1)
Efficient Approach: The above approach can be optimized by using Dynamic Programming as there are overlapping subproblems 
that can be stored to minimize the number of recursive calls. The idea is to find the minimum cost of painting the current 
house by any color on the basis of the minimum cost of the other two colors of previously colored houses. 
Follow he steps below to solve the given problem:
Create an auxiliary 2D dp[][3] array to store the minimum cost of previously colored houses.
Initialize dp[0][0], dp[0][1], and dp[0][2] as the cost of cost[i][0], cost[i][1], and cost[i][2] respectively.
Traverse the given array cost[][3] over the range [1, N] and
 update the cost of painting the current house with colors red, blue, 
 and green with the minimum of the cost other two colors in dp[i][0], dp[i][1], and dp[i][2] respectively.
After completing the above steps, print the minimum of dp[N – 1][0], dp[N – 1][1], and dp[N – 1][2] 
as the minimum cost of painting all the houses with different adjacent colors.
*/
int min_cost_painting_rgb(vector<vector<int>> costs)
{
    vector<vector<int>> dp(costs.size(),vector<int>(3,0));
    int n=costs.size();
    dp[0][0]=costs[0][0];
    dp[0][1]=costs[0][1];
    dp[0][2]=costs[0][2];
    for(int i=1;i<costs.size();i++)
    {
        dp[i][0]=costs[i][0]+min(dp[i-1][1],dp[i-1][2]);
        dp[i][1]=costs[i][1]+min(dp[i-1][0],dp[i-1][2]);
        dp[i][2]=costs[i][2]+min(dp[i-1][0],dp[i-1][1]);
    }
    return min(dp[n-1][0],min(dp[n-1][1],dp[n-1][2]));
}
int min_cost_painting_ncolors(vector<vector<int>> costs)
{
  int n=costs.size(),m=costs[0].size();
  vector<vector<int>> dp(n,vector<int>(m,0));
  for(int j=0;j<m;j++) dp[0][j]=costs[0][j];
  /*Here the complexity is O(n^3)*/
   for(int i=1;i<n;i++)
   {
       for(int j=0;j<m;j++)
       {
            int temp=INT_MAX;
            for(int k=0;k<m;k++)
            {
                if(k!=j)
                 temp=min(temp,dp[i-1][j]);
            }
            dp[i][j]=temp+costs[i][j];
       }
   }
   /*Here we can optimise the above code to O(n^2) by maintaining least and sleast reprsenting 1stmin and 2ndmin*/
   int least=INT_MAX,sleast=INT_MAX;
   for(int j=0;j<m;j++)
   {
       if(dp[0][j]<=least)
       {
           sleast=least;
           least=dp[0][j];
       }else if(dp[0][j]<=sleast)
       sleast=dp[0][j];
   }
   /*Here we dont need to take care of */
   for(int i=1;i<n;i++)
   {
       int nleast=INT_MAX;
       int nsleast=INT_MAX;
       for(int j=0;j<m;j++)
       {
           if(dp[i-1][j]!=least)
             dp[i][j]=least+costs[i][j];
            else
            dp[i][j]=sleast+costs[i][j];
        if(dp[i][j]<=nleast)
       {
           nsleast=nleast;
           nleast=dp[i][j];
       }else if(dp[i][j]<=nsleast)
       nsleast=dp[i][j];
    }
     least=nleast;
     sleast=nsleast;
   }
   int ans=INT_MAX;
   for(int j=0;j<m;j++)
   ans=min(ans,dp[n-1][j]);
   return ans;

}
/*1. You are given a number n and a number k in separate lines, representing the number of fences and number of colors.
2. You are required to calculate and print the number of ways in which the fences could be painted so that not more than 
two consecutive  fences have same colors.*/
/*As per the above question let us assume two variables .One is same which is the count of possible valid configurations such that
last two houses have same color.Another one is diff which is the count of possible valid configurations such that last two houses have 
different colors.The total ways will be equal to sum of same+diff.
For the sake of simplicity let us take three colors r,g and b and let us try to build the table for n=5 houses
 
Houeses            1                    2                        3                            4                           5

same color         0                    3(rr,gg,bb)              6(As we can onlu)            18(prev house diff)         48
for last two                                                     attach to those config
houses                                                            which have diff color

diff color for    3(r,g,b)             6(rg,rb,gr,gb,bg,br)         9*(k-1)=18                     prev total*2=48            132
last two houses   | 
                  (As we can paint     (As we can attach                 
                  with any color)        (k-1) color for each
                                         way of last house
                                         of config)


Total ways        3                      9                         24                             66                       180
*/
int paint_house(int n,int k)
{
    if(n==1)
      return k;
      /*Base condition*/
      int same=0,diff=k;
      int total=same+diff;
      for(int i=2;i<=n;i++)
      {
          same=diff;
          diff=(k-1)*total;
          total=same+diff;
      }
      return total;
}
/*Tiling Problem
1. You are given a number n representing the length of a floor space which is 2m wide. It's a 2 * n board.
2. You've an infinite supply of 2 * 1 tiles.
3. You are required to calculate and print the number of ways floor can be tiled using tiles.
Let us take n*2 board try to fill it with different rotations
1?If we place it vertically then it exectly fits into the dominoes leaving behind n-1 tile space
therefore the problem is converted into suproblem f(n-1)
2.Let us place horizontally covering n-2 space 1m height
Since the board is 2*n it  
  ----------------------
  | 2*1   |
   space  
  |-------| 2*n-2 space
   placed 
  |tile   |
   -------------------
   <-2->   <-n-2 space->
                
After placing the tile we have left over with 2*(n-2) space (let it be n ways we can fill) and 2*1 space above the placed
tile(Let it be m ways we can left)
So total no.of ways flling remaining tiles with dominoes is m*n.But here m equals 1 as only one tile can be placed in that space(2*1)
[horizontally only possible] .So we remain with f(n-2) space problem
Therefore after considering both the cases we can divide the problem into subproblems
      f(n)=f(n-1)[when placed vertically]+f(n-2)[when placed horizontally]
Base conditons:
 f(0)=0,f(1)=1,f(2)=2;
 */ 
int filling_tiles_with_dominoes(int n)
{
    int dp[n+1];
    if(n<3) return n;
    dp[0]=0;
    dp[1]=1;
    dp[2]=2;
    for(int i=3;i<=n;i++) dp[i]=dp[i-1]+dp[i-2];
    return dp[n];
}
/*let us take the tile width of m*n and m*1 tile
We follow the same approach as above as we
i)if placed vertically left with f(n-1) space
ii)If placed horizontally left with n-m space and (m-1)*m space above the place tile
as the place above tile height is <m we caanot place vertically only we can place horizontally
So if dp[i<m]=1 else f(n)=f(n-1)+f(n-m)*/
int filling_tiles_with_dominoes(int n,int m)
{
    int dp[n+1];
    if(n<1) return 0;
    dp[0]=0;
    for(int i=1;i<=n;i++)
     {
         if(i<m) dp[i]=1;
         else dp[i]=dp[i-1]+dp[i-m];
     }
    return dp[n];
}
/*
_______________________________________________________________________________________________

friends pairing:
1. You are given a number n, representing the number of friends.
2. Each friend can stay single or pair up with any of it's friends.
3. You are required to print the number of ways in which these friends can stay single or pair up.
E.g.
1 person can stay single or pair up in 1 way.
2 people can stay singles or pair up in 2 ways. 12 = 1-2, 12.
3 people (123) can stay singles or pair up in 4 ways. 123 = 1-2-3, 12-3, 13-2, 23-1.
*/
/*
Approach: 
Let us try to draw the recursion tree for 123
                                              
                                              123
                                            /   |  \
                                           1   2    21
                                                    /\
                                                    2 21

Following are valid pairs {23-1},{13-2},{3-2-1},{3-21}

Now let us build the recurisve function:
Let f(n) be the number of ways to pair up the friends and n be the last friend
                                      f(n)
                                    /      \
            (it can remain single) f(n-1)   f(n-2)*(n-1) case whre it can be paired with any one friend n-1 friends
                                                        * f(n-2)[remianing possoible pairings of n-2]

So f(n)=f(n-1)+(n-1)*f(n-2) with base values as f[0]=1,f[1]=1;
______________________________________________________________________________________________               
*/
int noOfwaysOfPairing(int n){
    vector<int> dp(n+1);
    dp[0]=1;dp[1]=1;
    for(int i=2;i<=n;i++){
        dp[i]=dp[i-1]+(i-1)*dp[i-2];
    }
    return dp[n];
}
/*_____________________________________________________________________________________________
Above question for combination.There will be no permutation as we are dealing with 
only current element,
If we are asked to find out the permutations then rec function be :
f(n)=(any n can be single) n*f(n-1)+(pair any two friends from n friends)nC2*f(n-2)

_________________________________________________________________________________________________
*/
int noOfwaysPairingPermute(int n){
    vector<int> dp(n+1);
    dp[0]=1;dp[1]=1;
    for(int i=2;i<=n;i++){
        dp[i]=i*dp[i-1]+(i*(i-1))/2*(dp[i-2]);
    }
    return dp[n];
}
/*1. You are given a number n, representing the number of elements.
2. You are given a number k, representing the number of subsets.
3. You are required to print the number of ways in which these elements can be partitioned in k non-empty subsets.
E.g.
For n = 4 and k = 3 total ways is 6
12-3-4
1-23-4
13-2-4
14-2-3
1-24-3
1-2-34

As we have solved recursion problem in the above problem let us take a look at the dp intution
                                                   f(n,k)
                                        (Count of paritiotining
                                                   n elemnts into k subsets)
                                                   

                f(n-1,k-1)                                                             f(n-1,k)  
            (Count of partioning n-1 elements                                         (count of partiotiong n-1 elements
            into k-1 subsets)                                                          into k susbets)
Let us analyse the each case:
  1.If n-1 elements are partitioned into k-1 elements then parent eleemnt has only one option to make another own subset 
  as we want k subsets.So for this case there is only one way for parent element  therefore count of this case 1*f(n-1,k-1)

  2.If n-1 elements are partionined into k subsest xx-xx-xxx--xx..(k subsets) then the parent elemnet has\
   k options as it can join with any subsets (for ex:xxk-xx-xx-xx..(k subsets),xx-xx-xxk-xxx-xxx..(k items))
    so the count of ways for this case is k*f(n-1,k)
    
So total ways is f(n,k)=f(n-1,k-1)+f(n-1,k)*k;

Base Conditions for this problem
If n==0  f(n,k)=0;
if k==0  f(n,k)=0
if(n<k)  f(n,k)=0  as we cannot partions 3 members into 5 groups     
if(n==k) f(n,k)=1 
if k==1 f(n,k)=1  */

int count_partion_k_subsets(int n,int k)
{
    vector<vector<int>> dp(k+1,vector<int>(n+1,0));
    if(n==0 or k==0 or n<k)
     return 0;
     for(int i=1;i<=k;i++)
     {
         for(int j=1;j<=n;j++)
         {
             if(i==1) dp[i][j]=1;
             else if(j<i) dp[i][j]=0;
             else if(j==i) dp[i][j]=1;
             else dp[i][j]=dp[i-1][j-1]+dp[i][j-1]*i;
         }
     }
     return dp[k][n];
}

int main()
{
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;cin>>n;
    vector<vector<int>> costs(n,vector<int>(3,0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
        cin>>costs[i][j];
    }
    //cout<<min_cost_painting(costs);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}
