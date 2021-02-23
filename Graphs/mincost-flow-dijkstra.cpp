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
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define mp make_pair

typedef long long int tint;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

const int INF = 1<<29;
struct mincost {

	struct edge {
		int u, v, cap, cost, flow;
		int rem() { return cap - flow; }
	};

	int n;
	vi *adj;
	vector<edge> e;


	mincost(int n): n(n) {
		adj = new vi[n];
		e.clear();
	}

	void addEdge(int u, int v, int cap, int cost) {
		adj[u].pb(si(e)); e.pb((edge){u,v,cap,cost,0});
		adj[v].pb(si(e)); e.pb((edge){v,u,0,-cost,0});
	}

	int *pot, *dist, *pre, *cap;
	pii flow(int s, int t) {
		pot = new int[n];
		dist = new int[n];
		pre = new int[n];
		cap = new int[n];

		fill(pot, pot+n, 0);
		// fill(pot, pot+n, INF); pot[s] = 0;
		// for (;;) {
		// 	bool change = false;
		// 	forn(u,n) forn(i,si(adj[u])) {
		// 		edge E = e[adj[u][i]];
		// 		if (E.rem() && pot[E.v] > pot[u] + E.cost) {
		// 			change = true;
		// 			pot[E.v] = pot[u] + E.cost;
		// 		}
		// 	}
		// 	if (!change) break;
		// }

		pii res(0,0);
		for (;;) {
			fill(dist, dist+n, INF); dist[s] = 0;
			fill(pre, pre+n, -1);
			fill(cap, cap+n, 0); cap[s] = INF;
			priority_queue<pii> q; q.push(mp(0,s));
			while (!q.empty()) {
				pii top = q.top(); q.pop();
				int u = top.second, d = -top.first;
				if (u == t) break;
				if (d > dist[u]) continue;
				forn(i,si(adj[u])) {
					edge E = e[adj[u][i]];
					int c = E.cost + pot[u] - pot[E.v];
					if (E.rem() && dist[E.v] > dist[u] + c) {
						dist[E.v] = dist[u] + c;
						pre[E.v] = adj[u][i];
						cap[E.v] = min(cap[u], E.rem());
						q.push(mp(-dist[E.v], E.v));
					}
				}
			}
			if (pre[t] == -1) break;

			forn(u,n) 
				if (dist[u] == INF) pot[u] = INF;
				else pot[u] += dist[u];

			res.first += cap[t];
			res.second += cap[t]*pot[t];

			for (int v = t; v != s; v = e[pre[v]].u) {
				e[pre[v]].flow += cap[t];
				e[pre[v]^1].flow -= cap[t];
			}
		}
		
		return res;
	}
};

int main() {}