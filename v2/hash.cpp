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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<int K>
struct string_hashing {

    int n, MOD, x[K];
    vi pot[K], cum[K];

    bool prime(int n) {
        for (int d = 2; d*d <= n; d++) if (n%d == 0) return false;
        return true;
    }

    string_hashing(const string &s) {
        MOD = 1e9 + rng() % int(1e9);
        while (!prime(MOD)) ++MOD;
        forn(i, K) x[i] = rng() % MOD;

        n = si(s);
        forn(i, K) {
            pot[i].resize(n+1);
            cum[i].resize(n+1);
            pot[i][0] = 1;
            cum[i][0] = 0;
            forsn(j, 1, n+1) {
                pot[i][j] = (ll) pot[i][j-1] * x[i] % MOD;
                cum[i][j] = ( (ll) cum[i][j-1] * x[i] + s[j-1] ) % MOD;
            }
        }
    }

    array<int, K> hash(int from, int to) {
        array<int,K> ans;
        assert(0 <= from && to <= n);
        forn(i, K) {
            ans[i] = (cum[i][to] - (ll) cum[i][from] * pot[i][to-from]) % MOD;
            if (ans[i] < 0) ans[i] += MOD;
        }
        return ans;
    }
    
};

int main() { }
