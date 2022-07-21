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
vector<vector<int>> dp(1001,vector<int>(100,0));
// Longest Common Subsequence Problem solution using recursion
// Given two sequences, find the length of longest subsequence present in both of them.
// A subsequence is a sequence that appears in the same relative order, but not necessarily 
//This function is the recursive solution to the LCS Problem
//The Base Condition is that if any one of the string is emepty then the 
//Maximum LCS is zero
//Let n and m be the respective string sizes of x and y
//Therfore if(n==0 or m==0) return 0;
//Recurisve Hypothesis
//We will count the LCS from backwards
//if the last eleemnt of both strings are eqaual then we will take the element add 1 to it
//and solve for f(n-1,m-1)
//if they are not equal then one case is that we dont take the elemntnin  n and keep the element 
//in m i.e., f(n-1,m)
//Another case is that we dont take from m-1 and keep the element in n as same i.e.,f(n,m-1)
//We will return the max of both the cases
int LCS_Recursive(string x,int n,string y,int m)
{
    if(n==0 or m==0) return 0;
    //since we have taken the element we add 1 and call for f(n-1,m-1)
    if(x[n-1]==y[m-1]) return 1+LCS_Recursive(x,n-1,y,m-1);
  //return max of both cases
    else return max(LCS_Recursive(x,n-1,y,m),LCS_Recursive(x,n,y,m-1));
}
int LCS_Memorise(string x,int n,string y,int m)
{
    if(n==0 or m==0) dp[n][m]=0;
    if(dp[n][m]!=-1) return dp[n][m];
    else
    {
        if(x[n-1]==y[m-1]) return dp[n][m]=1+LCS_Memorise(x,n-1,y,m-1);
        else  return dp[n][m]=max(LCS_Memorise(x,n-1,y,m),LCS_Memorise(x,n,y,m-1));
    }
}
//Here dp[i][j] state denotes the Longest common subsequence of i sized string x
//j sized string y1
int LCS_Top_Down(string x,int n,string y,int m)
{
    //base cases
    for(int i=0;i<n+1;i++) for(int j=0;j<m+1;j++) if(i==0 or j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<m+1;j++)
    {
        if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    return dp[n][m];
}
//In this problem we have to tell the maximum substrung which is different from
//LCS
//In LCS the strings may differ in size,we have to represent the maximum no of string that is in
//same order with another string
//For ex:s1=abcde s2=abfce For this problem the LCS is 4
//as string abce is in same order in both the strings
//But In case of substring probelm the sizes of both strings must be equal
//it is the maximum contigups substring part that is same in both the cases
// For above example the maximum substring that is common in both the strings is ab or ce 
//and the ans is 2 
int     LC_Substring(string x,int n,string y,int m)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<m+1;j++) if(i==0 or j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<m+1;j++)
    {
        if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=0;
    } 
    int maxe=0;
    for(int i=0;i<n+1;i++) for(int j=0;j<m+1;j++) maxe=max(maxe,dp[i][j]);
    return maxe;
}
//In this problem we have to print the LCS
//We start from the end of the table and move the steps as in original top down approach
//from backwards
//As soon as we get x[i-1]==y[j-1] we will add the charcater to osf
//move to i-1 and j-1 block as we have done 1+dp[i-1][j-1] in original top down step
//If that is not the case we check for both the values dp[i-1][j] and dp[i][j-1]
//We will move to that block which has got max value
//As in original top down step dp[i][j]=max(dp[i-1][j],dp[i][j-1])
string Print_LCS(string x,int n,string y,int m)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<m+1;j++) if(i==0 || j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<m+1;j++)
    {
        if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    //Starting from bottom block dp
    int i=n,j=m;
    string osf;
    while(i!=0 and j!=0)
    {
        //If both the characters are equal then move to back diagnol box 
        if(x[i-1]==y[j-1]) {osf+=x[i-1];i--;j--;}
        else
        {
            //Else check for both adjacent cells of dp move to respective max valued cell
            int temp1=dp[i-1][j];
            int temp2=dp[i][j-1];
            if(temp1>temp2) i--;
            else j--;
        }
    }
    reverse(osf.begin(),osf.end());
    return osf;
}
//Here in this problem we are given with 2 strings we have to represent a single 
//string that contaisn both the subsequences
//we have to tell the lenght of that supersequence
//Let us take a string s1=gtxtab
//s2=ggcfh
//In normal hand book method we eleminate all the common letters write it only once
//in the super sequence and write the other elements as it is in the supersequence 
//For above example since g is present in both the string we write it only one time
//and compare the above strings remove the repeated parts
//if  we closely observe whar we are doing in the above problem is eliminating
//the longest subsequence from both the strings and writing it only one time
//in the super sequence
//In the worst case the super string will be s1+s2=m+n size and after removing the 
//longest subsequence we will get the shortest
//Therfore er return m+n-dp[n][m]; 
int Shortest_Common_Supersequences(string x,int n,string y,int m)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<m;j++) if(i==0 or j==0)dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<m+1;j++)
    {
        if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    return m+n-dp[n][m];
}
//In this problem we are given two strings x and y
//we have to tell the minimum no of insertions and deletions required inorder to 
//convert string from x to y
//For this problem inorder to have minimum no of insertions and deletions we will 
//find the LCS which is common to both the cases
//as this subsequence need not be altered
//Except this LCS we have to delete the other elements which is uncommon from another 
//string so the minimum no of deletions will be n-dp[n][m]
//And we have to insert the other elements which are presnet in y not in x
//as we have to convert x to y therfore the minimum insertions will be
//m-dp[n][m]
pairi Minimum_Insertion_Deletion(string x,int n,string y,int m)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<m+1;j++) if(i==0 || j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<m+1;j++)
    {
        if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]); 
    }
    return {n-dp[n][m],m-dp[n][m]};
}
//Here we have to find the length of the longest palindromic subsequence
//Since we have to find the palindrome string it should be same from backwars also
//The subbsequence must be in the same order from backwards
//So it can be generalised that Longest_Palindromic_Subsequence=LCS(a,reverse of string a)
//Here we are finding the longest Common subsequebce that is common to each other
//string a and reverse of string 
//As the Longest palindrome of a string is the common subsequence that is common 
//from front and backwards
int Longest_Palindromic_Subsequence(string x,int n)
{
    string y=x;
    reverse(x.begin(),x.end());
    for(int i=0;i<n+1;i++) for(int j=0;j<n+1;j++) if(i==0 || j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<n+1;j++)
    {
        if(y[i-1]==x[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    return dp[n][n];
} 
int Minimum_Delt_Palindrome(string x,int n)
{
    string y=x;
    reverse(x.begin(),x.end());
    for(int i=0;i<n+1;i++) for(int j=0;j<n+1;j++) if(i==0 || j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<n+1;j++)
    {
        if(y[i-1]==x[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    return n-dp[n][n];
}
// Given two strings X and Y, print the shortest string that has both X and Y as 
//subsequences. If multiple shortest supersequence exists, print any one of them.`
// Examples:
// Input: X = "AGGTAB",  Y = "GXTXAYB"
// Output: "AGXGTXAYB" OR "AGGXTXAYB" 
// OR Any string that represents shortest
// supersequence of X and Y

// Input: X = "HELLO",  Y = "GEEK"
// Output: "GEHEKLLO" OR "GHEEKLLO"
// OR Any string that represents shortest 
// supersequence of X and Y
//Here we have to print the shortest Superequence that contains both the subsequences of
//strings
//Fo ex: if x=acbdef and y=acbcf output=acbdcef
//This question is similar with printing LCS 
//In this problem also we will traverse the dp table in the same way
//Case 1;if(x[i-1]==y[j-1]) since this character present in LCS we have to add it only once
//osf+=x[i-1];
//Case 2 if they are not equal
//In the case of lcs we will move to max valued cell without any addition
//But in the case super sequence we have to add those odd characters which are differentt
//in the string
//if we are moving towards i-- cell then x[i-1] charctere getting changed while j--
//are constant so we have to add the character which is getting changed osf+=x[i-1]
//In the same way if we are moving towards j-- cell y[j-1] characters are geting changed
//while i-- character are kept constant
//Here another case arises
//if any of i value or j value becomes 0 then it represents the situation
//we are given one nonempty string and an empty string so the shortes supersequence in
//this case will be the whole non empty string
//so we keep on adding the characters until the other non empty strings becomes empty
//since the supersequence is stored in reverse order atlast we will reverse the string 
//and return the string
string Print_Shortest_SuperSequence(string x,int n,string y,int m)
{
   for(int i=0;i<n+1;i++) for(int j=0;j<m+1;j++) if(i==0 or j==0) dp[i][j]=0;
   for(int i=1;i<n+1;i++) for(int j=1;j<m+1;j++)
   {
       if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
       else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
   }
   int i=n,j=m;
   string osf;
   while(i>0 and j>0)
   {
       //If both char are equal we will add only once
       if(x[i-1]==y[j-1]) {osf+=x[i-1];i--;j--;}
       else
       {
           //if dp[i-1] got max value we are moving to i-- block then we are adding x[i-1]
           //as  these charcters are getting changed
           if(dp[i-1][j]>dp[i][j-1]) {osf+=x[i-1];i--;}
           else {osf+=y[j-1];j--;}
       }
   }
   //At last if i==0 then add remaining string of y
   if(i==0) while(j>0) {osf+=y[j-1];j--;}
   //else add x remaining string
   else while(i>0) {osf+=x[i-1];i--; }
   //at last reverse the order
   reverse(osf.begin(),osf.end());
   return osf;
}
// Longest Repeating Subsequence
// Given a string, print the longest repeating subsequence such that the 
//two subsequence don’t have same string character at same position, i.e., any i’th character 
//in subsequences shouldn’t have the same index in the original string.
// Example:
// Input: str = "aab"
// Output: "a"
// The two subsequence are 'a'(first) and 'a' 
// (second). Note that 'b' cannot be considered 
// as part of subsequence as it would be at same
// index in both.
//Ex2: x="aabdxbd" ans="abd" as this part of string is present in both the strings and it
//was repeating
//Approach of the problem
//Here we have only one string which is an odd case of LCS
//Since we want a repeating subsequence we work on simple string
//We will pass the same string as 2nd parameter 
//For this Case the normal LCS will be whole length of string
//Fo ex x="geeks" and y="geeks" the LCS will be "geeks"
//Let us take a charcter at any random position then that character will be a part of 
//Longest_Repeating Subsequence if the same charcter is present at any position other
//than i th position then only we will uncrement value of LCS with 1 value
//So for normal LCS we have to add an extra condition that i!=j
//if(x[i-1]==y[j-1] and i!=j) dp[i][j]=1+dp[i-1][j-1]
//iN all other cases proceeed same as LCS algo
int Longest_Repeaing_Subsequence(string x,int n)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<n+1;j++) if(i==0 || j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<n+1;j++)
    {
        //Extra condition
        if(x[i-1]==x[j-1] and i!=j) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    return dp[n][n];
}
//Here we have to tell the small string subsequrnce is present in big string y
//The point here to note in LCS is if  n,m are the respective sizes of strings x and y
//then the range of LCS will be (0,min(n,m))
//If the small string is present wholly in big string y then LCs length should be equal
//to n as the small string is n 
bool Is_Sequence_Present(string x,int n,string y,int m)
{
    for(int i=0;i<n+1;i++) for(int j=0;j<m+1;j++) if(i==0 or j==0) dp[i][j]=0;
    for(int i=1;i<n+1;i++) for(int j=1;j<m+1;j++)
    {
        if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    return n==dp[n][m];
}
//if we want to make a string palindrome then minimum of no.of deletions will be equal
//to minimum no of insertions
//So this questions turns out to be same as the min no of deletions questions
//which is done in previously
int Min_Insertion_Deletion(string x,int n)
{
    for(int i=0;i<n+1;i++)for(int j=0;j<n+1;j++) dp[i][j]=0;
    string y=x;
    reverse(x.begin(),x.end());
    for(int i=1;i<n+1;i++) for(int j=1;j<n+1;j++)
    {
        if(x[i-1]==y[j-1]) dp[i][j]=1+dp[i-1][j-1];
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    return n-dp[n][n];
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string x="abcf",y="accf";
    // pairi p=Minimum_Insertion_Deletion(x,4,y,3); 
     //string x="abcecba";
    //cout<<p.first<<" "<<p.second;
    //<<Minimum_Delt_Palindrome(x,7);
    //cout<<Print_Shortest_SuperSequence(x,6,y,4);
    //cout<<Longest_Palindromic_Subsequence(x,9);
    cout<<Is_Sequence_Present(x,4,y,4);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;

} 
int solve(vector<int> &A) {
    int n=A.size();
    vector<vector<int>> dp(n,vector<int>(2,0));
    dp[0][0]=A[0];dp[0][1]=-A[0];
    for(int idx=1;idx<n;idx++){
        dp[idx][0]=min(dp[idx-1][0]+A[0],dp[idx-1][1]-A[0]);
        dp[idx][1]=min(dp[idx-1][0]-A[0],dp[idx-1][1]+A[0]);
    }
     return min(dp[n-1][0],dp[n-1][1]);
}