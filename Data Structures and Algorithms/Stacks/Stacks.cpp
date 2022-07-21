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
//Infix to Post fix Conversion
//Declaring the precision values
int Prec(char ch)
{
    if(ch=='^') return 3;
    if(ch=='/') return 2;
    if(ch=='*') return 1;
    if(ch=='+' || ch=='-') return -1;
    else return -2;
}
//Converts the given expression to postfix expression using stacks 
string Post_Fix_Conv(string s)
{
    stack<char> st;
    string res;
    for(int i=0;i<s.size();i++)
    {
        char ch=s[i];
        //In case the ch is an operand  we will directly add to the resultant string
        if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || (ch>='0' and ch<='9'))
         res+=ch;
         //In case it it  leftward parenthesis then we will directly push into stack
        else if(ch=='(')
            st.push(ch);
        //If it was rightward paranthesis then we will pop the elemnts from the stack unti
        //we get a leftward paranthesis
        else if(ch==')')
        {
            while(!(st.top()=='('))
            {
                res+=st.top();
                st.pop();
            }
            st.pop();
        }
        else 
        {
            //This case is if any operator is scanned then we will check the precision and 
            //pop and push as per their respective precision values
            while(!(st.empty()) and (Prec(ch)<=Prec(st.top())))
            {
                res+=st.top();
                st.pop();
            }
            st.push(ch);
        }  
    }
    while(!st.empty())
    {
        res+=st.top();
        st.pop();
    }
    return res;
}
//Postfix or Prefix expression to Infix expression
bool Is_operator(char x)
{
    switch(x)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        return true;
    }
    return false;
}
//This function is for prefix to infix conversion
//If we want to do for post fix then simply start from string s[0];
//whuch we started from length -1;
string Pre_to_Infix(string s)
{
     stack<string> st;
     for(int i=s.size()-1;i>=0;i--)
     {
         char ch=s[i];
         if(Is_operator(ch))
         {
             string temp1=st.top();st.pop();
             string temp2=st.top();st.pop();
             //Making the new string
             string temp3="("+temp1+ch+temp2+")";
             st.push(temp3);
         }
         else
         {
             st.push(string(1,ch));
         }
     }
     return st.top();
}
string Pre_to_Post(string s)
{
    stack<string> st;
    for(int i=s.size()-1;i>=0;i--)
    {
        char ch=s[i];
        if(Is_operator(ch))
        {
            string temp1=st.top();st.pop();
            string temp2=st.top();st.pop();
            string temp3=temp1+temp2+ch;
            st.push(temp3);
        }
        else
        {
            st.push(string(1,ch));
        }
    }
    return st.top();
}
string Post_to_Pre(string s)
{
    stack<string> st;
    for(int i=0;i<s.size();i++)
    {
        char ch=s[i];
        if(Is_operator(ch))
        {
            string temp1=st.top();st.pop();
            string temp2=st.top();st.pop();
            string temp3=ch+temp2+temp1;//Here is the diffence betweeen post to pre and
            //pre to post
            st.push(temp3);
        }
        else
        {
            st.push(string(1,ch));
        }
    }
    string ans="";
    while(!st.empty())
    {
        ans+=st.top();
        st.pop();
    }
    return ans;
}
//Span count Problem
//In this problem we have to tell the array the no.of elements which are lesser than 
//the current index element
vi Span_Count(vi price)
{
    int n=price.size();
    stack<int> st;
    //ans array for n values distance
    vi ans(n);
    //We will push the index as 0 into the stack
    st.push(0);
    //Intialsing the first element dist to be 1
    ans[0]=1;
    for(int i=1;i<n;i++)
    {
        //In this while loop we are popping out all the elemnts until we get any index which
        //is higher than any present index value
        //we again put this last index in stack inorder to check for further values
        while(!(st.empty()) and (price[i]>=price[st.top()]))
         st.pop();
         //If the stack became empty then all the elements are lesser than the present elemnt
          ans[i]=(st.empty())?i+1:i-st.top();
          //We are pushing the current value
          st.push(i);
    }
    return ans;
}
//Function to return whether brackets are balanced or not
bool Is_brackets_balance(string s)
{
    stack<char> st;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='(' || s[i]=='[' || s[i]=='{')
         {st.push(s[i]); continue;}
         //If the left ward brackets are coming we are just simply pushing into the stack 
         //if there is no leftward bracket and the stcak is empty then also we will return  fslde
         else if(st.empty()) return false;
         else   
         {
             //case by case checking
             switch(s[i])
                {
                    case ')':
                           {
                               if(st.top()!='(') return false;
                               else { st.pop();break;}
                           }
                    case '}':
                           {
                               if(st.top()!='{') return false;
                               else {st.pop();break;}
                           }
                    case ']':
                          {
                              if(st.top()!='[') return false;
                              else {st.pop();break;}
                          }     
                }
         }
    }
    return true;
}
//Next greater element
void Next_great_ele(vi v)
{
    stack<int> st;
    //vi ans(v.size(),0);
    umpi mp;
    st.push(v[0]);
    for(int i=1;i<v.size();i++)
    {
       if(st.empty()) st.push(v[i]);
       //Until top of the elemnt becomes greater we will cout the v[i]
       //We can avoid the cout by mapping the elemnets
       //cause we wont  get in correct order
       while(st.empty()==false and st.top()<v[i])
       {
           mp[st.top()]=v[i];
           st.pop();
       }
       st.push(v[i]);
    }
    while(!(st.empty()))
    {
        mp[st.top()]=-1;
        st.pop();
    }
    for(int i=0;i<v.size();i++)
    cout<<mp[v[i]]<<' ';
}
vi Next_freq_elem(vi v,vi freq)
{
    stack<int> st;
    vi ans(v.size(),0);
    //We have pushed the index 0;
    st.push(0);
    for(int i=1;i<v.size();i++)
    {
        //If the frequency of the current element is less than the top of the stack 
        //elemnt frequency of the stack
        if(freq[v[i]]<freq[v[st.top()]]) st.push(i);
        else 
        {
            //Popping out until the above condition satisfures
            while(!st.empty() and freq[v[i]]>freq[v[st.top()]])
            {
                ans[st.top()]=v[i];//Here in question it is given we have to input the element
                //which has greater element thats why we are assigning the value 
                st.pop();
            }
        // After popping all less elements pushing the present index
             st.push(i);
        }
    }
    while(!(st.empty()))
    {
        //Assigning the remaining the elements as -1
       ans[st.top()]= -1;
       st.pop();
    }
    return ans;
}
//Count no.of greatest elements using dp and stack
vi Indexing(vi v)
{
    stack<int> s;
    vi next(v.size(),0);
    //Here we are pushing the first index of the vector
    s.push(0);
    for(int i=1;i<v.size();i++)
    {
        while(!(s.empty()))
        {
            int cur=s.top();
            //If the current elemnt is greater than the top of the stack;s elemnt then
            //assign next[cur] to ptresent value
            if(v[i]>v[cur])
            {
             next[cur]=i;s.pop();
            }
            else break;
        }
        s.push(i);   
    }
    while(!s.empty())
    {
        next[s.top()]=-1;
        s.pop();
    }
    return next;
}
int count_nge(vi v,int ind)
{
    vi next=Indexing(v);
    vi dp(v.size());
    //Here we atre declaring the dp and traveesing from backwards
    for(int i=v.size()-2;i>=0;i--)
    {
        if(next[i]==-1) dp[i]=0;
        else
        //dp[i]=1+dp[next[i]]since we are including the next element also and checking how
        //greater elements are there for the next of the current elemnt then we will gie the ans
        //as 1+dp[next[i]] Here 1 is added because since we the next element is also greter
        //so we are addding the element 1
        dp[i]=1+dp[next[i]];
    }
    //return the dp[index of the given query]
    return dp[ind];
}
//More Simple approach
int count_nge_simple(vi v,int ind)
{
    stack<int> s;
    int n=v.size();
    s.push(n-1);
    vi next(v.size());
    next.pb(0);
    for(int i=(n-2);i>=0;i--)
    {
      while(!s.empty() and v[i]>=v[s.top()])
       s.pop();
       if(s.empty()) next.pb(0);
       else
       {
           next.pb((next[n-s.top()-1])+1);
       }
       s.push(i);
    }
    reverse(next.begin(),next.end());
    return next[ind];
}
//Max of L and R product
bool knows(int a,int b,vii M)
{
     return M[a][b];
}
int Find_Celebrity(int n,vii M)
{
    stack<int> s;
    for(int i=0;i<n;i++) s.push(i);
    while(s.size()>1)
    {
        int a=s.top();s.pop();
        int b=s.top();s.pop();
        if(knows(a,b,M)) s.push(b);
        else s.push(a);
    }
    if(s.empty()) return -1;
    int c=s.top();s.pop();
    for(int i=0;i<n;i++)
    {
        if(i!=c and (knows(c,i,M) and !knows(i,c,M))) return -1;
    }
    return c;

}

int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    stack<int> S1;
    stack<int> S2;
    // for(int i=0;i<10;i++) {S1.push(i);S2.push(10-i);}
    // //Here swap function used to swap the contents of both the stacks
    // S1.swap(S2);
    // while(!(S1.empty()))
    // {
    //     cout<<S1.top()<<' '<<S2.top()<<'\n';
    //     S1.pop();S2.pop();
    // 
//     S1.emplace(1);
//     S1.emplace(2);
// // cout<<S1.size();
//     int cnt=0;
//     while(!(S1.empty()))
//     {
//         cout<<S1.top()<<' ';
//         S1.pop();
//         cnt++;
//    }
    //Finding the size of the stack without using the stack
  // cout<<cnt;
    // string s;
    // cin>>s;
    // string res=Post_to_Pre(s);
    // cout<<res;
    // vi price(6);
    // for(int i=0;i<6;i++) cin>>price[i];
    // vi ans=Span_Count(price);
    // for(int i=0;i<6;i++) cout<<ans[i]<<' ';
//    int n;cin>>n; vi v(n);
//    for(int i=0;i<n;i++) cin>>v[i];
   //Next_great_ele(v);
//    int maxe=0;
//     for(int i=0;i<n;i++)
//     {
//        if(maxe<v[i]) maxe=v[i];
//     }
//     vi freq(maxe+1,0);
//     for(int i=0;i<n;i++) freq[v[i]]++;
//     vi ans=Next_freq_elem(v,freq);
//     for(int i=0;i<ans.size();i++) cout<<ans[i]<<' ';

   //for(int i=0;i<n;i++) cout<<ans[i]<<' ';
//    cout<<count_nge_simple(v,1);
     
    vector<vector<int>> M(4, vector<int>(4, 0));
     for(int i=0;i<4;i++)
     {
         for(int j=0;j<4;j++) cin>>M[i][j];
     } 
     cout<<Find_Celebrity(4,M);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}