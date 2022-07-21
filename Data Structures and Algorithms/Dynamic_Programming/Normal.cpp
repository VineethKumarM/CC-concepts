#include<bits/stdc++.h>
#define vi vector<int>
using namespace std;
vector<int> flip(string A) {
     int cur_sum=0,max_sofar=0,left=1,right=-1;
    vector<int> ans(2,0);
    for(int i=0;i<A.size();i++){
           if(A[i]=='0') cur_sum+=1;
           else cur_sum-=1;
           if(cur_sum<0) {
               cur_sum=0;
               left=i+2;
           }
           if(cur_sum>max_sofar){
               right=i+1;
               ans[0]=left,ans[1]=right;
               max_sofar=cur_sum;
           }
    }
    if(max_sofar==0) return {};
    else return ans;
}
int main()
{
    //int v[10];
   // for(int i=0;i<10;i++) cin>>v[i];
   cout<<flip("011")[0]<<' '<<flip("011")[1]<<'\n';

}