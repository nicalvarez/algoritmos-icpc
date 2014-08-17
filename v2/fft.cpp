#include <bits/stdc++.h>
using namespace std;

typedef complex<double> comp;
typedef long long tint;

#define forn(i,n) for (int i = 0; i < (int)(n); i++)
#define forsn(i,a,b) for (int i = int(a); i < int(b); i++)
#define dforsn(i,a,b) for (int i = int(b-1); i >= int(a); i--)

#define si(c) ((int)(c).size())
#define pb push_back

template<class T>
ostream& operator<<(ostream &out, vector<T> v) { for (T x: v) out << fixed << setprecision(8) << x << ' '; return out; }

void pad(vector<comp> &a) {
	int n = si(a);
	while (n & (n-1)) n += n & (-n);
	a.resize(n,0);
}

vector<comp> fft(const vector<comp> &a, bool inv) {
	int n = si(a);
	if (n == 1) return a;

	vector<comp> ae, ao;
	forn(i,n) if (i & 1) ao.pb(a[i]); else ae.pb(a[i]);
	vector<comp> c = fft(ae, inv), d = fft(ao, inv);

	vector<comp> res(n);
	comp ri = 1;
	comp r = exp(comp(0,-2*M_PI / n));
	if (inv) r = conj(r);
	n /= 2;
	forn(i,n) {
		comp val = ri*d[i];
		res[i] = c[i] + val;
		res[n+i] = c[i] - val;
		ri *= r;
	}
	if (inv) forn(i,2*n) res[i] /= 2;
	return res;
}

inline int binv(int x, int k) {
	int res = 0;
	forn(_,k) {
		res = (res << 1) | (x & 1);
		x >>= 1;
	}
	return res;
}

vector<comp> fft2(const vector<comp> &a, bool inv) {
	int n = si(a);
	int k = 0; while ((1<<k) < n) k++;
	vector<comp> b(n);
	forn(i,n) b[i] = a[binv(i,k)];

	for (int step = 1; step < n; step *= 2) {
		comp r = exp(comp(0,-2*M_PI / (2*step)));
		if (inv) r = conj(r);
		for (int i = 0; i < n; i += 2*step) {
			comp ri = 1;
			for (int j = i; j < i+step; j++) {
				comp val = ri*b[j+step];
				b[j+step] = b[j] - val;
				b[j] = b[j] + val;
				ri *= r;
			}
		}
	}
	if (inv) forn(i,n) b[i] /= n;
	return b;
}

template<class C, class T>
void FFT(C &a, T root, bool inv) {
	int n = si(a);
	int k = 0; while ((1<<k) < n) k++;
	assert ((1<<k) == n);

	int *rev = new int[n];
	rev[0] = 0; forsn(i,1,n) rev[i] = (rev[i>>1]>>1) | ((i&1) << (k-1));
	forn(i,n) if (rev[i] < i) swap(a[i], a[rev[i]]);

	// static T r[k];
	T *r = new T[k];
	if (inv) root = T(1)/root;
	r[k-1] = root;
	dforsn(i,0,k-1) r[i] = r[i+1]*r[i+1];
	
	forn(l,k) {
		int step = 1<<l;
		for (int i = 0; i < n; i += 2*step) {
			T ri = 1;
			for (int j = i; j < i+step; j++) {
				T val = ri * a[j+step];
				a[j+step] = a[j] - val;
				a[j] += val;
				ri *= r[l];
			}
		}
	}
	if (inv) forn(i,n) a[i] /= T(n);
	delete[] rev;
	delete[] r;

}

// template<class C, class T>
// C DFT(C &a, T root, bool inv) {
// 	int n = si(a);
	
// 	static T b[n];
// 	if (inv) root = T(1) / root;
// 	T r = 1;
// 	forn(i,n) {
// 		b[i] = 0;
// 		dforsn(j,0,n) b[i] = b[i]*r + a[j];
// 		r *= root;
// 	}
// 	if (inv) forn(i,n) b[i] /= T(n);
// 	forn(i,n) a[i] = b[i];
// }

tint expomod(tint x, tint e, tint m) {
	tint res = 1;
	while (e) {
		if (e&1) res = res*x%m;
		e >>= 1;
		x = x*x%m;
	}
	return res;
}

/***********************************************************
K|Menor primo de la forma (2**K * impar) + 1
0 2
1 3
2 5
3 41
4 17
5 97
6 193
7 641
8 257
9 7681
10 13313
11 18433
12 12289
13 40961
14 114689
15 163841
16 65537
17 1179649
18 786433
19 5767169
20 7340033
21 23068673
22 104857601
23 377487361
24 754974721
25 167772161
26 469762049
27 2013265921
28 3489660929
29 12348030977
30 3221225473
31 75161927681
32 184683593729
33 77309411329
34 1288490188801
35 2027224563713
36 206158430209
37 2061584302081
38 4123168604161
39 2748779069441
40 29686813949953
41 6597069766657
42 39582418599937
43 79164837199873
44 263882790666241
45 1231453023109121
46 1337006139375617
47 3799912185593857
48 4222124650659841
49 12947848928690177
50 7881299347898369
51 38280596832649217
52 31525197391593473
53 459367161991790593
54 882705526964617217
55 180143985094819841
56 1945555039024054273
57 4179340454199820289
58 28534807239019462657
59 15564440312192434177
60 35740566642812256257
61 122209679488325779457
62 484227031934875729921
63 83010348331692982273
64 461168601842738790401
***********************************************************/

// Number-theoretic transform
// R = n-th primitive root module MOD (where n is si(a)) 
// MOD = prime module
vector<tint> fft3(const vector<tint> &a, bool inv, tint R, tint MOD) {
	int n = si(a);
	int k = 0; while ((1<<k) < n) k++;
	vector<tint> b(n);
	forn(i,n) b[i] = a[binv(i,k)];

	for (int step = 1; step < n; step *= 2) {
		// comp r = exp(comp(0,-2*M_PI / (2*step)));
		tint r = expomod(R,n/2/step,MOD);
		if (inv) r = expomod(r, MOD-2, MOD);
		for (int i = 0; i < n; i += 2*step) {
			tint ri = 1;
			for (int j = i; j < i+step; j++) {
				tint val = ri*b[j+step]%MOD;
				b[j+step] = (b[j] - val + MOD) % MOD;
				b[j] = (b[j] + val) % MOD;
				ri = ri*r%MOD;
			}
		}
	}
	tint invn = expomod(n,MOD-2,MOD);
	if (inv) forn(i,n) b[i] = b[i]*invn%MOD;
	return b;
}

vector<tint> covolve(const vector<tint> &a, const vector<tint> &b, tint R, tint MOD) {
	int n = si(a);
	vector<tint> fa = fft3(a,false,R,MOD), fb = fft3(b,false,R,MOD);
	forn(i,n) fa[i] = fa[i]*fb[i]%MOD;
	return fft3(fa,true,R,MOD);
}

vector<comp> covolve(const vector<comp> &a, const vector<comp> &b) {
	int n = si(a);
	vector<comp> fa = fft2(a,false), fb = fft2(b,false);
	forn(i,n) fa[i] *= fb[i];
	return fft2(fa,true);
}

int main() {
	vector<tint> a = {2,3,10,12,0,0,0,0}, b = {0,17,4,15,0,0,0,0};
	vector<complex<double>> ad(a.begin(), a.end());

	cout << ad << endl;
	cout << fft2(ad, false) << endl;
	FFT(ad, exp(complex<double>(0,-2*M_PI/si(a))), false);
	cout << ad << endl;

	return 0;



	vector<tint> c(8,0);
	forn(i,8) forn(j,8) if (i+j < 8) {
		c[i+j] += a[i]*b[j];
	}
	cout << c << endl;

	tint R = 996173970, MOD = 998244353;	
	cout << covolve(a,b,expomod(R,1<<15,MOD),MOD);

}