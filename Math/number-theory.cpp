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
typedef pair<tint,int> pti;

tint gcd(tint a, tint b) { return a ? gcd(b%a, a): b; }

vector<pti> factor(tint n) {
	vector<pti> res;
	for (tint d = 2; d*d <= n; d++) if (n % d == 0) {
		pti f(d,0);
		while (n % d == 0) { f.second++; n /= d; }
		res.pb(f);
	}
	if (n > 1) res.pb(mp(n,1));
	return res;
}

tint phi(tint n) {
	vector<pti> fac = factor(n);
	tint res = 1;
	for (auto f: fac) {
		res *= f.first - 1;
		forn(_,f.second-1) res *= f.first;

	}
	return res;
}

tint expomod(tint x, tint e, tint m) {
	if (e == 0) return 1;
	tint res = expomod(x*x%m, e/2, m);
	if (e&1) res = (res * x) % m;
	return res;
}

vector<tint> prim_roots(tint n, int cant=1) {
	vector<tint> res;
	tint p = phi(n);
	vector<pti> fac = factor(p);
	forsn(r,1,n) if (gcd(n,r) == 1) {
		for (auto f : fac) if (expomod(r, p/f.first, n) == 1)
			goto hell;
		res.pb(r);
		if (--cant == 0) break;
		hell:;
	}
	return res;
}

int main() {
	// for (tint r : prim_roots(11,11)) cerr << r << endl;
	// cout << prim_roots(998244353, 1).back() << endl;

	// const int MOD = 998244353;
	// cout << expomod(3,7*17*16,MOD) << endl;

	// tint r = 996173970;

	// auto fs = factor(5794704);
	auto fs = factor(1005060096);

	for (auto it : fs) cout << it.first << ' ' << it.second << endl;
	
	// cout << expomod(r,1<<17,MOD) << endl;

	return 0;
}