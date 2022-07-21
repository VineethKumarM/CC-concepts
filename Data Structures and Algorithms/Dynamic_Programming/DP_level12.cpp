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
/*Egg Dropping Problem:
You are given k identical eggs and you have access to a building with 
n floors labeled from 1 to n.

You know that there exists a floor f where 0 <= f <= n such that any
 egg dropped at a floor higher than f will break, and any egg dropped 
 at or below floor f will not break.

Each move, you may take an unbroken egg and drop it from any floor x
 (where 1 <= x <= n). If the egg breaks, you can no longer use it. 
 However, if the egg does not break, you may reuse it in future moves.

Return the minimum number of moves that you need to determine with 
certainty what the value of f is.

___________________________________Approach_________________________________________

Case 1:Since we have to tell the guranteed minimum number of attempts in finding the
crictical floor we have to take consderation into these two cases:

i.The answer should be guanteed so we will consider the worst case at each floor
so that in that worst case we can gurantee the answer we can find the critical floor
ii.It should be minimum no of attemps so we will take the minimum among all the max no
of cases.

Let us cdefine the dp state dp[i][j] as follows the miimum number of attempst needed
to find the critical floor if we have i eggs and j floors

for finding f(i,j) we go at each floor and caluclate the two possibilities

i.the eggs breaks at kth floor -->then minimum no of attempts will be f(i-1,k-1)
   we left with i-1 eggs and k-1 floors as the all the floors above >=k will broke
   so the crictical floor lies in b/w 0 -(k-1) and since the egg broke we left with i-1
   eggs

ii.The egg surivev at kth floor --> then minimum no of attemps will be f(i,j-k)
   we know all the floors below k will never contain crictial fllor 
   so we left with j-k flooors and 

since we need a guranteed answer we take maximum of these two cases..so that we can
be sure of finding the critcial floor independent of what situation it arise
[the egg may broke or may not]
 
 We take min of all these max case as we need minimum number of attemps+guranteed answer

 Base Case:if eggs=0 attemps==0 we cannot do any attempts
           if floors=0 attempts=0;
           if floors=1attemps =1;
           if eggs=1 attempts will be mo of floors as we start from first floor
           and if it breaks then we move to another above floor or else if it breaks
           we can say that it is a guranteed floor.


*/
int eggDroppingProblem(int eggs,int floors){
    vector<vector<int>> dp(eggs+1,vector<int>(floors+1,0));
    for(int i=1;i<=eggs;i++){
        for(int j=1;j<=floors;j++){
            if(i==1) dp[i][j]=floors;
            else if(j==1) dp[i][j]=1;
            else{
                int worstCase=INT_MAX;
                for(int k=1;k<=j;k++){
                    int eggSurvive=dp[i][j-k];
                    int eggBroke=dp[i-1][k-1];
                    worstCase=min(worstCase,max(eggSurvive,eggBroke));
                }
                dp[i][j]=1+worstCase;
            }
        }
    }
    return dp[eggs][floors];
}
/*You are given an integer array nums. Two players are playing a game 
with this array: player 1 and player 2.

Player 1 and player 2 take turns, with player 1 starting first.
 Both players start the game with a score of 0. At each turn, the player 
 takes one of the numbers from either end of the array (i.e., nums[0] or 
 nums[nums.length - 1]) which reduces the size of the array by 1. 
 The player adds the chosen number to their score. 
 The game ends when there are no more elements in the array.
Return true if Player 1 can win the game. If the scores of both players are equal,
 then player 1 is still the winner, and you should also return true.
You may assume that both players are playing optimally.

_______________________________________________________________________________________

Naive Approach is to generate all the caseand give each other same chance of choosing 
the number.Time complexity will be order of power of 2^n as we are checking all the 
possibilities.

We optimise through dp as many subproblems are solved again and again.

Let us define dp[i][j] as maximum score that playeer 1 can obtain if we are given 
only the subarray [i,j] to arr vector.

For example let arr={3,9,3,5,2,4,23,4,} 
Now dp[2][5] is max score obtained by player p1  if we are given with the subarray
{3,5,2,4}

Let us try to build the equation dp[i][j];

 Player 1 turn:                    f(i,j)
                                /          \
                               /            \
Player 2 turn:           arr[i]+f(i-1,j)      arr[j]+f(i,j-1)
                            /                   \
                           /                     \
                    min(f(i-2,j),f(i-1,j-1))     min(f(i-1,j-1),f(i,j-2))


Since our turn is p1,we have a choice either we can pick up arr[i] or arr[j]

Case 1: If we have pikced up arr[i] then we given player 2 with problem f(i-1,j)
As both players are playing optimally he chooses the element(first or last element)
such that the next state gives the minimum ans i.e,, after choosing first element
we will be given state f(i-2,j) or after choosing last element we will  be given
 f(i-1,j-1) .
 So if f(i-1,j-1)<f(i-2,j) the opponent choose j
 else he chooses i

Case2:Same it goes as above case  
We expolore both the cases we return max b/w them

Therefore,dp[i][j]=max(arr[i]+min(dp[i-2][j],dp[i-1][j-1]),arr[j]+min(dp[i-1][j-1]),dp[i][j-2])

Base Case:If i==j only one element is present dp[i][j]=arr[i]l
if gap==1 two elements present in subarray dp[i][j]=max(arr[i],arr[j]);

*/

int optimalStrategyGame(vector<int> &values){
    int n=values.size();
    vector<vector<int>> dp(n,vector<int>(n));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) dp[i][j]=values[i];
            else if(g==1) dp[i][j]=max(values[i],values[j]);
            else{
                dp[i][j]=max(values[i]+min(dp[i+2][j],dp[i+1][j-1]),values[j]+min(dp[i+1][j-1],dp[i][j-2]));
            }
        }
    }
}  
/*_________________________________________________________________________________*/
int maxCherriesDown=0,maxCherriesUp=0;
void pathUp(int row,int col,int csf,vector<vector<int>> &grid){
    if(row<0 or col<0 or row>=grid.size() or col>=grid[0].size() or grid[row][col]==-1)
       return;
    int cherries=grid[row][col];
    grid[row][col]=0;
    if(row==0 and col==0) {
        maxCherriesUp=max(maxCherriesUp,csf+cherries);
        grid[row][col]=cherries;
        return;
    }
    pathUp(row-1,col,csf+cherries,grid);
    pathUp(row,col-1,csf+cherries,grid);
    grid[row][col]=cherries;
    return;
    
}
void pathDown(int row,int col,int csf,vector<vector<int>> &grid){
    if(row<0 or col<0 or row>=grid.size() or col>=grid[0].size() or grid[row][col]==-1)
      return;
    int cherries=grid[row][col];
    grid[row][col]=0;
    if(row==grid.size()-1 and col==grid[0].size()-1){
         maxCherriesUp=0;
         pathUp(row,col,0,grid);
         maxCherriesDown=max(csf+cherries+maxCherriesUp,maxCherriesDown);
         grid[row][col]=cherries;
         return;
    }
    pathDown(row+1,col,csf+cherries,grid);
    pathDown(row,col+1,csf+cherries,grid);
    grid[row][col]=cherries;
    return;
}
/*Inorder to avoid two recursive calls we started with two persons from top of the cell
now the two persons can take steps in this way:
i.Both can take horizontal
ii.One vertical another horizontal
iii.One horizontal another vertical
iv.Both can take vertical

The paths will never cross each other as we can observe that r1+c1==r2+c2 so the states will always
be in diagnol of this type ['/']

If they are at the sane pos we can collect only one cherry and if they are at diff pos 
we can collecty cherries at those two pos..
From those pos we explore all paths from each direction we return the max no.of cherries path
through which we collected max_no.of cherrie

Recurisive dp traversal states be like:



                        /
                    /  /  /
                /  /  /  /  
             / /  /  /  /  /  
              /  /  /  /  / /
                /  /  /  /
                  /
     */
int cherryPickUp(int r1,int c1,int r2,int c2,vector<vector<int>> &grid){
    //out of boundary case
    if(r1>=grid.size() or r2>=grid.size() or c1>=grid[0].size()-1 or c2>=grid[0].size()-1)
     return INT_MIN;
     //no path exists from top to bottom we return inf
    if(grid[r1][c1]==-1 or grid[r2][c2]==-1) return INT_MIN;
    //as last diagnol has one cell so 
    //we can see in above diagram
    if(r1==grid.size()-1 and c1==grid[0].size()-1) return grid[r1][c1];
    int cherries=0;
    if(r1==r2 and c1==c2){
        cherries+=grid[r1][c1];
    }else{
        cherries+=(grid[r1][c1]+grid[r2][c2]);
    }
    int hh=cherryPickUp(r1,c1+1,r2,c2+1,grid);//horizontal horizontal
    int hv=cherryPickUp(r1,c1+1,r2+1,c2,grid);//horizontal vertical
    int vh=cherryPickUp(r1+1,c1,r2,c2+1,grid);//vertical horizontal
    int vv=cherryPickUp(r1+1,c1,r2+1,c2,grid);//vertical vertical
    //cherries+=max(max(hh,hv),max(vh,vv));
    //We can add these x cherries directly to cur cherries as if no path leads to INT_MIN cherries adding
    //some positive cherries(cur cherries) to x leads to >int_min which signfies a path exists
    //which won't be the case
    int x=max(max(vh,hh),max(vv,hv));
    if(x==INT_MIN) return INT_MIN;
    return cherries+x;
}
int cherryPickUp_Memorization(int r1,int r2,int c1,int c2,vector<vector<vector<vector<int>>>> &dp,vector<vector<int>> &grid){
     if(r1>=grid.size() or r2>=grid.size() or c1>=grid[0].size() or c2>=grid[0].size()) return INT_MIN;
     if(grid[r1][c1]==-1 or grid[r2][c2]==-1) return INT_MIN;
     if(r1==grid.size()-1 and c1==grid[0].size()-1) return dp[r1][c1][r2][c2]=grid[r1][c1];
     if(dp[r1][c1][r2][c2]!=-1) return dp[r1][r2][c1][c2];
     int cherries=0;
     if(r1==r2 and c1==c2) cherries+=grid[r1][c1];
     else cherries+=(grid[r1][c1]+grid[r2][c2]);
     int hh=cherryPickUp_Memorization(r1,c1+1,r2,c2+1,dp,grid);
     int hv=cherryPickUp_Memorization(r1,c1+1,r2,c2+1,dp,grid);
     int vh=cherryPickUp_Memorization(r1+1,c1,r2,c2+1,dp,grid);
     int vv=cherryPickUp_Memorization(r1+1,c1,r2+1,c2,dp,grid);
     int x=max(max(hh,hv),max(vh,vv));
     if(x==INT_MIN) return dp[r1][c1][r2][c2]=INT_MIN;
     return dp[r1][c1][r2][c2]=cherries+x;
}
/*above code has an use 4d space we can reduce it 3d space using the relation
 that r1+c1=r2+c2 is always constant in every recursive call
 */
int cherryPickUp_memorization_optimised(int r1,int c1,int r2,vector<vector<vector<int>>> &dp,vector<vector<int>> &grid){
     int c2=r1+c1-r2;
     if(r1>=grid.size() or r2>=grid.size() or c1>=grid[0].size() or c2>=grid[0].size()) return INT_MIN;
     if(grid[r1][c1]==-1 or grid[r2][c2]==-1) return INT_MIN;
     if(r1==grid.size()-1 and c1==grid[0].size()-1) return dp[r1][c1][r2]=grid[r1][c1];
     if(dp[r1][c1][r2]!=-1) return dp[r1][c1][r2];
     int cherries=0;
     if(r1==r2 and c1==c2) cherries+=grid[r1][c1];
     else cherries+=(grid[r1][c1]+grid[r2][c2]);
     int hh=cherryPickUp_memorization_optimised(r1,c1+1,r2,dp,grid);
     int hv=cherryPickUp_memorization_optimised(r1,c1+1,r2+1,dp,grid);
     int vh=cherryPickUp_memorization_optimised(r1+1,c1,r2,dp,grid);
     int vv=cherryPickUp_memorization_optimised(r1+1,c1,r2+1,dp,grid);
     int x=max(max(hh,hv),max(vh,vv));
     if(x==INT_MIN) return dp[r1][c2][r2]=INT_MIN;
     return dp[r1][c1][r2]=cherries+x;

 }
 /*____________________________________________________________________________________________________________
 
 Why the above approach works:

i.We cannot simply apply itertaion dp over this problem as we keep on changing the state and exploring all
the path.If once the path has been explored then all its substates problems has changed as we
are changing them grid[i][j]=0 as soon as we reach the cell.

ii.Why we get the same answer although we replaced the problem statement of going from top ->down and down->top
as two persons going from top->down simultaneously

                             0  0  0  0
                             0  0  0  0
                             0  0  0  0
                             0  0  0  0

Mathematical Proof:
Total no of ways from going top to bottom i.e.,(0,0)-->(3,3) ==>  HHHVVV
                                             All other paths will be permutation of above direction
                        Total Paths=(6!)/(3!)*(3!)


Total no of ways from going bottom to top i.e,(3,3,)-->(0,0)==>VVVHHH
                   Total Paths=(6!)/((3!)*(3!));
                                

Incase if obstacles are there:

                             0  0  0  0
                             0  0  -1  0
                             -1  0  0  0
                             0  0  0  0

Now from the above paths we need to delete those paths which pass through (1,2) and (2,0) as no path
exists from those cells

Top to bottom paths=total paths-(paths from top to -1 cell)*(paths from -1 cell to down)

                 =6!/((3!)*3!)-((3!/2!)*(3!/2!))-((2!/2!)*(4!)/(3!))
                                 |       |           |            |
                                 |       |         (0,0->2,0)      (2,0-->(3,3)) HHHV
                                 HHV     HVV(1,2->(3,3))
                                ((0,0) to (1,2))

                                  

Bottom to top paths =6!/((3!)*3!)-((3!/2!)*(3!/2!))-((4!)/(3!)*(2!/2!))
                                 |       |           |            |
                                 |       |         (3,3->2,0)     (2,0-->(0,0)) HHHV
                                 HHV     HVV(1,2->(0,0)
                                ((3,3) to (1,2))

As we can see that both the number of oaths are equal.It means doing catesian product over these two
we can do cartesian prodcut on one traveral.So we maintained two variable.to approach this
    */
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
