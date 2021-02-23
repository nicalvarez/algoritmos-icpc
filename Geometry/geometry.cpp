#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
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

//BEGIN CODE
const double EPS = 1e-8;

template<class T>
T myabs(T x) { return x < 0 ? -x : x; }

template<class T>
bool equal(T x, T y) { return myabs(x-y) < EPS; }

template <class T>
struct point {
	T x,y;

	point(T x = 0, T y = 0): x(x), y(y) {}

	point operator+(const point &o) const { return (point){x + o.x, y + o.y}; }
	point operator-(const point &o) const { return (point){x - o.x, y - o.y}; }
	T operator*(const point &o) const { return x*o.x + y*o.y; }
	T operator^(const point &o) const { return x*o.y - y*o.x; }
	point operator*(T k) const { return (point){k*x, k*y}; }
	friend point operator*(T k, const point &p) { return (point){k*p.x, k*p.y}; }
	point operator/(T k) const { return (point){x/k, y/k}; }

	void operator+=(const point &o) { *this = *this + o; }
	void operator-=(const point &o) { *this = *this - o; }
	void operator*=(T k) { *this = (*this) * k; }
	void operator/=(T k) { *this = (*this) / k; }

	T len2() const { return (*this) * (*this); }
	double len() const { return sqrt(len2()); }
	point normalize() const { return (*this) / len(); }

	T dist(const point &o) const { return (*this - o).len(); }

	point rotate(point rot) { return (point){x*rot.x - y*rot.y, x*rot.y + y*rot.x}; }
	point rotate(T angle, T ratio=1) { return rotate(ratio * (point){cos(angle), sin(angle)}); }

	T angle() const { return atan2(y,x); }

    T angle(const point &o) const {
        return o.angle() - angle();
    }

	bool operator<(const point &o) const { return x != o.x ? x < o.x : y < o.y; }	
	friend istream& operator>>(istream &in, point &p) { in >> p.x >> p.y; return in; }
	friend ostream& operator<<(ostream &out, const point &p) { out << '(' << p.x << ',' << p.y << ')'; return out; }
};

double canonicalAngle(double ang) {
    while (ang > M_PI) ang -= 2*M_PI;
    while (ang <= -M_PI) ang += 2*M_PI;
    return ang;
}

double positiveAngle(double ang) {
    while (ang > 2*M_PI - EPS) ang -= 2*M_PI;
    while (ang < -EPS) ang += 2*M_PI;
    return ang;
}

bool operator==(const point<double> &p, const point<double> &q) {
    return p.dist(q) < EPS;
}

bool operator==(const point<int> &p, const point<int> &q) {
    return (p-q).len2() == 0; 
}

bool operator==(const point<tint> &p, const point<tint> &q) {
    return (p-q).len2() == 0; 
}

template<class T>
bool operator!=(const point<T> &p, const point<T> &q) {
    return !(p == q);
}


template<class T> 
T angle(const point<T> &o, const point<T> &a, const point<T> &b) {
	T ab = a.dist(b), oa = o.dist(a), ob = o.dist(b);
	T cosang = (oa*oa + ob*ob - ab*ab) / (2*oa*ob);
	return acos(cosang);
}


template <class T>
T area(const point<T> &a, const point<T> &b, const point<T> &c) { return (b-a) ^ (c-a); }

template <class T>
T area(const vector<point<T> > &p) { 
	T res = 0;
	int n = si(p);
	forn(i,n) {
		int j = (i+1) % n;
		res += p[i] ^ p[j];
	}
	return .5 * res;
}

// Reemplazar las comparaciones <= por < cuando se quieren permitir puntos alineados
template <class T>
vector<int> convex_hull(const vector<point<T> > &p) {
	vector<point<T> > res;
	int n = si(p), k = 0;
	sort(all(p));
	forn(i,n) {
		while (k >= 2 && area(p[res[k-2]], p[res[k-1]], p[i]) <= 0) { k--; res.pop_back(); }
		res.pb(i);
	}
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && area(p[res[k-2]], p[res[k-1]], p[i]) <= 0) { k--; res.pop_back(); }
		res.pb(i);
	}
	return res;
}

template<class T>
bool point_in_poly(const vector<point<T> > &v, const point<T> &p) {
    bool res = false;
    int n = si(v);
    forn(i,n) {
        int j = i+1; if (j >= n) j -= n;
        int lo = i, hi = j;
        if (v[lo].y > v[hi].y) swap(lo,hi);
        if (v[lo].y <= p.y && p.y < v[hi].y && area(v[lo], v[hi], p) > 0) 
            res = !res;
    }
    return res;
}

template<class T>
bool point_in_poly_angle(const vector<point<T> > &v, const point<T> &p) {

    int n = si(v);
    double total = 0;
    forn(i, n) {
        int j = i+1; if (j >= n) j -= n;
        total += canonicalAngle((v[i]-p).angle(v[j]-p));
    }
    return fabs(total) > M_PI;
}

template<class T>
struct line {
    point<T> n;
    T c;

    line() {}

    line(const point<T> &p, const point<T> &q) {
        point<T> d = q-p;
        n = (point<T>){-d.y, d.x};
        c = n*p;
    }

    line(const point<double> &p, double angle) {
        point<double> d(cos(angle), sin(angle));
        n = (point<double>){-d.y, d.x};
        c = n*p;
    }

    void normalize() {
        double l = n.len();
        n /= l;
        c /= l;
    }

    line parallel(const point<T> &p ) const {
        line res = *this;
        res.c = res.n * p;
        return res;
    }

    line perpendicular(const point<T> &q ) const {
        line res;
        res.n = (point<T>){-n.y, n.x};
        res.c = res.n * q;
        return res;
    }

    double dist(const point<T> &p) const {
        return (n*p - c) / n.len();
    }

    // TODO: Testear
    point<double> project(const point<T> &p) {
        double d = dist(p);
        point<double> pd(p.x,p.y);
        return pd - n*(d / n.len());
    }

    bool isParallel(const line &o) const {
        return fabs(n ^ o.n) < EPS;
    }

    // TODO
    bool operator==(const line &o) const {

    }

    point<double> intersection(const line &o) const {
        point<double> A(n.x, o.n.x), B(n.y, o.n.y), C(c, o.c);
        double detX = C^B, detY = A^C, det = A^B;
        return point<double>(detX/det, detY/det);
    }

    bool belongs(const point<T> &p) const {
        return fabs((n^p) - c) < EPS;
    }
};

template <class T>
line<T> mediatriz(const point<T> &p, const point<T> &q) {
    point<T> m = (p+q) / T(2);
    return line<T>(p,q).perpendicular(m);
}

line<double> bisectriz(const point<double> &o, const point<double> &a, const point<double> &b) {
    point<double> na = o + (a-o).normalize(), nb = o + (b-o).normalize();
    return line<double>(o, (na+nb)/2);
} 

template <class T>
point<T> baricentro(const point<T> &a, const point<T> &b, const point<T> &c) {
    return (a+b+c) / T(3);
} 

template <class T>
point<double> circuncentro(const point<T> &a, const point<T> &b, const point<T> &c) {
    return mediatriz(a,b).intersection(mediatriz(b,c));
}

template <class T>
point<double> incentro(const point<T> &a, const point<T> &b, const point<T> &c) {
    return bisectriz(a,b,c).intersection(bisectriz(b,c,a));
}

template <class T>
point<double> ortocentro(const point<T> &a, const point<T> &b, const point<T> &c) {
    line<T> h1 = line<T>(a,b).perpendicular(c);
    line<T> h2 = line<T>(b,c).perpendicular(a);
    return h1.intersection(h2);
}

template <class T>
struct segment {
    point<T> p,q;
    line<T> l;

    segment(const point<T> &p, const point<T> &q): p(p), q(q), l(p,q) {}

};

template <class T>
double triangleInequality(T a, T b, T c) {
    T sum = a+b+c;
    T mx = max(max(a,b),c);
    return 2*mx - sum;
}

template <class T>
struct circle {
    point<T> o;
    T r;

    vector<point<double>> inter(const line<T> &l) const {
        double a = l.n.x, b = l.n.y, c = l.c;
        c -= a*o.x + b*o.y;

        double norm = sqrt(a*a + b*b);
        a /= norm; b /= norm; c /= norm;

        vector<point<double>> res;
        double disc = r*r - c*c;
        if (disc < 0) return res;
        if (disc > 0) {
            disc = sqrt(disc);
            res.push_back((point<double>){o.x + a*c + b*disc, o.y + b*c - a*disc});
            res.push_back((point<double>){o.x + a*c - b*disc, o.y + b*c + a*disc});
            return res;
        }
        res.push_back((point<double>){o.x + a*c, o.y + b*c});
        return res;
    }

    vector<point<double>> inter(const circle &c) const {
        vector<point<double>> res;

        double r1 = r, r2 = c.r, d = (c.o - o).len();
        if (d < EPS) return res;
        double ineq = triangleInequality(r1,r2,d);
        if (ineq < -EPS) { // 2 points
            point<T> dir = (c.o - o).normalize();
            double eq1 = d, eq2 = (r1*r1 - r2*r2) / d;
            double x = (eq1+eq2)/2;
            point<double> p = o + dir*x;
            return inter(line<double>(o,c.o).perpendicular(p));
        }
        else if (ineq < EPS) { // 1 point
            point<T> dir = (c.o - o).normalize();
            res.push_back(o+dir*r);
            return res;
        }
        return res;
    }
};



/*************************

point_in_poly(vector<point> p, point x)

struct line
	point normal;
	T d;

	// constructor dados dos puntos
	line(point, point)

	line(point, T angle)

	// Pasa la normal a longitud 1
	void normalize()

	// paralela que pasa por x
	line parallel(point x)

	// perpendicular por x
	line perpendicular(point x = {0,0})

	// distancia a un punto x
	T dist(point x)

	// proyeccion de x sobre la linea
	point proy(point x)

	bool isParallel(line o)

	bool operator==(line o) const 

	// intersección con línea o
	point inter(line o)

	// determina si x está en la línea
	bool belongs(point x)

line mediatriz(point a, point b)
line bisectriz(point o, point a, point b)

point baricentro(point a, point b, point c)
point circuncentro(point a, point b, point c)
point incentro(point a, point b, point c)
point ortocentro(point a, point b, point c)


tint area(const point &a, const point &b, const point &c) {
    return (b-a) ^ (c-a);
}

int sign(tint x) { 
    if (x < 0) return -1;
    if (x > 0) return +1;
    return 0;
}

bool intersect(const point &a, const point &b, const point &c, const point &d) {
    if (max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, b.x)) return false;
    if (max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)) return false;

    int sc = sign(area(a,b,c)), sd = sign(area(a,b,d));
    if (sc != 0 && sc == sd) return false;

    int sa = sign(area(c,d,a)), sb = sign(area(c,d,b));
    if (sa != 0 && sa == sb) return false;

    return true;
}



struct segment
	point a,b;

	T dist(point x)

	// Esta x en (a,b)
	bool belongs(point x) { (p-a).len() + (p-b).len() ==feq (a-b).len() }

bool hayInter(line l, segment s);
point inter(line l, segment s);

struct circle
	point c;
	T r;

	vector<point> inter(line o)
	vector<point> inter(circle o)


*************************/


int main() {
	//point<double> a = {2,1}, b = {3,5};

	//cout << a << ' ' << b << endl;
	//cout << a+b << endl;
	//cout << a - b << endl;
	//cout << a * b << endl;
	//cout << (a ^ b) << endl;

	//cout << 10*b << endl;
	//cout << (a+b)*0.5 << endl;

	//a += {10,10};
	//cout <<a  << endl;
} 
