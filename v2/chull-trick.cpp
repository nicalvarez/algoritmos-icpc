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

const int N = 1e5 + 10;

int n;
ll A[N], B[N];

bool bad(int l1, int l2, int l3) {
    return (B[l1] - B[l2]) * (A[l3] - A[l1]) >= (B[l1] - B[l3]) * (A[l2] - A[l1]);
}

vector<int> chull;

// Se agregan en orden de A[i] crecientes
// Si queres al reves, pone -A[i], -B[i] y usa -query(x)
void add(vi &chull, int l) {
    int sz = chull.size();
    while (sz >= 2 && bad(chull[sz-2], chull[sz-1], l)) {
        chull.pop_back();
        sz--;
    }
    chull.push_back(l);
}

ll eval(int l, ll x) { return A[l]*x + B[l]; }

pair<ll,int> query(const vi &chull, ll x) {
    int lo = -1, hi = chull.size()-1;
    while (lo+1 < hi) {
        int mi = (lo+hi)/2;
        if (eval(chull[mi],x) < eval(chull[mi+1],x)) lo = mi; else hi = mi;
    }
    return mp(eval(chull[hi],x), chull[hi]);
}

int main() {}
