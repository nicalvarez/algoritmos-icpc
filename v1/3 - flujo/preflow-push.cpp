typedef tint tipo;

const int
	MAXN = 500 + 50,
	INF = 1<<29;

struct edge {
	tipo c,f;
	edge() { c = f = 0; }
	tipo cr() { return c-f; }
};

typedef map<int,edge>::iterator iter;

int n, S, T, h[MAXN];
tipo ex[MAXN];
map<int,edge> net[MAXN];
iter eact[MAXN];

int k;
vector<int> active[2*MAXN];

void initGraph(int s, int t) {
	S = s; T = t;
	forn(u,n) {
		net[u].clear();
		ex[u] = h[u] = 0;
	}
	h[S] = n;
	k = 0; forn(d,2*n) active[d].clear();

}

void addEdge(int u, int v, int c) {
	net[u][v].c += c;
	eact[u] = net[u].begin();
}


void push(int u, int v) {
	if (v != S && v != T && ex[v] == 0) {
		int hv = h[v];
		active[hv].pb(v);
	}
	int cap = min(net[u][v].cr(), ex[u]);
	net[v][u].f = -(net[u][v].f += cap);
	ex[u] -= cap; ex[v] += cap;
}

void relabel(int u) {
	h[u] = INF;
	for (iter it = eact[u] = net[u].begin(); it != net[u].end(); it++) {
		int v = it->first; edge e = it->second;
		if (e.cr()) h[u] = min(h[u], h[v]);
	}
	h[u]++;
}

void process(int u) {
	for(iter &it = eact[u]; it != net[u].end(); it++) {
		int v = it->first; edge e = it->second;
		if (e.cr() && h[u] == h[v] + 1) push(u,v);
		if (ex[u] == 0) return;
	}
	relabel(u);
	k = h[u];
	active[h[u]].push_back(u);
}

tipo maxFlow() {
	for (iter it = net[S].begin(); it != net[S].end(); it++) {
		int v = it->first; edge e = it->second;
		net[v][S].f = -(ex[v] = net[S][v].f = net[S][v].c);
		if (v != S && v != T) active[0].push_back(v);
	}
	k = 0;

	for (;;) {
		while (k >= 0 && active[k].empty()) k--;
		if (k < 0) break;
		int u = active[k].back(); active[k].pop_back();
		process(u);
	}

	return ex[T];
}
