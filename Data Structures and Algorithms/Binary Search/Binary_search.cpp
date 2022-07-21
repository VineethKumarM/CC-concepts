#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
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
int Binary_Search(vi v,int x)
{
    int start=0;
    int end=v.size()-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;//here we are not doing simply because to avoid overflow
        if(v[mid]==x) return mid;
        else if(x>v[mid]) start=mid+1;
        else end=mid-1;
    }
    return  -1;
}
int Binary_Search_Reverse(vi v,int x)
{
    int start=0;
    int end=v.size()-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;//here we are not doing simply because to avoid overflow
        if(v[mid]==x) return mid;
        else if(x>v[mid]) end=mid+1;
        else start=mid-1;
    }
    return  -1;
}
//In case if we dont know the array is sorted in ascending or descending order
int Order_search(vi v,int x)
{
    if(v.size()==1 and v[0]==x) return 0;
    else if(v[0]>v[1]) return Binary_Search_Reverse(v,x);
    else Binary_Search(v,x);
    return -1;
}
//This function will return a pair of fist and last occurences of element
pairi First_Last_Occurence(vi v,int x)
{
    int start=0;
    int end=v.size()-1;
    int res1=-1,res2=-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        //Here is the change in normal binary search 
        //Once we find the v[mid] equal to x then we will equal end=mid-1 inorder to search the 
        //left part of that element we store the present mid value in res1
        if(v[mid]==x) {res1=mid;end=mid-1;}
        else if(v[mid]<x) {start=mid+1;}
        else end=mid-1;
    }
    start=0;end=v.size()-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        //in this case for the last occurence we check the right part of the array
        //assigns the occurence index to res2
        if(v[mid]==x) {res2=mid;start=mid+1;}
        else if(v[mid]<x) {start=mid+1;}
        else end=mid-1;
    }
    //If we have found the elemnt then return pair
    if(res1!=-1 and res2!=-1)
    return {res1,res2};
    //if no element found then we return -1 -1
    else return {-1,-1};
}
int Count_of_Elements_sorted(vi v,int x)
{
    pairi p=First_Last_Occurence(v,x);
    if(p.first!=-1)
    return p.second-p.first+1;
    else return -1;
}
//Finding no of times the array is sorted
//An array is rotated x times if first n eleemnt are palced at the end and n-x elemnt are in  front
int Find_Rotations_of_Array(vi v)
{
    //In this problem the index of minimum element will give the no of times array rotated
    int start=0;
    int n=v.size();
    int end=v.size()-1;
    while(start<=end) 
    {
        int mid=start+(end-start)/2;
        //Inorder to avoid overflow we will mod with n
        int prev=(mid+n-1)%n;
        int next=(mid+1)%n;
        //The given mid element can be decided whether it is a smaller elemnt or not by
        //comparing its two neighbours
        //If it smaller than v[mid-1] and v[mid+1] then that elemnt will be minimumof the element
        if(v[mid]<v[prev] and v[mid]<v[next]) return mid; 
        //Here the movement of us will be towards unsorted part as the unsorted part only contains
        //the smallest element will be contained in unsorted part
        //so here we compare the mid element with v[0] whether it is smaller or not
        //IF it is then the part is sorted then we make end as mid+1;
        else if(v[0]<v[mid]) start=mid+1;
        //Similarly if the right part is sorted then  move end to mid-1
        else if(v[mid]<v[n-1]) end=mid-1;
    }
    return -1;
}
int Search_in_Rotated_Array(vi v,int x)
{
    int flag=Find_Rotations_of_Array(v);
    int res1,res2;
    int start,end;
    start=0;
    end=flag-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(v[mid]==x) res1=mid;
        else if(v[mid]<x) start=mid+1;
        else end=mid-1;
    }
    if(res1==-1)
    {
      start=flag;
      end=v.size()-1;
     while(start<=end)
     {
        int mid=start+(end-start)/2;
        if(v[mid]==x) res2=mid;
     }
     return res2;
    }
   else return res2;
    
}
//Searching in  a nearly sorted array 
//By definition the nealy sorted array means if we the element position is at ith position
//in a normal sorted array then in nearly sorted array the element can be present at
//ith or(i-1)th or (i+1)th position in a nearly sorted array
int BS_in_Nearly_Sorted(vi v,int x)
{
    int start=0;
    int end=v.size()-1;
    int n=v.size();
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        //In normal binary search we only check the v[mid] but in this nearly sorted array 
        //we have to check mid-1,mid,mid+1 
        if(v[mid]==x) return mid;
        //Here we have to take care of the segmentation faults 
        //Sowe are keepin an extra condition in addition tothe check of element
        if(mid-1>=0 and v[mid-1]==x) return mid-1;
        if(mid+1<n and v[mid+1]==x) return mid+1;
        //Since we alreaduy checked the mid+1 element so we are shifting it to mid+2
        if(v[mid]<x) start=mid+2;
        if(v[mid]>x) end=mid-2;
    }
    return -1;
}
//Floor value of given element in a sorted array
//Here the floor value of a value is the maximum largest element thatis either equal or just
//smaller than the value in the given sorted array
int Floor_Value(vi v,int x)
{
    int start=0;
    int end=v.size()-1;
    //Here we make a tem value inorder to store the possible value 
    //if we get any better possible value than current res value then we will update it
    int res;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        //If the v[mid]==x then we found the exact value then we will return the value
        if(v[mid]==x) return v[mid];
        if(v[mid]<x)
        //Incaase if v[mid]<x then we got a less element than the given value 
        //Then it can be the possible value
        {
            //we store the v[mid] value in res as possible answer and move start to mid+1
            //to find the better value
            res=v[mid];
            start=mid+1;
        }
        else
        {
            //As usual binary serach if we v[mid]>x
            end=mid-1;
        }
    }
    return res;
}
int Ceil_Value(vi v,int val)
{
    int start=0;
    int end=v.size()-1;
    int res=-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(v[mid]==val) return v[mid];
        if(v[mid]>val)
        {
            res=v[mid];
            end=mid-1;
        }
        else start=mid+1;
    }
    //Checking res+1 index is in range of v.size() or  not
  return res;
}
char Find_Next_Alphabet(string s,char ch)
{
    int start=0;
    int end=s.size()-1;
    char res='#';
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(s[mid]==ch) start=mid+1;
        else if(s[mid]-'0'<ch-'0') start=mid+1;
        else
        {
            res=s[mid];
            end=mid-1;
        }
    }
    return res;
}
//Here we are given with an infinite sorted array
//We need to find the whether a givem element exists or not
//For approaching this problem we will intialsie the start and end with 0 and 2
//And in each binary search that we have done so far we can observe that the element if
//exists in an array then it should lie in between the start and end of the array
//For this problem since we dont know what to assign the value of end we will initailse it 
//with 2
//Then we keep on multiplying the end by 2 until we find v[mid]<x
//and update the start to previous end value
int Search_in_Infinite_Sorted_Array(vi v,int x)
{
    int start=0;
    int end=2;
    while(v[end]<x)
    {
        //If the v[end]<x then we havent found that element
        //then we update start to end
         start=end;
         //we update end as 2*end
       end*=2;
      
    }
    //Once we find the inrange values of start and end
    //then we wiil do the normal binary search
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(v[mid]==x) return mid;
        if(v[mid]<x) start=mid+1;
        else end-mid-1;
    }
    return -1;
}
int First_Occurence_in_Infinite_Sorted_Array(vi v)
{
    int start=0;
    int end=v.size()-1;
    while(v[end]!=1)
    {
        start=end;
        end*=2;
    }
    int res=-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(v[mid]==1) {res=mid;end=mid-1;}
        if(v[mid]==0) start=mid+1;
    }
    return res;
}
//In this problem we have to fing the min absolute differnce between any elemnt of sorted array
//and the given value
//Here two case arises 
//Case 1.when the given key is present in that sorted array then simply the mn=inimum diffence 
//will be 0
//Case 2.when the key is not present then the minimum differnce will come from 
//its ceil and floor value in the array
//So we will return the minimum absolute differnce between ceil and floor with the
//guven key value
int Min_Diffence_key(vi v,int key)
{
    //One way is to find ceil and floor value
    // int flag=Binary_Search(v,key);
    // //If flag==-1 means we haven't found the element
    // if(flag==-1)
    // {
    //     //floor value and ceil value
    //    int floor=Floor_Value(v,key);
    //    int ceil=Ceil_Value(v,key);
    //    //return the minum differnce
    //    return min(abs(key-floor),abs(key-ceil));
    // }
    // //Im case we found we will retun 0 value
    // else return 0;
    //Find if we observe that if the element is not present in array then at the end of 
    //the binary search the end value point to floor value index and star value point to index
    //of ceil value
    //So here we do a simple binary search
    int start=0;
    int end=v.size()-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        //In case if v[mid]==key then minimum differnce will be 0
        if(v[mid]==key) return 0;
        else if(v[mid]<key) start=mid+1;
        else end=mid-1;
    }
    //return the min absolute diffence
    return min(abs(v[start]-key),abs(v[end]-key));
}
//Peak Element finding in an unsorted array based on Binary Search Area Concept
//In this problem we have to find the peak element which is defined as the element
//which has both neighbours snmaller than it
//Here since it is an unsorted array we should have two criterion
//1.How to check v[mid] is an answer or not
//2.How to know whether to move left or right if we came to know that v[mid] cannot be the answer
//The 1st criteria can be checked by comparing v[mid+1] and v[mid-1] after ensuring the overflow 
//conditions
//For moving left or right we compare the v[mid] value with v[mid-1] and v[mid+1]
//If v[mid+1]>v[mid] then v[mid-1] cannot be answer as v[mid]>v[mid-1]
//So most probable ans lies to right end so we keep start=mid+1 as v[mid+1]>v[mid]
//one part is over we need to check other part for mid+1 value
//so we check on from mid+1 value
//Another point is that there is only one neighbour for edg values
//So we need to keep an extra condition tha if(mid==0) or midd=v.size()-1
int Peak_Element(vi v)
{
    int start=0;
    int end=v.size()-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        //Inorder to avoid the overflow we keep the edge conditions
        if((mid+1<v.size()) and mid-1>=0)
        {
            if(v[mid+1]<v[mid] and v[mid-1]<v[mid])
             return v[mid];
             //moving left to right based on v[mid+1] value and v[mid-1] value
               else if(v[mid+1]>v[mid]) start=mid+1;
              else end=mid-1;
        }
        //Extra conditions 
        else if(mid==0)
        {
          //comparing the right index with start value
            if(v[mid+1]<v[mid])
            return v[mid];
            else start=mid+1;
        }
        else if(mid==v.size()-1)
        {
            if(v[mid-1]<v[mid]) return v[mid];
            else end=mid-1;
        }
      
    }
  return -1;
}
//Bitonic array is defined as the array which is monotonically increasing at first
//then monotonically decreasing 
//Here we have to find the max element of bitonic array
//In normal array we can find the max elenment in O(n) array
//in bitonic array we can find the ans in O(log n) time
//If we closely observe since the array is monotonically increasing the decreasing then there
//a peak element in which both the neighbpurs are less than mid value
//So it is the previous question of finding the peak element
int Max_Biotonic_Array(vi v)
{
    int start=0;
    int end=v.size()-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(mid+1<v.size() and mid-1>=0)
        {
            if(v[mid+1]<v[mid] and v[mid-1]<v[mid]) return v[mid];
            else if(v[mid+1]>v[mid]) start=mid+1;
            else end=mid-1;
        }
        //If mid is zero
        else if(mid==0)
        {
            if(v[mid]>v[mid+1]) return v[mid];
        }
        else if(mid==v.size()-1)
        {
            if(v[mid]>v[mid-1]) return v[mid];
        }
    }
  return -1;
}
//Searching an element in bitonic array
int Bitonic_Array_Search(vi v,int val)
{
    int start=0;
    int end=v.size()-1;
    int res1=-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(mid+1<v.size() and mid-1>=0)
        {
            if(v[mid-1]<v[mid] and v[mid+1]<v[mid])
             {res1=mid ;break;}
             else if(v[mid]<v[mid+1]) start=mid+1;
             else end=mid-1;
        }
        else if(mid==0)
        {
            if(v[mid+1]<v[mid])
            res1=mid;
        }
        else if(mid==v.size()-1)
        {
            if(v[mid-1]<v[mid])
             res1=mid;
        }
    }
    start=0;
    end=res1;
    //cout<<res1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(v[mid]==val) return mid;
        else if(v[mid]<val) start=mid+1;
        else end=mid-1;
    }
    start=res1+1;
    end=v.size()-1;
    while(start<=end)
    {
        int mid=start+(end-start)/2;
        if(mid==val) return mid;
        else if(v[mid]<val) end=mid-1;
        else start=mid+1;
    } 
    return -1; 
}
//This function returns the pair of indixes of the given element in row and col wise sorted array
//if exists otherwise returm -1;
//Approach
//Start from upper right element
//Check if that elemnt is equal to x,if it is return the pair of indices
//if the element is smaller than x then we can't get the x value in that colum cause 
//all elemnts are greater than that element in that column
//so we will do j-- for searching left elements as they are smaller than current value 
//there is a probability that we can find the valuye
//Now condition 2 if the element is greater than current index elemnt then we cant get that element
//in left hand side as all elements left are smaller than that current element but we want greater
//element
//so we will do i++ since bottom elements are greater than probability is that we can get 
//the elemnnt
//Until the i and j are in range we do check the values
//if the i and j goes out of bound then we will return -1
//Complexoty of this code is O(n+m)
pairi Search_in_row_col_sorted_matrix(vii M,int n,int m,int x)
{
    //Intialsing i and j with right most value
      int i=0;
      int j=m-1;
      while(i>=0 and i<n and j>=0 and j<m)
      {
          //check if elemny equal
          if(M[i][j]==x) return {i,j};
          //if the element is greater than we cant get in bottom we will do j--
          else if(M[i][j]>x) j--;
          //else i++
          else i++;
      }
      return {-1,-1};
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vi v;
   // v.pb(11);v.pb(18);v.pb(12);v.pb(1);v.pb(4);v.pb(10);
    // reverse(v.begin(),v.end());
     //pairi p=First_Last_Occurence(v,10);
     //cout<<p.second-p.first+1;
    //  v.pb(1);v.pb(6);v.pb(5);v.pb(7);v.pb(8);v.pb(9);
    // cout<<BS_in_Nearly_Sorted(v,10);
    // v.pb(1);v.pb(2);v.pb(3);v.pb(4);v.pb(7);v.pb(8);
    // cout<<Ceil_Value(v,9);
    //string s="abcdx";
   // cout<<Find_Next_Alphabet(s,'y');
//    for(int i=0;i<100;i++) v.pb(0);
//      for(int i=0;i<100;i++) v.pb(1);
//   v.pb(1);v.pb(4);v.pb(7);v.pb(12);v.pb(8);v.pb(6);
//    cout<<Bitonic_Array_Search(v,7);
  v={2,2,3,3,45,1,1,2};
  cout<<Search_in_Rotated_Array(v,45);
   //cout<<First_Occurence_in_Infinite_Sorted_Array(v);
      #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}