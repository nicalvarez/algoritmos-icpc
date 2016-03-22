#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

template <class T, class Op, int L>
struct SparseTable {
    int n;
    T a[L][1<<L];
    Op op;

    void init(const vector<T> &v) {
        n = (int) v.size();
        copy(v.begin(), v.end(), a[0]);

        for (int l = 1; l < L; l++)
            for (int i = 0; i+(1<<l) <= n; i++)
                a[l][i] = op(a[l-1][i], a[l-1][i + (1<<(l-1))]);
    }

    T query(int l, int r) {
        //if (l >= r) return INF;
        int lg = 31 - __builtin_clz(r-l);
        return op(a[lg][l], a[lg][r - (1<<lg)]);
    }

};

struct cmp {
    int operator()(int i, int j) { return min(i,j); }
};

int main() {
    vector<int> v = {0,5,7,-2,14,12,8,2,10};
    int n = v.size(); cerr << "sz = " << n << endl;

    SparseTable<int,cmp,5> st;
    st.init(v);

    for (;;) {
        int l,r; cin >> l >> r;
        if (l == -1) break;
        cerr << st.query(l,r) << endl;
    }
}
