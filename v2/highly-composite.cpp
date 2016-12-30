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

vi p;

struct number {
    ll val, divi;
    vi e;

    bool operator<(const number &o) const {
        return val < o.val;
    }
};

bool prime(int n) {
    for (int d = 2; d*d <= n; d++) if (n%d == 0) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    for (int n = 2; ; n++) if (prime(n)) {
        p.pb(n);
        if (si(p) == 100) break;
    }

    set<number> cand;
    cand.insert((number){1,1,vi{}});

    const ll TOP = 1e9;

    vector<number> res;
    int last = 0;
    for (;;) {
        auto x = *cand.begin();
        if (x.divi > last) {
            res.pb(x);
            last = x.divi;
        }
        if (x.val > TOP) break;

        cand.erase(cand.begin());
        x.e.pb(0);
        forn(i,si(x.e)) {
            if (i == 0 || x.e[i-1] > x.e[i]) {
                x.divi /= x.e[i]+1;
                x.e[i]++;
                x.divi *= x.e[i]+1;
                x.val *= p[i];
                cand.insert(x);
                x.val /= p[i];
                x.divi /= x.e[i]+1;
                x.e[i]--;
                x.divi *= x.e[i]+1;
            }
        }
        x.e.pop_back();
    }

    for (auto num : res) cerr << num.val << ' ' << num.divi << endl;

    return 0;
}
