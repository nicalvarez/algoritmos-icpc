#include <bits/stdc++.h>
using namespace std;

namespace Karatsuba {

    int sz = 0, buffer[1<<25];
    void alloc(int *&pnt, int n) {
        pnt = buffer+sz;
        sz += n;
    }

    void multiply(int n, int a[], int b[], int c[]) {
        fill_n(c, 2*n, 0);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    c[i+j] += a[i] * b[j];
        }
        else {
            int osz = sz;
            int *a1, *a2; alloc(a1,n/2); alloc(a2,n/2);
            copy(a, a + n/2, a2); copy(a + n/2, a + n, a1);

            int *b1, *b2; alloc(b1,n/2); alloc(b2,n/2);
            copy(b, b + n/2, b2); copy(b + n/2, b + n, b1);

            int *c1, *c2; alloc(c1,n); alloc(c2,n);
            multiply(n/2, a1, b1, c1);
            multiply(n/2, a2, b2, c2);

            for (int i = 0; i < n/2; i++) a1[i] += a2[i], b1[i] += b2[i];
            int *c3; alloc(c3,n);
            multiply(n/2, a1, b1, c3);

            for (int i = 0; i < n; i++) {
                c[i + n] += c1[i];
                c[i + n/2] += c3[i] - c2[i] - c1[i];
                c[i] += c2[i];
            }
            sz = osz;
        }
    }

    vector<int> multiply(vector<int> a, vector<int> b) {
        int size = (int) max(a.size(), b.size());
        int n = 1; while (n < size) n *= 2;
        int osz = sz;
        int *A, *B, *C; alloc(A,n); alloc(B,n); alloc(C,n);
        fill_n(A,n,0); fill_n(B,n,0);
        copy(a.begin(), a.end(), A);
        copy(b.begin(), b.end(), B);
        multiply(n,A,B,C);
        sz = osz;
        n = a.size() + b.size() - 1;
        return vector<int>(C, C+n);
    }

};

int main() {
    vector<int> a = {1,2,3}, b = {2,2};
    for (int x : Karatsuba::multiply(a,b)) cerr << x << ' ';
    return 0;
}
