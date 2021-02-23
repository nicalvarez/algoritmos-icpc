#include <iomanip>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <complex>
#include <cassert>
#include <bitset>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define decl(v, c) typeof(c) v = c
#define forall(i, c) for(decl(i, c.begin()); i!=c.end(); ++i)
#define dforall(i, c) for(decl(i, c.rbegin()); i!=c.rend(); ++i)
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define D(a) cout << #a << "=" << a << endl;
#define pb push_back
#define mp make_pair

typedef long long int tint;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<tint> vt;
typedef vector<vt> vvt;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

const int MAXN = 1e5 + 100;

int n;
vi adj[MAXN];

int lvl[MAXN], sz[MAXN], pre[MAXN];
void dfs(int u, int p) {
    sz[u] = 1; pre[u] = p;
    for (int v : adj[u]) if (lvl[v] == -1 && v != p) {
        dfs(v,u);
        sz[u] += sz[v];
    }
}

void centroid(int u, int l) {
    dfs(u,-1);
    int n = sz[u], c = u;

    for (;;) {
        int w = -1;
        for (int v : adj[c]) if (lvl[v] == -1 && v != pre[c] && sz[v] > n/2) w = v;
        if (w == -1) break;
        c = w;
    }
    lvl[c] = l;
    for (int v : adj[c]) if (lvl[v] == -1) centroid(v,l+1);
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n;
    forn(_,n-1) {
        int u,v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }
    fill(lvl, lvl+n, -1);
    centroid(0,0);
    forn(u,n) {
        if (u) cout << ' ';
        cout << char('A' + lvl[u]);
    }
    cout << endl;
    
    return 0;
}
