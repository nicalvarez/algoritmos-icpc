#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
typedef vector<int> vi;

bool prime(int n) {
    for (int d = 2; d*d <= n; d++) if (n % d == 0) return false;
    return true;
}

int gcd(int a, int b) { return a ? gcd(b%a,a) : b; }

int n,k;
int f(int x) { return (x*tint(x) + k) % n; }

int pollard() {
    int a,b;
    a = b = rand()%n; 
    k = rand()%n;
    int d;
    for (;;) {
        a = f(a);
        b = f(f(b));
        d = abs(gcd(b-a,n));
        if (d != 1) break;
    }
    return d;
}

void factor(int n, vi &res) {
    if (prime(n)) return void(res.push_back(n));

    ::n = n; int d;
    while ((d = pollard()) == n);
    factor(d,res); factor(n/d,res);
}

int main() {
    srand(time(0));
    ios_base::sync_with_stdio(false);
    vi f; factor(31298206, f);
    sort(f.begin(), f.end());
    for (int fi : f) cerr << fi << ' '; cerr << endl;
    return 0;
}

