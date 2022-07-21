#include<bits/stdC++.h>
using namespace std;
//const long long int m=1000000007
//program to find gcd of two numbers
int gcd(int a,int b)
{
    if(a==0)
     return b;
     else
     return gcd(b%a,a);
}
//Extended Euclidean Algorithm to find x and y such that ax+by=gcd(a,b);
long long int gcdextended(long long int a,long long int b, long long int* x,long long int* y)
{
    if(a==0)
    {
        *x=0;
        *y=1;
        return b;
    }
   long long   int x1,y1;
    //referencing x1 and y1 instead of x and y to store values
    long long int gcd=gcdextended(b%a,a,&x1,&y1);
    //updating x1 and y1 values for each recursive call
    *x=y1-(b/a)*x1;
    *y=x1;
    return gcd;

}
//Finding modinverse of a number using Extended Euclidean Algorithm
void modinverse(long long int a ,long long int m)
{
   long long  int x,y;
   long long int g=gcdextended(a,m,&x,&y);
   if(g!=1)
    cout<<"Inverse doesbot exist";
    else
    {
        //m is added  inorder to avoid negative numbers
    long long int res=(x%m+m)%m;
    cout<<"Mod Inverse is "<<res;
    } 

} 
//Findng ModInverse using Iterative approach
long long int Imodinverse(long long int a, long long int m)
{
    long long int x,y;
    y=0;x=1;
    long long int m0=m;
    if(m==1)
    return 0;
    while(a>1)
    {
        //q is a quotient
        long long int t=m;
        long long int q=a/m;

    //Applyong Euclodieans Algorithm
    m=a%m;
    a=t;
    t=y;
    //updating x and y values
    y=x-q*y;
    x=t;
    }
    if(x<0)
    x+=m0;
    return x;
}
//To calucalte x^y under modulo m
long long int power(long long int x,unsigned long int y,unsigned long int m)\
{
    if(y==0)
    return 1;
    long long int p=power(x,y/2,m)%m;
    p=(p*p)%m;
    if(y%2==1)
     return (p*x)%m;
 else
 return p;

}
//Mod Inverse if m is a prime
void Modinversep(long long int a,long long int m)
{
    long int g=gcd(a,m);
    if(g!=1)
    cout<<"ModInverse Doesnot exist"<<endl;
    else
    cout<<power(a,m-2,m)<<endl;
}
int main()
{

     freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   //long long int x,y;
  long long  int a,m;
   cin>>a>>m;
//    cout<<gcdextended(a,b,&x,&y);
//    cout<<endl;
//    cout<<x<<" "<<y;
modinverse(a,m);
cout<<endl;
cout<<Imodinverse(a,m);
cout<<endl;
Modinversep(a,m);
   
     return 0;

}