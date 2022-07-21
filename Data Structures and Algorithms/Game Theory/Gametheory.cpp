#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++); 
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
ll max=1e18;
bool Iswinning(int n)
{
    if(n==4 || n==7) return true;
    if(n<4) return false;
    if(Iswinning(n-4) || Iswinning(n-7))
     return true;
     else
     return false;
}
/*Game od nim
If we have c1,c2,......cn then loosing state will be if(xor) all the numbers is 0
Minmax algo is used in tictac toe and chess problems*/
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<bool> fact(10000000,false);
    cout<<fact[0];
    //cout<<Iswinning(675);
    
    return 0;
}