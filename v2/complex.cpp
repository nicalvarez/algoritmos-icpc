struct comp {
	double re,im;
	comp(double re=0, double im=0): re(re), im(im) {}
};

comp operator+(const comp &a, const comp &b) { return {a.re + b.re, a.im + b.im}; }
comp operator-(const comp &a, const comp &b) { return {a.re - b.re, a.im - b.im}; }
comp operator*(const comp &a, const comp &b) { return {a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re}; }
void operator*=(comp &a, const comp &b) { a = a*b; }
ostream& operator<<(ostream &out, const comp &a) { out << a.re << " + " << a.im << 'i'; return out; }