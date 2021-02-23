#include <vector>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define decl(v, c) typeof(c) v = c
#define forall(i, c) for(decl(i, c.begin()); i!=c.end(); ++i)
#define pb push_back
typedef vector<int> vi;


const int MAXN = 100 + 10;

vi next[MAXN];
int M,pre[MAXN];
bool vis[MAXN];

void initGraph(int M, int N) {
	::M = M;
	forn(i,M) next[i].clear();
	forn(i,N) pre[i] = -1;
}

void addEdge(int u, int v) {
	next[u].pb(v);
}

bool augment(int u) {
	if (u == -1) return true;
	if (vis[u]) return false;
	vis[u] = true;
	forall(it,next[u]) {
		int v = *it;
		if (augment(pre[v])) {
			pre[v] = u;
			return true;
		}
	}
	return false;
}

int matching() {
	int res = 0;
	forn(u,M) {
		forn(v,M) vis[v] = false;
		res += augment(u);
	}
	return res;
}
