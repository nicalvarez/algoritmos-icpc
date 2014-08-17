#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <complex>
#include <cassert>
#include <bitset>
#include <cstring>
using namespace std;


#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define decl(v, c) typeof(c) v = c
#define forall(i, c) for(decl(i, c.begin()); i!=c.end(); ++i)
#define dforall(i, c) for(decl(i, c.rbegin()); i!=c.rend(); ++i)
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define mp make_pair


typedef long long int tint;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<tint> vt;
typedef vector<vt> vvt;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<string> vs;
typedef pair<int,int> pii;

struct op {
	const int ZERO = 1e9;
	int operator()(int a, int b) { return min(a,b); }
} op;

struct node {
	int l,r,lazy,sum;
	enum inter { FULL, EMPTY, PARTIAL };

	node() {}

	node(int a, int b, int val = 0) {
		l = a; r = b;
		lazy = 0;
		sum = val;
	}

	int get() { return sum + lazy; }
	
	void split(node &a, node &b) {
		a.lazy += lazy;
		b.lazy += lazy;
		lazy = 0;
	}

	void merge(node &a, node &b) {
		sum = op(a.get(), b.get());
		lazy = 0;
	}

	inter inter(int a, int b) {
		if (r <= a || l >= b) return EMPTY;
		if (a <= l && r <= b) return FULL;
		return PARTIAL;
	}
};


struct lazy {
	node *n;

	lazy(int n, int x[]) {
		this->n = new node[4*n];
		build(1, 0, n, x);
	}

	void build(int id, int a, int b, int x[]) {
		n[id] = node(a,b);
		
		if (a+1 == b); //n[id].sum = x[a];
		else {
			int m = (a+b+1)/2;
			build(2*id, a, m, x);
			build(2*id+1, m, b, x);
			n[id].merge(n[2*id], n[2*id+1]);
		}	
	}

	void _update(int id, int a, int b, int val) {
		switch (n[id].inter(a,b)) {
			case node::EMPTY: 
				return;
			case node::FULL:
				n[id].lazy += val;
				return;
			case node::PARTIAL:
				n[id].split(n[2*id], n[2*id+1]);
				_update(2*id, a, b, val);
				_update(2*id+1, a, b, val);
				n[id].merge(n[2*id], n[2*id+1]);
		}

	}

	void update(int a, int b, int val) { _update(1,a,b,val); }

	int _get(int id, int a, int b) {
		switch (n[id].inter(a,b)) {
			case node::EMPTY:
				return op.ZERO;
			case node::FULL:
				return n[id].get();
			case node::PARTIAL:
				n[id].split(n[2*id], n[2*id+1]);
				int res = op(_get(2*id, a, b), _get(2*id+1, a, b));
				n[id].merge(n[2*id], n[2*id+1]);
				return res;
		}
		return op.ZERO;
	}

	int get(int a, int b) { return _get(1,a,b); }

};

int main() {}
