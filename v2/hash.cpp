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

// Acordarse de hacer rng.seed(time(0))
mt19937 rng;
struct hashing {
    int mod, mul;

    bool prime(int n) { 
        for (int d = 2; d*d <= n; d++) if (n%d == 0) return false;
        return true;
    }

    void setValues(int mod, int mul) {
        this->mod = mod;
        this->mul = mul;
    }

    void randomize() {
        mod = uniform_int_distribution<>(0, (int) 5e8)(rng) + 1e9;
        while (!prime(mod)) mod++;
        mul = uniform_int_distribution<>(2,mod-2)(rng);
    }

    int hash(const string &s) {
        int res = 0;
        for (char c : s) res = (res * (ll) mul + c) % mod;
        return res;
    }
};


const int M = 1e6 + 10;
const int MOD = 1e9 + 7;

int n,m, fact[M];
string id[M]
hashing h1,h2;

int main() {
    fact[0] = 1; forsn(n,1,M) fact[n] = (ll) fact[n-1] * n % MOD;

    scanf("%d %d", &n, &m);
    while (n--) {
        int k; scanf("%d", &k);
        while (k--) {
            int x; scanf("%d", &x);

        }
    }

    return 0;
}
