#include <bits/stdc++.h>
using namespace std;


#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())
#define pb push_back
#define mp make_pair
#define forsn(i,a,b) for (int i = int(a); i < int(b); i++)
#define dforsn(i,a,b) for (int i = int(b)-1; i >= int(a); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << " = " << a << endl;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int 
	MAXN = 1e5 + 100,
	MAXL = 20;

int n;
vi adj[MAXN];

int pre[MAXN][MAXL], lvl[MAXN];
void dfs(int u, int p = 0, int l = 0) {
	pre[u][0] = p;
	lvl[u] = l;
	for (int v : adj[u]) if (v != p) dfs(v,u,l+1);
}

void precompute() {
	fill(pre[0], pre[0]+MAXL, 0); lvl[0] = -1;
	dfs(1,0);
	forsn(l,1,MAXL) forsn(u,1,n+1) pre[u][l] = pre[pre[u][l-1]][l-1];
}

int lca(int u, int v) {
	if (lvl[u] > lvl[v]) swap(u,v);
	dforsn(l,0,MAXL) if (lvl[pre[v][l]] >= lvl[u]) v = pre[v][l];

	if (u == v) return u;
	dforsn(l,0,MAXL) if (pre[u][l] != pre[v][l]) {
		u = pre[u][l];
		v = pre[v][l];
	}
	// assert(u != v);
	return pre[u][0];
}

/*
const int MAXN = 1e5, MAXK = 20;
int h[2*MAXN], lvl[MAXN];

int t = 0, d[MAXN];
void dfs(int u, int p, int l) {
    d[u] = t; h[t++] = l;
    lvl[u] = l;
    for (int v : adj[u]) if (v != p) {
        dfs(v,u,l+1);
        h[t++] = l;
    }
}
int st[MAXK][MAXN];

void initRMQ() {
    forn(i,2*n) st[0][i] = h[i];
    for (int k = 1; (1<<k) <= 2*n; k++) {
        forn(i,2*n - (1<<k)) st[k][i] = min(st[k-1][i], st[k-1][i+(1<<(k-1))]);
    }
}

int rmq(int i, int j) {
    int len = j-i+1;
    int pot = 31 - __builtin_clz(len);
    return min(st[pot][i], st[pot][j-(1<<pot)+1]);
}

int lcaDist(int u, int v) {
    return lvl[u] + lvl[v] - 2*rmq(min(d[u],d[v]), max(d[u],d[v]));
}

int query(int u) {
    int ans = res[u];
    for (int v : upd) {
        ans = min(ans, lcaDist(u,v));
    }
    return ans;
}
 */

int main() {}
