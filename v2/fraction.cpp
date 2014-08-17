#include <bits/stdc++.h>
using namespace std;

typedef long long tint;


tint gcd(tint a, tint b) { return a ? gcd(b%a, a): b; }
tint lcm(tint a, tint b) { return a / gcd(a,b) * b; }
struct fraction {
	tint a,b;

	fraction(): a(0),b(1) {}
	fraction(tint a, tint b=1): a(a), b(b) { 
		norm();
	}

	void norm() {
		tint d = gcd(a,b);
		a /= d; b /= d;
		if (b < 0) { a = -a; b = -b; }
	}
};

fraction operator+(const fraction &x, const fraction &y) {
	tint m = lcm(x.b, y.b);
	return fraction(m/x.b * x.a + m/y.b * y.a, m);
}

fraction operator-(const fraction &x) { return fraction(-x.a,x.b); }
fraction operator-(const fraction &x, const fraction &y) { return x + (-y); }
fraction operator*(const fraction &x, const fraction &y) { return fraction(x.a*y.a, x.b*y.b); }
fraction operator/(const fraction &x, const fraction &y) { return fraction(x.a*y.b, x.b*y.a); }

#define ass(op) void operator op ## = (fraction& a, const fraction &b) { a = a op b; }
ass(+) ass(-) ass(*) ass(/)

#define comp(op) bool operator op (const fraction &x ,const fraction &y) { return x.a*y.b op y.a*x.b; }
comp(<) comp(>) comp(<=) comp(>=) comp(==) comp(!=)

ostream& operator<<(ostream &out, const fraction &x) { out << x.a << '/' << x.b; return out; }

int main() {}