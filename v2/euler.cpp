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
 
namespace euler {

    vi tour, dead;
    void dfs(const vector<pii> &e, const vector<vi> &adj, int u) {
        while (!adj[u].empty()) {
            auto idx = adj[u].back();
            adj[u].pop_back();
            if (dead[idx]) continue;
            dead[idx] = true;
            int v = u ^ e[idx].first ^ e[idx].second;
            dfs(e,adj,v);
            tour.pb(idx);
        }
    }

    vi undirected(int n, const vector<pii> &e) {
        vector<vi> adj(n);
        vi deg(n);
        forn(i,si(e)) {
            int u = e[i].first, v = e[i].second;
            adj[u].pb(i);
            adj[v].pb(i);
            deg[u]++; deg[v]++;
        }
        forn(u,n) if (deg[u]%2) return vi();
        
        tour.clear();
        dead = vi(si(e));
        dfs(e,adj,0);
        if (si(tour) != si(e)) return vi();
        reverse(all(tour));
        return tour;
    }

    vi directed(int n, const vector<pii> &e) {
        vector<vi> adj(n);
        vi bal(n);
        forn(i,si(e)) {
            int u = e[i].first, v = e[i].second;
            adj[u].pb(i);
            bal[u]--; bal[v]++;
        }
        forn(u,n) if (bal[u] != 0) return vi();

        tour.clear();
        dead = vi(si(e));
        dfs(e,adj,0);
        if (si(tour) != si(e)) return vi();
        reverse(all(tour));
        return tour;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}
