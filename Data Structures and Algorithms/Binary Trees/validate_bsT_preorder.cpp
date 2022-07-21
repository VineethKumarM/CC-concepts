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
const ll size=2*(1e6+1);
const ll limit=1e10+7;
void validate(int &index,vector<int> &A,int min,int max){
    if(index>=A.size()) return;
    if(A[index]>=min and A[index]<=max){
        int root=A[index];
        index++;
        validate(index,A,min,root);
        validate(index,A,root,max);
    }
}
int solve(vector<int> &A) {
    int index=0;
    validate(index,A,INT_MIN,INT_MAX);
    return index==A.size();
}

int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<int> A={197, 74, 48, 6, 23, 93, 98, 146, 110, 919, 357, 247, 278, 267, 270, 775, 469, 436, 390, 412, 464, 458, 681, 629, 622, 503, 611, 583, 644, 705, 686, 702, 721, 759, 811, 830, 872, 902, 985, 961, 933, 994}; 
    cout<<solve(A);
    return 0;
 }
