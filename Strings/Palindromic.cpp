#include <iostream>
#include <string>
#include <map>
using namespace std;

#define si(c) ((int)(c).size())

struct node;
typedef node *pnode;
struct node {
    int len;
    pnode link;
    map<char,pnode> to;
};

int res = 0;
struct eertree {
    node odd, even;
    pnode maxSuf;
    string s;

    eertree() {
        odd.len = -1; odd.link = &odd;
        even.len = 0; even.link = &odd;
        maxSuf = &odd;
    }

    void add(char c) {
        int i = si(s)-1;
        s += c;
        pnode q = maxSuf;
        while (i - q->len < 0 || c != s[i - q->len]) q = q->link;
        
        pnode p;
        res = 1-q->to.count(c);
        if (!q->to.count(c)) {
            p = q->to[c] = new node();
            p->len = q->len+2;
            if (p->len < 2) p->link = &even;
            else {
                q = q->link;
                while (c != s[i-q->len]) q = q->link;
                p->link = q->to[c];
            }
        }
        maxSuf = p;
        //cerr << maxSuf->len << endl;
    }

    void print(pnode root, string pref) {
        cout << pref << ' ' << root->len << ' ' << root->link->len << endl;
        for (auto kv : root->to) 
            print(kv.second, pref+kv.first);
    }

    void print() {
        cout << "odd" << endl;
        print(&odd,"");
        
        cout << "even" << endl;
        print(&even,"");
    }
};


int main() {

    ios_base::sync_with_stdio(false);

    eertree et;
    string s; cin >> s;
    for (char c : s) {
        et.add(c);
        cout << res;
    }
    cout << endl;


    return 0;
}
