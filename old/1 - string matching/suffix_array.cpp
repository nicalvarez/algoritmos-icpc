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

const int
	MAXN = 100000 + 100,
	INF = 1<<29;

string s;
int n, t, r[MAXN], p[MAXN], lcp[MAXN];

bool bcomp(int i, int j) { return s[i] < s[j]; }
bool beq(int i, int j) { return s[i] == s[j]; }
bool comp(int i, int j) { return mp(p[i],p[(i+t)%n]) < mp(p[j],p[(j+t)%n]); }
bool eq(int i, int j) { return mp(p[i],p[(i+t)%n]) == mp(p[j],p[(j+t)%n]); }

int np[MAXN];
void refine(bool eq(int,int)) {
	np[r[0]] = 0;
	forsn(i,1,n) {
		int ra = r[i], rp = r[i-1];
		np[ra] = np[rp];
		if (!eq(ra,rp)) np[ra]++;
	}
	copy(np,np+n,p);
}

void computeSA() {
	forn(i,n) r[i] = i;
	sort(r,r+n,bcomp);
	refine(beq);

	for (t = 1; t < 2*n; t *= 2) {
		sort(r,r+n,comp);
		refine(eq);
	}
}

void computeLCP() {
	int l = 0;
	forn(i,n) if (p[i]) {
		int j = r[p[i]-1];
		while (s[(i+l) % n] == s[(j+l) % n]) l++;
		lcp[p[i]] = l ? l-- : l;
	}
	lcp[0] = lcp[n] = 0;
}
