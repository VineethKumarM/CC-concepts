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
/*Here is the snakes and laders probelm in whcih we are given a chess board of size 10*10
In this problem we can control the dice number
It means we can produce the dice number as per our requirment 
There are some ladders and some snakes at some cells
No two cells have both ladders and snakes
There is no snake at 100
If we are at 97 we cannot make jumpof 6 5 4
We should find the minimum no of moves to reach end of board which has cell number
*/
/*To approach this problem we will travel the bfs and increment the numbers level by level
To avoid infimnite overflow we will make a visted array so that no two cells are visted again 
as it may happen due to snakes then it may com back to same cell
*/
int bfs(umpii snak,umpii lad)
{
    queue<int> q;
    q.push(1);
    bool found=false;
    int moves=0;
    /*wekept the moves as 0 and visited array as false and push the current cell number
    and we will keep a counter to determine whether it has reached the 100 or not*/
    vb vis(101,false);
    vis[1]=true;
    /*so while the q is not empty and we havent reached the destination we keep on looping*/
    while(!q.empty() and !found)
    {
        /**/
        int sz=q.size();
        while(sz--)
        {
            /*we now traversing level by level*/
            int t=q.front();
            q.pop();
            for(int die=1;die<=6;die++)
             {
                 /*we are adiing all possibilities*/
                 /*if the t+die ==100 it means that we have reached the destination*/
                 if(t+die==100)
                  found=true;
                  /*if t+die<100 and if any ladder exist and it is not visited(keep the order in mind)*/
                  if(t+die<=100 and lad[t+die] and !vis[lad[t+die]])
                  {
                      /*then we push that eleement in the que for next level iteration*/
                      /*note that we are not pushing the current cell we are pushing the cell where the ladder
                      will takes us to*/
                       vis[lad[t+die]]=true;
                       /*if the lad[t+die] has 100 itself we will make the found as true*/
                       if(lad[t+die]==100)
                         found=true;
                         /*here we push the ladder element*/
                       q.push(lad[t+die]);
                  }
                  /*same with the snake case if we are at cell psition where 
                  the snake is there then we cannot push the current elemnt position only we can push the
                  elemnt where it drawabacks us and before pusging we should make sure that it is not visited*/
                  /*we should maintain the order here t+die<=100 within the board if snak[t+die] exists 
                  and then after we check whether that tail cell is visted*/
                  else if(t+die<=100 and snak[t+die] and !vis[snak[t+die]])
                  {

                      vis[snak[t+die]]=true;
                      if(snak[t+die]==100)
                        found=true;
                        q.push(snak[t+die]);
                  }
                /*At last we will push he cureent cell if the current cell is not visted within the
                board and no snake and no laddeer at the current cell*/
                  else if(t+die<=100 and !vis[t+die] and !snak[t+die] and !lad[t+die])
                  {
                      /*we will make the cell visited before pushing into the queue*/
                      vis[t+die]=true;
                        q.push(t+die);
                  }
             }
        }
        /*After traversing at each level we make the moves+=1 as we have moved to next level*/
        moves+=1;
    }
    if(found)
    return moves;
    else
    return -1;
}
int main()
{
    // freopen("Input.txt", "r", stdin); 
    // freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
     cin.tie(NULL);
    cout.tie(NULL);
    int ladders;cin>>ladders;
    umpii lad;
    for(int i=0;i<ladders;i++)
    {
        int a,b;cin>>a>>b;
        lad[a]=b;
    }
    int snakes;cin>>snakes;
    umpii snak;
    for(int i=0;i<snakes;i++){
           int a,b;cin>>a>>b;
           snak[a]=b;
    }
    int moves=bfs(snak,lad);
   cout<<moves<<'\n';
   
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
} 