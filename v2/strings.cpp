#include <vector>
#include <string>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())

typedef vector<int> vi;
typedef vector<vi> vvi;

vector<int> z_function (const string &s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r) z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]]) ++z[i];
		if (i+z[i]-1 > r) l = i,  r = i+z[i]-1;
	}
	return z;
}

vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j]) j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
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
