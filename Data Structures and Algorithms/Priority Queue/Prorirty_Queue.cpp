#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define vii vector<vector<int>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
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
/*A priority queue is an abstract data-type similar to a regular queue or stack data structure in which each element additionally 
has a "priority" associated with it. 
Add and remove of time complexity of O(logn)
And peek element is at O(1) time complexity
By default it gives the priority for Largest
Top element of priority_queue is max_one*/
void intro()
{
    priority_queue<int> pq;
    int i=9;
    /*Max-Heap Priority Queue*/
    while(i--) pq.push(i);
    while(pq.size()>0) 
    {
        cout<<pq.top()<<' ';
        pq.pop();
    }
    cout<<'\n';
    /*Min-Heap Priority Queue*/
    priority_queue<int,vector<int>,greater<int>> pqx;
    i=9;
    while(i--) pqx.push(i);
    while(pqx.size()>0)
    {
        cout<<pqx.top()<<' ';
        pqx.pop();
    }
    return;
}
/*Fing k Largest Elements*/
void k_largest(vi v,int k)
{
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=0;i<v.size();i++)
    {
        if(pq.size()<k)
         pq.push(v[i]);
         else
         {
            if(v[i]>pq.top())
            {
                pq.pop();
                pq.push(v[i]);
            }
              
         }
    }
    while(pq.size()>0)
    {
        cout<<pq.top()<<' ';
        pq.pop();
    }
   return;
}
void sort_nearly_sorted_array(vi &v,int k)
{
    priority_queue<int,vector<int>,greater<int>> pq;
    int cnt=0;
    for(int i=0;i<k;i++)
      pq.push(v[i]);
      for(int i=k;i<v.size();i++)
      {
          v[cnt]=pq.top();
          pq.pop();
          pq.push(v[i]);
          cnt++;
      }
      while(pq.size()>0)
      {
          v[cnt]=pq.top();
          pq.pop();
          cnt++;
      }
      for(int n:v) cout<<n<<' ';
}
/*Median Priority Queue is the queue on median priority queue
It contains one max-Priority_queue(left) and one min_heap_priority_queue(right)
Left stores the max_elemenet while right store min-element in their resepective collection elements
We will store the elements the half elements in sorted way in left and another half elements in right priority quueue
Since the elements should be in sorted way we will check if the coming elements is less than right.top() or not
If it is we will push it in left else we push it in right
At each stage we should make sure that abs(left.size()-right.size())<2 
for remove function we  will see the sizes of both queues  
if they have same size we will return the left queue top else we return the max-sized queue top
*/
class MedianPriorityQueue {
public:
  priority_queue <int> left;
  priority_queue <int, vector<int>, greater<int>> right;
  

  void push(int val) {
    //write your code here
     if(right.size()>0 and right.top()>=val)
         left.push(val);
        else right.push(val);
        if(left.size()-right.size()==2)
         {
             int x=left.top();
             right.push(x);
             left.pop();
         }
         else if(right.size()-left.size()==2)
         {
             int x=right.top();
             left.push(x);
             right.pop();
         }
  }

  int pop() {
    //write your code here
    if(size()==0) {
        cout<<"Underflow"<<'\n';
        return -1;
    }
    else if(left.size()>=right.size())
    {
        int x=left.top();
        left.pop();
        return x;
    }else{
        int x=right.top();
        right.pop();
        return x;
    }
  }

  int top() {
    //write your code here
    if(size()==0) {
        cout<<"Underflow"<<'\n';
        return -1;
    }
    else if(left.size()>=right.size())
    {
        return left.top();
    }else{
        return right.top();
    }
  }

  int size() {
    //write your code here
    return left.size()+right.size();
  }
};
void median_priority_queue_test(vi v)
{ 
      
    MedianPriorityQueue  mpq;
    for(int n:v) mpq.push(n);
   while(mpq.size()>0)
   {
       cout<<mpq.top();
       mpq.pop();
   }
}
int main()
{
    //freopen("Input.txt", "r", stdin); 
    //freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //intro();
   vi v={3,2,1,5,6,4,8,7,9};
  // sort_nearly_sorted_array(v,3);

      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}