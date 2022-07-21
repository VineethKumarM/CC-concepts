#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vvii vector<vector<int>>
#define vs vector<string>
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
void transpose(vvii m){
    /*For Rotating about 90 degree we simply transpose the matrix and reverse each row*/
    for(int i=0;i<m.size();i++){
       for(int j=0;j<i;j++)
        swap(m[i][j],m[j][i]);
    }
}
/*For rectangular matrix*/
vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int r=matrix.size(),c=matrix[0].size();
      vector<vector<int>> ans(c,vector<int>(r));
      for(int i=0;i<r;i++)
      {
        for(int j=0;j<c;j++)
          ans[j][i]=matrix[i][j];
      }
      return ans;
}
void rotateby_90(vvii m){
    for(int i=0;i<m.size();i++){
       reverse(m[i].begin(),m[i].end());
    }
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;

} 