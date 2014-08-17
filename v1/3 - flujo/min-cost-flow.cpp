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
#include <cstring>
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
#define D(a) cerr << #a << "=" << a << endl;
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

const int
	MAXN = 650,
	INF = 1<<29;

int n, S, T;
int cap[MAXN][MAXN], cost[MAXN][MAXN], flow[MAXN][MAXN];

vi adj[MAXN];

void initGraph(int n, int s, int t) {
	::n = n; S = s; T = t;
	fill(cap[0], cap[n], 0);
	fill(cost[0], cost[n], 0);
	fill(flow[0], flow[n], 0);
	forn(u,n) adj[u].clear();

}

void addEdge(int u, int v, int cap, int cost) {
	adj[u].pb(v); adj[v].pb(u);
	::cap[u][v] = cap;
	::cost[v][u] = -(::cost[u][v] = cost);
}

int pot[MAXN];
void initFlow() {
	fill(pot,pot+n,0);
}

int val(int u, int v) { return cost[u][v] + pot[u] - pot[v]; }

bool vis[MAXN];
int dist[MAXN], pre[MAXN], ca[MAXN];
int dijkstra() {
	fill(dist, dist+n, INF); dist[S] = 0;
	fill(ca, ca+n, 0); ca[S] = INF;
	fill(vis, vis+n, false);
	fill(pre, pre+n, -1);

	for (;;) {
		tint best = INF, u = -1;
		forn(v,n) if (!vis[v] && dist[v] < best) {
			best = dist[v];
			u = v;
		}
		if (u == -1) break;
		vis[u] = true;
		forn(i,si(adj[u])) {
			int v = adj[u][i], cr = cap[u][v] - flow[u][v], c = val(u,v);
			if (cr <= 0) continue;
			if (dist[u] + c < dist[v]) {
				dist[v] = dist[u] + c;
				ca[v] = min(cr, ca[u]);
				pre[v] = u;
			}
		}
	}
	forn(u,n) if (dist[u] < INF) pot[u] += dist[u];
	return ca[T];
}

int augment(int cap) {
	for (int v = T; v != S; v = pre[v]) {
		int u = pre[v];
		flow[v][u] = -(flow[u][v] += cap);
	}
	return cap * pot[T];
}


void go(int& mincost, int &maxflow) {
	int cap;
	mincost = maxflow = 0;
	initFlow();
	while ((cap = dijkstra()) > 0) {
		maxflow += cap;
		mincost += augment(cap);
	}
}

