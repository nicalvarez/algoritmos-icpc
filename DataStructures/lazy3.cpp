#include <bits/stdc++.h>
using namespace std;

struct node {
    int l,r;
    //int delta, sum;
    enum inter { FULL, EMPTY, PARTIAL };

    node () {}
    
    // TODO: poner el paramentro val = ZERO
    node(int l, int r, int val = 0): l(l), r(r) {
        // TODO: inicializar lazy y sum como corresponde
    }

    int get() { 
        // TODO: calcular el valor con delta y sum
    }

    void push(node &a, node &b) {
        // TODO: propagar delta, y setear delta = ZERO
    }

    void pull(node &a, node &b) {
        // TODO: calcular sum a partir de los hijos
    }

	inter inter(int a, int b) {
		if (r <= a || l >= b) return EMPTY;
		if (a <= l && r <= b) return FULL;
		return PARTIAL;
	}
};

struct lazy {
    node *n;

    lazy(int n) {
        this->n = new node[4*n];
        build(1,0,n);
    }

    void build(int id, int a, int b) {
        n[id] = node(a,b);
        if (a+1 < b) {
            int m = (a+b+1)/2;
            build(2*id, a, m);
            build(2*id+1, m, b);
            n[id].pull(n[2*id], n[2*id+1]);
        }
    }

    // TODO: Setear el tipo correcto para val
    void _update(int id, int a, int b, int val) {
        switch (n[id].inter(a,b)) {
            case node::EMPTY: return;
            case node::FULL:
                // TODO: Actualizar lazy
                return void();
            case node::PARTIAL:
				n[id].push(n[2*id], n[2*id+1]);
				_update(2*id, a, b, val);
				_update(2*id+1, a, b, val);
				n[id].pull(n[2*id], n[2*id+1]);
        }
    }

    // TODO: Seter tipo de val
    void update(int a, int b, int val) { _update(1,a,b,val); }

    // TODO: setar tipo de retorno
    int _get(int id, int a, int b) {
		switch (n[id].inter(a,b)) {
            case node::EMPTY: return 0; // TODO: poner ZERO
			case node::FULL: return n[id].get();
			case node::PARTIAL:
				n[id].push(n[2*id], n[2*id+1]);
                // TODO: calcular resultado a partir de hijos
                // int res = _get(2*id,a,b) + _get(2*id+1,a,b);
				n[id].pull(n[2*id], n[2*id+1]);
				//return res;
		}
		return 0; // TODO: setear ZERO
	}

	int get(int a, int b) { return _get(1,a,b); }
};


int main(int argc, char *argv[])
{
    
    return 0;
}
