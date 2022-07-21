#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vii vector<vector<int>>
#define vs vector<string>
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
     int *left;
     int* right;
}root;
//Height of Binary Tree using Recursion
//Here the hypothesis is that let us assume Trree_Height function will return the height of 
//the below part of the node
//Then at rhe node we will check for both left and right nodes then we will select the 
//maximum of both lh and rh add 1 to the present node height as now 1 layer is increased
int Tree_Height(Node *s)
{
    if(s==NULL) return 0;
    // // int rh=Tree_Height(s.right);
    // // int lh=Tree_Height(s.left);
    // return 1+max(lh,rh);
    return 1;

}
//This function inserts an element in a correct position
//Here the base codnition is that if the size of vector is 0 or the last elemnt of the 
//vector is greater than we directly push back the element at last and return the function
//as the elemnt cannot be inserted in lesser elements
//If that is not the case we will store last value and pop back and we call the insert function
//vector to insert at correct position
//Then as the remaining vector is correctly place we will place this larger element at last
void Insert_at_pos(vi &v,int val)
{
    if(v.size()==0 or v[v.size()-1]<=val) {v.pb(val);return;}
    int last=v[v.size()-1];
    v.pop_back();
    Insert_at_pos(v,val);
    v.pb(last);
    return;
}
//This function sorts the vector
//The base condition is that of the size of vector is 1 then the vector will be sorted as 
//only one element is present
//if that is not the case then we will pop the last element and intution is that
//sort function returns the remaining vector as sorted one
//then we will insert the last position at correct place by calling the insert function
void Recursion_Sort(vi &v)
{
    if(v.size()==1) return;
    int last=v[v.size()-1];
    //Here we are popping the element 
    v.pop_back();
    //Sort the remaining vector
    Recursion_Sort(v);
    //Then we will place the pooped element at correct position
    Insert_at_pos(v,last);
}
void Insert_in_Stack(sti &st,int val)
{
    if(st.size()==0 or st.top()<=val){st.push(val);return;}
    int last=st.top();
    st.pop();
    Insert_in_Stack(st,val);
    st.push(last);
}
void Sort_Stack(sti &st)
{
    if(st.size()==1) return;
    int last=st.top();
    st.pop();
    Sort_Stack(st);
    Insert_in_Stack(st,last);
}
//Deletion of middle element of the stack
//Here we will maintain a counter value and we will pop and call the function and increment the
//cnt.Until the cnt value reaches size/2 we keep popping then we return the function
//and we will push the poopped elements except the middle element
void Delete_mid(sti &st,int size,int cnt)
{
    if(size/2==cnt) {st.pop();return;}
    int top=st.top();
    st.pop();
    Delete_mid(st,size,cnt+1);
    st.push(top);
}
void Insert_at_bottom(sti &st,int val)
{
    if(st.size()==0) {st.push(val);return;}
    int top=st.top();
    st.pop();
    Insert_at_bottom(st,val);
    st.push(top);
}
void Reverse_stack(sti &st)
{
    if(st.size()==0) {return;}
    int top=st.top();
    st.pop();
    //Reverse the remaining stock then we wuill insert the pooped element at the bottom of
    //the stack 
    Reverse_stack(st);
    //Inserts the element at the bottom of the stack
    Insert_at_bottom(st,top);
}
//Kth symbol in a grammar problem
//Here we will generate a grammar in which n represents no.of rows and k column
//In each update if the former element is 1 write 10 else if it is 0 then write in 01
//in next row
//If we do this pattern we can observe that half part of the string is same as before string
//and remaining half part is the last rows string complement
//Note book
int Kth_symbol(int n,int k)
{
    //Base condition
    if(n==1 and k==1) return 0;
    //If k is less than half
    if(k<=n/2) return Kth_symbol(n-1,k);
    //If k is greater than half
    else return !Kth_symbol(n-1,k-n/2);
}
//Tower of Hanoil problem
//s=source
//d=destination
//h=helper
//n=no.of plates
//In this tower of hanoi problem the induction hypothesis is first move n-1 disks from
//source to helper
//then the next step will be moving the nth disk from source to destination 
//and then again move the disks from helper to source
void Tower_of_Hanoi(int s,int d,int h,int n)
{
    //Base ccondition is that move directly from source to destination if thr no.of disks are 1
    if(n==1){cout<<s<<"->"<<d<<'\n';return;}
    //Move the (n-1) disks from source to helper(Here parameters order changed)
    Tower_of_Hanoi(s,h,d,n-1);
    //Then print the step of moving from source to destination 
    cout<<s<<"->"<<d<<'\n';
    //Then again move n-1 disks from helper to destination
    Tower_of_Hanoi(h,d,s,n-1);
} 
vs v;
//If we have to print unique subsets then we will use a vector of string s and using map 
//we cab take care of duplicates
void Subset_Generation(string inp,string osf)
{
    if(inp.size()==0) {/*cout<<osf<<'\n';*/ v.pb(osf);return;}
    char first=inp[0];
    //Here we erasing the inp size so that inp size becomes reduced
    inp.erase(inp.begin()+0);
    Subset_Generation(inp,osf);
    Subset_Generation(inp,osf+first);
}
void Permuation_with_spaces(string inp,string osf)
{
    if(osf.size()==0){osf+=inp[0];inp.erase(inp.begin()+0);Permuation_with_spaces(inp,osf);return;}
    if(inp.size()==0) {cout<<osf<<'\n';return;}
    char ch=inp[0];
    inp.erase(inp.begin()+0);
    Permuation_with_spaces(inp,osf+' '+ch);
    Permuation_with_spaces(inp,osf+ch);
    return; 
}
//In this problem we have to permute with the given strimg with lower and upper case letters
//Input string will always will always be in lowe case format
void Permute_with_case_changes(string inp,string osf)
{
    if(inp.size()==0) {cout<<osf<<'\n';return;}
    char ch=inp[0];
    inp.erase(inp.begin()+0);
    //pushing back the same case letter in osf
    Permute_with_case_changes(inp,osf+ch);
    //Changing the lowercae letter to upeer case letter using toupper in bilit function
    //Since toupper returns the int we have to do typecasting
    Permute_with_case_changes(inp,osf+(char)toupper(ch));
}
void Permute_with_any_case_changes(string inp,string osf)
{
    if(inp.size()==0) {cout<<osf<<'\n';return;}
    char ch=inp[0];
    inp.erase(inp.begin()+0);
    if(ch>='a' and ch<='z')
    {
        Permute_with_any_case_changes(inp,osf+ch);
        Permute_with_any_case_changes(inp,osf+(char)toupper(ch));
    }
    else if(ch>='A' and ch<='Z')
    {
         Permute_with_any_case_changes(inp,osf+ch);
        Permute_with_any_case_changes(inp,osf+(char)tolower(ch));
    }
    else
    Permute_with_any_case_changes(inp,osf+ch);

}
void Geneate_Balanced_Paranthesis(int open,int close,string osf)
{
    //If we have used both the opening brackets and closing brackets then we will output the string
    if(open==0 and close==0) {cout<<osf<<'\n';return;}
    //Since we can add '(' at any point of time in osf 
    //So we can add until the open value becomes 0
    if(open){Geneate_Balanced_Paranthesis(open-1,close,osf+'(');}
    //We can only use closing bracket when there is an extra oprn bracket in string
    //that havent balnced yet
    //Since no.of open bracktes > no.of close brackets therefore the remaing usable open value 
    //must be less than remaining close value as there are remaining usable open and close 
    //brackets 
    if(close>open){Geneate_Balanced_Paranthesis(open,close-1,osf+')');}
} 
//Print N digits binary numbers having more than 1's or 0's for any prefix
//It means that for any prefix substring(starting from 0 to i where(i<n) for any i the
//count of 1 s sholud be more than the count of zeros )
//This probem is similar to the above condition
//here we can add 1 to osf at anypoint of time as increase of current 1;s doesnt matter
//If we have to add 0 to the osf then we can add only then when the current ones in the string 
//must be atleast one greater than count of zeroes
//As in the worst case they can be equal so if we maintain a minimum difernce of 1 by adding
//1 0 to it they  make them equal in worst case in all other cases
//the count of 1 s will always be less than 0
void N_bit_binary_prefix_1_greater(int n,int one,int zero,string osf)
{
    //As we are decrementing one at each step of adding a s=digit in osf
    //we will return the string when n becomes 0
    if(n==0){cout<<osf<<'\n';return;}
    //Adding 1 to the string doesnt violate the condition at any time
    N_bit_binary_prefix_1_greater(n-1,one+1,zero,osf+'1');
    //if we have to add 0 then we should have atleast one minimum differnce
     if(one>zero) N_bit_binary_prefix_1_greater(n-1,one,zero+1,osf+'0');
    return;
}
//In this last Joseph problem n people are standing in a circular way
//A person starting at index kill the person at 7 persons and then from that 7 persons
//another one is killed 
//And this cycle repeats and at last one person will remain
//So by IBH method in recurive problem the base condition willl be v.size()==1 then we 
//we can directly ans as v[0]
//If that is not the caase kill the persom as per the given value and use moduo inorder to avoid overflow cond
//ition then and remove the element from  the array and update index and use erase function 
//inorder to obtain new vectpr from the deleted one then again kill the person
//recurisvely  
void Last_Joseph(vi v,int n,int k,int ind,int &ans)
{
    if(v.size()==1) {ans=v[0];return;}
    ind=(ind+k)%(v.size());
    v.erase(v.begin()+ind);
    Last_Joseph(v,n,k,ind,ans);
    
}
int main()
{ 
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout); 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vi v;
    v.pb(1);v.pb(2);v.pb(6);v.pb(3);v.pb(7);v.pb(4);v.pb(10);
    sti st;
    st.push(1);st.push(2);st.push(6);st.push(7);st.push(4);st.push(10);st.push(12);
    // Recursion_Sort(v);
    // // for(int i=0;i<.size();i++) cout<<v[i]<<' ';
    //  Reverse_stack(st);
    // while(!st.empty())
    // {
    //     cout<<st.top()<<' ';
    //     st.pop();
    // }
     //cout<<Kth_symbol(4,4);
     //Tower_of_Hanoi(1,3,2,3);
     string s="a1B2";
    // Subset_Generation(s,"");
    //map<string,int> mp;
    // for(int i=0;i<v.size();i++)
    // 
    //     mp[v[i]]=0;
    // }
    //Permute_with_any_case_changes(s,"");
    //Geneate_Balanced_Paranthesis(4,4,"");
     //N_bit_binary_prefix_1_greater(4,0,0,"");
       //Permute_with_case_changes(s,"");
       vi vec;
       for(int i=1;i<101;i++)v.pb(i);
       int ans=0;
       Last_Joseph(v,100,1,0,ans);
       cout<<ans;
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}
 
