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

/*
   Convex hull trick con A, B y x de tipo T
   Las lineas se insertan por A descendente
   Las querySequential deben ser con x's ascendentes
   Calcula lower_envelope, busca minimizar la función.
   CAMBIAR SIGNOS si no se cumpliera alguna de estas condiciones.
*/
template <class T, int N>
struct chull_trick {
    int sz, opt, ind[N];
    T A[N], B[N]; 

    chull_trick() { clear(); }

    void clear() {
        sz = 0;
        opt = 0;
    }

    bool bad(T a3, T b3) {
        T a1 = A[sz-2], b1 = B[sz-2];
        T a2 = A[sz-1], b2 = B[sz-1];
        return (b3-b1)*(a1-a2) <= (b2-b1)*(a1-a3);
    }

    void add(T a, T b, int i) {
        while (sz >= 2 && bad(a,b)) sz--;
        A[sz] = a; B[sz] = b; ind[sz] = i; sz++;
    }

    pair<T,int> querySequential(T x) {
        opt = min(opt, sz-1);
        while (opt < sz-1 && A[opt]*x + B[opt] > A[opt+1]*x + B[opt+1]) opt++;
        return make_pair(A[opt]*x + B[opt], ind[opt]);
    }

    pair<T,int> queryBinary(T x) {
        int lo = -1, hi = sz-1;
        while (lo+1 < hi) {
            int mi = (lo+hi)/2;
            if (A[mi]*x + B[mi] < A[mi+1]*x + B[mi+1]) hi = mi; else lo = mi;
        }
        return make_pair(A[hi]*x + B[hi], ind[hi]);
    }
};
const int N = 1010;
const ll INF = 1e18;

int n,K; 
ll x[N], w[N], sw[N], swx[N], dp[N][N];

int main() {
    while (scanf("%d %d\n", &n, &K) != EOF) {
        forn(i,n) {
            scanf("%lld %lld\n", x+i, w+i);
            sw[i+1] = w[i] + sw[i];
            swx[i+1] = w[i]*x[i] + swx[i];
        }

        chull_trick<ll,N> ch;
        fill_n(dp[0], n, INF); dp[0][n] = 0;
        for (int k = 1; k <= K; k++) {
            for (int from = n; from >= 0; from--) {
                dp[k][n] = 0;
                ch.clear();
                for (int from = n-1; from >= 0; from--) {
                    ch.add(x[from], x[from]*sw[from+1] - swx[from+1] + dp[k-1][from+1], from+1);
                    ll x = -sw[from];
                    dp[k][from] = swx[from] + ch.querySequential(x).first;
                }
            }
        }
        printf("%lld\n", dp[K][0]);
    }

    return 0;
}
