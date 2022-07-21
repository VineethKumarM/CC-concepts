#include<bits/stdC++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vil vector<ll>
#define fl(i,n) for(int i=0;i<n;i++);
#define pb push_back
#define uint_64t unsigned ll
#define int_64t  ll
//unorderd sets run in O(1) time
//Ordered Set Runs in O(log n) time
//Setb will store distinct elements in sorted order by default in ascending 
//order
int main()
{
    freopen("Input.txt", "r", stdin); 
    freopen("Output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    cout.tie(NULL);
    //set<int> Set={1,2,3,4,5,1,6,3,4,5};
    class Persons
    {
        public:
        int age;
        string name;
        bool operator < (const Persons& rhs) const {return age<rhs.age;}
        bool operator > (const Persons& rhs) const {return age>rhs.age;}
    };
    set<Persons,std::greater<>> Set={{25,"Rakesh"},{12, "Rahul"},{30, "Ram"}};
    for(const auto &e:Set)
     cout<<e.age<<" "<<e.name<<endl;
    return 0;
}