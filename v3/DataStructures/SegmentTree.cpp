#include <algorithm>
#include <vector>
using namespace std;


template <class V, class Op>
struct SegmentTree {
    static Op op;

    struct Node {
        int a, b;
        Node *l, *r;
        V value;

        Node(int a, int b, V value=V()):
            a(a), b(b), 
            l(0), r(0),
            value(value)
        {
        }

        void pull() { 
            value = op(l->value, r->value);
        }
    };

    int n;
    Node *root;

    void init(const vector<V> &values) { 
        n = values.size();
        root = build(0,n,values);
    }

    Node* build(int a, int b, const vector<V> &values) {
        Node *res;
        if (a+1 < b) {
            res = new Node(a,b);
            int m = (a+b)/2;
            res->l = build(a,m,values);
            res->r = build(m,b,values);
            res->pull();
        }
        else res = new Node(a,b,values[a]);
        return res;
    }

    void set(Node *x, int pos, V v) {
        if (x->a + 1 == x->b) x->value = v;
        else {
            if (pos < x->l->b) set(x->l, pos, v);
            else set(x->r, pos, v);
            x->pull();
        }
    }
    void set(int pos, V v) { set(root,pos,v); }

    V get(Node *x, int a, int b) {
        if (b <= x->a || x->b <= a) return V();
        if (a <= x->a && x->b <= b) return x->value;
        else return op(get(x->l,a,b), get(x->r,a,b));
    } 
    V get(int a, int b) { return get(root,a,b); }

};

