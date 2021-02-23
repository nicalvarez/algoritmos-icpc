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

typedef long long tint;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

struct bipartite {
    int m;
	vector<bool> vis;
	vvi adj;
	vi pre;

	bipartite(int m, int n): m(m), vis(m), adj(m), pre(n,-1) {
	}

	void addEdge(int u, int v) {
		adj[u].pb(v);
	}

	bool dfs(int u) {
		if (u == -1) return true;
		if (vis[u]) return false;
		vis[u] = true;

		for (int v : adj[u]) {
			if (dfs(pre[v])) {
				pre[v] = u;
				return true;
			}
		}
		return false;
	}

	int match() {
		int res = 0;
		forn(u,m) {
			fill(all(vis),false);
			res += dfs(u);
		}
		return res;
	}
};


int main() {

}
