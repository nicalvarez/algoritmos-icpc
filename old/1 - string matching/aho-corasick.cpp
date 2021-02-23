struct node {
	int id;	char c; bool isfinal;
	node *parent, *pre, *pfinal;
	map<char,node*> child;

	node(node* parent = NULL, char c = ' ') {
		this->c = c; this->parent = parent;
		pre = pfinal = NULL;
		id = -1; isfinal = false;
	}
	void insert(const string& s, int id = -1) {
		int n = si(s);
		node* act = this;
		forn(i,n)
			if (act->child.count(s[i])) act = act->child[s[i]];
			else act = act->child[s[i]] = new node(act,s[i]);
		act->isfinal = true; act->id = id;
	}
	void clear() {
		forall(it,child) it->second->clear();
		child.clear(); c = ' '; parent = pre = pfinal = NULL;
	}
};

vs pat;
node *root;
void precompute() {
	root = new node();
	int np = si(pat);
	forn(i,np) root->insert(pat[i], i);

	queue<node*> q; forall(it,root->child) q.push(it->second);
	while (!q.empty()) {
		node *u = q.front(); q.pop();
		node *p = u->parent->pre; char c = u->c;
		while (p && !p->child.count(c)) p = p->pre;
		if (p == NULL) u->pre = root;
		else u->pre = p->child[c];

		if (u->pre->isfinal) u->pfinal = u->pre;
		else u->pfinal = u->pre->pfinal;
		forall(it,u->child) q.push(it->second);
	}
}

vvi match(const string& s) {
	int n = si(s), np = si(pat);
	vvi res(np);
	node* act = root;
	forn(i,n) {
		while (act && !act->child.count(s[i])) act = act->pre;
		if (act == NULL) act = root;
		else {
			act = act->child[s[i]];
			node *fin = act;
			while (fin && fin->isfinal) {
				int id = fin->id;
				res[id].pb(i-si(pat[id])+1);
				fin = fin->pfinal;
			}
		}
	}
	return res;
}
