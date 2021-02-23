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

struct node {
    int val, flag;
    int a,b;
    node *l,*r;

    node(int a, int b): a(a), b(b), l(0), r(0), val(0), flag(0) {}

    void push() {
        if (flag) {
            if (l) l->flag = !l->flag;
            if (r) r->flag = !r->flag;
            flag = 0;
            val = b-a-val;
        }
    }

    void pull() {
        val = 0;
        if (l) val += l->eval();
        if (r) val += r->eval();
    }

    int eval() {
        push();
        return val;
    }
};

struct lazy {
    node *root;

    void init(int n) {
        root = build(0,n);
    }

    node* build(int a, int b) {
        node *res = new node(a,b);
        if (a+1 == b) return res;
        else {
            int m = (a+b)/2;
            res->l = build(a,m);
            res->r = build(m,b);
            res->pull();
            return res;
        }
    }

    void update(node *x, int a, int b) {
        if (a <= x->a && x->b <= b) return void(x->flag = !x->flag);
        if (b <= x->a || x->b <= a) return;
        x->push();
        update(x->l, a, b);
        update(x->r, a, b);
        x->pull();
    }
    void update(int a, int b) { update(root,a,b); }
    
    int get(node *x, int a, int b) {
        if (a <= x->a && x->b <= b) return x->eval();
        if (b <= x->a || x->b <= a) return 0;
        int res = 0;
        x->push();
        res += get(x->l, a, b);
        res += get(x->r, a, b);
        x->pull();
        return res;
    }
    int get(int a, int b) { return get(root,a,b); }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    return 0;
}
