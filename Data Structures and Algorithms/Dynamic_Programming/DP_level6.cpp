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
/*There is only one character 'A' on the screen of a notepad. 
You can perform one of two operations on this notepad for each step:
Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.
*/
/*
______________________________________________________Approach_____________________________________

Let us see what the copy and paste operation will mean:
A -> CP --> AA  ->CP --->AAAA --->P -->AAAAA --->CP------->AAAAAAAAAA

If we do one c and p opertaion one after other the current no.ofA's get doubled if we do one p
then the current will get increased by previous copy value
Let us listdown all possiblities of copy paste for 1 to 10

1----->  0
2----->  CP[1]
3-----> CPP[3]
4---->CPPP/CPCP [4]
5----->CPPPP [5]
6----->CPPPPP/CPCPP/CPPCP
7----->CPPPPPPP
8----->CP{7}/CPCPCP/CPCPPCP
 If we take a close look at those numbers which have only one possibility....they are prime numbers

 So we can conclude that for prime numbers the min no.of operations will be n itself

For non -prime numbers:
 6--CPPCP  If we divide at point c---> CPP|CP (CPP(3)*Cp(2)) 3*2===>(3+2) opeations
 8->CPCPCP-->divide at C point CP|CP|CP===2*2*2=8  ==>(2^3)==>(3*2) operations

So for any number n we can conclude that if n can be expressed as =p^a*q^b*r^c
then total no of operations will be a*p+b*q+r*c given p ,q r are prime numbers.

We need to factorise the number n

*/
int minSteps(int n){
    int res=0;
    for(int i=2;i*i<=n;){
        if(n%i==0){
            res+=(n/i);
            n/=i;
        }else i++;
    }
    if(n>1) res+=n;
    return res;
}
/*
Given an integer array nums, return the length of the longest strictly increasing subsequence.

A subsequence is a sequence that can be derived from an array by deleting some or no elements without
 changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7]

___________________________________________________________Approach_______________________________

dp[i] stores the lis till now including nums[i]
*/
int longestIncreasingSubsequence(vector<int> &nums){
    int n=nums.size();
    vector<int> dp(n,0);
    for(int i=1;i<n;i++){
        int max_tn=-1,j=i-1;
        while(j--){
            if(nums[j]<nums[i]) 
              max_tn=max(max_tn,dp[j]);
        }
        dp[i]=max_tn+1;
    }
    return *max_element(begin(dp),end(dp));
}
/*
Let's construct the idea from following example.
Consider the example nums = [2, 6, 8, 3, 4, 5, 1], let's try to build the increasing subsequences starting with an empty one: sub1 = [].
Let pick the first element, sub1 = [2].
6 is greater than previous number, sub1 = [2, 6]
8 is greater than previous number, sub1 = [2, 6, 8]
3 is less than previous number, we can't extend the subsequence sub1, but we must keep 3 because in the future there may have the longest subsequence start with [2, 3], sub1 = [2, 6, 8], sub2 = [2, 3].
With 4, we can't extend sub1, but we can extend sub2, so sub1 = [2, 6, 8], sub2 = [2, 3, 4].
With 5, we can't extend sub1, but we can extend sub2, so sub1 = [2, 6, 8], sub2 = [2, 3, 4, 5].
With 1, we can't extend neighter sub1 nor sub2, but we need to keep 1, so sub1 = [2, 6, 8], sub2 = [2, 3, 4, 5], sub3 = [1].
Finally, length of longest increase subsequence = len(sub2) = 4.
In the above steps, we need to keep different sub arrays (sub1, sub2..., subk) which causes poor performance. But we notice that we can just keep one sub array, when new number x is not greater than the last element of the subsequence sub, we do binary search to find the smallest element >= x in sub, and replace with number x.
Let's run that example nums = [2, 6, 8, 3, 4, 5, 1] again:
Let pick the first element, sub = [2].
6 is greater than previous number, sub = [2, 6]
8 is greater than previous number, sub = [2, 6, 8]
3 is less than previous number, so we can't extend the subsequence sub. We need to find the smallest number >= 3 in sub, it's 6. Then we overwrite it, now sub = [2, 3, 8].
4 is less than previous number, so we can't extend the subsequence sub. We overwrite 8 by 4, so sub = [2, 3, 4].
5 is greater than previous number, sub = [2, 3, 4, 5].
1 is less than previous number, so we can't extend the subsequence sub. We overwrite 2 by 1, so sub = [1, 3, 4, 5].
Finally, length of longest increase subsequence = len(sub) = 4.*/
int longestIncreasingSubseuqnce(vector<int> &nums){
    vector<int> sub;
    for(int n:nums){
        if(sub.empty() or sub.back()<n) sub.push_back(n);
        else {
            auto it=lower_bound(begin(sub),end(sub),n);
            *it=n;
        }
    }
    return sub.size();
}
int maxSumlongestIncreasingSubsequence(vector<int> &nums){
    int n=nums.size();
    vector<int> dp(n,0);
    dp[0]=nums[0];
    for(int i=1;i<nums.size();i++){
        int maxi=0,j=i-1;
        while(j>=0){
            if(nums[i]>nums[j])
              maxi=max(maxi,dp[j]);
        }
        dp[i]=nums[i]+maxi;
    }
    return *max_element(begin(dp),end(dp));
}
int longestBitonicSequence(vector<int> &nums){
    int n=nums.size();
    vector<int> lis(n,0),lds(n,0);
    lis[0]=1,lds[n-1]=1;
    for(int i=1;i<n;i++){
        int j=i-1,maxi=0;
        while(j>=0){
            if(nums[i]>nums[j])
              maxi=max(maxi,lis[j]);
              j--;
        }
        lis[i]=1+maxi;
    }
    for(int i=n-2;i>=0;i--){
        int j=i+1,maxi=0;
        while(j<n){
            if(nums[i]>nums[j])
              maxi=max(maxi,lis[j]);
        }
        lis[i]=1+maxi;
    }
    int res=0;
    for(int i=0;i<n;i++) res=max(res,lis[i]+lds[i]-1);
    return res;
}
int maxNonOverlappingBridges(vector<vector<int>> &banks){
    sort(begin(banks),end(banks));
    int n=banks.size();
    vector<int> dp(n,0);
    for(int i=1;i<n;i++){
        int j=i-1,maxi=0;
        while(j>=0){
            if(banks[i][1]>banks[j][1])
              maxi=max(maxi,dp[j]);
        }
        dp[i]=1+maxi;
    }
    return *max_element(begin(dp),end(dp));
}
/*You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] 
represents the width and the height of an envelope.
One envelope can fit into another if and only if both the width and 
height of one envelope are greater than the other envelope's width and height.
Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
Note: You cannot rotate an envelope.*/
int russinaDollmaxEnvelopes(vector<vector<int>> &A){
    int n=A.size();
    sort(begin(A),end(A));
    vector<int> dp(n,0);
    dp[0]=1;
    for(int i=1;i<n;i++){
        int j=i-1,maxi=0;
        while(j--){
            if(A[i][0]>A[j][0] and A[i][1]>A[j][1])
             maxi=max(maxi,dp[j]);
        }
        dp[i]=1+maxi;
    }
    return *max_element(begin(dp),end(dp));
}
/*Above approach will take O(n^2) complexity. We can still optimise it through 
lis  nlogn approach*/
int russinaDollmaxEnvelopes(vector<vector<int>> &A){
    sort(begin(A),end(A),[](const vector<int> &a,const vector<int> &b){
         if(a[0]==b[0]) return a[1]>b[1];
         else return a[0]<b[0];
    });
    vector<int> sub;
    for(auto n:A){
        if(sub.empty() or sub.back()<n[1]) sub.push_back(n[1]);
        else{
            auto it=lower_bound(begin(sub),end(sub),n[1]);
            *it=n[1];
        }
    }
    return sub.size();
}
int perfectSquareSum(int n){
    vector<int> dp(n+1,0);
    for(int i=1;i<=n;i++){
        int j=1,mini=INT_MAX;
        for(int j=1;j*j<=i;j++){
              mini=min(mini,dp[j]);
        }
        dp[i]=1+mini;
    }
    return dp[n];
}
/*Applications :
Number of possible Binary Search Trees with n keys.
Number of expressions containing n pairs of parentheses which are correctly matched. 
For n = 3, possible expressions are ((())), ()(()), ()()(), (())(), (()()).
Number of ways a convex polygon of n+2 sides can split into triangles by connecting vertices.
convex
Number of full binary trees (A rooted binary tree is full if every vertex has either two children or no children) with n+1 leaves.
Number of different Unlabeled Binary Trees can be there with n nodes.
The number of paths with 2n steps on a rectangular grid from bottom left, i.e., (n-1, 0) to top right (0, n-1) that do not cross above the main diagonal.
rectangle
Number of ways to insert n pairs of parentheses in a word of n+1 letters, e.g., for n=2 there are 2 ways: ((ab)c) or (a(bc)). For n=3 there are 5 ways, ((ab)(cd)), (((ab)c)d), ((a(bc))d), (a((bc)d)), (a(b(cd))).
Number of noncrossing partitions of the set {1, …, 2n} in which every block is of size 2. A partition is noncrossing if and only if in its planar diagram, the blocks are disjoint (i.e. don’t cross). For example, below two are crossing and non-crossing partitions of {1, 2, 3, 4, 5, 6, 7, 8, 9}.  The partition {{1, 5, 7},  {2, 3, 8}, {4, 6}, {9}} is crossing and partition {{1, 5, 7}, {2, 3}, {4}, {6}, {8, 9}} is non-crossing.
partitiom
Number of Dyck words of length 2n. A Dyck word is a string consisting of n X’s and n Y’s such that no initial segment of the string has more Y’s than X’s.  For example, the following are the Dyck words of length 6: XXXYYY     XYXXYY     XYXYXY     XXYYXY     XXYXYY.
Number of ways to tile a stairstep shape of height n with n rectangles. The following figure illustrates the case n = 4:
stair
Number of ways to connect the points on a circle disjoint chords.  This is similar to point 3 above.
Number of ways to form a “mountain ranges” with n upstrokes and n down-strokes that all stay above the original line.The mountain range interpretation is that the mountains will never go below the horizon.Mountain_Ranges
Number of stack-sortable permutations of {1, …, n}. A permutation w is called stack-sortable if S(w) = (1, …, n), where S(w) is defined recursively as follows: write w = unv where n is the largest element in w and u and v are shorter sequences, and set S(w) = S(u)S(v)n, with S being the identity for one-element sequences.
Number of permutations of {1, …, n} that avoid the pattern 123 (or any of the other patterns of length 3); that is, the number of permutations with no three-term increasing subsequence. For n = 3, these permutations are 132, 213, 231, 312 and 321. For n = 4, they are 1432, 2143, 2413, 2431, 3142, 3214, 3241, 3412, 3421, 4132, 4213, 4231, 4312 and 4321*/
int catalanNumber(int n){
    vector<int> dp(n+1);
    dp[0]=1;dp[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            dp[i]+=(dp[j]*dp[i-j-1]);
        }
    }
    return dp[n];
}
/*same as catalan numbers
Let us suppose the given nodes are 1 2 3
  no.of ways(1) as root+no.of ways(2)as root+no.of ways(3) as root*/
int uniqueBinarySearchTrees(int n){
    vector<int> dp(n+1,0);
    dp[0]=1;dp[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            dp[i]+=(dp[j]*dp[i-j-1]);
        }
    }
    return dp[n];
}
int countingValleysAndMountains(int n){
    vector<int> dp(n+1,0);
    dp[0]=1;dp[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            dp[i]+=(dp[j]*dp[i-j-1]);
        }
    }
    return dp[n];
}
int countValidParantheses(int n){
    vector<int> dp(n+1,0);
    dp[0]=1;
    dp[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            dp[i]+=(dp[j]*dp[i-j-1]);
        }
    }
    return dp[n];
}
int nonIntersectingChords(int n){
    vector<int> dp(n+1,0);
    dp[0]=1;dp[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            dp[i]+=(dp[j]*dp[i-j-i]);
        }
    }
    return dp[n];
}
/*
    2               ______

    
    3                /\
                    /__\ 

    
    4                _________      ________
                    |  \     |     |     /  |
                    |    \   |     |   /    |
                    |________|     |________|


   5             T(4)*T(2)+T(3)*T(3)+T(2)*T(4)
*/
int waysOfPolygonTriangulation(int n){
    vector<int> dp(n+1,0);
    dp[2]=1;dp[3]=1;
    for(int i=4;i<=n;i++){
        for(int j=2;j<i;j++){
            dp[i]+=(dp[j]*dp[i-j]);
        }
    }
}
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
