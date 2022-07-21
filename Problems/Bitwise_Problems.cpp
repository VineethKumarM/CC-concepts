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
/*Bitwise and of range from [m,n]*/
/*Let us take the range from 16 to 19
16=10000
17=10001
18=10010
19-10011
/*If in any column any one of the bit get flipped then all that colum will become 0
Here no matter how many ones are there if we get any 1 0 in that column then the whole 
column will always be 0
We can make two obeservations
1.if any bit flips for a given position in the range [m,n] then the entire colum will be 0
for the whole column in that range
2,All the bits that are right to the flipped bit also flipped atleast once
from the above example we can see that the first 1 and 0 and 0  are not flipeed in the range but the 
at the remaining positions the bits get flipped
So if a bit is flipped at that pos then all the bits must have flipped as from the combinationd
they must be exhausted
we can obeserve another thing the left most elements are alwasy fixed in the given range
from the above example we can observe the fist 100 is always fixed for 16,17,18,19
So in  our algorithm we keep on right shifting the bits until we get left==right
If left=right it impiles that all the elements that are flipeed has been exhausted this are 
thr reaminig bits that are not flipped atleast once
since we have keep tracked the count variable as how many bits areflipped
at last we left shit those amny elemnts*/
/*As we can see that here 100 is haven't changed and remaining all the numbers got flippd atleast once*/
int bitwise_and(int left,int right){
    int cnt=0;
    while(left!=right){
        cnt++;
        left>>=1;
        right>>=1;
    }
    return (left<<cnt);
}
/*Singel Number Problem*/
/*Given an integer array nums, in which exactly two elements appear only once \
and all the other elements appear exactly twice. Find the two elements that appear only once. 
You can return the answer in any order.
You must write an algorithm that runs in linear runtime complexity
 and uses only constant extra space.
*/
/*Here we use the concept of bitmanipulation
We know that xor of same numbers we result into 0
we use the concept of this to avoid the O(n) space and and we can do in linear time complexity*/
/*First we will xor the whole array 
Let us the single frequency elements are x and y we get xy=x^y after xoring the whole array
as reaminging elenment all are got cancelled
So we have the value with xy we have to find the values of x and y
For that we will use the lsb in xy 
since it is 1 in the xy value then it is confirmed that one of the x and y should have 0 as
0^1 =1
So we should xor the all the vakues in the array this time we partion the results into two values
in one res1 we will xor those elements  which have set bit at that lsb position]
and we will xor which does nt have set bit at that position 
as all the double elements fall into any one of the sets (not possible to fall in didffereeng sets)
they will cancel each other we remain with single frequency eleements in  both the results
Inorder to check whther the bit ise set at that posituon
we will use the concept ofn negation
x =(x&(-x)) will set all the bits to 0 except the lsb bits
*/
vector<int> single_number(vi nums){
    int xy=0;
    for(int n:nums) xy^=n;
    /*take care of overflows we have to use long ints*/
    xy&=(-xy);
    vi ans={0,0};
    for(int n:nums){
         if(xy^n) ans[0]^=n;
         else ans[1]^=n;
    }
    return ans;
}
//Count of set bits from 1 to n with O(n) time complexity
//Let us assume a x and y such that x/2=y then the differene of set bits in these two numbers is 
//always less than or equal to 1
//if the x is odd then 1+count(y) else count(x)=count(y)
//let us assume x=7 and y=3 then x=111 y=011 then x/2 is 3 we are right shifting the things
//im case if is oadd the last bit is set we lost 1 bit when we divide them
//if it is even then last bit is 0 upon diving by 2 also the countwill be same for both the 
//nmbers
//6=110 and 3=011
vi countBits(int n)
{
    vi ans(n+1);
    ans[0]=0;
    for(int i=1;i<=n;i++)
    {
        if(i%2) ans[i]=1+ans[i/2];
        else ans[i]=ans[i/2];
    }
    return ans;
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout<<"Hello World!";
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}