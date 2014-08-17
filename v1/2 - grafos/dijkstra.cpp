#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define decl(v, c) typeof(c) v = c
#define forall(i, c) for(decl(i, c.begin()); i!=c.end(); ++i)
#define mp make_pair

typedef pair<int,int> pii;
typedef priority_queue<pii> heap;

const int INF = 1<<29;
const int MAXN = 10000;

heap q;
bool vis[MAXN];
int mindist[MAXN];

void init() {
	while (!q.empty()) q.pop();
	forn(u,MAXN) {
		vis[u] = false;
		mindist[u] = INF;
	}
}

void addNode(int u, int d) {
	if (mindist[u] <= d) return;
	mindist[u] = d;
	q.push(mp(-d,u));
}

void dijkstra(int s, vector<pii> adj[]) {
	init();
	addNode(s,0);
	while (!q.empty()) {
		pii t = q.top(); q.pop();
		int u = t.second, d = -t.first;
		if (vis[u]) continue;
		vis[u] = true;
		forall(it,adj[u]) {
			int v = it->first, cost = it->second;
			addNode(v,d + cost);
		}
	}
}

int main() {
	int nv,ne; cin >> nv >> ne;
	vector<pii> adj[MAXN];
	forn(_,ne) {
		int u,v,c; cin >> u >> v >> c;
		adj[u].push_back(mp(v,c));
	}
	dijkstra(0,adj);
	forn(u,nv) cout << mindist[u] << endl;
}
