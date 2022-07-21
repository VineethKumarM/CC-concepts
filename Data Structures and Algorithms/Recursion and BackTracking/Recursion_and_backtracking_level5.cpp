#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define vc vector<char>
#define vf vector<float>
#define vul vector<ull>
#define vb vector<bool>
#define vs vector<string>
#define vii vector<vector<int>>
#define vvcc vector<vector<char>>
#define vpii vector<pair<int,int>>
#define vvii vector<vector<int>>
#define vvbb vector<vector<bool>>
#define sti stack<int>
#define stc stack<char>
#define spii stack<pair<int,int>>
#define spic stack<pair<int,char>>
#define spcc stack<pair<char,char>>
#define pairi pair<int,int>
#define umpcb unordered_map<char,bool>
#define umpib unordered_map<int,bool>
#define umpsb unordered_map<string,bool>
#define umpci unordered_map<char,int>
#define umpii unordered_map<int,int>
#define umpsi unordered_map<string,int>
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
/*In this question we are given n friends each person has two option either he can pair up with any
of his friends or he can remain single
we have to print all the unique combinations where it should not contain any duplicates
for ex:(1,2) and (2,1) both are considered samwe
We should print only one of them
notebook
In this problem we keep the levels as friends and at ecah level we check the available optiosn available to us
So before processing further first we will check whether the current level friend is already paired up
by some other or not
If the current level friend is already upaired up by some other friend in the past levels 'then
we cannot do with this current level friend
So we increment the counter to solve for further level friends
If the current level hasnt been paired up then he has got two options
1.Hebcan remain single 
2.he can pair up with any next level friends as we should print the uniwue combinations so we can use 
only futher level members pairing only
We make the current levle used 
and for the option1 we simple increment the level of friend and solve for further level
friends
for 2nd option we check all the further levels whowere unused until now(imp point)
then we make the parining friend also as used one as paired cant be used for further cases
so we solve for further levels
and when we backtracking we will use the used as unused so it can be used for lower levels
and when we are done with the cuurent level also we wil make them as unused
*/
void friends_pairing(int i,int n,vb used,string osf){
    /*if alll friends were paired up we cn printbthe osr */
    if(i>n){
        cout<<osf<<'\n';
        return;
    }
    /*If the current friend was already paired up by some other friend then we cannot use the current
    friend we will process futher*/
    if(used[i]==true){
        friends_pairing(i+1,n,used,osf);
    }else{
        /*If the current friend is not used then we will mark the friend as used and process further*/
        used[i]=true;
        /*we check all further level friends who are not already used by lower level friend so that we can 
        pair up with the current level friedn*/
        friends_pairing(i+1,n,used,osf+"("+to_string(i)+") ");
        for(int j=i+1;j<=n;j++){
            /*check if the current friend is already used by anyone or not*/
            if(used[j]==false){
                /*since we are pairing up we assign true for pairing friend*/
            used[j]=true;
            /*after pairing solve for futher level friiends*/
            friends_pairing(i+1,n,used,osf+"("+to_string(i)+","+to_string(j)+") ");
            /*after paring with that friend make the used[j] as fa;lse so that it can be used by lowerlvel friend
            s dor further cases*/
            used[j]=false;}
        }
        used[i]=false;
    }
}
int kways=0;
void partition_k_subsets(int ind,int k,int sets_sf,vi v){
    if(ind==v.size()){
        if(k==sets_sf){
              kways+=1;
        }
      return;
    }
    if(sets_sf>k) return;
    partition_k_subsets(ind+1,k,sets_sf,v);
    partition_k_subsets(ind+1,k,sets_sf+1,v);
}
/*Here we have passed i as cur no ,n as total items,k as parition sets that we want to 
partition the sets,ssf is the sets so far formed and ans is the partition that we want to do
since we want to make k partitions we made the size of ans as k and passed this k sized
ans as a prameter into our function
Now the current number i has two options either it can go into a already existing set or it can
start a new set
For ex let us assume sets until now made are 1|2|3 now the current number is 4 so it has 4 optipns
either it can go into an existing set i.e.,14|2|3 or 1|24|3 or 1|2|34 
or the number itself can make a new set 1|2|3|4
so inorder to avoid permutauions we will set the current element into next set as it avoid permutaions
for example 1|_|_ now 2 has 12|_|_ or 1|2|_ or 1|_|2 but we can see here that last two [artions
are same 
So we will break out from the loop as soon as we get ans[j].size()==0*/
void partition_k_subsets_p(int i,int n,int k,int ssf,vvii ans){
   if(i>n){
       if(ssf==k){
           for(int j=0;j<ans.size();j++){
               for(int k=0;k<ans[j].size();k++)
                cout<<ans[j][k];
                cout<<' ';
           }
           cout<<'\n';
       }
       return;
   }
   /*Make anote that we should give ans.size(k) so that it rns loop for nonempty sets also
   It should be in the main function*/
   /*Here we are running the loop on current sets*/
    for(int j=0;j<ans.size();j++){
        /*If the ans[j] has size>0 then that set contains aready elemnts we push back the curremt
        element into an already existing set 
        Since we didint increased our no.of sets then we keep the ssf as same*/
        if(ans[j].size()>0){
            ans[j].pb(i);
            partition_k_subsets_p(i+1,n,k,ssf,ans);
            ans[j].pop_back();
        }else{
            /*Here we encounters our first empyy set and we will push the current element to make a
            new set since we have increased our set count we increment it*/
            ans[j].pb(i);
            partition_k_subsets_p(i+1,n,k,ssf+1,ans);
            ans[j].pop_back();
            /*to avoid permuataions we break from the loop*/
            break;
        }
    }
}
/*we do the same thing as we did in k partions but here before cout we check the cases whether
all the sets have equal sum or not*/
void equal_sum_k_subsets_partition(int ind,vi items,int totalsum,int k,int ssf,vvii ans){
    if(ind==items.size()){
        if(ssf==k){
            bool flag=true;
            for(int i=0;i<ans.size();i++){
                int sum=0;
                for(int j=0;j<ans[i].size();j++)
                  sum+=ans[i][j];
                  if(sum!=(totalsum/k))
                   { flag=false;break;}
            }
            if(flag){
                for(int i=0;i<ans.size();i++){
                    for(int j=0;j<ans[i].size();j++)
                     cout<<ans[i][j];
                     cout<<' ';
                }
                cout<<'\n';
            }
        }
        return;
}


    for(int i=0;i<ans.size();i++){
        if(ans[i].size()>0){
            ans[i].pb(items[ind]);
            equal_sum_k_subsets_partition(ind+1,items,totalsum,k,ssf,ans);
            ans[i].pop_back();
        }else{
            ans[i].pb(items[ind]);
            equal_sum_k_subsets_partition(ind+1,items,totalsum,k,ssf+1,ans);
            ans[i].pop_back();
            break;
        }
    }
}
/*Here we check the base codnitions for a valid partioning*/
void canwe_partion(vi items,int k){
    /*if items.size() to 1 paruins then ecah element goes into the same set then we print
    the whole set*/
    if(items.size()==1)
     { for(int i=0;i<items.size();i++) cout<<items[i];
       return;}
      int sum=0;
      for(int i=0;i<items.size();i++) sum+=items[i];
      /*here we caluclate the total sum of all elements and if it is not a multiple of k
      then we cannot partion in anyway then we return -1
      and if the sets to be partioned is greater than k we cannot parittion in that case also
      so we cout -1*/
      if(k>items.size() or sum%k!=0)
      { cout<<-1; return;}
      vvii ans(k);
      equal_sum_k_subsets_partition(0,items,sum,k,0,ans);
}
/*
In this problem, You are given 
1. A list of words, a list of alphabets(might be repeating) and score of every alphabet from a to z.
2. You have to find the maximum score of any valid set of words formed by using the given alphabets.
3. A word can not be used more than one time.
4. Each alphabet can be used only once. 
5. It is not necessary to use all the given alphabets.
*/
/*Each word has two options whether we can include that word in our final set or we will not include them
Here the conditiion must be checked that before we are adding that our current word it should not exdceed the 
max frequence of letters
until this condition fails we add yheir values if we are allowed to add the whole word into our set
then we store the cureent value and solve for remaining them words we will return the max of sno(where'
thecurrent word is not inclueded and the syes where we have included the current word)*/
int maxwords(int ind ,vs words,vi freq,vi val){
     if(ind==words.size()) return 0;
    int sno=0+maxwords(ind+1,words,freq,val);
    int swords=0;
     bool flag=false;
     string s=words[ind];
     for(int i=0;i<s.size();i++){
         char ch=s[i];
         if(freq[ch-'a']==0){
             flag=true;
             break;  
         }
         swords+=val[ch-'a'];
     }
     int syes=0;
     if(flag){
         syes=swords+maxwords(ind+1,words,freq,val);
     }
     for(int i=0;i<s.size();i++)
       freq[s[i]-'a']++;
     return max(syes,sno);
}
/*1. You are given a number n representing the length of a floor space which is 2m wide. It's a 2 * n board.
2. You've an infinite supply of 2 * 1 tiles.
3. You are required to calculate and print the number of ways floor can be tiled using tiles.
Let us draw the recursive diagram for the problem and try to approach the problem
Let us take small input 123 friends .since we dont want permuations we put friends at each level\



                                                                1

                     
                 23(1 remained single)                         2(13 paired)                           3(12 paired)

         
    3(2 single)                  23(23 paired)                2(single)                              3(single)    
     (1-2-3)                      (1-23)                      (13-2)                                  (12-3)


So there are 4 ways
                                                                                                          
    Here we can see that the future of 2 and 3 when (1 is paired with antof them )   the remaining element ;s future is same
    This is the subproblem we keeep on solving
    Basically f(n) has two options
    case1:when it wants to single the problem with the f(n-1)
    case2:when it wants to pair with anyof the higher level friends(inorder to avoid permutaion) the problem comveted to n-1*f(n-2)
    Therefore the problem is f(n)=f(n-1)+(n-1)*f(n-2)         
    
    if the permutations are allowed then we do the same process at each level then the answe will be dp[n]    */
int friends_pairing(int n)
{
    if(n<3) return n;
    int dp[n+1];
    dp[0]=0;
    dp[1]=1;
    dp[2]=2;
    for(int i=3;i<=n;i++)
      dp[i]=dp[i-1]+(i-1)*dp[i-2];/*Note that we are multiplting with (i-1) */
      return dp[n];
}
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //vb used(8,false);
   // friends_pairing(1,7,used,"");
//    vi v={1,2,3,4};
//      partition_k_subsets(0,3,0,v);
    //    vvii v(7);
    //    partition_k_subsets_p(1,4,3,0,v);
    vi items={2,7,3,6,4,5};
    canwe_partion(items,3);
     //cout<<kways;
    #ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec\n";
#endif
    return 0;
}