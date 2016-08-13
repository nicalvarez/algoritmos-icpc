#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forsn(i,a,b) for (int i = int(a); i < int(b); i++)
#define si(c) ((int)(c).size())
#define mp make_pair

#define D(x) cerr << #x << " = " << x << endl



// Two-phase simplex algorithm for solving linear programs of the form
//
//     maximize     c^T x
//     subject to   Ax <= b
//                  x >= 0
//
// INPUT: A -- an m x n matrix
//        b -- an m-dimensional vector
//        c -- an n-dimensional vector
//        x -- a vector where the optimal solution will be stored
//
// OUTPUT: value of the optimal solution (infinity if unbounded
//         above, nan if infeasible)
//
// To use this code, create an Simplex object with A, b, and c as
// arguments.  Then, call Solve(x).

typedef long double dbl;
typedef vector<int> vi;
typedef vector<dbl> vd;
typedef vector<vd> vvd;

const dbl
    UNBOUNDED = numeric_limits<dbl>::infinity(),
    INFEASIBLE = -numeric_limits<dbl>::infinity(),
    EPS = 1e-9;

struct Simplex {
    int m,n;
    vi N,B;
    vvd M;

    Simplex(const vvd &A, const vd &b, const vd &c):
        m(b.size()), n(c.size()), N(n+1), B(m), M(m+2, vd(n+2)) 
    {
        forn(i,m) forn(j,n) M[i][j] = A[i][j];
        forn(i,m) M[i][n] = -1, M[i][n+1] = b[i], B[i] = n+1+i;
        forn(j,n) M[m][j] = -c[j], M[m+1][j] = 0, N[j] = j;
        N[n] = n; M[m+1][n] = 1e4;
    }

    void pivot(int r, int s) {
        dbl val = M[r][s];
        forn(j,n+2) M[r][j] /= val;
        forn(i,m+2) if (i != r) {
            forn(j,n+2) if (j != s) M[i][j] -= M[r][j] * M[i][s];
            M[i][s] /= -val;
        }
        M[r][s] = dbl(1) / val;
        swap(B[r], N[s]);
    }

    dbl simplex(int x) {
        while (true) {
            int s = 0; 
            forsn(j,1,n+1) if (mp(M[x][j], N[j]) < mp(M[x][s], N[s])) s = j;
            if (M[x][s] > -EPS) return M[x][n+1];

            int r = -1;
            forn(i,m) if (M[i][s] > EPS) {
                if (r == -1) r = i;
                else {
                    double fi = M[i][n+1] / M[i][s];
                    double fr = M[r][n+1] / M[r][s];
                    if (mp(fi, B[i]) < mp(fr, B[r])) r = i;
                }
            }
            if (r == -1) return UNBOUNDED;
            pivot(r,s);
        }
    }

    dbl solve(vd &x) {
        int r = 0;
        forsn(i,1,m) if (M[i][n+1] < M[r][n+1]) r = i;
        if (M[r][n+1] < -EPS) {
            pivot(r,n);
            if (simplex(m+1) < -EPS) return INFEASIBLE;
            forn(i,m) if (B[i] == n) {
                int s = 0;
                M[i][n+1] = 0;
                forsn(j,1,n+1) if (abs(M[i][j]) > abs(M[i][s])) s = j;
                pivot(i,s);
                break;
            }
        }

        forn(j,n+1) if (N[j] == n) {
            forn(i,m+2) M[i][j] = 0;
            break;
        }

        dbl z = simplex(m);
        if (z != INFEASIBLE && z != UNBOUNDED) {
            x = vd(n);
            forn(i,m) if (B[i] < n) x[B[i]] = M[i][n+1];
        }
        return z;
    }

    void trace() {
        ios state(NULL);
        state.copyfmt(cerr);
        cerr << fixed << setprecision(4);

        int W = 15;
        forsn(i,-1,m+2) {
            forsn(j,-1,n+2) {
                if (i == -1) {
                    if (j == -1) cerr << setw(W) << "";
                    else if (j == n+1) cerr << setw(W) << "b";
                    else cerr << setw(W) << "x" << N[j];
                }
                else {
                    if (j == -1) {
                        if (i < m) cerr << setw(W) << "x" << B[i];
                        else cerr << setw(W) << "z" << i-m;
                    }
                    else cerr << setw(W) << M[i][j];
                }
            }
            cerr << endl;
        }
        cerr << "--------------------\n";
        cerr.copyfmt(state);
    }

};

// TEST: TCO 2008 R2: Precious Stones
struct PreciousStones {
    double value(vi s, vi g) {
        int n = si(s), m = 2+n;
        vvd A(m,vd(n));
        forn(i,n) A[i][i] = 1;
        forn(j,n) {
            A[n][j] = s[j] + g[j];
            A[n+1][j] = -s[j] - g[j]; 
        }

        vd b(m);
        forn(i,n) b[i] = 1;
        dbl sum = 0; forn(i,n) sum += g[i];
        b[n] = sum; b[n+1] = -sum;

        vd c(n);
        forn(i,n) c[i] = s[i];

        vd x;
        Simplex lp(A,b,c);

        return lp.solve(x);
    }
};

// TEST: SRM 231: Mixture
struct Mixture {
    double mix(vi mixture, vector<string> availableMixtures) {
        int n = si(availableMixtures),
            m = si(mixture);

        vvd M(n,vd(m));
        vd c(n);
        forn(i,n) {
            stringstream ss(availableMixtures[i]);
            forn(j,m) ss >> M[i][j];
            ss >> c[i]; c[i] = -c[i];
        }

        vvd A(2*m,vd(n)); vd b(2*m);
        forn(j,m) {
            forn(i,n) A[j][i] = M[i][j];
            b[j] = mixture[j];
            forn(i,n) A[j+m][i] = -M[i][j];
            b[j+m] = -mixture[j];
        }

        vd x;
        Simplex lp(A,b,c);

        double ans = lp.solve(x);
        if (ans == INFEASIBLE) return -1;
        else return -ans;
    }

};


int main() {
    if(false) {
        vvd A;
        vd b,c;
        A = {{1},{-1}},
        b = {1,-2},
        c = {1};

        vd x;
        Simplex lp(A,b,c);
        D(lp.solve(x));
        return 0;
    }


    Mixture m;
    cerr <<     m.mix(vi{6, 9, 4, 10, 8, 6, 8, 9}, 
    {"6 7 10 2 9 0 2 2 0", "7 0 0 8 9 3 3 2 0", "2 5 5 7 1 4 1 10 0", "2 8 1 9 8 5 9 5 3", "3 7 7 7 3 4 10 2 8", "4 8 8 5 6 6 4 1 9", "7 7 0 6 6 4 7 8 6", "10 2 4 0 3 7 0 1 5", "4 5 8 0 9 6 5 2 1", "7 1 3 6 4 10 0 9 1"});

cerr << m.mix(vi{1,1,1,1,1,1,1,1,1,1},
vector<string>
{"10 9 9 9 9 9 9 9 9 10 0",
 "0 10 9 9 9 9 9 9 9 0 0",
 "0 0 10 9 9 9 9 9 9 0 0",
 "0 0 0 10 9 9 9 9 9 0 0",
 "0 0 0 0 10 9 9 9 9 0 0",
 "0 0 0 0 0 10 9 9 9 0 0",
 "0 0 0 0 0 0 10 9 9 0 0",
 "0 0 0 0 0 0 0 10 9 0 0",
 "0 0 0 0 0 0 0 0 10 1 0",
 "0 0 0 0 0 0 0 0 0 10 1"}
);
    return 0;



    if (false) {
        m.mix(vi{1,2,3}, vector<string>{"1 0 0 1","0 1 0 2","0 0 1 3"});
    	
        m.mix(vi{7,7,8,10}, vector<string> {"9 0 4 8 4",
 "8 8 9 0 1",
 "0 10 3 10 7",
 "10 2 2 0 1",
 "8 9 10 2 6",
 "1 2 5 8 8",
 "4 7 8 9 6",
 "2 10 6 8 10",
 "6 3 9 7 1",
 "3 6 9 9 1"});
    	
}
    return 0;
  	
    cerr << value( vi{ 11, 9, 13, 10 }, vi{ 8, 14, 17, 21 });
    return 0;

    cerr << value(vi{0,0},vi{10,11}) << endl;
    cerr << value(vi{10,6},vi{3,10}) << endl;
    return 0;
    
//    vd c = {2,-1};
//    vd b = {2,-4};
//    vvd A = {
//        {2,-1},
//        {1,-5}
//    };
//    
//    vd x;
//    Simplex lp(A,b,c);
//    cerr << lp.solve(x) << endl;
//    //D(lp.solve(x));
    

//    vd c = {3,1,2};
//    vd b = {30,24,36};
//    vvd A = {
//        {1,1,3},
//        {2,2,5},
//        {4,1,2}
//    };
//
//    vd x;
//    Simplex lp(A,b,c);
//    //D(lp.simplexOne());
//    cerr << lp.solve(x) << endl;
//    for (auto xi : x) cerr << xi << ' '; cerr << endl;

    return 0;
} 

