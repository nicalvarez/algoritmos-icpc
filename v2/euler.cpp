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
    void dfs(const vector<pii> &e, vector<vi> &adj, int u) {
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

    // Looks for an eulerian tour (not path)
    // returns a vector of indexes of edges
    vi undirected_tour(int n, const vector<pii> &e) {
        vector<vi> adj(n);
        vi deg(n);
        int start = 0;
        forn(i,si(e)) {
            int u = e[i].first, v = e[i].second;
            adj[u].pb(i);
            adj[v].pb(i);
            deg[u]++; deg[v]++;
            start = u;
        }
        forn(u,n) if (deg[u]%2) return vi();
        
        tour.clear();
        dead = vi(si(e));
        dfs(e,adj,start);
        if (si(tour) != si(e)) return vi();
        reverse(all(tour));
        return tour;
    }

    // Looks for an eulerian path
    // returns a vector of indexes of edges
    vi undirected_path(int n, vector<pii> e) {
        vi deg(n);
        forn(i,si(e)) {
            int u = e[i].first, v = e[i].second;
            deg[u]++; deg[v]++;
        }
        vi odd;
        forn(u,n) if (deg[u]%2) odd.pb(u);
        if (si(odd) > 2) return vi();
        if (odd.empty()) return undirected_tour(n, e);

        // path
        assert(si(odd) == 2);
        int sz = si(e);
        e.eb(odd[0], odd[1]);
        auto ans = undirected_tour(n, e);
        if (si(ans) < si(e)) return vi();
        ans.erase(find(all(ans), sz));
        return ans;
    }

    // Looks for an eulerian tour (not path)
    // returns a vector of indexes of edges
    vi directed_tour(int n, const vector<pii> &e) {
        vector<vi> adj(n);
        vi bal(n);
        int start = 0;
        forn(i,si(e)) {
            int u = e[i].first, v = e[i].second;
            adj[u].pb(i);
            bal[u]--; bal[v]++;
            start = u;
        }
        forn(u,n) if (bal[u] != 0) return vi();

        tour.clear();
        dead = vi(si(e));
        dfs(e,adj,start);
        if (si(tour) != si(e)) return vi();
        reverse(all(tour));
        return tour;
    }

    // Looks for an eulerian path
    // returns a vector of indexes of edges
    vi directed_path(int n, vector<pii> e) {
        vi bal(n);
        forn(i,si(e)) {
            int u = e[i].first, v = e[i].second;
            bal[u]--; bal[v]++;
        }
        vi neg, pos;
        forn(u,n) {
            if (bal[u] < 0) neg.pb(u);
            if (bal[u] > 0) pos.pb(u);
        }
        if (neg.empty() && pos.empty()) return directed_tour(n, e);
        if (si(neg) > 1 || si(pos) > 1) return vi(); 
        if (bal[neg[0]] < -1 || bal[pos[0]] > 1) return vi();

        int sz = si(e); 
        e.eb(pos[0], neg[0]);
        auto ans = directed_tour(n, e);
        if (si(ans) < si(e)) return vi();
        ans.erase(find(all(ans), sz));
        return ans;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}
