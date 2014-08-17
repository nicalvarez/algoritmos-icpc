#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <complex>

using namespace std;

typedef vector<int> vi; 
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef set<int> se;
typedef pair<int,int> pii;
typedef long long int tint;

#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define decl(v, c) typeof(c) v = c
#define forall(i, c) for(decl(i, c.begin()); i!=c.end(); ++i)
#define all(c) (c).begin(), (c).end()
#define D(a) << #a << "=" << a << " "


#define si(a) int((a).size())
#define pb push_back

struct trie {
	typedef map<char,trie*> hijos;
	hijos child;
	bool final;
	
	trie() {
		final = false;
	}
	
	void insert(const string &s) {
		trie *now = this;
		int n = si(s);
		forn(i,n) {
			// actualizar data del nodo
			
			if (!(now->child.count(s[i]))) 
				now->child[s[i]] = new trie();
				
			now = now->child[s[i]];			
		}
		now->final = true; // o arco a '$'		
	}
	
	void clear() {
		//for (hijos::iterator it = child.begin(); it != child.end(); it++) {
		forall(it,child) {
			it->second->clear();					
		}
		child.clear();
	}
	
	void print(string tab = "") {
		forall(it,child) {
			cerr << tab << it->first << endl;
			it->second->print(tab + "--");			
		}
	}
	
	bool find(const string& s) {
		trie *now = this;
		int n = si(s);
		forn(i,n) {
			if (!(now->child.count(s[i]))) return false;
			now = now->child[s[i]];			
		}
		return now->final;
	}
};

int main () {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	trie t;
	for (;;) {
		string s; cin >> s;
		if (s == "*") break;
		t.insert(s);		
	}
	t.print();
	for (;;) {
		string s; cin >> s;
		if (s == "*") break;
		cerr << t.find(s) << endl;		
	}
    

  return 0;

}


