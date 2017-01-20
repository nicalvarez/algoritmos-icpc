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


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    return 0;
}

