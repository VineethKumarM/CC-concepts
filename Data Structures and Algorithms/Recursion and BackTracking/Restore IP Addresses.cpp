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
/*A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s.
  You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.*/
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;string res;
       for(int i=1;i<=3;i++){
           for(int j=1;j<=3;j++){
               for(int k=1;k<=3;k++){
                   for(int l=1;l<=3;l++){
                       if(i+j+k+l==s.size()){
                       int A=stoi(s.substr(0,i));
                       int B=stoi(s.substr(i,j));
                       int C=stoi(s.substr(i+j,k));
                       int D=stoi(s.substr(i+j+k,l));
                       if(A<=255 and B<=255 and C<=255 and D<=255){
                          res=to_string(A)+"."+to_string(B)+"."+to_string(C)+"."+to_string(D);
                           if(res.size()==(s.size()+3))
                               ans.push_back(res);
                       }
                     }   
                   }
               }
           }
       }
        return ans;
    }
int main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
 }
