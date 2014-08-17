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


struct maxflow {
	static const int INF = 1<<29;

	struct edge {
		int u, v, cap, flow;
		int rem() { return cap - flow; }
	};

	int n;
	vi *adj;
	vector<edge> e;

	maxflow(int n): n(n) {
		adj = new vi[n];
		e.clear();
	}

	void addEdge(int u, int v, int cap) {
		adj[u].pb(si(e)); e.pb((edge){u,v,cap,0});
		adj[v].pb(si(e)); e.pb((edge){v,u,0,0});
	}

	int *dist, *pre, *cap;
	int flow(int s, int t) {
		dist = new int[n];
		pre = new int[n];
		cap = new int[n];

		int res = 0;
		for (;;) {
			fill(dist, dist+n, (int)INF); dist[s] = 0;
			fill(pre, pre+n, -1);
			fill(cap, cap+n, 0); cap[s] = INF;

			queue<int> q; q.push(s);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				if (u == t) break;

				forn(i,si(adj[u])) {
					edge E = e[adj[u][i]];
					if (E.rem() > 0 && dist[E.v] == INF) {
						dist[E.v] = dist[u] + 1;
						pre[E.v] = adj[u][i];
						cap[E.v] = min(cap[u], E.rem());
						q.push(E.v);
					}
				}
			}
			if (pre[t] == -1) break;
			res += cap[t];
			for (int v = t; v != s; ) {
				int u = e[pre[v]].u;
				e[pre[v]].flow += cap[t];
				e[pre[v]^1].flow -= cap[t];
				v = u;
			}
		}

		return res;
	}
};

int main() { }