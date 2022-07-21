#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vb vector<bool>
#define vvii vector<vector<int>>
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
//Given an m x n binary matrix filled with 0's and 1's, find the largest square containing 
//only 1's and return its area.
//We can apporach this problem through the bottom up or top-down appoarch up
//Let us define a dp state to be the maximum square side that we can make using the current
//element as top left element
//so if matrix[i][j]=0 then we simply make dp[i][j]=0 as we cannot use 0 to form the square
//the intution goes below whenver matrix[i][j]=1;
//dp[i][j]=min(dp[i+1][j+1],min(dp[i+1][j],dp[i][j+1]);
//Let us see the explanation for the above intution
/*
1 1 1 1 1
1 1 1 1 0
1 1 1 1 0
1 1 1 0 0 
1 0 0 0 0
*/
//Let us supose this is the given configuration
//After iteration from bottom let us say we have reached the at dp[0][0]
//Now we have to decide the value of dp[0][0]
//we will see the botto,,right and diagnnol values of dp
//As it is clear rom the above picture the dp[1][0] is 3 as we can make square of size 3 using
//the current matrix[1][0] as top left
//in the same the dp[1][1] is 2 and dp[0][1] as 3
//Now inorder to decide the value we should see the maximum square that can be built using dp[0][0]
//as top left
//we can see that dp[1][1] as 2 only it means inorder to become 3 there is some element in 3rd row or 3rd col
//that restricts dp[1][1] to 3
//so we are sure that the 3rd row or col from 1 1 has 0
//so now for 1,0 to make it 4th the 4th row from 0,1 or 4 th column must contain 0
//so we wiill select the minimum of these 3 valueand add 1 to it
//as we have increased 1 more row and col value 
//we cann only add 1 to the min
//this can be seen 1 to min only as it is evdent from the above picture if we can make 4 square from 0,0
//the 0 that is restricting the 1,1 is also restriucting us to form sqyre of sixe 4*4
///we can prove the intution that dp[i][j]=min(dp[i+1][j+1],dp[i+1][j],dp[i][j+1])
//At last the we need to fill fir the last row and last col
//since we can construct only 1 sizded square usinng the last element
//we simplt asssign dp[i][j]=matrix[i][j] whenever i==m-1 or j==m-1;
int maximalsqaure(vvii mat){
    int m=mat.size(),n=mat[0].size();
    int ans=0;
    vector<vector<int>> dp(m,vector<int>(n,0));
    for(int i=m-1;i>=0;i--){
        for(int j=n-1;j>=0;j--){
            if(i==m-1 or j==n-1)
              dp[i][j]=mat[i][j];
            else if(mat[i][j]==0)
               dp[i][j]=0;
            else
             dp[i][j]=1+min(dp[i+1][j+1],min(dp[i+1][j],dp[i][j+1]));
             ans=max(ans,dp[i][j]);
        }
    }
    return ans;
}
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<vector<int>> triangle;
    triangle.pb({1});
    triangle.pb({2,3});
    triangle.pb({3,4,5});
    
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 