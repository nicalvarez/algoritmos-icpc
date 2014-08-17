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

const int MAXN = 200 + 10;

typedef tint tipo;
const int INF = 1<<29;
struct edge {
	tipo c,f;
	tipo r() { return c-f; }
};
int N,S,T;
edge red[MAXN][MAXN];
vi adjG[MAXN];

void reset() {
	forn(u,N) forn(i,si(adjG[u])) {
		int v = adjG[u][i];
		red[u][v].f = 0;
	}
}

void initGraph(int n, int s, int t) {
	N = n; S = s; T = t;
	forn(u,N) {
		adjG[u].clear();
		forn(v,N) red[u][v] = (edge){0,0};
	}
}

void addEdge(int u, int v, int c) {
	if (!red[u][v].c && !red[v][u].c) { adjG[u].pb(v); adjG[v].pb(u); }
	red[u][v].c += c;
}

int dist[MAXN];
bool dinic_bfs() {
	forn(u,N) dist[u] = INF;
	queue<int> q; q.push(S); dist[S] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		forn(i,si(adjG[u])) {
			int v = adjG[u][i];
			if (dist[v] < INF || red[u][v].r() == 0) continue;
			dist[v] = dist[u] + 1;
			q.push(v);
		}
	}
	return dist[T] < INF;
}

tipo dinic_dfs(int u, tipo cap) {
	if (u == T) return cap;

	tipo res = 0;
	forn(i,si(adjG[u])) {
		int v = adjG[u][i];
		if (red[u][v].r() && dist[v] == dist[u] + 1) {
			tipo send = dinic_dfs(v,min(cap,red[u][v].r()));
			red[u][v].f += send; red[v][u].f -= send;
			res += send; cap -= send;
			if (cap == 0) break;
		}
	}
	if (res == 0) dist[u] = INF;
	return res;
}

tipo dinic() {
	tipo res = 0;
	while (dinic_bfs()) res += dinic_dfs(S,INF);
	return res;
}
