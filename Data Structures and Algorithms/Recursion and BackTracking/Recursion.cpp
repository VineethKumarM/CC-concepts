#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
//Caluclating nth fibonocci Number
int Fibn(int n)
{
    if(n==0 or n==1) return n;
    int subprob1=Fibn(n-1);
    int subprob2=Fibn(n-2);
    return subprob1+subprob2;
}
//Printing n natural numbers in inc order
int print(int n)
{
    if(n==1) { cout<<1<<" "; return 1;}
    print(n-1);
    cout<<n<<" ";
    return 0;
}
//Function for caluclating no ways n person can go in a party 
//in either pair or single
int Countways(int n)
{
    if(n==1 || n==0) return 1;//since even and odd integrs may come we have to return 1                      
                              //at the end of prob
     int sub1=Countways(n-1);
      int sub2=Countways(n-2);
    return sub1+(n-1)*sub2;
}
//Recurisve Power in O(logn) 
int Recpow(int a,int n)
{
    if(n==0) return 1;
    if(n==1) return a;
    int temp=Recpow(a,n/2);
    if(n%2)
     return a*temp*temp;
     else
     return temp*temp;
     //return Recpow(a,n/2)*Recpow(a,n/2)
     //This will calucalte same number twicely and complexity is O(b);
     //Thats why we are storing temp value
}
//Pattern printing using recursive call
void printpattern(int n,int i)
{
    //if(n==1) {cout<<"*"<<endl;return;}
    //for(int i=0;i<n;i++) cout<<"*"<<' ';
    //cout<<endl;
   // cout<<*<' ';
    
    //cout<<"*"<<' ';
    if(n==0) return;
    if(n-i-1<n)
    {
        cout<<"* ";
        //cout<<endl;
        printpattern(n,i+1);
    }
    else
    {
        cout<<endl;
        printpattern(n-1,0);
    }
  
}
void printpattern1(int n,int i)
{
    if(n==0) return;
    if(i>0)
    {
        cout<<"* ";
        printpattern1(n,i-1);
    }
    else
    {

    }
}
//Printing all subsets using recursion
void PrintSubsets(int* arr,int i,int n,string osf)
{
    if(i==n)
    {
        cout<<osf<<endl;
        return ;
    }
    PrintSubsets(arr,i+1,n,osf+ to_string(arr[i])+" ");
    PrintSubsets(arr,i+1,n,osf);
}
//Printing binary Strings
void BinaryStrings(int n,int i,int p,string osf)
{
    if(i==n)
    {
       cout<<osf<<endl;
       return;
    }
    //cout<<osf[0]<<endl;;
   // int x=osf.size();
    if(osf[p]=='1')
    {
        BinaryStrings(n,i+1,i,osf+'0');
        //BinaryStrings(n,i+1,i,osf+'1');
    }
    else
    {
        BinaryStrings(n,i+1,i,osf+'0');
        BinaryStrings(n,i+1,i,osf+'1');
        
    }


}
//Identification whether array is sorted or not
bool issort(int *arr,int size)
{
    if(size==0){ return true;}
    if(issort(arr,size-1))
    {
        if(arr[size]>arr[size-1])
         return true;
         else
         return false;
    }
    else
    return false;
}
//No.of ways of reaching from first cell to last cell of a grid
int totalpaths=0;
void mazepaths(int i,int j,int n,int m,string osf)
{
    if(i==n-1 && j==m-1)
    {cout<<osf<<endl;totalpaths+=1;return;}
    if(i>n-1 || j>m-1) return;
    if(i<0 || j<0) return;//base case if they go out of grid
    mazepaths(i+1,j,n,m,osf+"R");
    mazepaths(i,j+1,n,m,osf+"D");
    //mazepaths(i+1,j+1,n,m,targ1,targ2,osf+"->");if the diagnol move
                                                // also allowed
}
int countjumps=0;
//osf=output_so_far
//ssf=sum_so_far
void totaljumps(int n,int ssf,string osf)
{
    if(ssf==n-1){countjumps+=1; cout<<osf<<endl;return;}
    if(ssf>n-1) return;
    for(int i=1;i<=6;i++)
    totaljumps(n,ssf+i,osf+to_string(i)+" ");
}
//Printing n values in lexographical order
string s="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void lexograph(int n,int i)
{
    if(n<i) return;
    cout<<i<<endl;
    for(int j=(i==0?1:0);j<=9;j++)
    {
        lexograph(n,10*i+j);
    }
}
//Pemuation of unique string
//If we want to permute a string in which the char may come more than once
//thrn store them into a set
//If the char is not in the set thrn iterate recurisve call
//otherwise leave it because for that char already recursive call has taken
void permutation(string inp,string perm)
{
    if(inp.size()==0) {cout<<perm<<endl;return;}
    unordered_set<char> s;/*Here we are defining in recursive call only 
                             because at each level the rest of the string 
                             may contain in double characters*/
    for(int i=0;i<inp.size();i++)
    {
       char ch=inp[i];
       if(s.count(ch)==0)
       {
        string ros=inp.substr(0,i)+inp.substr(i+1);/*Here complexity of this
        inbuilt function is O(n)Total complexity then becoming O(n^2)
         We can optimise this through backtracking */
       permutation(ros,perm+ch);
        s.insert(ch);
       }
    }
    
}
//Concept of Tail Recursion
/*
The idea used by compilers to optimize tail-recursive functions is simple,
 since the recursive call is the last statement, there is nothing left to
  do in the current function, so saving the current function’s stack frame is of no use
*/
//Example of tail Recursion
void printn(int n)
{
    if(n==0) cout<<0<<' ';
    print(n-1);
}
//Tail Call Elimination
//A tail-recursive is better than a non-tail recursive 
//as tail-recursion can be optimized by modern compilers. Modern compiler basically 
//does tail call elimination to optimize the tail-recursive code. 
//Example of Tail call Elimination
//It optimises the call by using recursive function since no stacks are formed 
//and less space
//Normal Recursive call uses O(n) space and for each recursive call O(1) space
//But Tail call elimination reduces O(1) space
void TailPrint(int n)
{
    start:
    if(n<0) return;
    cout<<" "<<n;
    n-=1;
    goto start;
}
//Tail Recursive call to caluclate factorial
ll Tailfact(ll n,ll a)
{
    start:
      if(n==1) return a;
      a*=n;
      n-=1;
      goto start;
}
ll TailArrSum(vi vec,int ind,ll sum)
{
    start:
    if(ind==vec.size()-1) return sum+vec[ind];
    sum+=vec[ind];
    ind+=1;
    goto start;

}
//Tail Elimination recursove call to find fibonacii Number
ll TailFib(ll n,ll ind,ll a,ll b,ll c)
{
    start:
    if(ind==n) return c;
     a=b;
     b=c;
     c=a+b;
     ind+=1;
     goto start;
     
}
void winner(vector<int>& nums,int &p1,int &p2,int cur_p)
    {
        if(nums.size()==0) return;
        int a=nums[0],b=nums[nums.size()-1];
        if(a>b)
        {
             auto it=nums.begin();
            if(cur_p==1)
            {
               
                nums.erase(it);
                p1+=a;
                winner(nums,p1,p2,!(cur_p));
            }
            else
            {
                 nums.erase(it);
                 p2+=a;
                winner(nums,p1,p2,!(cur_p));
            }
        }
        else{
            auto it=nums.end();
             if(cur_p==1)
            {
                nums.erase(it);
                 p1+=b;
                winner(nums,p1,p2,!(cur_p));
            }
            else
            {
                 nums.erase(it);
                 p2+=b;
                winner(nums,p1,p2,!(cur_p));
            }
        }
    }
    bool PredictTheWinner(vector<int>& nums) {
        int p1=0,p2=0;
        winner(nums,p1,p2,1);
            if(p1>=p2) return true;
        else return false;
    
    }
int main()
{   
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cout<<Fibn(10);
    //print(10);
   // cout<<Recpow(2,16);
   //cout<<Countways(10);
  // printpattern(5,0);
  //int arr[10]={1,2,3,4,5,6,7,8,9,10};
   //cout<<issort(arr,9);
   //int p=__builtin_popcount(113);
    //BinaryStrings(10,0,0,"");
    //mazepaths(0,0,4,4,"");
   // cout<<totalpaths;
    //totaljumps(6,0,"");
    //cout<<countjumps;
    //lexograph(1268,0);
   // string s="aac";
    //permutation("acwca","");
    //TailPrint(10);
    //cout<<Tailfact(7,1);
    // vi v(10);
    // for(int i=0;i<10;i++)
    //  v[i]=i+1;
    //  cout<<TailArrSum(v,0,0);
     cout<<TailFib(4,0,0,1,1);
    return 0;
}  