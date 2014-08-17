#define forn(i,n) for(int i=0;i<(int)(n);i++) 
#define si(c) ((int)(c).size()) 

typedef vector<int> vi; 

vi pre; 
void precompute(const string& pat) { 
	int m = si(pat), p = -1; pre = vi(m+1); pre[0] = -1; 
	forsn(i,1,m+1) { 
		while (p != -1 && pat[p] != pat[i-1]) p = pre[p]; 
		p++; pre[i] = p; 
	}
}

vi match(const string& s, const string& pat) { 
	vi res; int n = si(s), m = si(pat), p = 0; 
	forn(i,n) { 
		while (p != -1 && pat[p] != s[i]) p = pre[p]; 
		p++; if (p == m) { 
			res.pb(i-m+1); 
			p = pre[p]; 
		} 
	} 
	return res; 
}
