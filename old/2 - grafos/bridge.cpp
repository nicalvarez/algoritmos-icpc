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

const int MAXN = 100 + 10;
const int MAXE = 2*MAXN*MAXN + 100;

int n;
vector<pii> edges;
vi adj[MAXN];
bool bridge[MAXE];

// Los arcos se guardan asi para considerar la posibilidad de que existan
// multiples arcos entre un par de nodos y no sean considerados puentes
void addE(int u, int v) {
	int ne = si(edges);
	edges.pb(mp(u,v));
	adj[u].pb(ne); adj[v].pb(ne);
	bridge[ne] = false;
}


/* 
t = variable de tiempo
d[u] = descubrimiento del nodo u
b[u] = back edge 
comp[u] = nro de componentes conexas en que queda partido el grafo al quitar el nodo u, si comp[u] > 1 es punto de articulacion
bridge[ne] = indica si el arco ne es puente o no
Se llama con le = -1
*/
stack<int> estack;
int d[MAXN], b[MAXN], comp[MAXN], bc[MAXE], nbc, t;
void dfs(int le, int u) {
	b[u] = d[u]= t++;
	comp[u] = (le != -1);
	forn(i,si(adj[u])) {
		int ne = adj[u][i];
		if (ne == le) continue;

		pii e = edges[ne];
		int v = e.first ^ e.second ^ u;
		if (d[v] == -1) {
			estack.push(ne);
			dfs(ne,v);
			if (b[v] > d[u]) bridge[ne] = true;
			if (b[v] >= d[u]) {
				int last; do {
					last = estack.top();
					bc[last] = nbc;
					estack.pop();
				} while (last != ne);
				nbc++;
				comp[u]++;
			}
			else b[u] = min(b[u],b[v]);
		}
		else if (d[v] < d[u]) {
			estack.push(ne);
			b[u] = min(b[u],d[v]);
		}
	}
}

void init() {
	nbc = t = 0;
	forn(i,n) {
		d[i] = -1;
		adj[i].clear();
	}
	edges.clear();
	while (!estack.empty()) estack.pop();
}

int main() {
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);


	int m; cin >> n >> m;
	init();
	forn(_,m) {
		int u,v; cin >> u >> v; u--; v--;
		addE(u,v);
	}
 	forn(u,n) if (d[u] == -1) dfs(-1,u);
}

