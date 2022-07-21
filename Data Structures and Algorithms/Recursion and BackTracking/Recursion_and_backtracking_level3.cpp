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
/*This is the permutation of a given string where it may contain the duplicates
We should print all the permutations
Since the charcters may repeat in the original string we should avoid the permutation
one way is to permute as through normal recurisve function and store them in the set
as set does not allow duplicates
We can do it by storingthe frequency of charcters
We do this problem by box level approach 
as we select a box and put all those candiate charcters which are having freq>=1 and when we
are backtracking we again increase the frequency of that charcter*/
void permute_string(int cs,int ts,unordered_map<char,int> mp,string osf)
{
    if(ts==cs)
    {
     cout<<osf<<'\n';
     return;
    }
    for(auto it:mp)
    {
        /*here we check the frequency of that charcter in that table and if that character has 
        a frequeny greater than 1 the n we use the charcter*/
        if(mp[it.first]>0)
        {
          /*Here we have reduced the frequency of that charcter*/
            mp[it.first]=mp[it.first]-1;
            permute_string(cs+1,ts,mp,osf+it.first);
            /*when we are backtracking we set the frequency to normal range*/
            mp[it.first]=mp[it.first]+1;
        }
    }
}
/*this is another method of permuting the string by keeping the items at the level
where we put the boxes at the level in the last case(Notebook)*/
void permutations2(int cs,string s,vc spots,umpci LastOccurence)
{
    if(cs==s.size())
    {
        for(int i=0;i<spots.size();i++) cout<<spots[i];
        cout<<'\n';
        return;
    }
    char ch=s[cs];
    int lo=LastOccurence[ch];
    for(int i=lo+1;i<spots.size();i++)
    {
        if(spots[i]=='_')
        {
              spots[i]=ch;
              LastOccurence[ch]=i;
              permutations2(cs+1,s,spots,LastOccurence);
              spots[i]='_';
              LastOccurence[ch]=lo;
        }
    }

}
/*Here in this problem we have given a string where it may contain the duplicates 
we have  to select k distinc strings
Since here in the qstn it is gievn  that only one item should be used once we found any charcter
we intilauu aassign 1 to it so that the chaarcter is present
Int the recursive funtion we aasiifgn 0 to it and when we are bajtracking the
we again assign mp[ch]=1 so that theu get permmuted1*/
void distinct_words(string osf,umpci mp,int totalitems)
{
    if(osf.size()==totalitems)
    {
        cout<<osf<<'\n';
        return;
    }
    for(auto it:mp)
    {
        if(it.second>0)
        {
            osf+=it.first;
            mp[it.first]=0;
            distinct_words(osf,mp,totalitems);
            osf.pop_back();
            mp[it.first]=1;
        }
    }
}
/*permuting the given string while mantaining the order of charceters as in the original string
As the original string may contain duplicates we make a unique dtring where it contains distinct characters
by using the map
cs=currently_selected itmes
ts=total_items =need to be selected
uniwque string
lc=last item index thatwas selected
osf is the output so far
Since the order needs to be maintained the net element that isgoing to be selcted at greater index that is
being lastly selected
so we keep track of the lc and we start selecting from lc+1 index*/
void distinct_words_same_order(int cs,int ts,string unique,int lc,string osf)
{
    if(cs==ts)
    {
        cout<<osf<<'\n';
        return;
    }
    for(int i=lc+1;i<unique.size();i++)
    {
        distinct_words_same_order(cs+1,ts,unique,i,osf+unique[i]);
    }
}
/*In this problem we are given with denomination of coins we should find the ways of combining the coins
to have sum equal to target sum
in this problem we cannot use the sane coin twice so every coin as only two options
whether we should include that coin or not
The time complexity of this algorithm is O(2^n)*/
void coinchange(int cur_index,vi coins,int ssf,int target_sum,string osf)
{
    if(ssf>target_sum) return;
    if(cur_index==coins.size())
    {
           if(ssf==target_sum) cout<<osf<<'\n';
           return;
    }

//We are incrementing the current as for the next coins
//At firstbwe are including the coin and at last we are  not adding that coin
    coinchange(cur_index+1,coins,ssf+coins[cur_index],target_sum,osf+to_string(coins[cur_index]));
     coinchange(cur_index+1,coins,ssf,target_sum,osf);
}
/*In this problem we can take the coin any infinite number of times
there are two methods for approaching this problem
One is based on above problem where we have the constary=int that we should use the coins at most once
Since here we have an option that where we can use same element multiple times
so we wont increment the index here when we have choosen that particular element
When we haven't selected that item then we will incre,ent the cur_index for the next elements*/
void coinchange_infinite1(int cur_index,vi coins,int ssf,int target_sum,string osf)
{
    if(ssf>target_sum) return;
    if(cur_index==coins.size())
    {
        if(ssf==target_sum) cout<<osf<<'\n';
        return;
    }
    coinchange_infinite1(cur_index,coins,ssf+coins[cur_index],target_sum,osf+to_string(coins[cur_index]));
    coinchange_infinite1(cur_index+1,coins,ssf,target_sum,osf);
}
/*This is the second method of approaching the problem
let us take an example vi coins[2,3,5,7] and the target_sum is 12 ssf=0
For coin 2 it has got 7 options 2*6,2*5,2*4...2*1 and 0 times
where it hasn't selected any one of the items
So depending uons the neede sum we run a loop for selecting the multiple coins and increment the index
as the use of currentcoin has been used through all for loops*/
void coinchange_infinite2(int cur_index,vi coins,int ssf,int target_sum,string osf)
{
    if(ssf>target_sum) return;
    if(cur_index==coins.size())
    {
         if(ssf==target_sum) cout<<osf<<'\n';
         return;
    }
    //This is the needed sum i.e., targetsum-ssf/coins[cur_index] and we loop until the use of 
    //j=1 which means we have used the coin j many number of times
    for(int j=(target_sum-ssf)/coins[cur_index];j>=1;j--)
    {
        //
        string p=osf;
        for(int k=0;k<j;k++) p+=to_string(coins[cur_index]);
        coinchange_infinite2(cur_index+1,coins,ssf+j*coins[cur_index],target_sum,p);
    }
    //At last we haven;t selected the item 
    coinchange_infinite2(cur_index+1,coins,ssf,target_sum,osf);
}
/*This is an installment problem where we have given a vector of installments
and targeted_sum
You have to find all the ways of intalling to have target sum
Since here the order matters we have to print all the permutations
For this we keep track of boolean array and we will append the any unused item by for looping to
our string osf*/
void coinchange_permutations(vi coins,int ssf,int target_sum,string osf,vb used)
{
    if(ssf>target_sum) return;
    if(ssf==target_sum) 
    {
        cout<<osf<<'\n';
        return;
    }
       for(int i=0;i<used.size();i++)
       {
           if(used[i]==0)
           {
               used[i]=true;
               coinchange_permutations(coins,ssf+coins[i],target_sum,osf+to_string(coins[i]),used);
               used[i]=false;
           }
       }
}
bool isvalid(vvii grid,int cur_x,int cur_y,int val)
{
    for(int i=0;i<grid[0].size();i++)
    {
        if(grid[cur_x][i]==val)
        return false;
    }
    for(int i=0;i<grid.size();i++)
    {
        if(grid[i][cur_y]==val)
         return false;
    }
    /*submatrix cordinates x and y to which it belongs*/
    int sbx=cur_x-cur_x%3;
    int sby=cur_y-cur_y%3;
    /*We are checking in the submatrix whether that element is already there in the submatrix
    or not */
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grid[sbx+i][sby+j]==val)
             return false;
        }
    }
      return true;
}
/*Here we solve the sudoko problem in which we are provided with grid value 
whre grid[i][j]==0 means to fill the value
So we do hit  and backtrack with every number if it is valid to put the number there or not
Conditions for valid putting
1.The number should not  be there in the entire row,entire column
and it should notbe there at in the sub,matrix of length3*3
For starting index of submatrix we can use the formula that cur_row0cur_row%3
and col will be cur_col-cur_col%3*/
/*Time complexity of the code is 9^(n*n)*/
void solve_sudoko(vvii grid,int cur_x,int cur_y)
{
    if(cur_x==grid.size())
    {
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0;j<grid[0].size();j++) cout<<grid[i][j];
            cout<<'\n';
        }
        return;
    }
    //This is thee new row and newcol that we assign depemding upon cur_row and cur-col
    //If the cur_col is at llast colum we assignnew column and nw=ew row
    //else the nc=cur_col+1 and nr=cur_row
    int nr,nc;
    if(cur_y==grid[0].size()-1)
    {
        nr=cur_x+1;
        nc=0;
    }
    else
    {
        nr=cur_x;
        nc=cur_y+1;
    }
    //Here we check if the grid is already fiilled if it then solve for the nr,nc box
    //else check the nmbers and put them and after returning from the call backtrack the things
    if(grid[cur_x][cur_y]!=0) solve_sudoko(grid,nr,nc);
    else
    {
    for(int i=1;i<=9;i++)
    {
        if(grid[cur_x][cur_y]==0)
        {
           if(isvalid(grid,cur_x,cur_y,i))
           {
            grid[cur_x][cur_y]=i;
            solve_sudoko(grid,nr,nc);
            grid[cur_x][cur_y]=0;
          }
        }
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
   // string s="aabbcc";
    //unordered_map<char,int> mp;
   // for(int i=0;i<s.size();i++) mp[s[i]]++;
    //arrangements(0,4,mp,"");
    vc v(4,'_');
    //permutations2(0,s,v);
    //for(int i=0;i<s.size();i++) mp[s[i]]=-1;
   // permutations2(0,s,v,mp);
//    for(int i=0;i<s.size();i++) mp[s[i]]=1;
//    distinct_words("",mp,2);
    //distinct_words_same_order(0,2,"ab",-1,"");
  //  vi coins={2,3,5,4,7};
  //  vb used(5,false);
    //coinchange_infinite1(0,coins,0,12,"");
    //coinchange_permutations(coins,0,12,"",used);
   
   vvii grid={ { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

       solve_sudoko(grid,0,0);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 