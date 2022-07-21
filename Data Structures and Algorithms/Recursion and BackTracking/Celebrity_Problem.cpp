#include<bits/stdC++.h>
using namespace std; 
#define ll long long int
#define ull unsigned long long int
#define vi vector<int>
#define vil vector<ll>
#define vb vector<bool>
#define vc vector<char>
#define vull vector<ull>
#define vf vector<float>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define uint_64t unsigned ll
#define int_64t  ll
#define ld long double
#define umpi unordered_map<int,int>
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 10000
#define mod1 1e9+7
#define MAX 3000
//Stack Approach
int knows(int a,int b,vii M)
{
     return M[a][b];
}
//Using the concept of indegree and outdegree
//Complexity of O(n^2)
//Space complexity O(n)
int Find_Celeb_Graph(int n,vii M)
{
    vi indegree(n,0),outdegree(n,0);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int x=knows(i,j,M);
            indegree[j]+=x;
            outdegree[i]+=x;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(indegree[i]==n-1 and outdegree[i]==0) 
        return i;
    }
    return -1;
}
//Two pointer approach
//This is an time and space optimised algorithm O(n)
//Here we create two pointers one is start pointing at start index and another ois wnd pinting
//at end pointer
//Here we are iterate until start<end and if start konws end then start ++
//else end--;
int Find_Celeb_Pointer(int n,vii M)
{
    vi v(n);
    for(int i=0;i<n;i++) v[i]=i;
    int *start,*end;
    start=&v[0];end=&v[n-1];
    while(start!=end)
    {
        if(knows(*start,*end,M))
         start++;
         else end--;
    }
    //Here a is a posiible celebrity because there may be person that are known by a
    //That s why we have to check the condition if any person knows to A then return -1;
    //else return a;
    int a=*start;
    for(int i=0;i<n;i++)
    {
        if(M[a][i]==1) return -1;
    }
    return a;
}
//Find Celebrity by Recursion
//This function returns the potential celebrity
//This function gives only the possible index
int Find_Pot_Celebrity(int n,vii M)
{
    //Base cae if there are 0 people then celebrity will be -1;
    if(n==0) return -1;
    //Let id be the potential celebrity 
    //Recurrsion assumption
    int id=Find_Pot_Celebrity(n-1,M);
    //If there is no potential celebrity for n-1 people then return n-1;
    if(id==-1) return n-1;
    //Id id knows n-1 th person then n-1 will be celbrity;
    else if(knows(id,n-1,M)) return n-1;
    //if(n-1) persons id then id will be poential celebrity
    else if(knows(n-1,id,M)) return id;
    //if  none of them found then return -1
    return -1;
}
int Find_Celeb_Recur(int n,vii M)
{
    int id=Find_Pot_Celebrity(n,M);
    //here we have to chheck whether id is the correcyt celebrity by checking celebrity conditions
    if(id==-1) return -1;
    else{
      int c1=0,c2=0;
      for(int i=0;i<n;i++)
      {
             if(knows(i,id,M)) c1+=1;
             if(knows(id,i,M)) c2+=1;
      }
      if(c1==n-1 and c2==0) return id;
      else return -1;
     }
}
int Find_Celebrity(int n,vii M)
{
    stack<int> s;
    for(int i=0;i<n;i++) s.push(i);
    while(s.size()>1)
    {
        int a=s.top();s.pop();
        int b=s.top();s.pop();
        if(knows(a,b,M)) s.push(b);
        else s.push(a);
    }
    if(s.empty()) return -1;
    int c=s.top();s.pop();
    for(int i=0;i<n;i++)
    {
        if(i!=c and (!knows(i,c,M) and knows(i,c,M))) return -1;
    }
    return c;
}
int main()
{
    
     freopen("Input.txt", "r", stdin); 
     freopen("Output.txt", "w", stdout);
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     cout.tie(NULL);
     vector<vector<int>> M(4, vector<int>(4, 0));
     for(int i=0;i<4;i++)
     {
         for(int j=0;j<4;j++) cin>>M[i][j];
     } 
     cout<<Find_Celeb_Recur(4,M);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}