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
________________________________________________________________________________________________

We use matrix chain multiplication for minimising the matrix multiplication steps:
For example let us consider two matrices A(2*3) and B(3*2) then the no.operations in multiplyong
these two matrices..
  A*B=2*3*2=12    
Now consider following chain of matrices A(2*3)*B(3*2)*C(2*4)
Operation type1=(AB)*C=(2*3*2)*C=12+D(2*2)C=12+2*4*2=28 operations
Operation typ2=A(BC)=A(3*2*4)=24+(AD)=24+2*3*4=48 operations
We can observe it has taken minimum no of operation in type1 where we have multiplied AB first
then we multiplied resultant matrix with C.
So we build a dp state which impiles dp[i][j]=min cost of multiplying i to j matrices where i
is the index of array
caluclation of dp[i][j];
if(i>=j) dp[i][j]=0;
else{
    if(gap between i and j==1) then it is the case where we are given only two
    matrices with dimesions A[arr[i]*arr[i+1]] and B[arr[j]*arr[j]]
    as per the given question i+1==j therefore cost will be arr[i]*arr[j]*arr[j+1];

    else if the gap os greater than 2 then we try to find out every possible cost and find min of them
    For example let the matrices are ABCDEFG
    we break the point at k=3 then we find 
     left=min cost of ABC;resultant matrix will have dimension arr[i]*arr[k+1];
     right=min cost(DEFG) resutant matrix will have dimesion arr[k+1]*arr[j+1];
     then cost of res(ABC)*res(DEFG) will be arr[i]*arr[k+1]*arr[j+1];
     Therefore 
     dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+arr[i]*arr[k+1]*arr[j])
Important note is that:as we are building the dp table based on the gap value bw the indices
gap=0--->gap=1--->then gap2 and so on.......  so we traverse the table as given.
}
________________________________________________________________________________________________
*/
int minMatrixOperations(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n-1,vector<int>(n-1,0));
    /*Building the dp table as per gap*/
    for(int g=0;g<dp.size();g++){
        for(int i=0,j=g;j<dp.size();i++,j++){
            /*case where only one matrix is there*/
            if(g==0) dp[i][j]=0;
            /*case where only two matrices are there*/
            else if(g==1) dp[i][j]=arr[i]*arr[j]*arr[j+1];
            else{
                int min_sf=INT_MAX;
                /*we try to break at every start point of i to j-1 and find min of these*/
                for(int k=i;k<j;k++){
                    int left=dp[i][k],right=dp[k+1][j];
                    int cur=arr[i]*arr[k+1]*arr[j+1];
                    min_sf=min(min_sf,left+right+cur);
                }
                dp[i][j]=min_sf;
            }
        }
    }
    return dp[0][n-2];
}
/*
You are given n balloons, indexed from 0 to n - 1. 
Each balloon is painted with a number on it represented by an array nums. 
You are asked to burst all the balloons.
If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. 
If i - 1 or i + 1 goes out of bounds of the array, 
then treat it as if there is a balloon with a 1 painted on it.
Return the maximum coins you can collect by bursting the balloons wisely.

______________________________________________Approach____________________________________________
 
Recursive Function:Try to burst every possible balloon and find the max profit among all 
possibilities.

Since a recursive function there exist the same subproblem which we keep on caluclating:

Optimistaion:Using matrix chain multiplication
Let us try to define the dp  state dp[i][j]

dp[i][j]=max profit bursting i to j ballons including the array.
 Try to observe the clasue that has been added as including the array.Let us try to understand
 what it means.
[2,3,4,5,1,6] suppose we want to burst 3,4,5,1
dp[i][j]=max(C(451)+C(3),C(34)+C(5)+C(1),C(345)+C(1)) where C(x) represent of cost of bursting x

in the first possibilty we try to burst 451 then we burst in that cost of bursting 3 will be
C(3)=2*3*6 cause if we burst 451 then there is no number b/w 2 and 3 , 3 and 6 soif we burst
3 the profit we get 2*3*6 
Above value is including the array...
What abou excluding array:it does mean we areconsidering 3451 aas seerpate array
in that case 3 wiill be burst last no prev and next element exists then cost of bursting will be
simply as 1*3*1

Caluclating dp[i][j]:

We try to iterate over each element and make it as last element to be burst...
then we caluclate left=dp[i][k-1] and right=dp[k+1][j]....and sum up both the values
to the current cost of bursting
dp[i][j]=dp[i][k-1]+dp[k+1][j]+arr[k]*arr[i-1]*arr[j+1]

Here we need to take care on extra edge cases:
Above terms:
i.dp[i][k-1] if the current processngarray is 2,3,1,4 when we make 2 as our last element then there is no left
part so we make simply 0 when k==i
ii.dp[k+1][j] if the curretnt array is 2314 and we make 4 as the last element then there is nor right
so make it simply as 0 when k==j;
 
 iii.arr[i-1]*arr[k]*arr[j+1] when the whole array is 23145 and we are calulcating for part
 2314 and if we made the current processing as any of the elements then 2 will be part of left 14 will
 be right will be 14 and after bursting [3,5] if we try to burst as we made this as last element
 there is no left to it we make it 3*1*5 
 so when i==0 arr[i-1]=1 same goes when j==n-1 arr[j+1]=1;

*/
int maxCostBurstingBallons(vector<int> &nums){
    int n=nums.size();
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            int max_cost=INT_MIN;
            for(int k=i;k<=j;k++){
                /*edge cases*/
                int left=(k==i)?0:dp[i][k-1];
                int right=(k==j)?0:dp[k+1][j];
                int cur=(i==0?1:nums[i-1])*nums[k]*(j!=(n-1)?nums[j+1]:1);
                max_cost=max(max_cost,left+right+cur);
            }
            dp[i][j]=max_cost;
        }
    }
    return dp[0][n-1];
}
/*
You have a convex n-sided polygon where each vertex has an integer value.
 You are given an integer array values where values[i] is the value of the ith vertex 
 (i.e., clockwise order).

You will triangulate the polygon into n - 2 triangles. For each triangle, 
the value of that triangle is the product of the values of its vertices,
 and the total score of the triangulation is the sum of these values over all n - 2 
 triangles in the triangulation.

Return the smallest possible total score that you can achieve with some
 triangulation of the polygon.

 ________________________________________Appproach_____________________________________________

recursive function:we try to find all possibilities and find min cost

dp[i][j] :min cost polygon triangulation with polygon sides (j-i+1) and with values from i to j

We follow the same procedure as we have done in finding the triangulation.

dp[i][j]=dp[i][k]+arr[i]*arr[j]+arr[k]+dp[j][k]

we have made k as another vertex point making i and j as our base 
total cost
left polygon cost=dp[i][k],rightpolygon cost=dp[j][k] and current traingle cost=arr[i]*arr[j]*arr[k]

______________________________________________________________________________________________
*/
int minScorePolygonTriangulation(vector<int> &values){
    int n=values.size();
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0 or g==1) dp[i][j]=0;
            else if(g==2) dp[i][j]=values[i]*values[i+1]*values[j];
            else{
                int min_sf=INT_MAX;
               for(int k=i+1;k<j;k++){
                  int curTriangle=values[i]*values[k]*values[j];
                  int leftTriangle=dp[i][k],rightTriangle=dp[k][j];
                  min_sf=min(min_sf,leftTriangle+curTriangle+rightTriangle);
               }
               dp[i][j]=min_sf;
            }
        }
    }
}
/**/
int booleanParanthesization(string expr,string ops){
      int n=expr.size();
      vector<vector<int>> dpTrue(n,vector<int>(n,0)),dpFalse(n,vector<int>(n,0));
      for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0){
                char ch=expr[i];
                if(ch=='T'){
                    dpTrue[i][j]=1;
                    dpFalse[i][j]=0;
                }else{
                    dpTrue[i][j]=0;
                    dpFalse[i][j]=1;
                }
            }else{
                for(int k=i;k<j;k++){
                    int leftTrue=dpTrue[i][k],leftFalse=dpFalse[i][k];
                    int rightTrue=dpTrue[k+1][j],rightFalse=dpFalse[k+1][j];
                    char ch=ops[k];
                    if(ch=='&'){
                        dpTrue[i][j]+=leftTrue*rightTrue;
                        dpFalse[i][j]+=leftFalse*rightFalse+leftFalse*rightTrue+leftTrue*rightFalse;
                    }else if(ch=='^'){
                        dpTrue[i][j]+=leftFalse*rightTrue+leftTrue*rightFalse;
                        dpFalse[i][j]+=leftFalse*rightFalse+leftTrue*rightTrue;
                    }else if(ch=='|'){
                         dpTrue[i][j]+=leftTrue*rightTrue+leftFalse*rightTrue+leftTrue*rightFalse;
                         dpFalse[i][j]+=leftFalse*rightFalse;
                    }
                }
            }
        }
    }
    return dpTrue[0][n-1];
}
int optimisedBinarySearchTree(vector<int> &keys,vector<int> &freq){
    int n=keys.size();
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int g=0;g<n;g++){
        for(int i=0,j=g;j<n;i++,j++){
            if(g==0) dp[i][j]=freq[j];
            else if(g==1){
                int f1=freq[i],f2=freq[j];
                dp[i][j]=min(f1+2*f2,f2+2*f1);
            }else{
                int totalFreq=0;
                for(int k=i;k<=j;k++) totalFreq+=freq[k];
                /*we can optimise above step through precomputation*/
                int min_sf=INT_MAX;
                for(int k=i;k<=j;k++){
                    int left=(k==i)?0:dp[i][k-1];
                    int right=(k==j)?0:dp[k+1][j];
                    min_sf=min(min_sf,left+right+totalFreq);
                }
                dp[i][j]=min_sf;
            }
        }
    }
    return dp[0][n-1];
}
int rodCutting(vector<int> &cuts){
    int n=cuts.size();
    vector<int> ncuts(n+1,0);
    for(int i=0;i<n;i++) ncuts[i+1]=cuts[i];
    int dp[n+1];
    dp[0]=0;dp[1]=ncuts[1];
    for(int i=1;i<=n;i++){
          dp[i]=ncuts[i];
          int l1=1,r1=i-1;
          while(l1<=r1){
             dp[i]=min(dp[i],dp[l1]+dp[r1]);
             l1++;
             r1--;
          }
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
