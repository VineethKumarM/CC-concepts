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
//In matrix chain multiplication type problems we are given a string or an array
//We will choose a range of indices i and j
//The solve function in the type of solve(arr,i,j)
//and then we will choose every integer k in betweern i and j and call for the 
//function solve(arr,i,k) and solve(arr,k+1,j) store these values in temp and
//do the code to get ans from these two values as per the question
//for example return the max value of all temporary values
int Format(vi arr,int i,int j)
{
    if(i>j) return 0;
    int ans=0;
    for(int k=i;k<j;k++)
    {
        ans=max(Format(arr,i,k),Format(arr,k,j));
        //Here we will do sone extrq work inorder to get ans
    }
    return ans;
}
// Matrix Chain Multiplication using Recursion
//  Given a sequence of matrices, find the most efficient way to multiply 
//  these matrices together. The problem is not actually to  perform the multiplications, 
// but merely to decide in which order to perform the multiplications
//Here we have to output the minmimum cost of multiplication 
//The size of the matrix at an index arr[i] is defined as size=arr[i-1]*arr[i]
//cost of caluclating two matrices is defined as arr[i-1]*arr[i]*arr[j]
//As we will go through the normal format and make changes as per the give question
//Step1:What are the values  of parameters that should be passed
//Since at an index i the size of matrix is arr[i-1]*arr[i] so the minimum i that should
//be passed is 1 as if we pass 0 segenentation fault occurs
//Max value of j can be n-1 as size of matrix is defined at that point
//Step 2:Base Condition
//In normal format base condition is if(i>j) but for this problem we should add an extra
//condition 
//if i==j then size of array will be 1 but to define the matrix size minimum 2 array 
//elemnts are needed
//so we have to add an extra conditions for the normal format condition i.e if(i>=j) return 0;
//Step 3; k range values
//if we divide the problem at k index where k lies in between i and j then there are 
//two ways to break the problem
//Case1:solve(v,i,k) and solve(v,k+1,j)
//Case2:solve(v,i,k-1) and sove(v,k,j)
//If we select Case 1 then the value of k in for loop at max can reach j-1 as in
//that case k+1 is present therfore it can go only upto j-1
//After divinding the problem into (i,k) and (k+1,j) we get two matrices with minmium multiplication
//we have to multiply these final matrices add cost to them
//solve(v,i,k) this function return the minimum cost value for i to k index
//and the size of final matrix will be arr[i-1]*arr[k]
//solve(v,k+1,j) this matrix size will be arr[k]*arr[j]
//as per the definition of calucltaion of cost the cost will be arr[i-1]*arr[k]*arr[j]
//we will intialise our ans with INT_MAX value and finding mimnimum for each k update and 
//update our current minimum ans value
//Finally we return the ans
int Matrix_Chain_Multiplication(vi v,int i,int j)
{
    //Base Condition
    if(i>=j) return 0;
    int ans=INT_MAX;
    //caluclte min value for ecah update of k
    for(int k=i;k<=j-1;k++) ans=min(Matrix_Chain_Multiplication(v,i,k)+Matrix_Chain_Multiplication(v,k+1,j)+v[i-1]*v[k]*v[j],ans);
    return ans;
}
vector<vector<int>>dp(1001,vector<int>(1001,-1));
int MCM_memorise(vi v,int i,int j)
{
    if(i>=j) dp[i][j]=0;
    if(dp[i][j]!=-1) return dp[i][j];
    dp[i][j]=INT_MAX;
    for(int k=i;k<=j-1;k++)
    {
        dp[i][j]=min(MCM_memorise(v,i,k)+MCM_memorise(v,k+1,j)+v[i-1]*v[k]*v[j],dp[i][j]);
    }
    return dp[i][j];
}
// Palindrome Partitioning using Recursion
// Given a string, a partitioning of the string is a palindrome partitioning if 
// every substring of the partition is a palindrome. 
// Example:
//   “aba|b|bbabb|a|b|aba” is a palindrome partitioning of “ababbbabbababa”
//As in the previous problem we will go step by step method and make changes
//as per the given problem to the format 
//Step 1:What valus should we pass as parametres
//Since we want palindromes in partioning we will check from i=0 to j =n-1
//The parameters are 0 and n-1
//Step 2:Base Condition 
//In normal format if(i>j) return 0;
//if(i==j) then it represents a single character which is palindrome itself
//So the  no.of partions we have to do in that case is 0
//Un addition to the normal format base condition we will add this extra condition
//if(i>=j) return 0;
//Another base condition given string is itself a palindrome in this case also
//the partions we have to do is 0
//so we should add this condition that if(palindrome(s)) return 0;
//Step 3:range k values
//Type 1;solve(s,i,k) and solve(s,k+1,j)
//Type 2:solve(s,i,k-1) and solve(s,k,j)
//If we select type 1then k value can go upto j-1 only as k+1 term is present
//For each partion we will solve the subproblems and add 1 as we have divide onxe
//and find the minimum no of partiions
//Function to return is string palindrome in the givenrange s[i] to s[j]
bool Is_Palindrome(string s,int i,int j)
{
    bool flag=true;
    if(i>j) return false;
    while(i<=j) if(s[i]!=s[j]) {flag=false;break;} else {i++;j--;}
    return flag;
}
int Min_Palindrome_Partitioning(string s,int i,int j)
{
    //Base Condition
    if(i>=j) return 0;
    //Checks if the given sttring is palindrome in the given range s[i] to s[j]
    if(Is_Palindrome(s,i,j)) return 0;
    int ans=INT_MAX;
    //finds the min value
    for(int k=i;k<=j-1;k++)
     ans=min(Min_Palindrome_Partitioning(s,i,k)+Min_Palindrome_Partitioning(s,k+1,j)+1,ans);
    return ans;
}
//Memorised code
int Min_Palindrome_Partioning_Memorise(string s,int i,int j)
{
    if(i>=j) dp[i][j]=0;
    if(Is_Palindrome(s,i,j)) dp[i][j]=0;
    if(dp[i][j]!=-1) return dp[i][j];
    dp[i][j]=INT_MAX;
    for(int k=i;k<=j-1;k++)
     dp[i][j]=min(Min_Palindrome_Partioning_Memorise(s,i,k)+Min_Palindrome_Partioning_Memorise(s,k+1,j)+1,dp[i][j]);
    return dp[i][j];
}
//More optimised Code as per Interview Bit Approach
//Above solution will be accepted by most of the codin platforms
//But Interviews bits always wants the code to be as optimised as posssible
//The code will not be accepted if we use an extra space instead of required one
//The optimisation that we have done in this code is avoiding the xtra function call
//whenver we are caluclating the subproblem from i to k and k+1 to j
//we are directly calling these functions
//But cases may arise where these values already stired in dp table 
//Although  after the regular function call it return from the dp table but checking
//befire whether a value is presnet or not before calling always avoids the
//extra stcakflow and time 
//so before calling the functions we check in the for loop only whether the dp
//contains a value or not we will store them in variabke and do the rest of the operation
int Optimised_Palindrome_Partitioning(string s,int i,int j)
{
    if(i>=j) return dp[i][j]=0;
    if(Is_Palindrome(s,i,j)) return dp[i][j]=0;
    if(dp[i][j]!=-1) return dp[i][j];
    dp[i][j]=INT_MAX;
    for(int k=i;k<=j-1;k++)
    {
        //varibles to store left and right variables
        int left,right;
        //check if the value is present or not and assigns the respective values
        if(dp[i][k]!=-1) left=dp[i][k];
        else left=Optimised_Palindrome_Partitioning(s,i,k);
        if(dp[k+1][j]!=-1) right=dp[k+1][j];
        else right=Optimised_Palindrome_Partitioning(s,k+1,j);
        //here we will do the normal operation
        dp[i][j]=min(left+right+1,dp[i][j]);
    }
    return dp[i][j];
}
// Evaluate Expression To True-Boolean Parenthesization Recursion
// Given a boolean expression with following symbols.
// Symbols
//     'T' --- true 
//     'F' --- false 
// And following operators filled between symbols
// Operators
//     &   ---boolean AND
//     |   --- boolean OR
//     ^   --- boolean XOR 
// Count the number of ways we can parenthesize the expression
// so that the value of expression evaluates to true.
// Example:
// Input: symbol[]    = {T, F, T}
//        operator[]  = {^, &}
// Output: 2
// The given expression is "T ^ F & T", it evaluates true
// in two ways "((T ^ F) & T)" and "(T ^ (F & T))"
//Here also we will follow the same steps as in normal format and we will make cahnges as 
//per the given problem
//Step1:What values should we pass as parameters
//Since we want to evaluate ecah caharacter and at the edges only characters are present
//So we will pass i =0 and j=n-1;
//For this problem the normal format parameters is not sufficeient 
//Because since we have to find no.of ways we can make the expression true
//then it can be made from different possibilities
//For example if the operator is & ,for this whole expression to be true both the operands 
//should be true
//If the operator is ^,for whole expression to be true ,one of the operand must be true
//and another  operand must be false
//If the operator is |,for whole expresssion to be true either of the operand is true is enough
//either left operand,or right operand or both operands in all these cases the whole expression
//evaluates to true
//Let the recursive hypothesis is that our function returns the no of ways the strings can be true
//or false as per the given parameters
//For loop variables
//k value in for loop increments by 2 as after each character we get an operand
//s[k]=operator ,s[k-1] is a charcater  and s[k+1] is a charcter
//so we start k with i+1 and end k with j-1 as at these values s[k] is operand
//we want ways for each part either true ways or false ways
//so we define lf,lt,rf,rt
//indicating left false,left right,righyt false,right true
//let the no of ways the left part istrue is lt and right part true the
//if the operand is & then total ways for the whole expression to be true is 
//lt*rt
//as per the given operand we can find the ways
//and sum up all the values and return the sum
int True_Boolean_Paranthesisation(string s,int i,int j,char istrue)
{
    //Base condution
    if(i>j) return 0;
    //if(i==j)
    if(i==j) 
    {
        //if the given expresion asked to find true or false
        //return the value comparing with s[i]
        if(istrue=='T') return s[i]=='T';
        else return s[i]=='F';
    }
    //intialsies ans=0
    int ans=0;
    for(int k=i+1;k<=j-1;k+=2)
    {
        //Evaluates lt,lf,rt,rf by giving the differnbnt characters to istrue
        int lt=True_Boolean_Paranthesisation(s,i,k-1,'T');
        int lf=True_Boolean_Paranthesisation(s,i,k-1,'F');
        int rt=True_Boolean_Paranthesisation(s,k+1,j,'T');
        int rf=True_Boolean_Paranthesisation(s,k+1,j,'F');
        //depending different operands we will add the ways
       if(s[k]=='&') if(istrue=='T') ans+=lt*rt;else ans+=(rt*lf+lf*rf+lt*rf);
       if(s[k]=='^') if(istrue=='T') ans+=(rf*lt+lf*rt); else(lf*rf+lt*rt);
       if(s[k]=='|') if(istrue=='T') ans+=(lf*rt+rt*lt+rf*lt);else ans+=lf*rf;
    }
    //At last we will return the ans;
    return ans;
}
vector<vector<vector<int>>> dpb(1000,vector<vector<int>>(1000,vector<int>(2,-1)));
int True_Boolean_Paranthesisation_Memorisation(string s,int i,int j,char istrue)
{
    if(i>j) {if(istrue=='T') return dpb[i][j][1]=0;else return dpb[i][j][0]=0;}
    if(i==j){if(istrue=='T') return dpb[i][j][1]=(s[i]=='T');else return dpb[i][j][0]=(s[i]=='F');}
    if(istrue=='T') {if(dpb[i][j][1]!=-1) return dpb[i][j][1];}
    else {if(dpb[i][j][0]!=-1) return dpb[i][j][0];}
    //if(istrue=='T') dpb[i][j][1]=0;else dpb[i][j][0]=0; 
    int ans=0;
    for(int k=i+1;k<=j-1;k+=2)
    {
        int lf,lt,rf,rt;
        if(dpb[i][k-1][0]!=-1) lf=dpb[i][k-1][0];else lf=True_Boolean_Paranthesisation_Memorisation(s,i,k-1,'F');
        if(dpb[i][k-1][1]!=-1) lt=dpb[i][k-1][1];else lt=True_Boolean_Paranthesisation_Memorisation(s,i,k-1,'T');
        if(dpb[k+1][j][0]!=-1) rf=dpb[k+1][j][0];else rf=True_Boolean_Paranthesisation_Memorisation(s,k+1,j,'F');
        if(dpb[k+1][j][1]!=-1) rt=dpb[k+1][j][1];else  rt=True_Boolean_Paranthesisation_Memorisation(s,k+1,j,'T');
        if(s[k]=='&') {if(istrue=='T') ans+=lt*rt;else ans+=(rt*lf+lf*rf+lt*rf);}
        else if(s[k]=='|') {if(istrue=='T') ans+=(lt*rt+lf*rt+rf*lt);else ans+=lf*rf;}
        else if(s[k]=='^') {if(istrue=='T') ans+=(lf*rt+rf*lt);else ans+=(lt*rt+lf*rf);}
    }
    if(istrue=='T') return dpb[i][j][1]=ans;
    else return dpb[i][j][0]=ans;
}
//We can avoid the 3d matrix with the use of map
//we use string as "i j T"as index and keep the value in it
unordered_map<string,int> mp;
int True_Boolean_Paranthesisation_Memorisation_map(string s,int i,int j,char istrue)
{
     string temp;
     temp=to_string(i);
     temp+=(' ');
     temp.append(to_string(j));
     temp+=(' ');
     temp.pb(istrue);
     if(i>j){return mp[temp]=0;}
     if(i==j){return mp[temp]=(s[i]==istrue);}
     if(mp.find(temp)!=mp.end()) return mp[temp];
     int ans=0;
     for(int k=i+1;k<=j-1;k+=2)
     {
           int lf,lt,rt,rf;
           lf=True_Boolean_Paranthesisation_Memorisation_map(s,i,k-1,'F');
           lt=True_Boolean_Paranthesisation_Memorisation_map(s,i,k-1,'T');
           rf=True_Boolean_Paranthesisation_Memorisation_map(s,k+1,j,'F');
           rt=True_Boolean_Paranthesisation_Memorisation_map(s,k+1,j,'T');
           if(s[k]=='&') {if(istrue=='T') ans+=lt*rt;else ans+=(rt*lf+lf*rf+lt*rf);}
           else if(s[k]=='|') {if(istrue=='T') ans+=(lt*rt+lf*rt+rf*lt);else ans+=lf*rf;}
           else if(s[k]=='^') {if(istrue=='T') ans+=(lf*rt+rf*lt);else ans+=(lt*rt+lf*rf);}
     }
     return mp[temp]=ans;
}
// Scramble String using Recursion
// Given a string s1, we may represent it as a binary tree by partitioning it to 
//two non-empty substrings recursively.
// Below is one possible representation of A = “great”:
//  great
//    /    \
//   gr    eat
//  / \    /  \
// g   r  e   at
//            / \
//           a   t
// To scramble the string, we may choose any non-leaf node and swap its two children.

// For example, if we choose the node “gr” and swap its two children,
// it produces a scrambled string “rgeat”.

//     rgeat
//    /    \
//   rg    eat
//  / \    /  \
// r   g  e   at
//            / \
//           a   t
// We say that “rgeat” is a scrambled string of “great”.
// Similarly, if we continue to swap the children of nodes “eat” and “at”, it produces a scrambled string “rgtae”.
//     rgtae
//    /    \
//   rg    tae
//  / \    /  \
// r   g  ta  e
//        / \
//       t   a
// We say that “rgtae” is a scrambled string of “great”.
//Here we will define a recurive function that returns whether the given strings are 
//scrambled or not
//Here the base condition is that if the givem two strings are equal theya re always 
//scrambled
//If the given two strings of different it is not possible to swap string a to get string b
//Recursive Hypothesis
//If a string is given then let c1 and c2 be the childs of the given partitiobed
//that has been partitined at kth position into (0,k) and k-1 to end of strings
//At each level 2 cases arises
//whether these nob leafnodes(childs) are swapped or not
//As per the given condition of the 1stn we cannot partition the string to an e,mpty sring+full string
//Each child of parent should contain atleast one character
//If they are swappped then we will compare the scramblence of 1st part of strinng
//with last part of string and similarly we compare the scramblence of 2nd part with 
//1st part
//bool temp1=Scramble(1st(a),2nd(b)) && Scramble(2nd(a),1st(b))
//If they are not  swapped we simply test the scramblemnce of 1st partitioon with 2nd string's
//1st partition and 2nd partition of 1st string and 2nd partition of 2nd string
//bool temp2=Scramble(1st(a),1st(b)) && Scramble(2nd(a),2nd(b))
//Let temp1 be the boolean value of scramblence of the case 1 of the strings
//Let temp2 be the boolean value of scramblence of case 2 of strings
//if either of temp1 ortemp2 scramblence of strings is true then return
//After differnt partions at differnetposition we cannot conver the string a to string b
//then we will return false
bool Scrambled_string(string a,string b)
{
    //Base Conditions
    //if sizes are not equal
    if(a.size()!=b.size()) return false;
    //If the given two strings both are equal then return true
    if(a.compare(b)==0) return true;
    //If anyone of the string is empty
    //Here we equated to 1 also because if the given string contains only one character
    //and both strings are not equal as they are compared above with compare function
    //since it has got no childs so return false
    //if both string have same charcter value then it would have already retirned true from
    //compare function
    if(a.size()<=1) return false;
    for(int k=1;k<a.size();k++)
    {
        bool temp1=Scrambled_string(a.substr(0,k),b.substr(b.size()-k,k)) && Scrambled_string(a.substr(k,a.size()-k),b.substr(0,b.size()-k));
        bool temp2=Scrambled_string(a.substr(0,k),b.substr(0,k)) && Scrambled_string(a.substr(k,a.size()-k),b.substr(k,b.size()-k));
        if(temp1 or temp2) return true;
    }
    return false;
}
//Here we use memorisation to avoid extra recursive calls
//we store the string as an key and map it into its bool value whether it is a scrambled 
//or not
unordered_map<string,bool> mps;
bool Scrambled_string_memorise(string a,string b)
{
     string temp;
     temp+=a;temp.pb('_');temp+=b;
     if(a.size()!=b.size()) return false;
     if(a.compare(b)==0) return true;
     if(a.size()<=1) return false;
     if(mps.find(temp)!=mps.end()) return mps[temp];
     for(int k=0;k<a.size();k++)
     {
         bool temp1=Scrambled_string(a.substr(0,k),b.substr(b.size()-k,k)) && Scrambled_string(a.substr(k,a.size()-k),b.substr(0,b.size()-k));
         bool temp2=Scrambled_string(a.substr(0,k),b.substr(0,k)) && Scrambled_string(a.substr(k,a.size()-k),b.substr(k,b.size()-k));
         if(temp1 or temp2) return mps[temp]=true;
     }
     return mps[temp]=false;
}
// Egg Dropping using Recursion
// Problem statement: You are given N floor and K eggs. You have to minimize 
//the number of times you have to drop the eggs to find the critical floor 
//means the floor beyond which eggs start to break. Assumptions of the problem:
// If egg breaks at ith floor then it also breaks at all greater floors.
// If egg does not break at ith floor then it does not break at all lower floors.
// Unbroken egg can be used again.
// Note: You have to find minimum trials required to find the critical floor not the critical floor.
// Example:
// Input:
//     4
//     2 
//     Output:
//     Number of trials when number of eggs is 2 and number of floors is 4: 3
//Let us take an example to understand the problem
//There is a manager and under him there are 4 sde who can complete a project either 
//in best case x1 days or in worst case x2 days
//sde1=min x1 max x2
//sde2=min x3 max x4
//sde3=min x5 max x6
//sde4=min x7 maxx x8
//For each sde either he can complete in x1 time in best case scenario or max x2 time
//in worst case scenario
//There is a project given bt=y ceo to manager
//Now the manager has to tell what is the guranteed minimum time to get the project completed
//Now the mangaer has a choice to choose the sde but he cannot tell whether that sde complets
//the work in min time or max time cause that purely depends upon the sde which is 
//not in the hands of manger
//since the manager wants a guaranteed ans so he consider the worst case of each sde 
//and he wants the best answwer he will chhose the minimum of all worst cases
//min(max(sde1),max(sde2),max(sde3),max(sde4))
//This will give the manager to give the guaranteed best possible time
//The egg dropping problem is similar to the above case problem
//We have to tell the minimun no.of trails that should be made so that we can guarantee
//that we cab find the threshold floor
//Let f be the threshold floor
//Then f is defined as if we drop a egg at any floor x i/e,x>=f it will break
//If the x<f then it will not break
//Base conditions
//Here n means no.of floors and e means no.of eggs
//If n==0 then attempts will be 0
//if n==1 minimum attempts needed will be 0
//if e==1 then we have to check the floors from the bottom
//we start from 1 and we keep on droppingthe egg at ecah floor and uf it is broke theb 
//that is the first floor at which the egg starts breakinhg 
//if the egg didnt broke then we can reuse the egg move to upper floor and checks the remaining floor
//so if e==1min the worst case the minimum no of attempts will be total floors only
//thereore if(e==1) return n;
//Let the recurisve hypothesis is that solve(n,k) return the minimum no of attempts 
//needed to find the threshold floor for n floors using k eggs
//Now the loop starts and we check and throws the egg ate each floor finds the minimum \
//case in all throwiings
//Here two cases arises
//case 1  if the egg is brokem
//In this case if the egg is broken then it sure that in all the above floors of k the 
//egg will broke 
//so now we have to check below for k-1 floors and eggs we left with e-1
//case 1=temp1=solve(k-1,e-1)
//if the egg didnot borke then it was sure that the threshold floor will lie in between k and n-k
//case 2=temp2=solve(n-k,e) since the egg didnt broke in the case we kept the e as unchanged
//temp1 and temp2 are like min and max of sde1
//since we will selet the worst case scenario and since we attempted 1 time
//we add 1+max(solve(k-1,e-1) ,solve(n-k,e))
//we find min of all the possible sequences
//ans=min(ans,1+max(solve(k-1,e-1),solve(n-k,e))
//we will throw from each floor and checks for which floor we can throw
//the egg so that we can exactly telll where the threhold floor in minimum no of atttempts
//only
int Min_Egg_Dropping(int n,int e)
{
    if(n==0 or n==1) return 1;
    if(e==1) return n;
    if(e==0) return INT_MIN;
    int ans=INT_MAX;
    for(int k=1;k<=n;k++)
    {
        ans=min(ans,1+max(Min_Egg_Dropping(k-1,e-1),Min_Egg_Dropping(n-k,e)));
    }
    return ans;
}
int Min_Egg_Dropping_memorise(int n,int e)
{
    if(n==0 or n==1) return dp[n][e]=n;
    if(e==1) return dp[n][e]=n;
    if(dp[n][e]!=-1) return dp[n][e];
    int ans=INT_MAX;
    for(int k=1;k<=n;k++)
    {
        ans=min(ans,1+max(Min_Egg_Dropping_memorise(k-1,e-1),Min_Egg_Dropping_memorise(n-k,e)));
    }
    return dp[n][e]=ans;
}
int Min_Egg_Dropping_Optimised(int n,int e)
{
    if(n==0 or n==1) return dp[n][e]=1;
    if(e==1) return dp[n][e]=n;
    if(dp[n][e]!=-1) return dp[n][e];
    int ans=INT_MAX;
    for(int k=1;k<=n;k++)
    {
        int temp1,temp2;
        if(dp[k-1][e-1]!=-1) temp1=dp[k-1][e-1];else temp1=Min_Egg_Dropping_Optimised(k-1,e-1);
        if(dp[n-k][e]!=-1) temp2=dp[n-k][e];else temp2=Min_Egg_Dropping_Optimised(n-k,e);
        ans=min(ans,1+max(temp1,temp2));
    }
    return dp[n][e]=ans;
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vi v;v.pb(40);v.pb(20);v.pb(10);v.pb(30);v.pb(30);
    //cout<<Matrix_Chain_Multiplication(v,1,4);
    string s="T|T|F|T";
    //cout<<Optimised_Palind rome_Partitioning(s,0,s.size()-1);
    int cnt=0;
    //True_Boolean_Parathesisation(s,0,s.size()-1,cnt);
  //cout<<True_Boolean_Paranthesisation_Memorisation_map(s,0,s.size()-1,'T');
  //cout<<Scrambled_string("great","rtega");
  cout<<Min_Egg_Dropping_Optimised(7,2);
   //cout<<dpb[999][102][0];
    //cout<<cnt<<'\n';
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif   
    return 0;
} 