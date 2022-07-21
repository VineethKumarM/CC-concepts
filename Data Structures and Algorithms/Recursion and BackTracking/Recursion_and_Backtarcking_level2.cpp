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
void combinations(int n,int tb,int cur,string osf)
{
    //once it reached n it means it has tried all possible ways we will print only those which 
    //we have used only i elements
    if(cur>=n) {if(tb==0)cout<<osf<<'\n';return;}
    osf+='1';
    combinations(n,tb-1,cur+1,osf);
    osf.pop_back();
    osf+='0';
    combinations(n,tb,cur+1,osf);
}
/*Here is the permutations where the order matters 
We can solve the problem by making the recursive tree and backtracking
Supoose the boxes are filled with 0 indicating that here no item was filled yet
So we can put the cureent processing numbeer in any of those place so that w get all the
permutations
Whwn we are backtracking after solving the subproblem we have to make it empty as this box can be use
for remaining elements
If we have n places un the box we can place them in nPr permutations(where order of placing the
elements matters
nPr=n!/(n-r)!*/
void permutations(vi boxes,int tb,int num)
{
    if(tb<0) return;
    if(tb==0)
    {
        for(int i=0;i<boxes.size();i++)
        {
            if(boxes[i]!=0)
             cout<<boxes[i];
             else cout<<"_";
        }
        cout<<'\n';
        return;
    }
    for(int i=0;i<boxes.size();i++)
    {
        if(boxes[i]==0)
        {
            boxes[i]=num;
            permutations(boxes,tb-1,num+1);
            boxes[i]=0;
        }
    }
}
/*Another approach for permuting the thigs as we have target numbers to choose
We will use the same concept as of combinations as at each level we have two options that we can
include or not
In normal combinations probelem we will add _ or '0' to indicate that we are bot choosing the 
currennt item or else we will add that number at the end of the string we will push_back
the current element at the end of the string
In the permutations since the order matter we keep items array to keep track whether that indexed item is 
used or not
First option is to place an item in that box we have target number of numbers which are unused
so before placing the number we will check whether that number is already used or not using the
item array or not
After iteration of the for loop we move to the alternate option where we wont place any element
in that box
at last after iterating over all boxes we will print only those which have used exactly target 
number of numbers*/
void permuations2(int cb,int tb,vi items,string osf,int ssf,int target)
{
    if(cb>tb)
    {
        if(ssf==target)
         cout<<osf<<'\n';
         return;
    }
    /*Case1 where we place some number in that place*/
    /*Here we are iterating over the target number of numbers and we can place any one of the
    number in the range 0 to targte*/
    for(int i=0;i<target;i++)
    {
        if(items[i]==0)
        {
            items[i]=1;
            permuations2(cb+1,tb,items,osf+to_string(i+1),ssf+1,target);
            items[i]=0;
        }
    }
    /*Case2 where we place  wont fill any  number in that place*/
    permuations2(cb+1,tb,items,osf+'_',ssf,target);
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
void queens_permutations(int row,int n,vvbb &grid, vb items)
{
    if(row==n){totalpaths+=1;return;}
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
        if(isitsafe(grid,row,i,n) and items[j]==false)
        {
            grid[row][i]=true;
            items[j]=true;
            queens_permutations(row+1,n,grid,items);
            grid[row][i]=false;
            items[j]=false;
        }
        }
    }
}
//Ways of placing the queen
//Given a grid with n rows and n cols we should place q combinations
//This question is same as placing Q queens in n places
//Since it is a grid now the total places are n*n instead of n
//So only thing we have to take care od printing the grid
void placing_queen(int qsf,int row,int col,int tq,string osf)
{
    if(row==tq)
    {
        if(qsf==tq) cout<<osf;
        return;
    }
    //int nr and nc are newrow and newcol 
    int nr,nc;
    string ysf,nsf;
    if(col==tq-1)
    {
       nr=row+1;
       nc=0;
       ysf=osf+'q'+'\n';
       nsf=osf+'_'+'\n';
    }
    else
    {
            nr=row;
            nc=col+1;
            ysf=osf+'q';
            nsf=osf+'_';
    }
    placing_queen(qsf+1,nr,nc,tq,ysf);
    placing_queen(qsf,nr,nc,tq,nsf);
}
/*Placing the permute queens 
since we can  place  any where in the box whichis not filled    
so we will select those cases where the box is filled and when we are backtaracking we will remove
the element in that box*/
void placing_permutequeens(int qsf,int tq,vvii chess)
{
    if(qsf==tq)
    {
        for(int i=0;i<chess.size();i++)
        {
            for(int j=0;j<chess[0].size();j++)
            {
                if(chess[i][j]==0) cout<<'_';
                else cout<<chess[i][j];
            }
            cout<<'\n';
        }
    }
    for(int i=0;i<chess.size();i++)
    {
        for(int j=0;j<chess[0].size();j++)
        {
            if(chess[i][j]==0)
            {
                chess[i][j]=qsf+1;
                placing_permutequeens(qsf+1,tq,chess);
                chess[i][j]=0;
            }
        }
    }
}
void placing_permutequeens2(int qsf,int tq,vvii chess,vb items)
{
    if(tq==qsf)
    {
        for(int i=0;i<chess.size();i++) 
        {
            for(int j=0;j<chess[0].size();j++)
            {
                if(chess[i][j]==0)
                  cout<<'_';
                  else
                  cout<<chess[i][j];
            }
            cout<<'\n';
        }
    }
    for(int k=1;k<items.size();k++)
    {
        for(int i=0;i<chess.size();i++)
        {
            for(int j=0;j<chess[0].size();j++)
            {
                if(chess[i][j]==0 and items[k]==0)
                {chess[i][j]=1;items[k]=0;placing_permutequeens2(qsf+1,tq,chess,items);}
            }
        }
    }
}
void queenscombinations(int qsf,int tq,int cur_row,int cur_col,vvbb chess)
{
   
        if(qsf==tq)
        {
            for(int i=0;i<chess.size();i++)
             {
                 for(int j=0;j<chess[0].size();j++)
                 {
                     if(chess[i][j]==1) cout<<"q";
                     else cout<<'_';
                 }
                 cout<<'\n';
             }
             return;
        }
        
   
    for(int j=cur_col+1;j<chess[0].size();j++)
     {
         chess[cur_row][j]=true;
         queenscombinations(qsf+1,tq,cur_row,j,chess);
         chess[cur_row][j]=false;
     }
     for(int i=cur_row+1;i<chess.size();i++) {for(int j=0;j<chess[0].size();j++)
     {
         chess[i][j]=true;
         queenscombinations(qsf+1,tq,i,j,chess);
         chess[i][j]=false;
     }
     }
}
//this is the second method of placing comboations of cell in the chess box
//Here we assign a virtual number in the box to make it a one day array
//For a 4*4 chess we assign 0 to 15 numbers from each cell
//For any cell having cellnumber num we can find the row of it as row=num/4 and col=num%4;
//We keep track of last cell that we have placed queen from that number we will call recursion+
//backtraking until n*n 
//here one more thing we can note that we dont need to check whether a queen is placed or not
//before placing them as we are placing the cell from lcno+1 we are visiting them for
//the first time as they are afterwards of lcno+1
void queenscombinations2(int qsf,int tq,vvbb chess,int lcno)
{
    if(tq==qsf)
    {
        for(int i=0;i<chess.size();i++)
        {
            for(int j=0;j<chess[0].size();j++)
            {
                if(chess[i][j]==1)
                cout<<"q";
                else cout<<"_";
            }
            cout<<'\n';
        }
        return;
    }
    for(int i=lcno+1;i<chess.size()*chess.size();i++)
    {
        int row=i/4;
        int col=i%4;
        chess[row][col]=true;
        queenscombinations2(qsf+1,tq,chess,i);
        chess[row][col]=false;
    }
}
bool Isitsafe(int cur_row,int cur_col,vvbb chess)
{
    for(int i=cur_row-1;i>=0;i--)
    {
        if(chess[i][cur_col]==1) return false;
    }
    for(int i=cur_row-1,j=cur_col-1;i>=0 and j>=0;i--,j--)
    {
        if(chess[i][j]==1) return false;
    }
    for(int i=cur_row-1,j=cur_col+1;i>=0 and j<chess[0].size();j++,i--)
    {
        if(chess[i][j]==1) return false;
    }
    return true;
}
void queenscomb_safely(int qsf,int tq,int cur_row,int cur_col,vvbb chess)
{
    if(qsf==tq)
    {
        for(int i=0;i<chess.size();i++)
        {
        for(int j=0;j<chess[0].size();j++)
        {
            if(chess[i][j]==1) cout<<"q";
            else cout<<'_';
        }
        cout<<'\n';
        }
        return;
    }
    /*since we cannot place two elements in each row we directly jumping to the next row*/
    // for(int j=cur_col+1;j<chess[0].size();j++)
    // {
    //     if(Isitsafe(cur_row,j,chess))
    //     {
    //          chess[cur_row][j]=true;
    //          queenscomb_safely(qsf+1,tq,cur_row,j,chess);
    //          chess[cur_row][j]=false;
    //     }
    // }
    /*we are starting from the next row from the current row*/
    for(int i=cur_row+1;i<chess.size();i++)
    {
        for(int j=0;j<chess[0].size();j++)
        {
            //before placing we are  checking whether it is safe place to ot not

            if(Isitsafe(i,j,chess))
            {
                chess[i][j]=true;
                queenscomb_safely(qsf+1,tq,i,j,chess);
                chess[i][j]=false;
                
            }
        }
    }
}
bool Isitsafe_int(int cur_row,int cur_col,vvii chess)
{
    for(int i=cur_row-1;i>=0;i--)
    {
        if(chess[i][cur_col]!=0) return false;
    }
    for(int i=cur_row-1,j=cur_col-1;i>=0 and j>=0;i--,j--)
    {
        if(chess[i][j]!=0) return false;
    }
    for(int i=cur_row-1,j=cur_col+1;i>=0 and j<chess[0].size();i--,j++)
    {
        if(chess[i][j]!=0) return false;
    }
    return true;
}
/*In this approach we have stored all the candidate items so that ineach row we can
pkace any number that is not used untoil now and when we are bacjtracking we will
make the number as ununsed and the chess cell;s place as unoccupied
Here there is an extra space that we are using for storing the items we can do that row
col approach */
void queenspermue_safely(int qsf,int tq,int cur_row,vvii chess,vb items)
{
    if(cur_row==chess.size())
    {
        if(qsf==tq)
        {
            for(int i=0;i<chess.size();i++)
             {
                 for(int j=0;j<chess[0].size();j++)
                 {
                     if(chess[i][j]!=0) cout<<chess[i][j];
                     else cout<<'_';
                 }
                 cout<<'\n';
             }
        }
        return;
    }
    for(int j=0;j<chess[0].size();j++)
    {
        for(int i=0;i<items.size();i++)
        {
            if(items[i]==0 and Isitsafe_int(cur_row,j,chess))
            {
                items[i]=true;
                chess[cur_row][j]=i+1;
                queenspermue_safely(qsf+1,tq,cur_row+1,chess,items);
                chess[cur_row][j]=0;
                items[i]=false;
            }
        }
    }
}
/*Since we are placing any number in the empty place of chess we should check all the 8 directions*/
bool Isitsafe_permute(int row,int col,vvii chess)
{
    for(int i=row-1;i>=0;i--)
    {
        if(chess[i][col]!=0)
        return false;
    }
    for(int i=col-1;i>=0;i--)
    {
        if(chess[row][i]!=0)
         return false;
    }
     for(int i=col+1;i<chess[0].size();i++)
    {
        if(chess[row][i]!=0)
         return false;
    }
    for(int i=row+1;i<chess.size();i++)
    {
        if(chess[i][col]!=0)
        return false;
    }
    for(int i=row-1,j=col-1;i>=0 and j>=0;i--,j--)
    {
        if(chess[i][j]!=0)
        return false;
    }
    for(int i=row-1,j=col+1;i>=0 and j<chess[0].size();i--,j++)
    {
        if(chess[i][j]!=0)
        return false;
    }
    for(int i=row+1,j=col-1;i<chess.size() and j>=0;i++,j--)
    {
        if(chess[i][j]!=0) return false;
    }
    for(int i=row+1,j=col+1;i<chess.size() and j<chess[0].size();i++,j++)
    {
        if(chess[i][j]!=0) return false;
    }
    return true;

}
void queensafely_permute(int qsf,int tq,int osf,vvii chess)
{
    if(qsf==tq)
    {
        for(int i=0;i<chess.size();i++)
        {
          for(int j=0;j<chess[0].size();j++)
          {
              if(chess[i][j]!=0) cout<<chess[i][j];
              else cout<<'_';
          }
          cout<<'\n';
        }
        return;
    }
    for(int i=0;i<chess.size()*chess.size();i++)
    {
        int row=i/4;
        int col=i%4;
        
        if(chess[row][col]==0 and Isitsafe_permute(row,col,chess))
        {
               chess[row][col]=osf;
               queensafely_permute(qsf+1,tq,osf+1,chess);
               chess[row][col]=0;
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
   //combinations(4,2,0,"");
    // vector<int> boxes={0,0,0};
 
      //permuations2(1,3,boxes,"",0,2);
    //   vector<vector<bool>> grid(4,vector<bool>(4,false));
    //   vb items(4,0);
    //  queens_permutations(0,4,grid,items);
    //  cout<<totalpaths;

    //queenpermuations(0,0,0,2,"",items);
    //vb items(5,false);
     vector<vector<int>> chess(4,vector<int>(4,0));
     //plcing_permutequeens(0,3,chess);
     //queenscombinations(0,3,0,-1,chess);
    // queenscombinations2(0,3,chess,-1);
   // queenscomb_safely(0,4,-1,-1,chess);
   vb items(4,false);
    // queenspermue_safely(0,4,0,chess,items);
    queensafely_permute(0,4,1,chess);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}