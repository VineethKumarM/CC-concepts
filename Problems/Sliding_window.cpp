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
#define vpii vector<pair<int,int>>
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
const ll mod=1e9+7;
const ll size=2*(1e6+1);
const ll limit=1e10+7;
//Problem Link
//https://leetcode.com/problems/distinct-subsequences/
/*
Given two strings s and t, return the number of distinct subsequences of s which equals t.
A string's subsequence is a new string formed from the original string by deleting some
 (can be none) of the characters without disturbing the remaining characters' relative positions. 
 (i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).
*/
/*Here in this problem we will use the concept of sliding window using left and right pointers
So we keep left and right pointer at the startung pointer we make the pointer moves towards
right and we will keep putting the charcters in the map until the valid string 
If we get any charcter that is aleready present in the map it may means we have encountered the duplicate 
so we will keep on decrementing the frequency of map until the mp[cur_character] is 1
and at last we will store update the max len at each step*/
int sliding_window(string s){
    int len=0,left=-1,right=-1,n=s.size();
    unordered_map<char,int> mp;
     while(true)
     {
         //f1 and f2 is mainted  to ensure whether all chaaarcters are traversed or not
         //
         bool f1=true,f2=true;
          while(right<n)
          {
              //Here we keep on incre,enting the frequnecy of element
              right++;
               char ch=mp[right];
               mp[ch]++;
               //If anyof the frquency of the character is break from the loop and pop out all
               //the charcaters
               if(mp[ch]==2) break;
               else{
                   len=max(len,right-left);
               }
               f1=false;
          }
          //Here we will decrementing the frequecy
          while(left<right)
          {
              left++;
              char ch=mp[left];
              mp[ch]--;
              if(mp[ch]==1)
               break;
               f2=false;
          }
          if(f1 and f2) break;
     }
     
     return len;
}
//In te above approach we can see that we are atmost visiting each element in 2 times in the worst
//case
//for example take the string abcdefbb for this case we are vsiting the whole string again by 
//each step throught left pointer 
//we can avoid that if we can store the last repeated elennt index so that we cn directly make a jumo
//to that index to make it valid string
//So what in the map what we will store is the mindex of the charcter
//"abcdecg" suppose we have this string when we encounterd the second c we sinxe we already have one
//c we will make the left pointer mp[c]+1 and update the current index wuth mp[c] as current index
//with O(1) complexity
//and one more immportant thing is that we will update the value of left only when it is greater
//than current updating value
//for suppose consider a string "abcdedb" when we encounter 2nd d we already moed the pointer firstd+1
//and after d the b chat is repeating whichis already present in map
//Here we dont update left as mp[b]+1 as  left is already crossed the b while updating to d
int Distinct_subseq(string s){
    int len=0,right=0,left=0;
    unordered_map<char,int> mp;
    int n=s.size();
    while(right<n)
    {
        char ch=s[right];
        //ony update left if the value is maximum than prev left
         if(mp.find(ch)!=mp.end())
         left=max(left,mp[ch]+1);
         //upadate the map foreach character
         mp[ch]=right;
         //maximise the len ech time
         len=max(len,right-left+1);
    }
    return len;
}
/*
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
https://leetcode.com/problems/permutation-in-string/
In other words, return true if one of s1's permutations is the substring of s2.*/
bool checkInclusion(string s1, string s2) {
       if(s1.size()>s2.size()) return false;
        vector<int> hash1(26,0);
        vector<int> hash2(26,0);
        int left=0,right=0;
        while(right<s1.size())
        {
          hash1[s1[right]-'a']+=1;
           hash2[s2[right]-'a']+=1;
           right++;
        }
      right-=1;
       while(right<s2.size())
       {
         if(hash1==hash2) return true;
          right+=1;
          if(right<s2.size())
            hash2[s2[right]-'a']+=1;
           hash2[s2[left]-'a']-=1;
          left++;
       }
      return false;
    }
int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return;
}