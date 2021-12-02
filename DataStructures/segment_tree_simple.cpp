
#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << "=" << (a) << endl;
#define pb push_back
#define eb emplace_back
#define mp make_pair

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Val {

    // must return additive ZERO
    Val() {}

    Val& operator+=(const Val &o) {
        // implement
        return *this;
    }

    Val operator+(const Val &o) const {
        return Val(*this) += o;
    }

};

template<class Val>
struct segment_tree {

    struct node {
        Val val;
        node *left, *right;

        Val eval() {
            return val;
        }

        void pull() {
            val = left->eval() + right->eval();
        }

    };

    int n;
    node *root;

    segment_tree(int n=0): segment_tree(vector<Val>(n)) { }

    segment_tree(const vector<Val> &a) {
        n = si(a);
        root = build(0, n, a);
    }

    node* build(int from, int to, const vector<Val> &a) {
        if (from >= to) return nullptr;
        if (from+1 == to) return new node({a[from], nullptr, nullptr});
        auto ans = new node();
        int mid = (from+to) / 2;
        ans->left = build(from, mid, a);
        ans->right = build(mid, to, a);
        ans->pull();
        return ans;
    }

    void update_pos(node *u, int from, int to, int pos, Val val) {
        if (from+1 == to) {
            u->val = val;
            return;
        }
        int mid = (from + to) / 2;
        if (pos < mid) update_pos(u->left, from, mid, pos, val);
        else update_pos(u->right, mid, to, pos, val);
        u->pull();
    }

    void update_pos(int pos, Val val) {
        update_pos(root, 0, n, pos, val);
    }

    Val get(node *u, int from, int to, int a, int b) {
        if (to <= a || b <= from) return Val();
        if (a <= from && to <= b) return u->eval();
        int mid = (from + to) / 2;
        return get(u->left, from, mid, a, b) + get(u->right, mid, to, a, b);
    }

    Val get(int a, int b) {
        return get(root, 0, n, a, b);
    }

    template<class Cond>
    tuple<int,Val,Val> lower_bound(node *u, int from, int to, Val prefix, Cond cond) {
        if (from+1 == to) {
            auto cand = prefix + u->eval();
            if (cond(cand)) return {from, prefix, cand};
            else return {to, cand, cand};
        }

        int mid = (from + to) / 2;
        auto nprefix = prefix + u->left->eval();
        if (cond(nprefix)) {
            return lower_bound(u->left, from, mid, prefix, cond);
        }
        else {
            return lower_bound(u->right, mid, to, nprefix, cond);
        }
    }

    template<class Cond>
    tuple<int,Val,Val> lower_bound(Cond cond) {
        return lower_bound(root, 0, n, Val(), cond);
    }

};

using segment = segment_tree<Val>;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}
