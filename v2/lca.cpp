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

int main() {}