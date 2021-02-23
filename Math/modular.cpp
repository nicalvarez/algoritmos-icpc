#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
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

	friend istream& operator>>(istream &in, mod &m) {
		tint x; in >> x; m = mod(x);
		return in;
	}
};

template<int MOD>
istream& operator>>(istream &in, mod<MOD> &a) {
	tint x; in >> x;
	a = x;
	return in;
}

template<int MOD>
ostream& operator<<(ostream &out, const mod<MOD> &a) { 
	out << a.x;
	return out;
}

int main() {}