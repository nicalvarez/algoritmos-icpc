#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define mp make_pair


typedef long long int tint;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

typedef pair<tint,tint> ptt;

ptt egcd(tint a, tint b) {
	if (a == 0) return mp(0,1);
	tint q = b/a;
	ptt t = egcd(b-q*a, a);
	return mp(t.second - q*t.first, t.first);
}

tint inverse(tint x, tint m) {
	tint res = egcd(x,m).first;
	return (res % m + m) % m;
}

// m must be positive
template<typename T>
static T mod(T a, T m)
{
    a %= m;
    if (a < 0)
        a += m;
    return a;
}

// a must be relatively prime to m
template<typename T>
static T inverse(T a, T m)
{
    a = mod(a, m);
    if (a <= 1)
        return a;
    return mod((1 - inverse(m, a) * m) / a, m);
}

typedef long long ll;
int inverse(int a, int m) {
    if (a <= 1) return a;
    int ans = (1 - (ll) inverse(m%a,a)*m)/a;
    if (ans < 0) ans += m;
    return ans;
}

tint chinese(int n, tint r[], tint m[]) {
	tint M = 1;
	forn(i,n) M *= m[i];

	tint res = 0;
	forn(i,n) {
		tint xi = r[i];
		forn(j,n) if (j != i) {
			xi = xi * m[j] % M * inverse(m[j], m[i]) % M;
		}
		res += xi;
		if (res >= M) res -= M;
	}
	return res;
}

int main() {}
