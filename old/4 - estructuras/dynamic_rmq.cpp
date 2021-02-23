#include <iomanip>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <complex>
#include <cassert>
#include <bitset>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define decl(v, c) typeof(c) v = c
#define forall(i, c) for(decl(i, c.begin()); i!=c.end(); ++i)
#define dforall(i, c) for(decl(i, c.rbegin()); i!=c.rend(); ++i)
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define D(a) cout << #a << "=" << a << endl;
#define pb push_back
#define mp make_pair

typedef long long int tint;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<tint> vt;
typedef vector<vt> vvt;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

// MAXN es la cantidad maxima de elementos que se banca la estructura.
// pget(i, j) incluye i y no incluye j. preinit+posinit O(n).
// Funciona con cualquier operador + asociativo y con elemento neutro 0
// Se inicializa asi:
// cin >> n; preinit(n); forn(i, n) cin >> vec[MAX+i]; posinit();

typedef int tipo;
#define MAXN 100000
int MAX = 0;
tipo vec[3 * MAXN];

void preinit(int n) {
	MAX = 1 << (32 - __builtin_clz(n));
	fill(vec + MAX, vec + 3 * MAXN, 0); // 0 = elemento neutro
}
void posinit(void) { dforsn(i,0,MAX) vec[i] = vec[2*i] + vec[2*i+1]; } // + = operacion

void pset(int i, tipo val) {
	i += MAX;
	vec[i] = val;
	while (i) {
		i /= 2;
		vec[i] = vec[2 * i] + vec[2 * i + 1]; // + = operacion
	}
}

tipo _pget(int i, int j) { // intervalo [i,j)
	tipo res = 0; // 0 = elemento neutro
	if (j - i <= 0) return res;
	if (i % 2) res = vec[i++];
	res += _pget(i / 2, j / 2); // + = operacion
	if (j % 2) res += vec[--j]; // + = operacion
	return res;
}

tipo pget(int i, int j) { return _pget(i + MAX, j + MAX); }
