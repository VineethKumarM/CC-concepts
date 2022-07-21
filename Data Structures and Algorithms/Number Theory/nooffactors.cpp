#include<bits/stdC++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     cout.tie(NULL);
     freopen("input.txt", "r", stdin); 
     freopen("output.txt", "w", stdout);
     bool is_prime[m];
    for(int i=2;i<m;i++)
     is_prime[i]=true;
     for(long int i=2;i<m;i++)
     { 
         if(1LL*i*i<=m)
         {
          for(long  int num=2*i;num<=m;num+=i)
          {
            
              is_prime[num]=false;
          }  
         }
     }
     vector <int> freq;
    
     int t;cin>>t;
     while(t)
     {
         int n;
         cin>>n;
         vector <int> v;
         for(int i=0;i<n;i++)
         {
             int k;
             cin>>k;
             v.push_back(k);
         }
         for(int i=0;i<n;i++)
         {
            int z = 2;

         while (z * z <= n)
         {
        if (v[i]%z== 0)
             
            n /= z

        else
            z++;
         }

    if n > 1
        output n
   
         }


     }
     
     return 0;
}