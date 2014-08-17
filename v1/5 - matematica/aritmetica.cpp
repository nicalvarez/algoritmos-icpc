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

const int MOD = 10007;

tint mod(tint x, tint m) { return ((x%m) + m) % m; }


tint modexp(tint x, tint e) {
	if (e == 0) return 1;
	tint res = modexp(x, e/2); res = (res*res) % MOD;
	if (e & 1) res = (res * x) % MOD;
	return res;
}

pii egcd(tint a, tint b) {
	if (a) {
		pii res = egcd(b%a, a);
		return mp(res.second - res.first*(b/a), res.first);
	}
	return mp(0,1);
}

tint inv(tint n, tint m) {
	pii res = egcd(n, MOD);
	return mod(res.first, m);
}

inline tint expomod(tint a, tint e) {
	tint res = 1;
	while (e) {
		if (e & 1) res = (res * a) % MOD;
		a = (a * a) % MOD;
		e >>= 1;
	}
	return res;
}

// Iverso para MOD primo
inline tint inv(tint x) { return expomod(x, MOD-2); }

// Lucas Theorem
tint lcomb(tint m, tint n) {
	if (n < 0 || n > m) return 0;
	if (n == 0 || n == m) return 1;

	if (n >= MOD) {
		tint qm = m / MOD, rm = m % MOD;
		tint qn = n / MOD, rn = n % MOD;
		return (comb(qm, qn) * comb(rm, rn)) % MOD;
	}

	if (n*2 > m) n = m-n;
	tint res = 1;
	forn(i,n) {
		res = (res * (m-i)) % MOD;
		res = (res * inv(i+1)) % MOD;
	}
	return res;
}

tint fact[MAXC], ifact[MAXC];
tint comb(int m, int n) {
	tint res = fact[m];
	res = (res * ifact[n]) % MOD;
	res = (res * ifact[m-n]) % MOD;
	return res;
}

void initFact() {
	fact[0] = 1; forsn(i,1,MAXC) fact[i] = i * (fact[i-1]) % MOD;
	ifact[0] = 1; forsn(i,1,MAXC) ifact[i] = (inv(i, MOD) * ifact[i-1]) % MOD;
}
}
