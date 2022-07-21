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
#define vvii vector<vector<int>>
#define vvbb vector<vector<bool>>
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
/*Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.
Return any array that satisfies this condition.
*/
/*Since it is given the we can return any array which statisfies the above condition
our motto is to put all the even numbers one side and odd numbers another side at
the end of the array
we will make two pinters one is at start and another is at end of the array
we make a while loop until l<r satisfies so l will be in half part and r will be in right part
In l part even numbers should be there,in r part even numbers odd numbers should be there
so if we found a[l]%2==1 and a[r]%2==1 we swap both the value
*/
vector<int> sortArrayByParity(vector<int>& nums) {
       int l=0,r=nums.size()-1;
      while(l<r)
      {
          /*This two while loops as to satisy above conditions
          a[l]$2==1 and a[r]%2==0 then only we can swap the numbes until both the conditions
          l and r keeps on incrementing and decrementing*/
        while(l<r and nums[l]%2==0) l++;
        while(l<r and nums[r]%2==1) r--;
        swap(nums[l],nums[r]);
      }
      return nums;
}
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
      return 0;
}
