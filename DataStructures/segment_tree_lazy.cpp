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

struct Mod {

    // must return multiplicative ONE
    Mod() {}

    Mod& operator*=(const Mod &o) {
        // implement
        return *this;
    }

    Mod operator*(const Mod &o) const {
        return Mod(*this) *= o;
    }

    Val operator*(const Val &o) const {
    }
};


template<class Val, class Mod>
struct segment_tree_lazy {

    struct node {
        Val val;
        Mod mod;
        node *left, *right;

        Val eval() {
            return mod * val;
        }

        void pull() {
            mod = Mod();
            val = left->eval() + right->eval();
        }

        void push() {
            left->mod = mod * left->mod;
            right->mod = mod * right->mod;
            mod = Mod();
        }
    };

    int n;
    node *root;

    segment_tree_lazy(int n=0) {
        segment_tree_lazy(vector<Val>(n));
    }

    segment_tree_lazy(const vector<Val> &a) {
        n = si(a);
        root = build(0, n, a);
    }

    node* build(int from, int to, const vector<Val> &a) {
        if (from >= to) return nullptr;
        if (from+1 == to) return new node({a[from], Mod(), nullptr, nullptr});
        auto ans = new node();
        int mid = (from+to) / 2;
        ans->left = build(from, mid, a);
        ans->right = build(mid, to, a);
        ans->pull();
        return ans;
    }

    void update(node *u, int from, int to, int a, int b, Mod mod) {
        if (to <= a || b <= from) return;
        if (a <= from && to <= b) return void(u->mod = mod * u->mod);
        u->push();
        int mid = (from+to) / 2;
        update(u->left, from, mid, a, b, mod);
        update(u->right, mid, to, a, b, mod);
        u->pull();
    }

    void update(int a, int b, Mod mod) {
        update(root, 0, n, a, b, mod);
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

    Val get(node *u, int from, int to, int a, int b, Mod mod) {
        if (to <= a || b <= from) return Val();
        if (a <= from && to <= b) return mod * u->eval();
        int mid = (from + to) / 2;
        mod = mod * u->mod;
        return get(u->left, from, mid, a, b, mod) + get(u->right, mid, to, a, b, mod);
    }

    Val get(int a, int b) {
        return get(root, 0, n, a, b, Mod());
    }

    template<class Cond>
    tuple<int,Val,Val> lower_bound(node *u, int from, int to, Val prefix, Mod mod, Cond cond) {
        if (from+1 == to) {
            auto cand = prefix + mod*u->eval();
            if (cond(cand)) return {from, prefix, cand};
            else return {to, cand, cand};
        }

        int mid = (from + to) / 2;
        mod = mod * u->mod;
        auto nprefix = prefix + mod * u->left->eval();
        if (cond(nprefix)) {
            return lower_bound(u->left, from, mid, prefix, mod, cond);
        }
        else {
            return lower_bound(u->right, mid, to, nprefix, mod, cond);
        }
    }

    template<class Cond>
    tuple<int,Val,Val> lower_bound(Cond cond) {
        return lower_bound(root, 0, n, Val(), Mod(), cond);
    }

};

using segment = segment_tree_lazy<Val,Mod>;

int main() {

}
