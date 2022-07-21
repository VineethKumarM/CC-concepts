#include <bits/stdc++.h>
using namespace std;
class que{
stack<int> st1;
stack<int> st2;
public:
void push(int p){
st1.push(p);
}
int pop(){
if(st1.empty() && st2.empty()){
return -1;
}
if(st2.empty()){
while(!st1.empty()){
st2.push(st1.top());
st1.pop();
}
}
int top = st2.top();
st2.pop();
return top;
}
int empty(){
if(st1.empty() && st2.empty()){
return 1;
}
else
return 0;
}
};
int main(){
que qu;
cout<<"Enter NO.of Elements:"<<endl;
int n;
cin>>n;
cout<<"Enter the elements:"<<endl;
for(int i=0;i<n;i++)
{
  int k;
  cin>>k;
  qu.push(k);
}
cout<<"Elements of Queue"<<endl;
for(int i=0;i<n;i++)
cout<<qu.pop()<<endl;
return 0;

}