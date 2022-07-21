#include<bits/stdC++.h>
#include<cstdlib>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vb vector<bool>
#define vii vector<vector<int>>
#define vvcc vector<vector<char>>
#define vpii vector<pair<int,int>>
#define vvii vector<vector<int>>
#define vvbb vector<vector<bool>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
#define pairi pair<int,int>
#define umpcb unordered_map<char,bool>
#define umpib unordered_map<int,bool>
#define umpsb unordered_map<string,bool>
#define umpci unordered_map<char,int>
#define umpii unordered_map<int,int>
#define umpsi unordered_map<string,int>
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
bool canplace_horizontally(vvcc grid,string word,int i,int j)
{
    if(j-1>=0 and grid[i][j-1]!='+')
       return false;
       if(j+word.size()<grid[0].size() and grid[i][j+word.size()]!='+')
        return false;
    for(int jj=0;jj<word.size();jj++)
    {
        if(j+jj>=grid[0].size())
          return false;
        if(grid[i][j+jj]=='_' || grid[i][j+jj]==word[jj])
         continue;else{
             return false;
         }
    }
    return true;
}
bool canplace_vertically(vvcc grid,string word,int i,int j)
{
    if(i-1>=0 and grid[i-1][j]!='+')
      return false;
      if(i+word.size()<grid.size() and grid[i+word.size()][j]!='+')
       return false;
    for(int ii=0;ii<word.size();ii++)
    {
        if(i+ii>=grid.size()) return false;
        if(grid[i+ii][j]=='_' || grid[i+ii][j]==word[ii])
        {continue;}else{
             return false;
         }
    }
    return true;
}
vb place_horizontally(vvcc &grid,string word,int i,int j)
{
    vb weplaced(word.size(),false);
    for(int jj=0;jj<word.size();jj++)
    {
        if(grid[i][j+jj]=='_')
        {
            weplaced[jj]=true;
            grid[i][j+jj]=word[jj];
        }
    }
    return weplaced;
}
void unplace_horizonatlly(vvcc &grid,vb weplaced,int i,int j)
{
    for(int jj=0;jj<weplaced.size();jj++)
    {
        if(weplaced[jj]==true){
            grid[i][j+jj]='_';
        }

    }
}
vb place_vertically(vvcc &grid,string word,int i,int j)
{
    vb weplaced(word.size(),false);
    for(int ii=0;ii<word.size();ii++)
    {
        if(grid[i+ii][j]=='_')
        {
            weplaced[ii]=true;
            grid[i+ii][j]=word[ii];
        }
    }
    return weplaced;
}
void unplace_vertically(vvcc &grid,vb weplaced ,int i,int j)
{
    for(int ii=0;ii<weplaced.size();ii++)
    {
        if(weplaced[ii]==true)
        {
               grid[i+ii][j]='_';
        }
    }
}
void CrossWord_Puzzle(vvcc& grid,vector<string> words,int ind)
{
    if(ind==words.size())
    {
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0;j<grid[0].size();j++)
            {
                cout<<grid[i][j];
            }
            cout<<'\n';
        }
        return;
    }
    string word=words[ind];
    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid[0].size();j++)
        {
          if(grid[i][j]=='_' or grid[i][j]==word[0])
          {
            if(canplace_horizontally(grid,word,i,j))
            {
                vb weplaced=place_horizontally(grid,word,i,j);
                CrossWord_Puzzle(grid,words,ind+1);
                unplace_horizonatlly(grid,weplaced,i,j);
            }
            if(canplace_vertically(grid,word,i,j))
            {
                vb weplaced=place_vertically(grid,word,i,j);
                CrossWord_Puzzle(grid,words,ind+1);
                unplace_vertically(grid,weplaced,i,j);
            }
          }
        }
    }
}
int getnum(string s,umpci mp)
{
    int ind=0;
    int sum=0;
    while(ind!=s.size())
    {
        sum*=10;
        sum+=mp[s[ind]];
        ind++;
    }
    return sum;
}
/*In this Crypty_arthimetic_puzzle question we are given 3 strings where each s1 contains distinct
charcters but in between the strings may have dupliactes
We should give a mapping to each distinct charcter in the string such that 
the mapped values of s1 has num1 as in the same order of characters of s1,
s2 has num2 (as per the given mapping s3 has num3 
we should print all the mappings in the ascending ordeer of the charcters in which
num1+num2==num3 as per the given mapping and each charcter in our should get a disttinct integer
We cannot give mp[s]=4 and mp[d]=4;
This should not happen in our string
for example let us take 3 strings send,more,money
Let us giev a mapping or d->7 e->8 m->0 n->1 o->3 r->6 s->2 y->5
value of num1 of s1(send)=2817
value of num2 of s2(more)=0368*/
/*value of num3 of s3(money)=03185
We can see that num1+num2=num3 so we printed the map in ascending charcters of mp
Inorder to approach this problem we will maintain a unique string where it contians 
the unque character of all 3 strings and each string charcter has 10 options they make take 
any number which is not alreasdy used as map should not contain any duplicatess
wee make boolean array for and for acceesing the unique string charcters we make a countere 
for the index
So the base condition is that when the index reaches the unique string length it means
that all the characteres are mapped so now we check the conditon that whether num1+num2==num2
or not*/
void Crypty_arthimetic_puzzle(int idx,string unique,umpci mp,vb used,string s1,string s2,string s3)
{
     if(idx==unique.size())
     { 
         int num1=getnum(s1,mp);
         int num2=getnum(s2,mp);
         int num3=getnum(s3,mp);
         if(num1+num2==num3)
         {
             for(int i=0;i<26;i++)
             {
                 char ch='a'+i;
                 if(mp.find(ch)!=mp.end())
                  cout<<ch<<"->"<<mp[ch]<<' ';
             }
             cout<<'\n';
         }
         return;
     }
     char ch=unique[idx];
     for(int i=0;i<=9;i++)
     {
       if(used[i]==false)
       {
           used[i]=true;
           mp[ch]=i;
           Crypty_arthimetic_puzzle(idx+1,unique,mp,used,s1,s2,s3);
           used[i]=false;
           mp[ch]=-1;
       }
    }
}
int ans=0;
vi dx={1,-1,0,0};
vi dy={0,0,1,-1};
 vector<vector<bool>> vis(3,vector<bool>(3,false));
void goldmine(vvii grid,int row,int col)
{
    if(row<0 or row>=grid.size() or col<0 or col>=grid[0].size())
       return;
       if(vis[row][col]!=0) return ;
       if(grid[row][col]==0) return;
       vis[row][col]=true;
       ans+=grid[row][col];
       for(int i=0;i<4;i++)
       {
          goldmine(grid,row+dx[i],col+dy[i]);
       }
}
int gold_max_collection(vvii grid)
{
    int ans1=0;
    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid[0].size();j++)
        {
            if(grid[i][j]!=0 and vis[i][j]==0)
             {
                 goldmine(grid,i,j);
                 ans1=max(ans1,ans);
                 ans=0;
             }
        }
    }
    return ans1;
}
/**/
int Josephus_game(int n,int k)
{
    if(n==1) return 0;
    int rem=Josephus_game(n-1,k);
    return (rem+k)%n;
}
/*Placing n  queesn algorithm using branch and bound algorithm*/
int totalways=0;
/*In this algorithm we will approach using bramch and bound
for ex when we place a queen at the row r we will block whole colum and we will block the normal
diagnol and we will block the reverse diagnol
So before placing we we wiil check whether that block is already blocked due to previous queens
and if it is allow to place there we will mark the col as blockd and the nfiag,rdiag
as blocked and incre,ent the row+1 for next row and solve further
when we are bacltracking we will make the col and rdiag and ndiag as false
Ads we keep on solving if we reached row==grid.size() it means that we have placed
all the queens and we will incre,emt totalways+=1
for blocking the diagnol we will assign a block number at a gird[row][j]=row+j
So if we want to block the normal diagnol we aintain  aboolean array of size 2*(n-1)
and we block the number row+j in thatarraya
For revese diagnol we aassign grif[row][j]=row-j;since the valu e may become negiative
we add +(n-1) to it for reverse diagnol rdiag[row-j+n-1]=false
For example for  normal diagnol for 4*4 board the values are
0 1 2 3
1 2 3 4
2 3 4 5
3 4 5 6
we can see that row+j has same value for blocking normal diagnol
For revese diagnol after adding row-j+(n-1)
3 2 1 0
4 3 2 1
5 4 3 2
6 5 4 3
we can see that for blocking reverse diag row-j+grid.size()-1 all are same 
so before placoinh the queren we check whether that block isblocked or not by checking col 
rdiag and ndiag
If it isnt blocked place it there and solve further 
and when we are backtrcking make them false*/
void place_queens_branch_and_bound(int row,vvii grid,vb col,vb ndiag,vb rdiag)
{
    if(row==grid.size())
    {
        totalways+=1;
        return;
    }
    for(int j=0;j<col.size();j++)
      {
          if(col[j]==false and ndiag[row+j]==false and rdiag[row-j+grid[0].size()-1]==false)
          {
              col[j]=true;
              ndiag[row+j]=true;
              rdiag[row-j+grid[0].size()-1]=true;
              grid[row][j]=1;
              place_queens_branch_and_bound(row+1,grid,col,ndiag,rdiag);
              col[j]=false;
              ndiag[row+j]=false;
              rdiag[row-j+grid[0].size()-1]=false;
              grid[row][j]=0;
          }
      }
}
void dfs(int i,int n)
{
    if(i>n) return;
    cout<<i<<'\n';
    for(int j=0;j<=9;j++)
       dfs(10*i+j,n);
}
/*In this problem we are gievn an integer n we should print all the numbers from 1 to n
in lexogrpahical maanner 
for exammple if(n==19)
1 10 11 12 13 14 15 16 17 18 10 2 3 4 5 6 7 8 9
for this we will start the loop from 1 to 9 in intial state and we will do dfs to print all
the numbers we complete our 1 family and print all numbers posiible  with it and 
we then go to the 2 number family,then 3,then 4 .....so on;
Make a note that here we are printing the number in preordder that is we print prnt root first
then left and then right*/
void print_lexographically(int n)
{
    if(n==0) return;
    for(int i=1;i<=9;i++)
       dfs(i,n);
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // vvcc grid={{'+','_','+'},{'_','_','_'},{'+','_','+'}};
    // vector<string> words={"ant","and"};
    // CrossWord_Puzzle(grid,words,0);
    //  string s1,s2,s3;
    //   s1="send",s2="more",s3="money";
    //   umpci mp;
    //   string unique;
    //   for(int i=0;i<s1.size();i++)
    //   {
    //       if(!mp[s1[i]])
    //         {mp[s1[i]]=-1;unique+=s1[i];}
    //   }
    //   for(int i=0;i<s2.size();i++)
    //   {
    //       if(!mp[s2[i]])
    //       {
    //           mp[s2[i]]=-1;
    //           unique+=s2[i];
    //       }
    //   }
    //   for(int i=0;i<s3.size();i++)
    //   {
    //       if(!mp[s3[i]])
    //       {
    //           mp[s3[i]]=-1;
    //           unique+=s3[i];
    //       }
    //   }
    //   vb used(10,false);
    //  Crypty_arthimetic_puzzle(0,unique,mp,used,s1,s2,s3);
     // vvii grid={{7,0,0},{0,0,3},{1,1,1}};
    //vector<vector<bool>> vis(3,vector<bool>(3,false));
      //for(int i=0;i<3;i++) {for(int j=0;j<3;j++)  {vis[i][j]=false;}}
     //cout<<gold_max_collection(grid);
     //cout<<Josephus_game(5,3);
    //  vector<vector<int>> grid(8,vector<int>(8,0));
    //  vb col(8,false);vb ndiag(2*(8-1),false);
    //  vb rdiag(2*(8-1),false);
    //  place_queens_branch_and_bound(0,grid,col,ndiag,rdiag);
    //  cout<<totalways<<'\n';
      print_lexographically(19);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 