#include<bits/stdC++.h>
using namespace std;
class Node
{
    public:
    int data;
    Node *next;
    Node *prev;

} *head=NULL;
Node *tail;
//pushing into double linked list
void push(Node *h,int k)
{
    Node *newnode;
    Node *temp;
    newnode=new Node();
    newnode->data=k;
    if(head==NULL)
    {
        head=newnode;
        temp=newnode;
        tail=newnode;
    }
    else
    {
        temp->next=newnode;
        newnode->prev=temp;
        temp=newnode;
        tail=newnode;
    }

}
//printing of linkedlist
void print(Node* n)
{
    while(n!=0)
    {
        cout<<n->data<<" ";
        n=n->next;
    }
}
//insert at begin
void insertb()
{
    Node *newnode;
    newnode=new Node();
    cin>>newnode->data;
    newnode->next=NULL;


    newnode->prev=NULL;
    newnode->next=head;
    head->prev=newnode;
    head=newnode;
}
void inserte()
{
    Node *newnode;
    newnode=new Node();
    cin>>newnode->data;
    newnode->next=NULL;

    
    newnode->prev=tail;
    newnode->next=0;
    tail->next=newnode;
    tail=newnode;
}
//insert at p
void insertp(int p)
{
    Node *temp=head;
    int i=1;
    while(i<p-1)
    {
        temp=temp->next;
        i++;
    }
    Node *newnode;
    newnode=new Node();
    cin>>newnode->data;
    newnode->prev=temp;
    newnode->next=temp->next;
    temp->next=newnode;
    newnode->next->prev=newnode;
    
}
//Deletion at begining
int deleteb()
{
    Node *temp=head;
    head=head->next;
    head->prev=NULL;
    int k=temp->data;
    free(temp);
    return k;
}
//deletion at end
void deletee()
{
    Node *temp=tail;
    //tail=tail->prev;
    tail->prev->next=NULL;
    tail=tail->prev;
    free(temp);
}
//deletion at position p
void deletep(int p)
{
    Node *temp=head;
    int i=1;
    while(i<p-1)
    {
        temp=temp->next;
        i++;
    }
    temp->next->next->prev=temp;
    temp->next=temp->next->next;

}
//Reverse the linked list
void reverse()
{
    Node *temp=head;
    Node *temp1=temp;
    while(temp!=NULL)
    {
      temp1=temp1->next;
       temp->next=temp->prev;
       temp->prev=temp1;
       temp=temp1;
    }
    head=tail;
}
int main()
{
 
  
     freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
     push(head,3);
     push(head,4);
     push(head,5);
     print(head);
     cout<<endl;
     insertb();
     insertb();
     print(head);
     cout<<endl;
     inserte();
     print(head);
     cout<<endl;
     insertp(5);
     print(head);
     cout<<endl;
      cout<<deleteb();
    //  cout<<endl;
    //  print(head);
    //  cout<<endl;
    //  deletee();
    //  print(head);
    //   cout<<endl;
    //   deletep(3);
    //   print(head);
      reverse();
      cout<<endl;
      print(head);
      print(head);
   
     return 0;

}
