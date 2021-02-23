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

const int N = 1e5 + 10;

int n;
vi adj[N];

int col[N], pre[N];
int cyc_s, cyc_t;
bool dfs(int u) {
    col[u] = 1;
    for (int v : adj[u]) {
        if (col[v] == 0) {
            pre[v] = u;
            if (dfs(v)) return true;
        }
        else {
            if (col[v] == 1) {
                cyc_s = v;
                cyc_t = u;
                return true;
            }
        }
    }
    col[u] = 2;
    return false;
}

vi build_cycle() {
    vi res;
    forn(u,n) if (dfs(u)) {
        for (int v = cyc_t; v != cyc_s; v = pre[v]) res.pb(v);
        res.pb(cyc_s);
        reverse(all(res));
        break;
    }
    return res;
}

int main() {
}
