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
class Node
{
    public:
    int data;
   
    Node *next;
} *head;
Node *head1;
//printing of linkedlist
void print(Node* n)
{
    while(n!=0)
    {
        cout<<n->data<<" ";
        n=n->next;
    }
}
//pushing of elements
void push(Node **headref,int p)
{
    Node* newnode=new Node();
    newnode->data=p;
    newnode->next=*headref;
    *headref=newnode;

}
//insert at begining
void insertb(Node** headref,int num)
{
    Node  *newnode;
    newnode=new Node();
    newnode->data=num;
    newnode->next=(*headref);
    *headref=newnode;


}
//insert at specific position
void insertp(Node *n, int p)
{
    Node *temp=n;
    int i=1;
    while(i<p-1)
    {
        temp=temp->next;
        i++;
    }
    Node *newnode;
    newnode=new Node();
    cin>>newnode->data;
    newnode->next=temp->next;
    temp->next=newnode;

}
//insert at end
void inserte(Node *headref,int p)
{
    
    Node *newnode=new Node();
    Node *temp=headref;
    while(temp->next!=NULL)
    {
           
           temp=temp->next;
    }
    temp->next=newnode;
    newnode->data=p;
    newnode->next=NULL;


}
//delete head of node
void deleteb(Node **headref)
{
    Node *temp;
    temp=(*headref);
    *headref=temp->next;
    free(temp);

}
//delete at aspecidied position p
void deletep(Node** n,int p)
{
    int i=1;
    Node *temp=*n;
    while(i<p-1)
    {
        temp=temp->next;
        i++;
    }
    int j=1;
    Node *last=*n;
    while(j<p)
    {
        last=last->next;
        j++;
    }
    temp->next=last->next;
    free(last);

}
//delete at end position
void deletee(Node **headref)
{
    Node *temp=*headref;
    Node *secondlast;
    while(temp->next!=NULL)
    {
        secondlast=temp;
        temp=temp->next;
    }
    secondlast->next=NULL;
    free(temp);
}
//counting of nodes
int count(Node *headref)
{
    if(headref==NULL)
     return 0;
     else
     return 1+count(headref->next);
}
//searching in linked list
bool search(Node *n,int x)
{
    Node *temp=n;
    while(temp->next!=NULL)
    {
        if(temp->data==x)
        return true;
        temp=temp->next;
    }
    return false;

}
//getting nth node of a linkedlist
int getn(Node *n,int p)
{
    Node *temp=n;
    int cnt=0;
    while(temp->next!=NULL)
    {
        cnt+=1;
        if(cnt==p)
        return temp->data;
        temp=temp->next;
    }
    return -1;
}
//frequency in a linked list
int freq(Node *headref,int x)
{
    Node *temp=headref;
    int cnt=0;
    while(temp->next!=NULL)
    {
        if(temp->data==x)
         cnt+=1;
         temp=temp->next;
    }
    return cnt;
}
int palind(Node *headref,int n)
{
    int p=n/2;
    Node *first=head;
    Node *second=head;
    int q=1;
    while(p--)
    {
         cout<<second->data;
        second=second->next;
      
    }
     second=second->next;
    int k=n/2;
    while(k--)
    {
        if(first->data!=second->data)
        {
            q=0;
            break;
        }
        else
        {
            first=first->next;
            second=second->next;

        }
    }
    return q;
}
bool Is_Palindrome(Node* head){
         
       
        Node* temp= head;
 
       stack <int> st;
  
 
       
    
        while(temp != NULL){
                st.push(temp->data);
 
                
                temp=temp->next;
        }
        while(head != NULL ){
             int k=st.top();
             st.pop();
            if(head -> data != k){
                return false;
            }
 
           head=head->next;
        }
 
return true;
}

//reversing linked list
Node * reverse(Node  *s,Node *headref,int q)
{
    Node *p,*c,*n;
    p=NULL;
    c=headref;
    n=headref;
    Node *max;
    Node *t=headref;
    int cnt=0;
    while(n!=0)
    {
        cnt+=1;
        n=n->next;
       // cout<<n<<endl;
        c->next=p;
       // cout<<c->next<<endl;;
        p=c;
        //cout<<p<<endl;
        c=n;
        if(cnt==q)
        {
          max=n;
        n=NULL;
        }
        //cout<<c<<endl;
        headref->next=max;
        
    }
    if(headref==head)
     head=p;
     else
     s->next=p;
     return p;
    
} 
int main()
{
    
    //  freopen("input.txt", "r", stdin); 
    // freopen("output.txt", "w", stdout);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    
   /* Node *second=NULL;
    Node *third=NULL;

    head=new Node();
    second=new Node();
    third =new Node();
    head->data=1;
    head->next=second;
    second->data=3;
    second->next=third;
    third->data=4;
    third->next=NULL;*/


 
    /*int ch;
    cin>>ch;
    while(ch)
    {
        newnode=new Node();
        int a;cin>>a;
        newnode-> data=a;
        newnode->next=0;
        if(head->next==0)
        {
            head->next=newnode;
            temp=newnode;
        }
        else
        {
            temp->next=newnode;
            temp=newnode;
        }
        cin>>ch;
        if(ch)
         continue;
        else
         break;
    }*/
    ll n;cin>>n;
    ll k;cin>>k;push(&head,k);
    for(ll i=0;i<n-1;i++)
    {
        cin>>k;
        inserte(head,k); 
    }
    if(Is_Palindrome(head)) cout<<"YES"<<'\n';
    //cout<<palind(head,n);

    
    //push(&head,2);
    //for(int i=10;i>=6;i--)
    //{
    //    push(&head,i);
    //}
    
    //insertb(&head,0);
  


    //print(head);
    /*for(int i=0;i<10;i++)
    {
       
    insertp(head,i+3);
    
    }
    //inserte(head,5);
    print(head);
    deletee(&head);
    */

  
  //  print(head);
    
//     cout<<endl;
//     //int d=count(head);
//     //reverse(head,head,2);
//     //print(head);
//    // cout<<endl;
//     Node *f=head;
//     Node *t=f->next;
//    // cout<<t->next->data<<endl;
//     reverse(f,f,4);

//     print(head);
//     Node *temp=head->next;
//     cout<<endl;
//     //cout<<t->next->data<<endl;
//     f=f->next;
//    reverse(f,f,4);
//     print(head);
//     cout<<endl;
    
//     cout<<f->data;
//     //cout<<search(head,5);
//     //cout<<count(head);
//     //cout<<getn(head,(k+1)/2);
   
  
   
     return 0;

}
