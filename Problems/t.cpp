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
#define ull unsigned long long int
#define ld long double
#define Maxx 10000
const ll mod=1e9+7;
const ll limit=1e10+7;
int solve(const vector<int> &A) {
    int ans=0,n=A.size();
    vector<unordered_map<int,int>> mp(n);
    for(int i=0;i<A.size();i++){
        int temp=0;
        for(int j=0;j<i;j++){
            long long cd=((long long)A[i]-(long long)A[j]);
            if(cd<=INT_MIN or cd>=INT_MAX) continue;
            int apsending_here=mp[j][cd];
            mp[i][cd]=max(mp[i][cd],1+apsending_here);
            cout<<i<<" "<<cd<<" "<<mp[i][cd]<<'\n';
            temp=max(temp,mp[i][cd]);
        }
        cout<<'\n';
        ans=max(ans,temp);
    }
    return ans;
}

int main()
 {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ////vector<string> v={ "nc7-hdly-hrht","nr1-7-1-7-0-4"};
   //v=reorderLogs(v);
   //for(auto &s:v) cout<<s<<'\n';
   //vector<int> v={10, 28, 9, 25, 8, 25, 9, 27, 23, 6, 13, 4, 1, 13, 11, 10, 21, 7, 7, 13, 9, 28, 8, 28, 10, 24, 11, 28};
 //  cout<<solve(v);
	//<<solve(383,879,80);
   // vector<string> v={ "2.673662", "2.419159", "0.573816", "2.454376", "0.403605", "2.503658", "0.806191"};
    //cout<<solve(v);
   // vector<vector<int>> v={{1,2,3,4},{2,2,3,4},{3,2,3,4},{4,5,6,7}};
   vector<int> v={2,2,2};
   cout<<solve(v);
   //cout<<minSmoke(v);
    //cout<<solve(10000,5);
    
	return 0;
 }
 //Lonest ap
 //binary tree max path
 //min stack
 //rotate duplicates ii
 //potions