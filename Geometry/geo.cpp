#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << "=" << (a) << endl;
#define pb push_back
#define eb emplace_back
#define mp make_pair

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const double PI = acos(-1);
const double EPS = 1e-9;


namespace geo {

    using T = double;
    using point = complex<T>;

    struct indexed_point : public complex<double> {
        int index;
    };

    double dot(point a, point b) { return real(conj(a)*b); }
    double cross(point a, point b) { return imag(conj(a)*b); }
    double len(point a) { return abs(a); }
    double len2(point a) { return dot(a,a); }
    point normalize(point a)  { return a / abs(a); }
    point rotate(point a, double theta) { return a * exp(point(0,theta)); }
    double angle(point a) { return arg(a); }
    bool btw(point a, point b, point x) {
        double ineq = abs(a-b) - abs(a-x) - abs(x-b);
        return abs(ineq) < EPS;
    }


    double canonicalAngle(double ang) {
        while (ang > PI) ang -= 2*PI;
        while (ang <= -PI) ang += 2*PI;
        return ang;
    }

    double positiveAngle(double ang) {
        while (ang > 2*PI - EPS) ang -= 2*PI;
        while (ang < -EPS) ang += 2*PI;
        return ang;
    }

    double angle(point a, point o, point b) {
        return canonicalAngle(angle(b-o) - angle(a-o));
    }

    double area(const vector<point> &p) {
        int n = si(p);
        double ans = 0;
        for (int i = 0, j = 1; i < n; i++, j++)
            ans += cross(p[i], p[j%n]);
        return ans / 2;
    }

    vector<point> chull(vector<point> p) {
        auto cmp = [](point a, point b) {
            return mp(real(a), imag(a)) < mp(real(b), imag(b)); 
        };

        auto bad = [](point a, point b, point c) {
            auto C = cross(a-b,c-b);
            auto D = dot(a-b, c-b);
            return C < 0 || (C == 0 && D <= 0);
        };

        sort(all(p), cmp);
        p.erase(unique(all(p)), p.end());

        vector<point> hull;
        int n = si(p);
        forn(i,2*n-1) {
            int idx = (n-1) - (abs(n-1-i));
            while (si(hull) >= 2 && bad(hull.end()[-2], hull.end()[-1], p[idx])) hull.pop_back();
            hull.pb(p[idx]);
        }
        hull.pop_back();
        reverse(hull.begin()+1, hull.end());
        return hull;
    }

    double in_poly(const vector<point> &p, point x) {
        int n = si(p);
        double ang = 0;
        forn(i,n) {
            int j = (i+1) % n;
            if (btw(p[i], p[j], x)) return true;
            ang += canonicalAngle(arg(p[j]-x) - arg(p[i]-x));
        }
        return abs(ang) > PI;
    }

    struct halfplane {
        point p, v;
        halfplane(point p, point v): p(p), v(v) {}

        int sign(point x) {
            auto C = cross(v, x-p);
            if (abs(C) < EPS) return 0;
            return C < 0 ? -1 : +1;
        }

        point inter(point a, point b) {
            double t = cross(a-p, b-a) / cross(v, b-a);
            return p + v*t;
        }

    };

    vector<point> cut(const vector<point> &p, halfplane h) {
        vector<point> ans;
        int n = si(p);
        forn(i,n) {
            point a = p[i], b = p[(i+1)%n];
            auto sa = h.sign(a), sb = h.sign(b);
            if (sa >= 0) ans.pb(a);
            if (sa*sb == -1) ans.pb(h.inter(a,b));
        }
        return ans;
    }

    bool inside(vector<point> &p, point x) {
        int n = si(p);
        auto C1 = cross(x-p[0], p[1]-p[0]);
        auto C2 = cross(x-p[0], p[n-1]-p[0]);

        if (C1 < 0 && C2 > 0) {
            int lo = 0, hi = n-1;
            while (lo+1 < hi) {
                auto mi = (lo+hi) / 2;
                if (cross(x-p[0], p[mi]-p[0]) >= 0) hi = mi;
                else lo = mi;
            }
            return cross(p[hi]-p[lo], x-p[lo]) >= 0;
        }

        if (C1 == 0) {
            auto D1 = dot(x-p[0], p[1]-p[0]);
            auto D2 = dot(p[1]-p[0], p[1]-p[0]);
            return D1 >= 0 && D1 <= D2;
        }
        if (C2 == 0) {
            auto D1 = dot(x-p[0], p[n-1]-p[0]);
            auto D2 = dot(p[n-1]-p[0], p[n-1]-p[0]);
            return D1 >= 0 && D1 <= D2;
        }
        return false;
    }

    // right,left tangents
    pair<point,point> tangent(vector<point> &p, point x) {
        int n = si(p);
        pair<point,point> ans;

        auto find_one = [&](auto cmp) {
            if (cmp(0,n-1)) return 0;
            int lo = 0, hi = n-1;
            while (lo+1 < hi) {
                auto mi = (lo+hi) / 2;
                if (cmp(lo, mi)) lo = mi;
                else hi = mi;
            }
            return hi;
        };

        auto cmpRight = [&](int i, int j) {
            auto ci = cross(p[i]-x, p[(i+1)%n] - p[i]);
            auto di = dot(p[i]-x, p[(i+1)%n] - p[i]);
            bool li = ci < 0 || (ci == 0 && di > 0);

            auto cj = cross(p[j]-x, p[(j+1)%n] - p[j]);
            auto dj = dot(p[j]-x, p[(j+1)%n] - p[j]);
            bool lj = cj < 0 || (cj == 0 && dj > 0);

            if (li != lj) return li < lj;

            if (li) return cross(p[j]-x, p[i]-x) > 0;
            else return cross(p[j]-x, p[i]-x) < 0;
        };
        ans.first = p[find_one(cmpRight)];

        auto cmpLeft = [&](int i, int j) {
            auto ci = cross(p[i]-x, p[(i+1)%n] - p[i]);
            auto di = dot(p[i]-x, p[(i+1)%n] - p[i]);
            bool li = ci < 0 || (ci == 0 && di > 0);

            auto cj = cross(p[j]-x, p[(j+1)%n] - p[j]);
            auto dj = dot(p[j]-x, p[(j+1)%n] - p[j]);
            bool lj = cj < 0 || (cj == 0 && dj > 0);

            if (li != lj) return li > lj;

            if (li) return cross(p[j]-x, p[i]-x) > 0;
            else return cross(p[j]-x, p[i]-x) < 0;
        };
        ans.second = p[find_one(cmpLeft)];
        return ans;
    }

}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}
