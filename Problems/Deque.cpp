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
//const ll size=2*(1e6+1);
const ll limit=1e10+7;
int findMedian(vector<vector<int> > &A) {
    for(int i=0;i<A.size();i++){
        for(int j=i+1;j<A[0].size();j++){
             swap(A[i][j],A[j][i]);
        }
    }
    for(int i=0;i<A.size();i++) sort(A[i].begin(),A[i].end());
    for(int i=0;i<A.size();i++){
        for(int j=i+1;j<A[0].size();j++){
             swap(A[i][j],A[j][i]);
        }
    }
    for(int i=0;i<A.size();i++){
        for(int j=0;j<A[0].size();j++){
            cout<<A[i][j]<<' ';
        }
        cout<<'\n';
    }
    int size=A.size()*A[0].size();bool flag=false;
    if(size%2==0) flag=true;
    size/=2;
    int i=size/A.size(),j=size%(A[0].size());
    int res=-1; res=A[i][j];
    if(flag){
        if(j+1<A[0].size()) return (res+A[i][j+1])/2;
        else return (res+A[i+1][j])/2;
    }
    return res;
}


int main()
{
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<vector<int>> v={
  {1, 3, 5},
  {2, 6, 9},
  {3, 6, 9}
    };
    cout<<findMedian(v);
     #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}