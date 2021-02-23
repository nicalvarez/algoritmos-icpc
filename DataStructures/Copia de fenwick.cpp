#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define mp make_pair

typedef long long int tint;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

struct bit {
	int n, *sum;

	bit(int n): n(n) {
		sum = new int[n];
		fill(sum, sum+n, 0);
	}

	void add(int x, int val) {
		for (int i = x; i < n; i += i & (-i)) sum[i] += val;
	}

	int get(int x) {
		int res = 0;
		for (int i = x; i > 0; i -= i & (-i)) res += sum[i];
		return res;
	}

	int ith(int i) {
		int res = 0, l = 31 - __builtin_clz(n);
		dforsn(k,0,l+1) if (sum[res | (1<<k)] < i) {
			res |= 1<<k;
			i -= sum[res];
		}
		return res+1;
	}

};

int main() {}