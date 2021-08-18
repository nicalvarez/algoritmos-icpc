
template<class T>
struct band_matrix {

    struct row {
        int n, from;
        vector<T> a;

        row(int n, int from): n(n), from(from), a(n) {}

        T &operator[](int i) {
            i -= from;
            assert(0 <= i && i < n);
            return a[i];
        }
    };

    vector<row> m;
    
    band_matrix(int n, int w) {
        forn(i,n) m.eb(2*w+1, i-w);
    }

    row &operator[](int i) { 
        assert(0 <= i && i < si(m));
        return m[i];
    }

    vector<T> solve(vector<T> v) {
        auto m = *this;
        int sz = si(m.m);

        for (int i = 0; i < sz; i++) {
            double c = m[i][i];
            for (int j = i-w; j <= i+w; j++) if (0 <= j && j < sz) m[i][j] /= c;
            v[i] /= c;

            for (int j = i+1; j < sz && j-i <= w; j++) {
                double mul = m[j][i];
                for (int k = i; k <= i+w; k++) if (k < sz) {
                    m[j][k] -= mul * m[i][k];
                }
                v[j] -= mul * v[i];
            }
        }

        for (int i = sz-1; i >= 0; i--) {
            for (int j = i-1; j >= 0 && i-j <= w; j--) {
                double mul = m[j][i];
                m[j][i] = 0;
                v[j] -= mul * v[i];
            }
        }

        return v;
    }
};
