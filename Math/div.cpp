#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e8 + 100;

bool criba[MAXN];

vector<int> p;

int main(int argc, const char *argv[])
{
    fill(criba+2, criba+MAXN, true);
    for (int i = 2; i*i < MAXN; i++) if (criba[i]) {
        for (int j = i*i; j < MAXN; j += i) criba[j] = false;
    } 

    for (int i = 2; i < MAXN; i++) if (criba[i]) p.push_back(i);
    cerr << p.size() << endl;
    for (int i = 0; i < 10; i++)  cerr << p[i] << ' '; cerr << endl;
    
    return 0;
}
