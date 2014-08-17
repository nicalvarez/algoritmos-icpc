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

namespace SA {
	int n;
	string s;

	int t;
	int *p, *r;

	bool bcomp(int i, int j) { return s[i] < s[j]; }
	bool comp(int i, int j) {  return mp(r[i], r[(i+t)%n]) < mp(r[j], r[(j+t)%n]); }

	int *nr;
	void refine (bool comp(int,int)) {
		nr[p[0]] = 0;
		forsn(i,1,n) {
			nr[p[i]] = nr[p[i-1]];
			if (comp(p[i-1], p[i])) nr[p[i]]++;
		}
		copy(nr, nr+n, r);
	}

	void computeArray() {
		p = new int[n];
		r = new int[n];
		nr = new int[n];
		forn(i,n) p[i] = i;
		
		sort(p, p+n, bcomp);
		refine(bcomp);	

		for (t = 1; t < n; t *= 2) {
			int i = 0, j;
			while (i < n) {
				j = i;
				while (j < n && r[p[j]] == r[p[i]]) j++;
				sort(p+i, p+j, comp);
				i = j;
			}
			refine(comp);
		}
	}

	int *lcp;
	void computeLCP() {
		lcp = new int[n+1];
		int l = 0;

		forn(i,n) if (r[i]) {
			int j = p[r[i]-1];
			while (s[(i+l)%n] == s[(j+l)%n]) l++;
			lcp[r[i]] = l ? l-- : l;
		}
		lcp[0] = lcp[n] = 0;
	}

	void initSA(const string &_s) {
		s = _s + char(0);
		n = si(s);

		computeArray();
		computeLCP();
	}
}

int main(int argc, char **argv) {}