#include <bits/stdc++.h>
using namespace std;

/*
 * TODO: 
 *      - Mezclar con FFTs
 *      - Implementar .inverse() y .sqrt()  (series de potencia)
 *      - Implementar multiplicacion (lenta y rápida (fft))
 *      - Horner's Rule (creo)... evaluar el polinomio de manera piola, bah
 *
 *
 *
 *
 *
 *
 */
struct poly {
    vector<double> c;

    poly(const vector<double> &c): c(c) {}

    double eval(double x) {
        double res = 0;
        int n = c.size();
        for (int i = n-1; i >= 0; i--) res = res*x + c[i];
        return res;
    }

    poly operator+(const poly &o) const {
        int m = c.size(), n = o.c.size();
        vector<double> res(max(m,n));
        for (int i = 0; i < m; i++) res[i] += c[i];
        for (int i = 0; i < n; i++) res[i] += o.c[i];
        return poly(res);
    }

    poly operator*(const poly &o) const {
        int m = c.size(), n = o.c.size();
        vector<double> res(m+n-1);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res[i+j] += c[i] * o.c[j];
        return poly(res);
    }

};


poly interpolate(const vector<double> &x, const vector<double> &y) {
    int n = x.size();
    poly p({});
    for (int i = 0; i < n; i++) {
       double a = y[i] - p.eval(x[i]);
       for (int j = 0; j < i; j++) {
           a /= x[i] - x[j];
       } 
       poly add({a});
       for (int j = 0; j < i; j++) add = add*poly({-x[j],1});
       p = p + add;
    }
    return p;
}
