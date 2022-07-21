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
// Function to find the index of number
// at first position of
// kth sequence of set of size n
int findFirstNumIndex(int& k, int n)
{

	if (n == 1)
		return 0;
	n--;

	int first_num_index;
	// n_actual_fact = n!
	int n_partial_fact = n;

	while (k >= n_partial_fact
		&& n > 1) {
		n_partial_fact
			= n_partial_fact
			* (n - 1);
		n--;
	}

	// First position of the
	// kth sequence will be
	// occupied by the number present
	// at index = k / (n-1)!
	first_num_index = k / n_partial_fact;

	k = k % n_partial_fact;

	return first_num_index;
}

// Function to find the
// kth permutation of n numbers
string findKthPermutation(int n, int k)
{
	// Store final answer
	string ans = "";

	set<int> s;

	// Insert all natural number
	// upto n in set
	for (int i = 1; i <= n; i++)
		s.insert(i);

	set<int>::iterator itr;

	// Mark the first position
	itr = s.begin();

	// subtract 1 to get 0 based indexing
	k = k - 1;

	for (int i = 0; i < n; i++) {

		int index
			= findFirstNumIndex(k, n - i);

		advance(itr, index);

		// itr now points to the
		// number at index in set s
		ans += (to_string(*itr));

		// remove current number from the set
		s.erase(itr);

		itr = s.begin();
	}
	return ans;
}

// Driver code
int main()
{

	int n = 200, k = 4342;

	string kth_perm_seq
		= findKthPermutation(n, k);

	cout << kth_perm_seq << endl;

	return 0;
}
