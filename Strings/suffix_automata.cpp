#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())

namespace suffix_automata
{
    struct state {
        int len, link;
        map<char,int> next;
    };

    const int MAXLEN = 100000;
    state st[MAXLEN*2];
    int sz, last;

    void sa_init() {
        sz = last = 0;
        st[0].len = 0;
        st[0].link = -1;
        ++sz;

        /*
        // Inicializar los estados
        for (int i=0; i<MAXLEN*2; ++i)
        st[i].next.clear();
        */
    }

    void sa_extend (char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p;
        for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
            st[p].next[c] = cur;
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    void process(const string &s) {
        sa_init();
        forn(i,si(s)) sa_extend(s[i]);
    }
}

int main(int argc, char *argv[])
{

    return 0;
}
