#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())

struct trie {
    struct node {
        // int next[MAXC];
        map<char,int> next;
        bool leaf;
    };

    int sz;
    node *t;

    trie(int maxnodes) {
        t = new node[maxnodes];
        sz = 1;
    }

    void add(const string &s) {
        int v = 0;
        forn(i,si(s)) {
            // char c = s[i] - 'a';
            char c = s[i];
            // if (t[v].next[c] == -1)
            if (!t[v].next.count(c)) {
                //fill_n(t[sz].next, MAXC, -1);
                t[sz].next.clear();
                t[v].next[c] = sz++;
            }
            v = t[v].next[c];
        }
        t[v].leaf = true;
    }

    bool find(const string &s) {
        int v = 0;
        forn(i,si(s)) {
            // char c = s[i] - 'a';
            char c = s[i];
            // if (t[v].next[c] == -1)
            if (!t[v].next.count(c)) return false;
            v = t[v].next[c];
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
    
    return 0;
}
