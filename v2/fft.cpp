#include <bits/stdc++.h>
using namespace std;
 
#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define eb emplace_back
#define mp make_pair
 
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

template<int N>
struct mod {
    static const int MOD = N;

    // For MOD = 998244353, root = 3 works
    static const int root = 3;

    int value;

    mod(ll value=0) {
        this->value = value % MOD;
        if (this->value < 0) value += MOD;
    }

    bool operator==(const mod &o) const { return value == o.value; }
    bool operator!=(const mod &o) const { return value != o.value; }


    mod &operator+=(const mod &o) {
        value += o.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    friend mod operator+(mod a, const mod &b) {
        return a += b;
    }

    mod &operator-=(const mod &o) {
        value -= o.value;
        if (value < 0) value += MOD;
        return *this;
    }

    friend mod operator-(mod a, const mod &b) {
        return a -= b;
    }

    mod &operator*=(const mod &o) {
        value = (ll) value * o.value % MOD;
        return *this;
    }

    friend mod operator*(mod a, const mod &b) {
        return a *= b;
    }

    int _inv(int a, int m) const {
        if (a <= 1) return a; 
        auto k = -_inv(m%a,a);
        if (k < 0) k += a;
        return ((ll)m*k+1) / a;
    }

    mod inverse() const {
        return (mod) {_inv(value, MOD)};
    }

    mod &operator/=(const mod &o) {
        return (*this) *= o.inverse();
    }

    friend mod operator/(mod a, const mod &b) {
        return a /= b;
    }

    mod operator^(ll e) {
        mod ans = 1, a = *this;
        while (e > 0) {
            if (e&1) ans *= a;
            e /= 2;
            a *= a;
        }
        return ans;
    }

    friend ostream &operator<<(ostream &out, mod m) {
        out << m.value;
        return out;
    }
};

namespace fft {
    template<class T>
    vector<T> fft(vector<T> a, T w, bool inv) {
        int n = si(a);
        int k = 0; while ((1<<k) < n) k++;
        assert ((1<<k) == n);

        vector<int> rev(n);
        rev[0] = 0; forsn(i,1,n) rev[i] = (rev[i>>1]>>1) | ((i&1) << (k-1));
        forn(i,n) if (rev[i] < i) swap(a[i], a[rev[i]]);

        vector<T> r(k);
        if (inv) w = T(1) / w;
        r[k-1] = w;
        dforsn(i,0,k-1) r[i] = r[i+1]*r[i+1];

        forn(l,k) {
            int step = 1<<l;
            for (int i = 0; i < n; i += 2*step) {
                T ri = 1;
                for (int j = i; j < i+step; j++) {
                    T t = ri * a[j+step];
                    a[j+step] = a[j] - t;
                    a[j] += t;
                    ri *= r[l];
                }
            }
        }
        if (inv) {
            T invn = T(1) / T(n);
            forn(i,n) a[i] *= invn;
        }
        return a;
    }

    template<class T>
    vector<T> _mult(vector<T> a, vector<T> b, T w) {
        auto ta = fft(a, w, 0);
        auto tb = fft(b, w, 0);
        forn(i,si(a)) ta[i] *= tb[i];
        auto c = fft(ta, w, 1);
        return c;
    }

    const double PI = acos(-1);
    typedef complex<double> comp;
    vector<comp> multiply(vector<comp> a, vector<comp> b) {
        int n = si(a), m = si(b);
        int sz = 1; while (sz < n+m) sz *= 2;
        a.resize(sz); b.resize(sz);
        auto w = exp(comp(0,2*PI/sz));
        return _mult(a,b,w);
    }

    template<class M>
    vector<M> multiply(vector<M> a, vector<M> b) {
        int n = si(a), m = si(b);
        int sz = 1; while (sz < n+m) sz *= 2;
        a.resize(sz); b.resize(sz);
        auto w = M(M::root) ^ ((M::MOD-1) / sz);
        return _mult(a,b,w);
    }
}

/*
    Times:
        product: 60 ms
        inverse: 220 ms
        log: 250 ms
        sqrt: 400 ms
        exp: 650 ms
        power: 900 ms
*/
template<class T>
struct series {

    vector<T> a;

    series(T a0=0) {
        a = vector<T>{a0};
    }

    series(const vector<T> a): a(a) {}

    series cap(int n) {
        series ans = *this;
        if (si(ans.a) > n) ans.a.resize(n);
        return ans;
    }

    friend series operator+(const series &p, const series &q) {
        int n = max(si(p.a), si(q.a));
        vector<T> ans(n);
        forn(i,n) {
            if (i < si(p.a)) ans[i] += p.a[i];
            if (i < si(q.a)) ans[i] += q.a[i];
        }
        return series(ans);
    }

    friend series operator-(const series &p, const series &q) {
        int n = max(si(p.a), si(q.a));
        vector<T> ans(n);
        forn(i,n) {
            if (i < si(p.a)) ans[i] += p.a[i];
            if (i < si(q.a)) ans[i] -= q.a[i];
        }
        return series(ans);
    }

    series &operator*=(const series &o) {
        a = fft::multiply(a,o.a);
        return *this;
    }

    friend series operator*(series p, const series &q) {
        return p *= q;
    }

    friend series operator*(T k, series p) {
        forn(i,si(p.a)) p.a[i] *= k;
        return p;
    }

    series derivative(int n) {
        series ans;
        int sz = min(n, si(a)-1);
        ans.a.resize(sz);
        for (int i = 1; i <= sz; i++) {
            ans.a[i-1] = T(i) * a[i];
        }
        return ans;
    }

    series integral(int n) {
        series ans;
        int sz = min(n, si(a)+1);
        ans.a.resize(n);
        forn(i,n-1) ans.a[i+1] = a[i] / T(i+1);
        return ans;
    }

    series inverse(int n) {
        int sz = 0;
        series a_cap, ans = T(1) / a[0];
        a_cap.a.clear();
        for (int k = 1; sz < n; k++) {
            a_cap.a.reserve(sz);
            while (sz < (1<<k)) {
                if (sz < si(a)) 
                    a_cap.a.pb(a[sz]);
                sz++;
            }
            ans *= series(2) - (a_cap * ans).cap(sz);
            if (si(ans.a) > sz) ans.a.resize(sz);
        }
        return ans;
    }

    series sqrt(int n, T b0) {
        int sz = 0;
        series a_cap, ans = b0;
        a_cap.a.clear();
        for (int k = 1; si(ans.a) < n; k++) {
            while (sz < (1<<k)) {
                if (sz < si(a)) 
                    a_cap.a.pb(a[sz]);
                sz++;
            }
            ans = T(1)/2 * (ans + a_cap * ans.inverse(sz)).cap(sz);
            if (si(ans.a) > sz) ans.a.resize(sz);
        }
        return ans;
    }

    // a[0] should be 1
    series log(int n) {
        auto ans = (this->derivative(n) * this->inverse(n)).integral(n);
        if (si(ans.a) > n) ans.a.resize(n);
        return ans;
    }

    // a[0] should be 0
    series exp(int n) {
        int sz = 0;
        series a_cap, ans = T(1);
        a_cap.a.clear();
        for (int k = 1; sz < n; k++) {
            while (sz < (1<<k)) {
                if (sz < si(a)) 
                    a_cap.a.pb(a[sz]);
                sz++;
            }
            ans *= series(1) + a_cap - ans.log(sz);
            if (si(ans.a) > sz) ans.a.resize(sz);
        }
        return ans;
    }

    // compute a^k modulo x^n
    // a[0] should be != 0
    series power(int n, ll k) {
        series ans = *this;
        auto a0 = ans.a[0];
        auto inv_a0 = T(1) / a0;
        forn(i,si(ans.a)) 
            ans.a[i] *= inv_a0;
        return (a0^k) * (k * ans.log(n)).exp(n);
    }

    friend ostream &operator<<(ostream &out, const series &s) {
        for (auto x : s.a) out << x << ' ';
        return out;
    }
};

const int MOD = 998244353; 

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    vi a = {1,5,7,-1,5};
    vi b = {4,7,17};
    vi c(si(a)+si(b));
    forn(i,si(a)) forn(j,si(b)) c[i+j] += a[i]*b[j];
    for (auto x : c) cerr << real(x) << ' '; cerr << endl;

    {
        vector<fft::comp> at, bt;
        for (auto x : a) at.eb(x);
        for (auto y : b) bt.eb(y);
        auto c = fft::multiply(at,bt);
        for (auto x : c) cerr << real(x) << ' '; cerr << endl;
    }

    {
        int sz = 32;
        vector<mod<MOD>> pt = {1,-4};
        auto ps = series(pt);
        //auto catalan = 2 * (series(mod<MOD>(1)) + ps.sqrt(sz,1)).inverse(sz);
        auto catalan = series(mod<MOD>(2)).inverse(sz) * (series(mod<MOD>(1)) - ps.sqrt(sz,1));
        cerr << "catalan: "; forn(i,sz) cerr << catalan.a[i] << ' '; cerr << endl;
        //auto s = 2 * (series(1) + series(vector<mod<MOD>>{1,-4}).sqrt(32,1)).inverse();
    }

    {
        vector<mod<MOD>> at, bt;
        for (auto x : a) at.eb(x);
        for (auto y : b) bt.eb(y);
        auto c = fft::multiply(at,bt);
        for (auto x : c) cerr << x.value << ' '; cerr << endl;

        auto as = series(at);
        cerr << "a: "; forn(i,si(as.a)) cerr << as.a[i] << ' '; cerr << endl;

        int sz = 32;
        auto inv = as.inverse(sz);
        auto root = as.sqrt(sz, 1);
        {
            vi check(sz);
            cerr << "root: "; forn(i,sz) cerr << root.a[i] << ' '; cerr << endl;
            forn(i,si(root.a)) forn(j,si(root.a)) {
                if (i+j < sz){ 
                    check[i+j] += (ll) root.a[i].value * root.a[j].value % MOD;
                    if (check[i+j] >= MOD) check[i+j] -= MOD;
                }
            }
            cerr << "check: "; forn(i,sz) cerr << check[i] << ' '; cerr << endl;
        }

        {
            cerr << "inv: "; forn(i,sz) cerr << inv.a[i] << ' '; cerr << endl;
            vi check(sz);
            forn(i,si(a)) forn(j,si(inv.a)) {
                if (i+j < sz) {
                    check[i+j] += (ll) a[i] * inv.a[j].value % MOD;
                    if (check[i+j] >= MOD) check[i+j] -= MOD;
                }
            }
            cerr << "check: "; forn(i,sz) cerr << check[i] << ' '; cerr << endl;
        }
    }
    {
        int sz = 32;
        vector<fft::comp> a = {1,-1};
        auto s = series(a);
        auto l = s.inverse(sz).log(sz);
        cerr << "log: "; forn(i,sz) cerr << real(l.a[i])*i << ' '; cerr << endl;

    }
    if (false) {
        int sz = 32;
        vector<mod<MOD>> fact(sz);
        fact[0] = 1;
        forsn(n,1,sz) fact[n] = fact[n-1] * n;

        vector<mod<MOD>> a = {0,1};
        auto s = series(a);
        auto e = (s.exp(sz) - series(mod<MOD>(1))).exp(sz);
        cerr << "e^x: "; forn(i,sz) cerr << e.a[i]*fact[i] << ' '; cerr << endl;
    }
    {
        int sz = 1<<17;
        series<mod<MOD>> s = vector<mod<MOD>>{1,1};
        auto l = s.power(sz,1e9 + 7);
        //auto l = s.exp(sz);
        cerr << "log: "; forn(i,32) cerr << l.a[i] << ' '; cerr << endl;

//        auto raiz = l.sqrt(sz,1);
//        cerr << "sqrt: "; forn(i,32) cerr << raiz.a[i] << ' '; cerr << endl;

        //auto e = s.power(sz,10);
        //cerr << "comb(10,*): "; forn(i,32) cerr << e.a[i] << ' '; cerr << endl;

        //auto e2 = e.inverse(sz);
        //cerr << "e2: "; forn(i,32) cerr << e2.a[i] << ' '; cerr << endl;

        //auto square = e*e;
        //cerr << "square: "; forn(i,32) cerr << square.a[i] << ' '; cerr << endl;
    }

    return 0;
}
