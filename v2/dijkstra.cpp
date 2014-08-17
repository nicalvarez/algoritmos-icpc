#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define mp make_pair

typedef long long int tint;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

struct distra {
	static const int INF = 1<<29;

	int n;
	vector<pii> *adj;

	distra(int n): n(n) {
		adj = new vector<pii>[n];
	}

	void addEdge(int u, int v, int c) {
		adj[u].pb(mp(v,c));
		// adj[v].pb(mp(u,c)); // si es bidireccional
	}

	int *dist, *pre;
	void go(int s, int t=-1) {
		dist = new int[n];
		pre = new int[n];
		fill(dist, dist+n, (int)INF); dist[s] = 0;
		fill(pre, pre+n, -1);
		priority_queue<pii> q; q.push(mp(0,s));
		while (!q.empty()) {
			pii top = q.top(); q.pop();
			int u = top.second, d = -top.first;
			if (u == t) break;
			if (d > dist[u]) continue;
			forn(i,si(adj[u])) {
				int v = adj[u][i].first, c = adj[u][i].second;
				if (dist[v] > dist[u] + c) {
					dist[v] = dist[u] + c;
					pre[v] = u;
					q.push(mp(-dist[v],v));
				}
			}
		}
	}

	bool *vis;
	void go2(int s, int t=-1) {
		dist = new int[n];
		pre = new int[n];
		vis = new bool[n];
		fill(dist, dist+n, (int) INF); dist[s] = 0;
		fill(pre, pre+n, -1);
		fill(vis, vis+n, false);
		for (;;) {
			int u = -1;
			forn(i,n) if (!vis[i] && (u < 0 || dist[i] < dist[u])) u = i;

			if (u < 0) break;

			vis[u] = true;
			forn(i,si(adj[u])) {
				int v = adj[u][i].first, c = adj[u][i].second;
				if (dist[v] > dist[u] + c) {
					dist[v] = dist[u] + c;
					pre[v] = u;
				}
			}
		}
	}
};

int main() {}