#include<bits/stdC++.h>
using namespace std; 
#define ll long long int
#define ull unsigned long long int
#define vi vector<int>
#define vil vector<ll>
#define vb vector<bool>
#define vc vector<char>
#define vull vector<ull>
#define vf vector<float>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define uint_64t unsigned ll
#define int_64t  ll
#define ld long double
#define umpi unordered_map<int,int>
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n),P2(n^1),P2(n^1),P2(n)
#define P6(n) P4(n),P4(n^1),P4(n^1),P4(n)
#define Look_Up P6(0),P6(1),P6(0),P6(1)
#define phi 1.6180339887498948 
#define N 6
#define Maxx 10000
#define mod1 1e9+7
#define MAX 3000
class StackNode
{
    public:
    int data;
    StackNode *next;
};
StackNode *top=NULL;
void push(int dat)
{
    if(top==NULL)
    {
       StackNode *s=new StackNode();
       s->data=dat;
       s->next=NULL;
       top=s;
    }
    else
    {
        StackNode *s=new StackNode();
        s->data=dat;
        s->next=top;
        top=s;
    }
}
void pop()
{
    if(top==NULL) exit(1);
    else
    {
      StackNode *temp;
      temp=top;
      top=top->next;
      temp->next=NULL;
      free(temp);
    }
}
int top_data()
{
    if(top==NULL) exit(1);
    else return top->data;
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    push(3);
    push(4);
    pop();
    push(7);
    push(8);
    cout<<top_data();
   // cout<<top->data;
        #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}