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


double determinant(vector<vector<double>> a) {
    static const double EPS = 1E-9;
    int n = si(a);

    double det = 1;
    for (int i=0; i<n; ++i) {
        int k = i;
        for (int j=i+1; j<n; ++j)
            if (abs (a[j][i]) > abs (a[k][i]))
                k = j;
        if (abs (a[k][i]) < EPS) {
            det = 0;
            break;
        }
        swap (a[i], a[k]);
        if (i != k)
            det = -det;
        det *= a[i][i];
        for (int j=i+1; j<n; ++j)
            a[i][j] /= a[i][i];
        for (int j=0; j<n; ++j)
            if (j != i && abs (a[j][i]) > EPS)
                for (int k=i+1; k<n; ++k)
                    a[j][k] -= a[i][k] * a[j][i];
    }
    return det;
}

typedef vector<double> vd;
typedef vector<vd> vvd;

vvd inverse(vvd a) {
    static const double EPS = 1e-9;
    int n = si(a);
    vvd res(n,vd(n));
    forn(i,n) res[i][i] = 1;

    forn(col,n) {
        int pick = col;
        forsn(i,pick+1,n) if (fabs(a[i][col]) > fabs(a[pick][col])) pick = i;
        if (fabs(a[pick][col]) < EPS) return vvd();

        if (pick != col) {
            swap(a[col], a[pick]);
            swap(res[col], res[pick]);
        }

        double c = a[col][col];
        forn(j,n) {
            a[col][j] /= c;
            res[col][j] /= c;
        }
        forn(i,n) if (i != col) {
            double c = a[i][col];
            forn(j,n) {
                a[i][j] -= c * a[col][j];
                res[i][j] -= c * res[col][j];
            }
        }
    }
    return res;
}

vvd operator*(vvd a, vvd b) {
    int x = si(a), y = si(a[0]), z = si(b[0]);
    vvd res(x,vd(z));
    forn(i,x) forn(k,y) forn(j,z) res[i][j] += a[i][k] * b[k][j];
    return res;
}

const int MOD = 1e9 + 7;
int expomod(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e&1) res = res*a%MOD;
        e /= 2;
        a = a*a%MOD;
    }
    return res;
}
int inverse(int x) { return expomod(x,MOD-2); }
void mult(int &x, int y) { x = (ll) x * y % MOD; }
void sub(int &x, int y) { x -= y; if (x < 0) x += MOD; }

int determinant(vector<vi> a) {
    int n = si(a); assert(si(a[0]) == n);
    forn(i,n) forn(j,n) {
        a[i][j] %= MOD; 
        if (a[i][j] < 0) a[i][j] += MOD;
    }

    int det = 1;
    forn(i,n) {
        int k = i;
        forsn(j,i+1,n) if (a[j][i]) {
            k = j;
            break;
        }
        if (!a[k][i]) return 0;
        swap(a[i], a[k]);
        if (i != k && det) det = MOD-det;
        mult(det, a[i][i]);

        int inv = inverse(a[i][i]);
        forsn(j,i+1,n) mult(a[i][j], inv);
        forn(j,n) if (j != i && a[j][i])
            forsn(k,i+1,n) sub(a[j][k], (ll) a[i][k] * a[j][i] % MOD);
    }
    return det;
}

void print(vvd a) {
    int n = si(a), m = si(a[0]);
    forn(i,n) { forn(j,m) cerr << a[i][j] << ' '; cerr << endl; }
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    vvd mat = {{10, -9, -12}, {7, -12, 11}, {-10, 10, 3}};
    print(mat); cerr << "--------------------" << endl;

    auto inv = inverse(mat);
    forn(i,3) forn(j,3) inv[i][j] *= 319;

    print(inv); cerr << "--------------------" << endl;
    




    return 0;
}

