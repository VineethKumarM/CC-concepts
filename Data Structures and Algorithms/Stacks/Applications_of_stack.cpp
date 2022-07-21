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
vi Next_greater_element(vi v)
{
    vi ans;
    sti st;
    int n=v.size();
    for(int i=n-1;i>=0;i--)
    {
        //If stack is empty then push -1 to the ans vector
        if(st.empty()) ans.pb(-1);
        //if st.size()?>0 and top of stack is greater than current element of vector then
        //push it into the stack
        else if(st.size()>0 and st.top()>v[i]) ans.pb(st.top());
        //if size of stack>0 and st.top()<v[i] then pop out all the elements until the top
        //is greater than current element
        else if(st.size()>0 and st.top()<v[i])
        {
            while(st.size()>0 and st.top()<=v[i])
             st.pop();
             //If the while loop ended due to empty stack then push -1 to ans vector as no other e
             //element exists
             if(st.size()==0) ans.pb(-1);
             //If the while loop breaked since we found the greater element then push the top element
            //into vector
             else ans.pb(st.top());
        }
        //As usual push the array elemnnt into stack
        st.push(v[i]);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
//Next greater element from left side
vi Next_Greater_to_left(vi v)
{
    vi ans;
    sti st;
    int n=v.size();
    for(int i=0;i<n;i++)
    {
        if(st.empty()) ans.pb(-1);
        else if(st.size()>0 and st.top()>=v[i]) ans.pb(st.top());
        else if(st.size()>0 and st.top()<v[i])
        {
            while(st.size()>0 and st.top()<=v[i])
             st.pop();
            if(st.size()==0) ans.pb(-1);
            else ans.pb(st.top());
        }
      st.push(v[i]);
    }
    return ans;
}
//Next smaler element from left
vi Next_smaller_to_left(vi v)
{
    vi ans;
    sti st;
    int n=v.size();
    for(int i=0;i<n;i++)
    {
        if(st.empty()) ans.pb(-1);
        else if(st.size()>0 and st.top()<=v[i]) ans.pb(st.top());
        else if(st.size()>0 and st.top()>v[i])
        {
            while(st.size()>0 and st.top()>=v[i])
             st.pop();
             if(st.empty()) ans.pb(-1);
             else ans.pb(st.top());
        }
        st.push(v[i]);
    }
    return ans;
}
vi Next_smaller_to_right(vi v)
{
    sti st;
    vi ans;
    int n=v.size();
    for(int i=n-1;i>=0;i--)
    {
        if(st.empty()) ans.pb(-1);
        else if(st.size()>0 and st.top()<=v[i]) ans.pb(st.top());
        else if(st.size()>0 and st.top()>v[i])
        {
            while(st.size()>0 and st.top()>v[i]) st.pop();
            if(st.empty()) ans.pb(-1);
            else ans.pb(st.top());
        }
        st.push(v[i]);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
//Stock Span Probelm
//This problem is a variation of next greater element from left side but here we have to store
//the indices
vi Stock_Span_Prob(vi v)
{
   vi ans;
   spii st;
   int n=v.size();
   for(int i=0;i<n;i++)
   {
       if(st.empty()) ans.pb(-1);
       else if(st.size()>0 and st.top().first>v[i]) ans.pb(st.top().second);
       else if(st.size()>0 and st.top().first<=v[i])
       {
           while(st.size()>0 and st.top().first<=v[i])
           st.pop();
           if(st.empty()) ans.pb(-1);
           else ans.pb(st.top().second);
       }
       st.push({v[i],i});
   }
   return ans;
}
//Max Area of Histogram
//In this approach we caluclte the right smallest element which is smaller than current index
//as from this bar we can't make any rectangle
//For normal caluclation rse we assign -1 if there is no smaller element is there
//but here we assign a pseudo pillar of height 0 at index n(as 0 based index n-1 pillars height
//was given
//Similarly we caluclte the left smallest element which is smaller than current index
//as beyond this bar we cant make any rectangle
//Similarly in the case of rse  we assign -1 in this case lse
//From the left and right indices we can get the width of each rectangle for that particular \
//height as width[i]=right[i]-left[i]-1;
vi Right_bar(vi v)
{
    spii st;
    vi ans;
    int n=v.size();
    for(int i=n-1;i>=0;i--)
    {
        if(st.empty()) ans.pb(n);
     //Assigning n value in place of -1 on case of rse
        else if(st.size()>0 and st.top().first<v[i]) ans.pb(st.top().second);
        else if(st.size()>0 and st.top().first>=v[i])
        {
            while(st.size()>0 and st.top().first>=v[i])
            st.pop();
            if(st.size()==0) ans.pb(n); //Same approach as of above
            else ans.pb(st.top().second);
        }
        st.push({v[i],i});
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
vi Left_bar(vi v)
{
    spii st;
    vi ans;
    int n=v.size();
    for(int i=0;i<n;i++)
    {
        if(st.empty()) ans.pb(-1);//Assignimg the pseudo pillar of -1 in the case of lse
        else if(st.size()>0 and st.top().first<v[i]) ans.pb(st.top().second);
        else if(st.size()>0 and st.top().first>=v[i])
        {
            while(st.size()>0 and st.top().first>=v[i])
            st.pop();
            if(st.size()==0) ans.pb(-1);
            else ans.pb(st.top().second);
        }
        st.push({v[i],i});
    }
    return ans;
}
int Max_Area_of_Histogram(vi v)
{
    int n=v.size();
    //For each case width storing
    vi width(n);
    //For the right_bar indexes
    vi right=Right_bar(v);
    //For the left bar indices
    vi left=Left_bar(v);
    //width caaluclation
    for(int i=0;i<n;i++) width[i]=right[i]-left[i]-1;
    int ans=0;
    //Finding max area
    for(int i=0;i<n;i++) ans=max(ans,(v[i]*width[i]));
    return ans;
}
//The Binary matrix area is the maximum area covered by the rectangle made by 1's
//Since we know how to find for the single array using max area of histogram
//We try to convert the 2d array binary matrix to 2d array by temp vector by the following 2 steps
//Step 1:For each row as soon as we counter the 1 we will increase the building height by 1
//Step2:For each row if we encounter the building height to be zero then we will that temp vector to be zero
//Here note that we are not decreasing the current building height we are making that element to be 0
//as we buildings are not on ground level
int Max_Binary_Matrix_Area(vii M)
{
    int n=M.size();
    vi temp(n,0);
    int ans=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(M[i][j]==0)
             temp[j]=0;
             else
             temp[j]+=M[i][j];
        }
       ans=max(ans,Max_Area_of_Histogram(temp));
    }
    return ans;
}
int Rain_Water_Trapping_Area(vi v)
{
    int n=v.size();
    vi Maxr(n);
    vi Maxl(n);
     int sum_area=0;
    /// int Max=v[0];
    Maxl[0]=v[0];
    //Here we will try to find the maximum element to the left of that subarray of current element
    for(int i=1;i<n;i++)
    {
       Maxl[i]=max(Maxl[i-1],v[i]);
    }
    //Max=v[n-1];
    Maxr[n-1]=v[n-1];
    //Here we will try to find the maximum element to the right subarray of each elemnt
    for(int i=n-2;i>=0;i--)
    {
        Maxr[i]=max(Maxr[i+1],v[i]);
    }
    //cout<<Maxl[4];
    for(int i=0;i<n;i++)
    //The area trapped will be differnce min of both Maxl and Maxr and  height of that element
      sum_area+=min(Maxl[i],Maxr[i])-v[i];
    return sum_area;
}
//Implementing the minstack using extra space of stack
sti stk;//origibal stack
sti sstk;//supported stack
//Here we will form 3 functions for pushing ,popping and getting the min elemnt of the stack
//This user define function is made inorder to put data into supprted stack correctlu
void push_min_stk(int data)
{
    stk.push(data);//As usual we push the data into original stack
    //If the supported stack is empty or the inputtig data is less than the supported stack
    //top then we will push the data into supported stack alsoas we find new minimum of the stack
    if(sstk.size()==0 or data<=sstk.top()) sstk.push(data);
    //One main thing here if the data ==sst.top() in that case also we are pushing the data
    //If we once this 2nd;s 15 from the stack then we will also pop from the su[roted stack
    //Then the 15 in the stack will be gone in supporeted stack but another 15 is still present in the
    //original stock
    //If we call fet min te=he top of the sst contains another element which is the not the case
}
int pop_min_stack()
{
    //If the original stack is empty then we will return -1 as we cannot pop the stack
    if(stk.empty()) return -1;
    //Let's store the top of the stack in ans
    int ans=stk.top();
    //As usual pop the top element from the original stack
    stk.pop();
    //If the popped element is also present in the minimum then pop from the supported stack also
    //as the original stack no more contains this element
    if(ans==sstk.top()) sstk.pop();
    return ans;
}
int get_min()
{
    if(sstk.empty()) return -1;
    else return sstk.top();
}
//Implementing min element using O(1) space
//In this case we build a relation between st.top() and min elemnt
int mini; 
void push_stack(int data)
{
    if(stk.empty())
    {
        //If stk is emoty then simply push the data and assign the data as min element
        stk.push(data);
        mini=data;
    }
    else
    {
        //Else if data<min then we dont push the data directly to the stack
        //Instead we 2*data-mini until now inorder to have a relation b/w the last two elements
        //and then we update the mini element as stack
        if(data<mini)
        {
            stk.push(2*data-mini);
            mini=data;
        }
        else stk.push(data);
    }
}
int top_stack()
{
    //If stk is emoty then return -1
    if(stk.empty()) return -1;
    //In that stack if stk=.top() is less than mini that means it is a corrupted value 
    //so we should return the mini as inplace of this mini we have pushed the corrupted value
    else if(stk.top()<mini) return mini;
    //If it is not the case then we simply retuern the stl.top()
    else return stk.top();
}
void pop_stack()
{
    //Incase of pooping if stk.top()is less than mini then it implies it is a corrupted value t
    //and here we are removing the min elemnt itself so we should get the last min value 
    //it can be dine by 28mini-stk,top()
    //then we will update this value to min elemt
    if(stk.top()<mini)
    {
        mini=2*mini-stk.top();
        stk.pop();
    }
    //if we are not poopping the small elemnt then simply pop the stack
    else stk.pop();
}
int get_min_element()
{
    //if stk is empty then return -1
    if(stk.empty()) return -1;
    //else return the mini eleme3nt of the stack until now
    else return mini;
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int n;cin>>n;
    // vi v(n);
    // v.pb(6); v.pb(2);v.pb(5);v.pb(4);v.pb(5);
    // v.pb(1);v.pb(6);
    // vi ans=Stock_Span_Prob(v);
    // for(int i=0;i<ans.size();i++)
    // if(ans[i]==-1) cout<<-1<<' ';
    // else cout<<i-ans[i]<<' ';
     // cout<<Max_Area_of_Histogram(v);
    //  int n=4;
    //   vector<vector<int>> M( n , vector<int> (n, 0));
    //  for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>M[i][j];
      // for(int i=0;i<n;i++) for(int j=0;j<n;j++) cout<<M[i][j];
      //for(int i=0;i<n;i++) cin>>v[i];
    // cout<<Max_Binary_Matrix_Area(M);
    push_stack(7);
     push_stack(8);
      push_stack(1);
       push_stack(9);
       pop_stack();
       pop_stack();
       cout<<mini;
    
    //cout<<get_min();
    //cout<<Rain_Water_Trapping_Area(v);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}