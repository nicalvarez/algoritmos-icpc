#include <vector>
#include <string>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())

typedef vector<int> vi;
typedef vector<vi> vvi;

template<class T>
vi z_function (const T &s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r) z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]]) ++z[i];
		if (i+z[i]-1 > r) l = i,  r = i+z[i]-1;
	}
	return z;
}

template<class T>
vi prefix_function(const T &s) {
    int n = si(s);
    vi pi(n+1);
    pi[0] = -1;
    for (int i = 1; i <= n; i++) {
        int &p = pi[i];
        p = pi[i-1];
        while (p != -1 && s[p] != s[i-1]) p = pi[p];
        ++p;
    }
    return pi;
}


vi kmp(const string &p, const string &t) {
    string s = p + "#" + t;
    vi pf = prefix_function(s);

    int start = si(p)+1;
    vi res(pf.begin() + start, pf.end());
    return res;
}

namespace automata {
    const int alphabet = 26; 

    vvi build_automata(string s) {
        s += '#';
        int n = si(s);
        vi pi  = prefix_function(s);
        vvi aut(n, vi(alphabet));
        forn(i,n) {
            for (char j = 0; j < alphabet; j++) { 
                char c = 'a' + j; // CAMBIAR POR EL ALFABETO POSTA!
                if (i > 0 && c != s[i])
                    aut[i][c] = aut[pi[i-1]][c];
                else
                    aut[i][c] = i + (c == s[i]);
            }
        }
        return aut;
    }
}

int main() {}
