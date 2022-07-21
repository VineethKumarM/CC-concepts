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
struct ListNode {
   int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
/*Concept of slow  pointer and fast pointer 
 let us take an example of two pointers one is named as fast and slow with fast is lagging behind  one pointer
 f-s-p where p is the next pointer then fast moves by two steps and reaches p and slow moves by 1 step reaches the p pointer
 so fast and slow pointer arrived at same pointer
 let us take another pointer with two pointer diffrece
 f-p-s-p in this case fast moves by steps and slow move by one step then the pointers will be p-p-f-s we can observe that itis the same 
 case as of
 In this way we can take any diifrence of poiners we can assure that fast pointer definitely reaches the slow pointer
 This concept can be used to find cycles in the lists
 We move two pointers at theri respective speeds if we get the slow==fast then we got a cycle in that case\
 Since in the cyckled lists the ListNode we wont get any that points its next node to NULL*/
 bool is_there_cycle(ListNode* head){
     if(head==NULL or head->next==NULL) return false;
     ListNode* fast=head;
     ListNode* slow=head;
     while(fast->next!=NULL and fast->next->next!=NULL){
         fast=fast->next->next;
         slow=slow->next;
         if(fast==slow)
          return true;
     }
     return false;
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