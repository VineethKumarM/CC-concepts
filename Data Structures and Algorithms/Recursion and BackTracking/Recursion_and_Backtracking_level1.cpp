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
#define vvii vector<vector<int>>
#define vvbb vector<vector<bool>>
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
void PrintDecInc(int n)
{
    if(n==1) {cout<<n<<'\n';return;}
    cout<<n<<'\n';
    PrintDecInc(n-1);
    cout<<n<<'\n';
}
int Powlog(int a,int n)
{
    if(n==0) return 1;
    int k=Powlog(a,n/2);
    if(n%2)  return a*k*k;
    else return k*k;
}
char findKthBit(int n,int k)
{
    int max=(1<<n)-1;
    if(n==1) return '0';
    if(k==((max+1)/2)) return '1';
    else if(k<=(max/2)) return findKthBit(n-1,k);
    else
    {
        char ch=findKthBit(n-1,max+1-k);
        if(ch=='0') return '1';
        else return '0';
    }
}
int maxofarray(int arr[],int idx)
{
    if(idx<0) return INT_MIN;
    if(arr[idx]>maxofarray(arr,idx-1)) return arr[idx];
    else return maxofarray(arr,idx-1);
}
int firstoccurence(vi arr,int idx,int val)
{
    if(idx==arr.size()) return -1;
    if(arr[idx]==val) return idx;
    else return firstoccurence(arr,idx+1,val);
}
void printpermutations(string s,int ind,int n,string osf)
{
    if(ind==n) {cout<<osf<<'\n';return;}
    printpermutations(s,ind+1,n,osf+s[ind]);
    //If we want to print the dashes also then add osf+"-" in the recursive call
    printpermutations(s,ind+1,n,osf);
}
vector<string> keypad={"?!","abc","def","ghi","jkl","mnop","qrst","uv","wxyz",".,;"};
void keypadpermutations(vi v,int ind,string osf){
    if(ind==v.size()) {cout<<osf<<'\n';return;}
    int n=v[ind];
    for(int i=0;i<keypad[n].size();i++)
     keypadpermutations(v,ind+1,osf+keypad[n][i]);
}
//A person is at floor n he wants to get down the problem with the condition he can only take
//some specified steps only
//This functiikn returns all the possible ways of reaching the ground floor
//All the possible steps are in the vector steps
int countstairpaths(int n,vi steps)
{
    if(n==0) return 1;
    if(n<0) return 0;
    int sum=0;
    for(int i=0;i<steps.size();i++) sum=sum+countstairpaths(n-steps[i],steps);
    return sum;
}
//No.of ways of reaching from 0,0 to n-1,m-1 position(0 based indexing) 
int getmazepaths(int i,int j,int n,int m)
{
    if(i<0 or j<0) return 0;
    if(i>=n or j>=m) return 0;
    if(i==n-1 and j==m-1) return 1;
    return getmazepaths(i+1,j,n,m)+getmazepaths(i,j+1,n,m);
}
void permutations(string str,string osf)
{
    if(str.size()==0) {cout<<osf<<'\n';return;}
    for(int i=0;i<str.size();i++)
    {
       string s=str.substr(0,i)+str.substr(i+1);
       permutations(s,osf+str[i]);
    }

}
vector<char> alph={'0','a','b','c','d','e','f','g','h','i','k','l','m','n','o','p','q','r','s','t','u',
'v','w','x','y','z'};
void printencodings(string s,string osf)
{
    if(s.size()==0) {cout<<osf<<'\n';return;}
    else if(s.size()==1)
    {
        char ch=s[0];
        if(ch=='0') return;
        else
        {
          int x=s[0]-'0';
          osf+=alph[x];
          cout<<osf<<'\n';return;
        }
    }
    else
    {
        
          char ch=s[0];
          string rsq=s.substr(1);
        if(ch=='0') return;
        else
        {
          int x=s[0]-'0';
          osf+=alph[x];
          printencodings(rsq,osf);
        }
        string ch12=s.substr(0,2);
        string roq=s.substr(2);
        int ch12v=stoi(ch12);
        if(ch12v<=26)
        {
            osf+=alph[ch12v];
            printencodings(roq,osf);
        }
    }
}
int grid[5][5];
bool vis[5][5];
vector<int> dx={-1,0,0,1};
vector<int> dy={0,-1,1,0};
bool isvalid(int x,int y,int m,int n)
{
    if(x<0 or y<0) return false;
    else if(x>m or y>n) return false;
    else if(vis[x][y] or grid[x][y]==1) return false;
    return true;
}
int getPaths(int x,int y,int m,int n)
{
    if(x==m and y==n) return 1;
    int paths=0;
    vis[x][y]=true;
    for(int i=0;i<4;i++)
    {
        if(isvalid(x+dx[i],y+dy[i],m,n))
        {
            
           paths+=getPaths(x+dx[i],y+dy[i],m,n);
         
        }
    }
      vis[x][y]=false;
    return paths;
}
void printpaths(int x,int y,int n,int m,string osf)
{
   if(x<0 or y<0 or x>=n or y>=m or (grid[x][y]==1) or (vis[x][y]==true)) return;
   if(x==n-1 and y==m-1) {cout<<osf<<'\n';return;}
   vis[x][y]=true;
   printpaths(x+1,y,n,m,osf+="r");
   printpaths(x,y+1,n,m,osf+="d");
   printpaths(x-1,y,n,m,osf+="t");
   printpaths(x,y-1,n,m,osf+="l");
   vis[x][y]=false;
}
/*There are two options that we can include or not\
so for once we add the element in osf and pop_back() and the current element
as there are two options for each element 
Here note that as soon as we get the targetsum==cur_sum we arebnot printing the osf vector 
elements
We are keeping an extra conditions the current index must reach the v.size() so that we are
confirmed that we have traversed the whole vector
This needs to be taken care as of although after reaching the targetsum there may  be negative
elements in the vector which upon adding nullify each other keeping the targetsum as unchanged*/
void targetsubset_sum(vector<int> v,int i,int n,int cur_sum,int targetsum,vector<int> osf)
{
    if(i>n) return;
    if(i==n and (targetsum==cur_sum)) {for(int i=0;i<osf.size();i++) cout<<osf[i]<<" ";cout<<'\n';return;}
    osf.pb(v[i]);
    targetsubset_sum(v,i+1,n,cur_sum+v[i],targetsum,osf);
    osf.pop_back();
    targetsubset_sum(v,i+1,n,cur_sum,targetsum,osf);
}
int totalpaths=0;
bool isitsafe(vvbb &grid,int row,int col,int n)
{
    for(int i=row-1,j=col;i>=0;i--)
    {
        if(grid[i][j]==true) return false;
    }
    for(int i=row-1,j=col-1;i>=0 and j>=0;j-- and i--)
    {
        if(grid[i][j]==true) return false;
    }
    for(int i=row-1,j=col+1;i>=0 and j<n;i-- and j++)
    {
        if(grid[i][j]==true) return false;
    }
    return true;
}
void queens_permutations(int row,int n,vvbb &grid)
{
    if(row==n){totalpaths+=1;return;}
    for(int i=0;i<n;i++)
    {
        if(isitsafe(grid,row,i,n))
        {
            grid[row][i]=true;
            queens_permutations(row+1,n,grid);
            grid[row][i]=false;
        }
    }
}
int main()
{
     freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // PrintDecInc(5);
    // cout<<Powlog(3,4);
    //cout<<findKthBit(3,6);
    //int arr[4]={1,2,3,4};
    //cout<<(1<<3);
   // cout<<maxofarray(arr,3);
   //cout<<firstoccurence(arr,0,3);
    //  string s="abcdef";
    //  vi v={1,2,3};
     //printpermutations(s,0,s.size(),"");
     //keypadpermutations(v,0,"");
     //cout<<countstairpaths(4,v);
    // cout<<getmazepaths(0,0,3,3);
    //permutations("abcd","");
   // printencodings("123","");
//    int n,m;cin>>n>>m;
// //    grid.resize(n+1);
// //    vis.resize(n+1);
//    for(int i=0;i<n;i++)
//    {
//        for(int j=0;j<m;j++)
//          {
//              cin>>grid[i][j];
//              vis[i][j]=false;
//          }
//    }
//     printpaths(0,0,n,m,"");
// vector<int> v={10,20,-30,40,50,80};
// vector<int> osf;
// targetsubset_sum(v,0,v.size(),0,60,osf)
 vector<vector<bool>> chess(3,vector<bool>(3,false));
 // print_queensplacing(chess,0,chess.size());
 // cout<<totalways;
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}