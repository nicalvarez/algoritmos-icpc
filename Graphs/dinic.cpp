#include <bits/stdc++.h>
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
#define eb emplace_back
#define mp make_pair

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

template<int MAXN>
struct dinic {

    struct edge {
        int u,v,c,f;
        int r() { return c-f; }
    };

    static const int INF = 1e9;

    int N,S,T;
    vector<edge> e;
    //edge red[MAXN][MAXN];
    vi adjG[MAXN];

    void reset() {
        forn(u,N) for (auto ind : adjG[u]) {
            auto &ei = e[ind];
            ei.f = 0;
        }
    }

    void initGraph(int n, int s, int t) {
        N = n; S = s; T = t;
        e.clear();
        forn(u,N) adjG[u].clear();
    }

    void addEdge(int u, int v, int c) {
        adjG[u].pb(si(e)); e.pb((edge){u,v,c,0});
        adjG[v].pb(si(e)); e.pb((edge){v,u,0,0});
    }

    int dist[MAXN];
    bool dinic_bfs() {
        forn(u,N) dist[u] = INF;
        queue<int> q; q.push(S); dist[S] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto ind : adjG[u]) {
                auto &ei = e[ind];
                int v = ei.v;
                if (dist[v] < INF || ei.r() == 0) continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist[T] < INF;
    }

    int dinic_dfs(int u, int cap) {
        if (u == T) return cap;

        int res = 0;
        for (auto ind : adjG[u]) {
            auto &ei = e[ind], &ej = e[ind^1];
            int v = ei.v;
            if (ei.r() && dist[v] == dist[u] + 1) {
                int send = dinic_dfs(v,min(cap, ei.r()));
                ei.f += send; ej.f -= send;
                res += send; cap -= send;
                if (cap == 0) break;
            }
        }
        if (res == 0) dist[u] = INF;
        return res;
    }

    int flow() {
        int res = 0;
        while (dinic_bfs()) res += dinic_dfs(S,INF);
        return res;
    }

    vi cut() {
        dinic_bfs();
        vi ans;
        for (auto u : adjG[S]) if (dist[e[u].v] == INF) ans.pb(e[u].v);
        for (auto u : adjG[T]) if (dist[e[u].v] < INF) ans.pb(e[u].v);
        return ans;
    }

    vi indep() {
        dinic_bfs();
        vi ans;
        for (auto u : adjG[S]) if (dist[e[u].v] < INF) ans.pb(e[u].v);
        for (auto u : adjG[T]) if (dist[e[u].v] == INF) ans.pb(e[u].v);
        return ans;
    }
};


int main() {
}
