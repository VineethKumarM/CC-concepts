#include<bits/stdC++.h>
using namespace std;

int maxs(int a[],int n)
{
    int maxf,maxe;
    maxf=0;
    maxe=0;
    for(int i=0;i<n;i++)
    {
        maxe=maxe+a[i];
        if(maxf<maxe)
        maxf=maxe;
        if(maxe<0)
        maxe=0;
       
    }
    return maxf;
}
//indices als
int maxi(int a[],int n)
{
    int maxf,maxe;
    int s=0,e=0,start=0;
    maxf=0;
    maxe=0;
    for(int i=0;i<n;i++)
    {
        maxe=maxe+a[i];
        if(maxf<maxe)
        {
        maxf=maxe;
        start=s;
        e=i;

        }
        if(maxe<0)
        {
        maxe=0;
        s=i+1;
        }
    }
    cout<<start<<" "<<e<<endl;
    return maxf;
}
int maxp(int a[],int n)
{
    int maxf,maxe;
    maxf=0;
    maxe=1;
    for(int i=0;i<n;i++)
    {
        maxe=maxe*a[i];
        if(maxf<maxe)
        maxf=maxe;
    
       
    }
    return maxf;
}
int main()
{
 
  
     freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   int t;
   cin>>t;
   int arr[t];
   for(int i=0;i<t;i++)
    cin>>arr[i];

  cout<<maxi(arr,t);
   
     return 0;

}