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

template<class C, class T>
void FFT(C &a, T root, bool inv, int n=-1) {
	if (n == -1) n = si(a);
	int k = 0; while ((1<<k) < n) k++;
	assert ((1<<k) == n);

	int *rev = new int[n];
	rev[0] = 0; forsn(i,1,n) rev[i] = (rev[i>>1]>>1) | ((i&1) << (k-1));
	forn(i,n) if (rev[i] < i) swap(a[i], a[rev[i]]);

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
	if (inv) {
		T invn = T(1) / T(n);
		forn(i,n) a[i] *= invn;
	}
	delete[] rev;
	delete[] r;
}

template<class C, class T>
void DFT(C &a, T root, bool inv) {
	int n = si(a);
	
	T *b = new T[n];
	if (inv) root = T(1) / root;
	T r = 1;
	forn(i,n) {
		b[i] = 0;
		dforsn(j,0,n) b[i] = b[i]*r + a[j];
		r *= root;
	}

	if (inv) {
		T invn = T(1) / T(n);
		forn(i,n) b[i] *= invn;
	}
	forn(i,n) a[i] = b[i];
	delete[] b;
}

#define mp make_pair

template<class T>
T expo(T x, tint e) {
	T res = 1;
	while (e) {
		if (e&1) res *= x;
		e >>= 1;
		x *= x;
	}
	return res;
}

pair<tint,tint> egcd(tint a, tint b) {
	if (a == 0) return mp(0,1);
	tint q = b/a;
	auto res = egcd(b - q*a, a);
	return mp(res.second - q*res.first, res.first);
}

template <int MOD>
struct mod {
	tint x;

	mod(): x(0) {}

	mod(tint _x) {
		x = _x % MOD;
		if (x < 0) x += MOD;
	}

	mod operator+(const mod &o) const { return mod(x+o.x); }
	mod operator-(const mod &o) const { return mod(x-o.x); }
	mod operator*(const mod &o) const {  return mod(x*o.x); }
	
	// Para primos
	mod inv() const { return expo(*this,MOD-2); }

	// Para no primos
	// mod inv() const {
	// 	auto g = egcd(x,MOD);		
	// 	return mod(g.first);
	// }

	mod operator/(const mod &o) const { return (*this) * o.inv(); }

	#define op_ass(op) void operator op ## = (const mod &o) { *this = (*this) op o; }
	op_ass(+) op_ass(-) op_ass(*) op_ass(/)

	#define rel(op) bool operator op (const mod &o) const { return x op o.x; }
	rel(<) rel(<=) rel(>) rel(>=) rel(==) rel(!=)


	friend ostream& operator<<(ostream &out, const mod &m) {
		out << m.x;
		return out;
	}
};

const int MOD = 998244353;

int main() {
	vector<tint> a = {2,3,10,12,0,0,0,0}, b = {0,17,4,15,0,0,0,0};
	vector<mod<MOD>> ad(a.begin(), a.end());
	vector<mod<MOD>> bd(b.begin(), b.end());

	mod<MOD> root = expo(mod<MOD>(3), (7*17) << (23-3));

	FFT(ad,root,false);
	FFT(bd,root,false);
	forn(i,si(ad)) ad[i] *= bd[i];
	FFT(ad,root,true);

	cout << ad << endl;

	vector<tint> c(si(a));
	forn(i,si(a)) forn(j,si(b)) {
		int k = (i+j)%si(a);
		c[k] += a[i]*b[j];
	}

	cout << c << endl;


	// cout << DFT(ad, false) << endl;
	// FFT(ad, exp(complex<double>(0,-2*M_PI/si(a))), false);
	// cout << ad << endl;

	return 0;



	// vector<tint> c(8,0);
	// forn(i,8) forn(j,8) if (i+j < 8) {
	// 	c[i+j] += a[i]*b[j];
	// }
	// cout << c << endl;

	// tint R = 996173970, MOD = 998244353;	
	// cout << covolve(a,b,expomod(R,1<<15,MOD),MOD);

}