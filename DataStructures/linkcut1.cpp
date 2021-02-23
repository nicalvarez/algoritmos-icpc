namespace LinkCut {
    struct node{
        node *l, *r, *p;
        bool flip;
        int sz;

        bool isRoot() { return p == NULL || (p->l != this && p->r != this);}

        void normalize() {
            if (flip) {
                flip = false;
                swap(l,r);
                if (l) l->flip = !l->flip;
                if (r) r->flip = !r->flip;
            }
            sz = 1;
            if (l) sz += l->sz;
            if (r) sz += r->sz;
        }
        int value() {
            if (r) return r->sz;
            else return 0;
        }
        void update() {
            sz = 1;
            if (l) sz += l->sz;
            if (r) sz += r->sz;
        }

        node(): l(NULL), r(NULL), p(NULL), flip(false) {}
    };
    static void connect(node* p, node* q, bool left) {
        if (left) q->l = p;
        else q->r = p;
        if (p) p->p = q;
    }
    static void rotate(node* p) {
        node* q = p->p;
        node *r = q->p;
        bool root = q->isRoot();
        bool left = (p == q->l);
        connect(left?p->r:p->l, q, left);
        connect(q, p, !left);
        if (!root) connect(p, r, q == r->l);
        else p->p = r;
        q->update();
    }
    static void print(node* p) {
        cerr << "(";
        if (p->l) print(p->l);
        cerr << ".";
        if (p->r) print(p->r);
        cerr << ")";
    }
    static void splay(node *p) {
        while(!p->isRoot()) {
            node *q = p->p;
            node *r = q->p;
            if (!q->isRoot()) r->normalize();
            q->normalize();
            p->normalize();
            if (q->isRoot()) rotate(p);                                     //ZIG
            else {
                if ((r->l == q && q->l == p) || (r->r == q && q->r == p)) { //ZIG-ZIG
                    rotate(q), rotate(p);
                } else {                                                    //ZIG-ZAG
                    rotate(p), rotate(p);
                }
            }
        }
        p->normalize();
        p->update();
    };

    static node* expose(node *q) {
        node* r = NULL;
        for (node *p=q; p; p = p->p) {
            splay(p);
            p->l = r;
            p->update();
            r = p;
        }
        splay(q);
        return r;
    }

    /*static node* findRoot(node *p) {
        expose(p);
        while(p->r) {
            p = p->r;
            p->normalize();
        }
        splay(p);
        return p;
    }*/

    static void link(node *p, node *q) { // p and q must be nodes in different trees
        expose(p);
        p->flip = !p->flip;
        p->p = q;
    }

    static bool connected(node*p, node* q) {
        if (p == q) return true;
        expose(p);
        expose(q);
        return p->p != NULL; 
    }

    static void cut(node *p, node *q) { // p and q must be connected by an edge
        expose(p);
        p->flip = !p->flip;
        expose(q);
        p->p = NULL;
        q->r = NULL;

    }
    static int dist(node* p, node *q) {
        if (p == q) return 0;
        expose(p);
        p->flip = !p->flip;
        expose(q);
        if (p->p == NULL) return -1;
        return q->value();
    }
};

