int gcd(int a, int b) { return b != 0 ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a!=0 || b!=0 ? a / gcd(a,b) * b : 0; }

class fraction {
	void norm() { int g = gcd(n,d); n/=g; d/=g; if( d<0 ) { n=-n; d=-d; } }
	int n, d;

public:
	fraction() : n(0), d(1) {}
	fraction(int n_, int d_) : n(n_), d(d_) {
		assert(d != 0);
		norm();
	}

	fraction operator+(const fraction& f) const {
		int m = lcm(d, f.d);
		return fraction(m/d*n + m/f.d*f.n, m);
	}
	fraction operator-() const { return fraction(-n,d); }
	fraction operator-(const fraction& f) const { return *this + (-f); }
	fraction operator*(const fraction& f) const { return fraction(n*f.n, d*f.d); }
	fraction operator/(const fraction& f) const { return fraction(n*f.d, d*f.n); }

	bool fraction::operator<(const fraction& f) const { return n*f.d < f.n*d; }
	
	friend std::ostream& operator<<(std::ostream&, const fraction&);
};

ostream& operator<<(ostream& os, const fraction& f) {
	os << f.n;
	if(f.d != 1 && f.n != 0) os << '/' << f.d;
	return os;	
}
