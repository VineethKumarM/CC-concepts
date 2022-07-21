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
//Tower of Hanoil problem
//s=source
//d=destination
//h=helper
//n=no.of plates
//In this tower of hanoi problem the induction hypothesis is first move n-1 disks from
//source to helper
//then the next step will be moving the nth disk from source to destination 
//and then again move the disks from helper to source
void Tower_of_Hanoi(int s,int d,int h,int n)
{
    //Base ccondition is that move directly from source to destination if thr no.of disks are 1
    if(n==1){cout<<s<<"->"<<d<<'\n';return;}
    //Move the (n-1) disks from source to helper(Here parameters order changed)
    Tower_of_Hanoi(s,h,d,n-1);
    //Then print the step of moving from source to destination 
    cout<<s<<"->"<<d<<'\n';
    //Then again move n-1 disks from helper to destination
    Tower_of_Hanoi(h,d,s,n-1);
}  
int main()
{
    
     freopen("Input.txt", "r", stdin); 
     freopen("Output.txt", "w", stdout);
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     cout.tie(NULL);
     Tower_of_Hanoi(3,1,2,3);
       #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}