#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)

typedef vector<int> vi;

vi manacher(const string &s) {
    int n = si(s);
    vi p(n,1);
    int a = 0;
    forsn(i,1,n) {
        int &k = p[i];
        if (a + p[a] > i) {
            k = a+p[a]-i;
            if (p[2*a-i] < k) {
                k = p[2*a-i];
                continue;
            }
        }
        while (0 <= i-k && i+k < n && s[i-k] == s[i+k]) k++;
        if (i+k > a+p[a]) a = i;
    }
    return p;
}

string preprocess(const string &s) {
    int n = si(s);
    string res(2*n+1, '#');
    forn(i,n) res[2*i+1] = s[i];
    return res;
}

int main() {
    string s = "el evangelio oilegnave le";
    string s2 = preprocess(s);
    cerr << s << endl << s2 << endl << endl;

    for (int x : manacher(s2)) cerr << x << ' '; cerr << endl;
    return 0;
}

