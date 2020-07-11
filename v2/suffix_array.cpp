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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


vi suffix_array(const string &s) {
    int n = si(s);
    vi sa(n), rank(n);
    forn(i,n) {
        sa[i] = i;
        rank[i] = s[i];
    }
    vector<ll> rank2(n);
    for (int len = 1; len < n; len *= 2) {
        forn(i,n) rank2[i] = (ll(rank[i])<<32) + (i+len < n ? rank[i+len] : 0);
        sort(all(sa), [&](int i, int j) { return rank2[i] < rank2[j]; });
        forn(i,n) rank[sa[i]] = i > 0 && rank2[sa[i-1]] == rank2[sa[i]] ? rank[sa[i-1]] : i;
    }
    return sa;
}

vi lcp(const vi &sa, const string &s) {
    int n = si(sa);
    vi rank(n);
    forn(i,n) rank[sa[i]] = i;
    vi lcp(n-1);

    int h = 0;
    forn(i,n) if (rank[i] < n-1) {
        int j = sa[rank[i]+1];
        while (max(i,j)+h < n && s[i+h] == s[j+h]) ++h;
        lcp[rank[i]] = h;
        if (h) --h;
    }
    return lcp;
}

int main(int argc, char **argv) {}
