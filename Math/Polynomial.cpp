#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

#define forn(i,n) for (int i = 0; i < n; i++)
#define si(c) ((int)(c).size())
#define mp make_pair
#define dforsn(i,a,b) for (int i = int(b)-1; i >= int(a); i--)
typedef long long tint;

tint MOD;
struct mod {
    tint x;

    mod(): x(0) {}

    mod(tint _x) {
        x = _x % MOD;
        if (x < 0) x += MOD;
    }

    void operator+=(const mod &o) { 
        x += o.x;
        if (x >= MOD) x -= MOD;
    }

    void operator-=(const mod &o) {
        x -= o.x;
        if (x < 0) x += MOD;
    } 

    void operator*=(const mod &o) {
        x *= o.x;
        if (x >= MOD) x %= MOD;
    }

    #define oper(op) mod operator op (const mod &o) const { mod res = *this; res op##= o; return res; }
    oper(+) oper(-) oper(*) oper(/)
    #undef oper

        mod operator-() const { return mod(-x); }


    static mod expo(mod x, tint e) {
        mod res = 1;
        while (e) {
            if (e&1) res *= x;
            e >>= 1;
            x *= x;
        }
        return res;
    }

    static pair<tint,tint> egcd(tint a, tint b) {
        if (a == 0) return mp(0,1);
        tint q = b/a;
        auto res = egcd(b - q*a, a);
        return mp(res.second - q*res.first, res.first);
    }

    // Para primos
    //mod inv() const { return expo(*this,MOD-2); }

    //Para no primos
    mod inv() const {
        auto g = egcd(x,MOD);		
        return mod(g.first);
    }

    void operator/=(const mod &o) { (*this) *= expo(o,MOD-2); }

    #define rel(op) bool operator op (const mod &o) const { return x op o.x; }
    rel(<) rel(<=) rel(>) rel(>=) rel(==) rel(!=)

    tint tintValue() const { return x; }

    friend ostream& operator<<(ostream &out, const mod &m) {
        out << m.x;
        return out;
    }
};


template<class T>
struct poly {
    vector<T> c;

    poly(T x0=0): c(1,T(x0)) {}
    poly(const vector<T> &c): c(c) {}

    size_t size() { return c.size(); }

    T eval(T x) {
        T res = 0;
        dforsn(i,0,si(c)) res = res*x + c[i];
        return res;
    }

    void operator+=(const poly &o) {
        int m = si(c), n = si(o.c);
        if (n > m) c.resize(n,0);
        forn(i,n) c[i] += o.c[i];
    }

    void operator-=(const poly &o) {
        int m = si(c), n = si(o.c);
        if (n > m) c.resize(n,0);
        forn(i,n) c[i] -= o.c[i];
    }

    #define oper(op) poly operator op (const poly &o) const { poly res = *this; res op##= o; return res; }
    oper(+) oper(-)

    poly operator*(const poly &o) const {
        int m = si(c), n = si(o.c);
        vector<T> res(m+n-1,0);
        forn(i,m) forn(j,n) res[i+j] += c[i]*o.c[j];
        return poly(res);
    }

    #define opass(op) void operator op##= (const poly &o) { *this = (*this) op o; }
    opass(*)

    friend ostream& operator<<(ostream &out, const poly &p) {
        dforsn(i,0,si(p.c)) out << p.c[i] << ' ';
        return out;
    }

};

//struct poly {
    //vector<int> c;

    //poly () {};
    //poly (const vector<int> &c): c(c) {}

    //void operator+=(const poly &o) {
        //int n = si(o);
        //c.resize(max(si(c), n), 0);
        //forn(i,n) {
            //c[i] += o.c[i];
            //if (c[i] >= MOD) c[i] -= MOD;
        //}
    //}

    //poly operator+(const poly &o) const { poly res = *this; res += o; return res; }
    //poly operator-(const poly &o) const { poly res = *this; res -= o; return res; }

    //void operator-=(const poly &o) {
        //int n = si(o);
        //c.resize(max(si(c), n), 0);
        //forn(i,n) {
            //c[i] -= o.c[i];
            //if (c[i] < 0) c[i] += MOD;
        //}
    //}

    //friend poly simpleMult(const poly &p, const poly &q) {
        //int m = si(p), n = si(q);
        //poly res; res.c.resize(m+n-1,0);
        //forn(i,m) forn(j,n) {
            //res.c[i+j] += p.c[i] * tint(q.c[j]) % MOD;
            //if (res.c[i+j] >= MOD) res.c[i+j] -= MOD;
        //}
        //return res;
    //}

    //void split(int N, poly &a, poly &b) {
        //a = poly(vector<int>(c.begin(), c.begin()+N)); 
        //b = poly(vector<int>(c.begin()+N, c.end())); 
    //}

    //poly operator<<(int shift) {
        //vector<int> res(shift,0);
        //forn(i,si(c)) res.pb(c[i]);
        //return poly(res);
    //}

    //friend poly karatsubaMult(const poly &P, const poly &Q) {
        //poly p = P, q = Q;
        //int m = si(p), n = si(q);
        //int N = max(m,n);

        //if (N < 50) return simpleMult(p,q);

        //p.c.resize(N,0);
        //q.c.resize(N,0);

        //N /= 2;
        //poly p1,p2; p.split(N, p1, p2);
        //poly q1,q2; q.split(N, q1, q2);
        //poly z0 = karatsubaMult(p1,q1),
             //z2 = karatsubaMult(p2,q2),
             //z1 = karatsubaMult(p1+p2, q1+q2) - z0 - z2;

        //return z0 + (z1 << N) + (z2 << (2*N));
    //}

    //poly operator*(const poly &o) const {
        //poly p = *this;
        //return karatsubaMult(p,o);
    //}

    //int size() const { return si(c); }

    //friend ostream& operator<<(ostream &out, const poly &p) {
        //for (int x : p.c) out << x << ' ';
        //return out;
    //}
//};

template<class T>
poly<T> interpolate(const vector<T> &x, const vector<T> &y) {
    poly<T> res = T(0), prod = T(1);
    int n = si(x); assert(n == si(y));
    forn(i,n) {
        res.eval(x[i]);
        T ck = (y[i] - res.eval(x[i])) / prod.eval(x[i]);
        res += poly<T>(ck)*prod;
        prod *= poly<T>(vector<T>{-x[i],1}); 
    }
    return res;
}

const int MAXK = 2100;
tint dp[2*MAXK][2*MAXK];

#define pb push_back
struct CandyDrawing {
int findProbability(int N, int K, int MOD) {
    if (K == 0) return 1;
    ::MOD = MOD;
    dp[0][0] = 1; 
    vector<mod> x, y;
    x.pb(mod(0)); y.pb(mod(0));
    for (int n = 1; n <= 2*K; n++) {
        dp[n][0] = 1; dp[n][n+1] = 0;
        for (int k = 1; k <= n; k++) {
            dp[n][k] = dp[n-1][k] + n*dp[n-1][k-1]%MOD;
            if (dp[n][k] >= MOD) dp[n][k] -= MOD; 
        }
        x.pb(mod(n));
        y.pb(mod(dp[n][K]));
    }
    poly<mod> p = interpolate(x,y);
    cerr << p << endl;
    return p.eval(N).tintValue();
}
};

int main(int argc, char *argv[])
{
    CandyDrawing sol;
    //cout << sol.findProbability(602841311, 1650, 1999997777) << endl;
    cout << sol.findProbability(10,6,7) << endl;
    //cout << sol.findProbability(1000000000,1000,int(1e9 + 9));
    return 0;
}
