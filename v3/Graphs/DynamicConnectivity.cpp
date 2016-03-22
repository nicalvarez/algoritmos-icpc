#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define forn(i,n) for (int i = 0; i < (int)(n); i++)
#define forsn(i,a,b) for (int i = (int)(a); i < (int)(b); i++)
#define pb push_back
#define eb emplace_back
#define mp make_pair

typedef vector<int> vi;
typedef pair<int,int> pii;

template<int N>
struct UnionFind {
    int n, pre[N], comp;
    vector<pair<int&,int>> changes;

    void init(int n) {
        this->n = n;
        forn(i,n) pre[i] = i;
        changes.clear();
        comp = n;
    }

    int assign(int &l, int r) {
        changes.eb(l,l);
        return l = r;
    }

    int find(int u) {
        return assign(pre[u], u == pre[u] ? u : find(pre[u]));
    }

    bool merge(int u, int v) {
        int a = find(u);
        int b = find(v);
        if (a != b) {
            assign(pre[a], b); 
            assign(comp, comp-1);
            return true;
        }
        return false;
    }

    int snapshot() { return si(changes); }

    void restore(int snapshot) {
        while (si(changes) > snapshot) {
            auto lr = changes.back(); changes.pop_back();
            lr.first = lr.second;
        }
    }
};


template <int N, int M>
struct DynamicConnectivity {

#define ADD 0
#define DEL 1
#define QUERY 2

    struct query {
        int type,u,v;
    };

    int sz, match[M];
    query q[M];
    UnionFind<N> dsu;
    map<pii,int> last;
    vi res;

    void init(int n) {
        sz = 0;
        dsu.init(n);
        last.clear();
        res.clear();
    }

    void add(int u, int v) {
        if (u > v) swap(u,v);
        q[sz].type = ADD;
        q[sz].u = u; q[sz].v = v;
        last[mp(u,v)] = sz;
        //last[mp(u,v)].push(sz); 
        match[sz] = -1;
        sz++;
    }

    void remove(int u, int v) {
        if (u > v) swap(u,v);
        q[sz].type = DEL;
        q[sz].u = u; q[sz].v = v;
        int prev = last[mp(u,v)];
        //int prev = last[mp(u,v)].front(); last[mp(u,v)].pop();
        match[prev] = sz;
        match[sz] = prev;
        sz++;
    }

    void query() {
        q[sz].type = QUERY;
        match[sz] = -1;
        sz++;
    }

    void process() {
        forn(i,sz) if (q[i].type == ADD && match[i] == -1) match[i] = sz;
        go(0,sz);
    }

    void go(int l, int r) {
        if (l+1 == r) {
            if (q[l].type == QUERY) res.pb(dsu.comp);
            return;
        }
        int snap, m = (l+r) / 2;
        snap = dsu.snapshot();
        forsn(i,m,r) if (match[i] != -1 && match[i] < l) dsu.merge(q[i].u, q[i].v);
        go(l,m);
        dsu.restore(snap);

        snap = dsu.snapshot();
        forsn(i,l,m) if (match[i] != -1 && match[i] >= r) dsu.merge(q[i].u, q[i].v);
        go(m,r);
        dsu.restore(snap);
    }
};

