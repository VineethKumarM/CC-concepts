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
#define vvii vector<vector<int>>
#define vvbb vector<vector<bool>>
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
/*Given an array of positive integers nums and a positive integer target,
 return the minimal length of a contiguous subarray [numsl, numsl+1, ..., numsr-1, numsr] 
 of which the sum is greater than or equal to target. If there is no such subarray, 
 return 0 instead.
*/
/*Inorder to approach this problem we will keep a left pointer */
int minSubArrayLen(int target, vector<int>& nums) {
       int ans=INT_MAX;
        int left=0;
        int sum=0;
        for(int i=0;i<nums.size();i++)
        {
            sum+=nums[i];
            while(sum>=target)
            {
                ans=min(ans,(i+1-left));
                sum-=nums[left];
                left++;
            }
        }
        return (ans!=INT_MAX) ? ans:0;
}

/*
Given an integer array nums, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order.

Return the shortest such subarray and output its length.
https://leetcode.com/problems/shortest-unsorted-continuous-subarray/*/
 int findUnsortedSubarray(vector<int>& nums) {
            int mini=INT_MAX,maxi=INT_MIN;
         int n=nums.size();
           for(int i=0;i<n-1;i++)
             if(nums[i]>nums[i+1])
               mini=min(mini,nums[i+1]);
         for(int i=n-1;i>0;i--)
           if(nums[i-1]>nums[i])
             maxi=max(maxi,nums[i-1]);
         if(mini==INT_MAX and maxi==INT_MIN) return 0;
         int start=0,end=0;
           for(int i=0;i<n;i++) 
             if(nums[i]>mini)
             {start=i;break;}
           for(int i=n-1;i>=0;i--)
             if(nums[i]<maxi)
             {end=i;break;}
         return end-start+1;
    }
/*
Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.*/
int subarraySum(vector<int>& nums, int k) {
       int cursum=0;
        int cnt=0;
       unordered_map<int,int> mp;
       for(int i=0;i<nums.size();i++)
       {
         cursum+=nums[i];
          if(cursum==k) cnt+=1;
          if(mp.find(cursum-k)!=mp.end())
            cnt+=mp[cursum-k];
         mp[cursum]++;
       }
      return cnt;
    }
/*Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
https://leetcode.com/problems/contiguous-array/

 */
int findMaxLength(vector<int>& nums) {
        unordered_map<int,int> mp;
      for(int i=0;i<nums.size();i++)
        if(nums[i]==0) nums[i]=-1;
         //unordered_map<int,int> mp;
        int ans=INT_MIN;
       int sum=0;
      for(int i=0;i<nums.size();i++)
      {
         sum+=nums[i];
         if(mp.find(sum)!=mp.end())
           ans=max(ans,i-mp[sum]);
          else mp[sum]=i;
        if(sum==0) ans=max(ans,i+1);
      }
      if(ans==INT_MIN) return 0;
      return ans;
    }
/*Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.
A subarray is a contiguous part of an array.
https://leetcode.com/problems/subarray-sums-divisible-by-k/*/
 int subarraysDivByK(vector<int>& nums, int k) {
      int sum=0;
      int ans=0;
      unordered_map<int,int> mp;
       for(int i=0;i<nums.size();i++)
       {
         if(nums[i]<0)
         {
           int x=abs(nums[i])/k;
           nums[i]=k*(x+1)+nums[i];
         }
         sum+=nums[i];
         if(mp.find(sum%k)!=mp.end())
           ans+=mp[sum%k];
          if(sum%k==0) ans+=1;
          mp[sum%k]++;
       }
         return ans;
    }
/*https://leetcode.com/problems/longest-mountain-in-array/submissions/*/
int longestMountain(vector<int>& arr) {
      int ans=0;
      int n=arr.size();
      for(int i=1;i<n;i++)
      {
        int count=1;
        int j=i;
        bool flag=false;
        while(j<n and arr[j]>arr[j-1])
        {
          j++;
          count++;
         
        }
        while(i!=j and j<n and arr[j]<arr[j-1])
        {
          j++;
          count++; flag=true;
        }
        if(i!=j and count>2 and flag)
        {
          ans=max(ans,count);
          j--;
        }
        i=j;
      }
       return ans; 
    }
int main()
{
     freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}