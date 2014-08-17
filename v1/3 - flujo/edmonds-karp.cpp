typedef tint tipo;

const int
	MAXN = 500 + 50,
	INF = 1<<29;

struct edge {
	tipo c,f;
	edge() { c = f = 0; }
	tipo cr() { return c-f; }
};

int n, S, T;
map<int,edge> net[MAXN];

void initGraph(int s, int t) {
	forn(u,n) net[u].clear();
	S = s; T = t;
}

void addEdge(int u, int v, int c) {
	net[u][v].c += c; net[v][u].c; // += c si el grafo es no-dirigido
}

typedef map<int,edge>::iterator iter;
int pre[MAXN], dist[MAXN];
tipo cap[MAXN];
tipo bfs() {
	fill(pre, pre+n, -1);
	fill(dist, dist+n, INF); dist[S] = 0;
	cap[S] = INF;
	queue<int> q; q.push(S);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (iter it = net[u].begin(); it != net[u].end(); it++) {
			int v = it->first; edge e = it->second;
			if (e.cr() && dist[v] == INF) {
				dist[v] = dist[u] + 1;
				pre[v] = u;
				cap[v] = min(cap[u], e.cr());
				q.push(v);
				if (v == T) return cap[v];
			}
		}
	}
	return 0;
}

void augment(int cap) {
	for (int v = T; v != S; v = pre[v]) {
		int u = pre[v];
		net[v][u].f = -(net[u][v].f += cap);
	}
}

tipo maxFlow() {
	tipo cap, res = 0;
	while ((cap = bfs())) {
		augment(cap);
		res += cap;
	}
	return res;
}
