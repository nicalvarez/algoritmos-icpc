#include <bits/stdc++.h>
using namespace std;
 
#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << "=" << a << endl;
#define pb push_back
#define eb emplace_back
#define mp make_pair
 
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int INF = 1e9;
const int N = 1e5;

int n;
vector<pair<int,int>> adj[N];

vector<int> spfa(int S) {
    vector<bool> in_queue(n);
    vector<int> dist(n, INF);
    dist[S] = 0;
    queue<int> q;
    q.push(S);
    in_queue[S] = true;
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        in_queue[u] = false;
        for (auto vc : adj[u]) {
            int v,c; tie(v,c) = vc;
            if (dist[v] > dist[u] + c) {
                dist[v] = dist[u] + c;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return dist;
}


 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}
