#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define eb emplace_back
#define mp make_pair

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

struct mincost {
    static const int INF = 1e9;

    struct rib {
        int b, u, c, f;
        size_t back;
    };
    
    int n;
    vector<vector<rib>> g;

    mincost(int n): n(n), g(n,vector<rib>(n)) {}
   

    void add_edge(int a, int b, int u, int c) {
        rib r1 = { b, u, c, 0, g[b].size() };
        rib r2 = { a, 0, -c, 0, g[a].size() };
        g[a].push_back (r1);
        g[b].push_back (r2);
    }


    // k: tope de flujo permitido
    pii flow(int s, int t, int k = INF) {
        int flow = 0, cost = 0;
        while (flow < k) {
            vector<int> id (n, 0);
            vector<int> d (n, INF);
            vector<int> q (n);
            vector<int> p (n);
            vector<size_t> p_rib (n);
            int qh=0, qt=0;
            q[qt++] = s;
            d[s] = 0;
            while (qh != qt) {
                int v = q[qh++];
                id[v] = 2;
                if (qh == n)  qh = 0;
                for (size_t i=0; i<g[v].size(); ++i) {
                    rib & r = g[v][i];
                    if (r.f < r.u && d[v] + r.c < d[r.b]) {
                        d[r.b] = d[v] + r.c;
                        if (id[r.b] == 0) {
                            q[qt++] = r.b;
                            if (qt == n)  qt = 0;
                        }
                        else if (id[r.b] == 2) {
                            if (--qh == -1)  qh = n-1;
                            q[qh] = r.b;
                        }
                        id[r.b] = 1;
                        p[r.b] = v;
                        p_rib[r.b] = i;
                    }
                }
            }
            if (d[t] == INF)  break;
            int addflow = k - flow;
            for (int v=t; v!=s; v=p[v]) {
                int pv = p[v];  size_t pr = p_rib[v];
                addflow = min (addflow, g[pv][pr].u - g[pv][pr].f);
            }
            for (int v=t; v!=s; v=p[v]) {
                int pv = p[v];  size_t pr = p_rib[v],  r = g[pv][pr].back;
                g[pv][pr].f += addflow;
                g[v][r].f -= addflow;
                cost += g[pv][pr].c * addflow;
            }
            flow += addflow;
        }

        // se puede repetir el while de arriba
        // mientras encuentre flujo negativo
        // (si el flujo debe ser >= k)
        
        return mp(flow, cost);
    }

};

int main() {

}
