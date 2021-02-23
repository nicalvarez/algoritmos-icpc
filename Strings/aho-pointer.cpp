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

int node_sz = 0;
struct node {
    static const int SZ = 28;

    int id;
    char c;
    node *nxt[SZ], *p, *link, *output;
    bool leaf;

    node(node *p = 0, char c = 0): p(p), c(c), link(0), leaf(0), output(0) {
        id = node_sz++;
        fill_n(nxt, SZ, nullptr);
    }

    void add(const string &s) {
        auto st = this;
        for (char c : s) {
            if (!st->nxt[c-'a']) st->nxt[c-'a'] = new node(st,c);
            st = st->nxt[c-'a'];
        }
        st->leaf = true;
        st->output = st;
    }

    node *getNxt(char c) {
        if (!nxt[c-'a']) {
            if (p) nxt[c-'a'] = getLink()->getNxt(c);
            else nxt[c-'a'] = this;
        }
        return nxt[c-'a'];
    }

    node *getLink() {
        if (!link) {
            if (p && p->p) link = p->getLink()->getNxt(c);
            else if (p) link = p;
            else link = this;
        }
        return link;
    }

    node *getOutput() {
        if (!output) {
            if (p) output = getLink()->getOutput();
            else output = this;
        }
        return output;
    }

    bool isLeaf() {
        return getOutput()->id;
    }

};

int main() {}
