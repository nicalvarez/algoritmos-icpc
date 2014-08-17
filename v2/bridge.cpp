#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
#define forn(i,n) for (int i = 0; i < (int)(n); i++)
#define si(c) ((int)(c).size())
#define pb push_back
#define mp make_pair

struct bridge {

	struct edge {
		int u,v, comp;
		bool bridge;
	};

	int n;
	vi *adj;
	vector<edge> e;

	bridge(int n): n(n) {
		adj = new vi[n];
		e.clear();
		initDfs();
	}

	void initDfs() {
		d = new int[n];
		b = new int[n];
		comp = new int[n];
		nbc = t = 0;
	}

	void addEdge(int u, int v) {
		adj[u].pb(si(e)); adj[v].pb(si(e));
		e.pb((edge){u,v,-1,false});
	}

	int *d, *b, t, nbc;
	int *comp;
	stack<int> st;
	void dfs(int u, int pe) {
		b[u] = d[u] = t++;
		comp[u] = (pe != -1);

		forn(i,si(adj[u])) {
			int ne = adj[u][i];
			if (ne == pe) continue;
			int v = e[ne].u ^ e[ne].v ^ u;
			if (d[v] == -1) {
				st.push(ne);
				dfs(v,ne);
				if (b[v] > d[u]) e[ne].bridge = true; // bridge
				if (b[v] >= d[u]) { // art
					int last;
					do {
						last = st.top(); st.pop();
						e[last].comp = nbc;
					} while (last != ne);
					nbc++;
					comp[u]++;
				} 
				b[u] = min(b[u], b[v]);
			}
			else if (d[v] < d[u]) { // back edge
				st.push(ne);
				b[u] = min(b[u], d[v]);
			}
		}
	}

};

int main() { }