#define MAXN 300
const int INF = 1<<30;

int n,c[MAXN][MAXN];
bool mark[MAXN];
int lm[MAXN],rm[MAXN];
bool dfs(int u) {
	forn(v,n) if ((c[u][v] == 0) && (!mark[v])) {
		mark[v] = true;
		if (rm[v] == -1 || dfs(rm[v])) {
			lm[u] = v; rm[v] = u;
			return true;
		}
	}
	return false;
}
int go() {
	int res = 0, matching = 0;
	fill(mark,mark+n,false);
	fill(lm,lm+n,-1); fill(rm,rm+n,-1);
	forn(i,n) {
		int rest = INF;
		forn(j,n) rest = min(rest, c[i][j]);
		forn(j,n) c[i][j] -= rest;
		res += rest;
	}

	while (matching < n) {
		restart:
		for (;;) {
			fill(mark,mark+n,false);
			forn(i,n) if (lm[i] == -1 && dfs(i)) { matching++; goto restart; }
			break;
		}

		int rest = INF;
		forn(i,n) if (lm[i] == -1 || mark[lm[i]])
		forn(j,n) if (rm[j] == -1 || !mark[j])
			rest = min(rest, c[i][j]);

		forn(i,n) if (lm[i] == -1 || mark[lm[i]]) {
			forn(j,n) c[i][j] -= rest;
			res += rest;
		}
		forn(j,n) if (rm[j] != -1 && mark[j]) {
			forn(i,n) c[i][j] += rest;
			res -= rest;
		}
	}

	return res;
}
