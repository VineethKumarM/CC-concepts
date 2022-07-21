#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++);  
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
//Permutation of a string using recursive function
//This function creates a lot of copies of original strings in sublevels
//use of Substr function is of O(n) complexity So total complexity will
//become O(n^2)
void PermutationsR(string inp,string osf)
{
    if(inp.size()==0) {cout<<osf<<endl;return;}
    for(int i=0;i<inp.size();i++)
    {
        char ch=inp[i];
        string rs=inp.substr(0,i)+inp.substr(i+1);
        PermutationsR(rs,osf+ch);
    }
}
//Inorder to optimise we will use backtracking
//This code will just swap the original string and aafter permutation 
//it will undo swapping
//Here we are iterating from i=j we already fixed the string upto j-1;
void PermutationsB(string inp,int j)
{
    if(inp.size()-1==j) {cout<<inp<<endl;return;}
    for(int i=j;i<inp.size();i++)
    {
        swap(inp[i],inp[j]);
        PermutationsB(inp,j+1);
        swap(inp[i],inp[j]);

    }
} 
int totalpaths=0;
//return true if the position if currebt cell is in safe position or not
bool Isitsafe(int i,int j,int n,vector<vector<bool>>& visited)
{
     return (i>=0 and j>=0 and i<n and j<n and visited[i][j]==false);
    
}  
//upadtes in 4 possible paths and finds whether a valid path exist or not  
void helper(int i,int j,int n,vector<vector<int>> &grid,vector<vector<bool>>& visited)
{
    if(i==n-1 and j==n-1) {totalpaths+=1;return;}
    if(!Isitsafe(i,j,n,visited)) return;
    visited[i][j]=true;
    if(i+1<n and grid[i+1][j]==0) {helper(i+1,j,n,grid,visited);}
    if(i-1>=0 and grid[i-1][j]==0) {helper(i-1,j,n,grid,visited);}
    if(j+1<n and grid[i][j+1]==0) {helper(i,j+1,n,grid,visited);}
    if(j-1>=0 and grid[i][j-1]==0) {helper(i,j-1,n,grid,visited);} 
    visited[i][j]=false;
}  
//Return total paths  
int RatMazePaths(vector<vector<int>> &grid)
{
    int n=grid.size();
    vector<vector<bool>> visited(n,vector<bool>(n,false));
    helper(0,0,n,grid,visited);
    return totalpaths;
}
void SubsetBackTrack(int *arr,int i,int n,vector<int> &osf)
{
    if(i==n)
    {
        if(osf.size()>0)
         for(int i=0;i<osf.size();i++) cout<<osf[i]<<' ';cout<<endl;
         return;
    }
    osf.pb(arr[i]);
    SubsetBackTrack(arr,i+1,n,osf);
    osf.pop_back();
    SubsetBackTrack(arr,i+1,n,osf);
    return;
}
/*Concept of Pruning:It is in the context with abandoning thosw subproblems which
will lead to a succesful answer*/
int Countways=0;
/*Here this function will returns a boolean value whether it is safe to put q
on particular block */
bool Isitsafe(vector<vector<bool>> &grid,int row,int col,int n)
{
    for(int i=row-1;i>=0;i--) {if(grid[i][col]) return false;}
    for(int i=row-1,j=col-1;i>=0 and j>=0;i-- and j--)
    {
        if(grid[i][j]) return false;
    }
    for(int i=row-1,j=col+1;i>=0 and j<n;i-- and j++)
    {
        if(grid[i][j]) return false;
    }
    return true;
}
//Queen problem
/*Most important observation safe placing queen problem is that each row should 
contain a queen otherwise atleat one row contains 2 queens in same row whch may
counter each other
From this observation row wise rather than [row+1][col+1] wise which is the 
optimised solution*/
void Pruning(vector<vector<bool>> &grid,int curr_row,int n)
{
    if(curr_row==n){Countways+=1;return;}
    for(int i=0;i<n;i++)
    {
        if(Isitsafe(grid,curr_row,i,n))/*checking if safe place q in that cell 
        and iterting over n rows and updating current row+1 so that after reaching
        n rows we found a valid solution*/
        {
            grid[curr_row][i]=true;/*Since it is valid cell keeping the queen 
            at this place caluclating remaining all posiibilities through
            recurive call*/
            Pruning(grid,curr_row+1,n);//recursive call
            grid[curr_row][i]=false;//backtracking
        }
    }
} 
//Finding existence of knightour path in a n*n board
int totalTours=0;
//For display of knight paths
void Display(vector<vector<int>> &grid,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
         cout<<grid[i][j]<<' ';
         cout<<endl;
    }
}
//t=return true if it is safe to go because it can't travel a cell twicely or get
//out of grid
bool isitsafe(vector<vector<int>> &grid,int n,int row,int col,vector<vector<bool>> visited)
{
    return row>=0 and col>=0 and row<n and col<n and visited[row][col]==false;
}
//Forcaluclating total no of differnt tours
void KnightTour(vector<vector<int>> &grid,int n,int row,int col,int count,vector<vector<bool>> visited)
{
    if(count==n*n-1)/*Here we are maintaing count integer along with funcion
    inoreder to know whwere to stop recursion If we reachhed all cell then count
    will be n*n-1;*/
    {
        grid[row][col]=count;
        Display(grid,n);
        cout<<endl;
        totalTours+=1;
        return; 
    }
    int movex[8]={-2,-2,-1,-1,2,2,1,1};
    int movey[8]={1,-1,2,-2,1,-1,2,-2};
    visited[row][col]=true;//marking it to be visited and checking 
     grid[row][col]=count;//for grid dipaly purpose
    for(int i=0;i<8;i++)
    {
        if(isitsafe(grid,n,row+movex[i],col+movey[i],visited))/*checking all the 8 
        possibilities if it is safe to place here such that the cell is 
        not repeating*/
        {
            KnightTour(grid,n,row+movex[i],col+movey[i],count+1,visited);
            //recursive call once we found right cell
        }
    }
    grid[row][col]=-1;//agin we are backtracking to -1
    visited[row][col]=false;//backtrack
}
/*No.of ways placing knights in a n*n board such that they can:t attack themselves*/
//isitsafepalace to place here as same as of case of queens
void displayp(vector<vector<bool>> &grid,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(grid[i][j]) cout<<"k ";
            else cout<<". ";
        }
        cout<<endl;
    }
    cout<<endl;
}
bool IsItsafe(vector<vector<bool>>&grid,int n,int cur_row,int cur_col)
{
    if(cur_row-2>=0 and cur_col-1>=0 and grid[cur_row-2][cur_col-1]) return false;
    if(cur_row-2>=0 and cur_col+1<n and grid[cur_row-2][cur_col+1]) return false;
    if(cur_row-1>=0 and cur_col-2>=0 and grid[cur_row-1][cur_col-2]) return false;
    if(cur_row-1>=0 and cur_col+2<n and grid[cur_row-1][cur_col+2]) return false;
    return true;
}
int Knightways=0;
//Since there is no optimistation posiible we should travel to each cell
//so once we are updating col wise keepinhg row const
//once we are updating row wise and keeping col const
//here we are making a count value also inorder to ensure that if n knights are 
//placed then return and we found a valid placing
void Knightplaces(vector<vector<bool>>& grid,int n,int cur_row,int cur_col,int count)
{
    if(count==n) {Knightways+=1;/*displayp(grid,n)*/;return;}
    for(int i=cur_row;i<n;i++)//i started from curr_row because already we kept r
    //ks
    {
            for(int j=(i==cur_row)?cur_col:0;j<n;j++)/*Here we are puttimng condition
            on column whether it is running for currentrow or another row because
            if it is in the curr row we willstar from that colum only otherwise
            we will start from column from 0 in next row */ 
            {
                if(IsItsafe(grid,n,i,j))
                {
                     grid[i][j]=true;
                     Knightplaces(grid,n,i,j+1,count+1);
                     grid[i][j]=false;
                }
            }
    }
   
    
    //return;
}
//Concept of bitmasking inorder to optimise the n queens problem
int queenplaces=0;
/*Although isitsafe checking and recursion needs to be done but we can optimise 
isitsafe function by making a boolean array 
We will book all the leftdiagnols(ld) and rightdiagnols(rd) and col and if we 
encounter a queen place in that we simmply return
Although bool is of 1 bytes we can reduce the size by taking bitset which produce
required size of bits we can access them using simple array
Inorder to pair all left indices and right indices and col we can build a relation
in between those indices
jere we are not at all taking the grid into consideration because we woant only 
no ways which reduces time complexity O(n^2)*/
bitset<100> col,ld,rd;
void nqueens(int n,int cur_row)
{
    if(cur_row==n-1){queenplaces+=1;return;}
    for(int c=0;c<n;c++)
    {
        if(!col[c] and !ld[cur_row-c+n-1] and !rd[cur_row+c])
        {
            col[c]=ld[cur_row-c+n-1]=rd[cur_row+c]=1;/*Before recursion we will 
            book that whole indexes and caluclates all possibilities and we
            will unbook the col,ld and rd*/
            nqueens(n,cur_row+1);
            col[c]=ld[cur_row-c+n-1]=rd[cur_row+c]=0;
        }
    }
}
//Incase if we have to print the grid we have to pass the grid by refernce
void displayg(vector<vector<bool>> &grid,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(grid[i][j]) cout<<"k ";
            else cout<<". ";
        }
        cout<<endl;
    }
    cout<<endl;
}
//Function to display the grid  also
void nqueensg(vector<vector<bool>> &grid,int n,int cur_row)
{
    if(cur_row==n){queenplaces+=1;displayg(grid,n);return;}
    for(int c=0;c<n;c++)
    {
        if(!col[c] and !ld[cur_row-c+n-1] and !rd[cur_row+c])
        {
            col[c]=ld[cur_row-c+n-1]=rd[cur_row+c]=grid[cur_row][c]=1;/*Before recursion we will 
            book that whole indexes and caluclates all possibilities and we
            will unbook the col,ld and rd*/
            nqueensg(grid,n,cur_row+1);
            col[c]=ld[cur_row-c+n-1]=rd[cur_row+c]=grid[cur_row][c]=0;
        }
    }
}
//Placing of n kings of n*n board
//Same case as of knights except the is itsafe condition 
bool IsItsafeKing(vector<vector<bool>>&grid,int n,int cur_row,int cur_col)
{
    if(cur_row-1>=0 and cur_col>=0 and grid[cur_row-1][cur_col]) return false;
    if(cur_row+1<n and cur_col>=0 and grid[cur_row+1][cur_col]) return false;
    if(cur_row>=0 and cur_col-1>=0 and grid[cur_row][cur_col-1]) return false;
    if(cur_row>=0 and cur_col+1<n and grid[cur_row][cur_col+1]) return false;
    if(cur_row-1>=0 and cur_col-1>=0 and grid[cur_row-1][cur_col-1]) return false;
    if(cur_row-1>=0 and cur_col+1<n and grid[cur_row-1][cur_col+1]) return false;
    
    return true;
}
int Kingways=0;
void Kingplaces(vector<vector<bool>>& grid,int n,int cur_row,int cur_col,int count)
{
    if(count==n) {Kingways+=1;displayp(grid,n);return;}
    for(int i=cur_row;i<n;i++)//i started from curr_row because already we kept r
    //as constant and keep checking further columns
    {
            for(int j=(i==cur_row)?cur_col:0;j<n;j++)
            {
                if(IsItsafeKing(grid,n,i,j))
                {
                     grid[i][j]=true;
                     Kingplaces(grid,n,i,j+2,count+1);//Here we are incrementing +2
                     //because we know that j+1 wont be a solution
                     grid[i][j]=false;
                }
            }
    }
}
//Algorithm fir finding words in a grid of characters
int totalwords=0;
/*Here we are using pruning techinque that we can find any word which may tell
whether we can fiund answer or not and we are ciunting paths in this function only
inorder to less the parameters and if we use in the recusive call we should mainatian\
a counter pointer whuch is not fruitful and nit sure that it will give correct
ans*/
int Wordpos(string s1,string s2,string s3,int n,string osf)
{
    
    if(n>0 and osf.size()<=s1.size() and osf==s1.substr(0,n)){if(n==s1.size())totalwords+=1;return true;}
    if(n>0 and osf.size()<=s2.size() and osf==s2.substr(0,n)){if(n==s2.size())totalwords+=1;return true;}
    if(n>0 and osf.size()<=s3.size() and osf==s3.substr(0,n)){if(n==s3.size())totalwords+=1;return true;}
    return false;
}
/*Here we are find for each grid of thr cell by checking upward ,downward,left ward
and right ward it will complement if it has found word usinnthe word pos function*/
void findwords(vector<vector<char>>& grid,string s1,string s2,string s3,int cur_row,int cur_col,int maxpos,int count,string& osf)
{
    if(count>maxpos) {return;}
    if(cur_row<0 or cur_col<0 or cur_row>grid.size()-1 or cur_col>grid.size()-1){return;}
    char ch=grid[cur_row][cur_col];
    osf.pb(ch);
     if(Wordpos(s1,s2,s3,count+1,osf))
     {
         findwords(grid,s1,s2,s3,cur_row,cur_col+1,maxpos,count+1,osf);
         findwords(grid,s1,s2,s3,cur_row-1,cur_col,maxpos,count+1,osf);
         findwords(grid,s1,s2,s3,cur_row+1,cur_col,maxpos,count+1,osf);
         findwords(grid,s1,s2,s3,cur_row,cur_col-1,maxpos,count+1,osf);
     }
     osf.pop_back(); 
}
/*Since fidpos will find the ans for each cell of the grid we should check for
each cell of the loop so w e are using a nested loop */
void helperg(vector<vector<char>>& grid,string s1,string s2,string s3)
{
    string h="";
    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid.size();j++)
         findwords(grid,s1,s2,s3,i,j,4,0,h);
    }
}


int main()
{ 
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   // PermutationsB("ABCDEFG",0);
   //int k;cin>>k;
   //vector<vector<int>> grid(k,vector<int>(k,0));
//    for(int i=0;i<k;i++)
//        for(int j=0;j<k;j++) cin>>grid[i][j];
//         cout<<RatMazePaths(grid);
//   int arr[8]={1,2,3,4,5,6,7,8};
//   vector<int> osf;
//   SubsetBackTrack(arr,0,8,osf);
//     int k;cin>>k;
//     vector<vector<char>> grid(k,vector<char>(k,0));   
//     // Pruning(grid,0,k);
//      //cout<<Countways<<endl;
//      //vector<vector<int>> grid(k,vector<int>(k,-1));
//      //vector<vector<bool>> visited(k,vector<bool>(k,false));
//     // KnightTour(grid,k,0,0,0,visited);
//     //Kingplaces(grid,k,0,0,0);
//      //cout<<Kingways;
//     for(int i=0;i<k;i++)
//     {
//         for(int j=0;j<k;j++)
//          cin>>grid[i][j];
//     }
//   //string p="";
//   //findwords(grid,"ban","can","and",0,0,3,0,p);
//   helperg(grid,"sadr","sund","modd");
//   cout<<totalwords<<endl;
          PermutationsB("ABSGHK",0);
   #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
  //string s="queen";1
   //findwords(grid,s1,s2,s3,0,2,3,0,"");
  //cout<<s.substr(0,0);
//cout<<grid[0][1];
     //nqueensg(grid,k,0);
     //cout<<queenplaces<<endl;
    return 0;
} 