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
//Reversing the stack without using another stack
void insert_at_bottom(char ch,stack<char> &s)
{
    if(s.empty()) s.push(ch);
    else
    {
        //Here we are popping out the element from the stack since we want to have origina stack bottom element at the 
        //top of the new stack
        char a=s.top();
        s.pop();
        insert_at_bottom(ch,s);
        s.push(a);
    }
}
//Reverse the stack
void reverse_stack(stack<char> &s)
{
    if(s.size()>0)
    {
        char ch=s.top();
        s.pop();
        reverse_stack(s);
        insert_at_bottom(ch,s);
    }
}
//Sorting the stack using recursion
void Insert_sort(stack<int> &Stack,int key)
{
    if(Stack.empty() || key>Stack.top()) { Stack.push(key);return;}
    int x=Stack.top();
    Stack.pop();
    Insert_sort(Stack,key);
    Stack.push(x);
}
void Sort_the_stack(stack<int> &Stack)
{
    if(Stack.empty()) return;
    int d=Stack.top();
    Stack.pop();
    Sort_the_stack(Stack);
    Insert_sort(Stack,d);
}
//Sorting the stack using a temporary stack
sti Sort_stack_temp(sti &st)
{
    sti temp;
    while(!st.empty())
    {
        int x=st.top();
        st.pop();
        //here we keep on poppping the elements until we get the min element and pushing the
        //elements in the stack in the already sorted order to original stack
        //So the for next iteration will this loop will not work and at last we are pushing them
        //again in their sorted order
        while((!temp.empty()) and (temp.top()>x))
        {
            st.push(temp.top());
            temp.pop();
        }
        //Here we are pushing into the temp stack
        temp.push(x);
    }
    return temp;
}
//Reversing the stack using Linked List Logic and O(n) time and O(1) space 
//The above recursion function will take O(n) extra space
class StackNode
{
    public:
    int data;
    StackNode *next;
    StackNode(int data)
    {
        this->data=data;
        this->next=NULL;
    }
};
class Stack
{
    StackNode* top;
    public:
      void push(int data)
      {
          if(top==NULL)
          {
              top=new StackNode(data);
              return;
          }
          StackNode *s=new StackNode(data);
           s->next=top;
           top=s;
      }
      StackNode* pop()
      {
          StackNode *s=top;
          top=top->next;
          return s;
      }
      bool Isempty(StackNode *s)
      {
          if(s==NULL) return true;
          else return false;
      }
      void display()
      {
          StackNode *s=top;
          while(s!=NULL)
          {
              cout<<s->data<<' ';
              s=s->next;
          }
      }
      //Using the simple logic of reversing linked list connection
      //In linked list we will always push and pop from the head pointer from the
      //linked list
      void reverse()
      {
          StackNode *cur,*prev,*succ;
          cur=prev=top;
          cur=cur->next;
          prev->next=NULL;
          while(cur!=NULL)
          {
             succ=cur->next;
             cur->next=prev;
             prev=cur;
             cur=succ;
          }
          top=prev;
      }

};
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // stack<char> st;
    // st.push('a');
    // st.push('b');
    // st.push('c');
    // st.push('d');
    // st.push('e');
    stack<int> sta;
    sta.push(1);
    sta.push(3);
    sta.push(5);
    sta.push(6);
    sta.push(9);
    sta.push(10);
    sta.push(-2);
    //Insert_order(st,7);
    // sti res=Sort_stack_temp(sta);
    // while(!res.empty())
    // {
    //     cout<<res.top()<<' ';
    //     res.pop();
    // }
    Stack *s=new Stack();
    s->push(1);
    s->push(2);s->push(3);
    s->reverse();
    //s->display();
    s->display();
        #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}
