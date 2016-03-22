#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define forsn(i,a,b) for (int i = int(a); i < int(b); i++)
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())

template <int N, class T>
struct SuffixArray {
    int n, p[N], r[N], lcp[N];
    vector<T> s;

    void build(const vector<T> &s) {
        this->n = si(s);
        this->s = s;

        forn(i,n) p[i] = i;
        sort(p, p+n, [&](int i, int j) { return s[i] < s[j]; });
        int ind = 0; 
        forn(i,n) {
            if (i && s[p[i-1]] != s[p[i]]) ++ind;
            r[p[i]] = ind;
        }

        int len;
        static int nr[N];
        auto cmp = [&](int i, int j) { return r[(i+len)%n] < r[(j+len)%n]; };
        for (len = 1; len < 2*n; len *= 2) {
            int i = 0, j;
            while (i < n) {
                j = i+1; while (j < n && r[p[j]] == r[p[i]]) j++;
                sort(p+i, p+j, cmp);
                i = j;
            }
            int ind = 0;
            forn(i,n) {
                if (i && (r[p[i-1]] < r[p[i]] || cmp(p[i-1], p[i]))) ind++;
                nr[p[i]] = ind;
            }
            copy(nr, nr+n, r);
        }

        int k = 0;
        forn(i,n) {
            if (r[i] == n-1) k = 0;
            else {
                int j = p[r[i]+1];
                if (k) k--;
                while (s[i+k] == s[j+k]) k++;
            }
            lcp[r[i]] = k;
        }
    }
};


// DECL: SparseTable<int,cmp,18> rmq;
// MAIN: rmq.init(vector<int>(sa.lcp, sa.lcp+si(s)-1));
/* pii range(int i, int len) {
    i = sa.r[i];
    pii res;
    int lo = -1, hi = i;
    while (lo+1 < hi) {
        int mi = (lo+hi)/2;
        if (rmq.query(mi,i) >= len) hi = mi; else lo = mi;
    }
    res.first = hi;

    lo = i; hi = si(sa.s);
    while (lo+1 < hi) {
        int mi = (lo+hi)/2;
        if (rmq.query(i,mi) >= len) lo = mi; else hi = mi;
    }
    res.second = hi;
    return res;
}*/

int main() {
    string s = "banana"; s += char(0);
    auto v = vector<char>(s.begin(), s.end());
    SuffixArray<20,char> sa;
    sa.build(v);
    int n = si(s); 
    forn(i,n) cerr << sa.p[i]+1 << ' '; cerr << endl;
    forn(i,n-1) cerr << sa.lcp[i] << ' '; cerr << endl;
}
