struct node {
	node *s[2],*f,*minv;
	int val,d,id;
	bool rev,col,inv;
	bool isr() { return !f||(f->s[0]!=this && f->s[1]!=this);}
	bool dir() { return f->s[1]==this;}
	void setc(node *c,int d) { s[d]=c;if (c) c->f=this;}
	void push() {
		if (rev) { swap(s[0],s[1]); rep(i,0,2) if (s[i]) s[i]->rev^=1;} rev=0;
		if (inv) { col^=1; rep(i,0,2) if (s[i]) s[i]->inv^=1; } inv=0;
	}
	void upd() {
		minv=this; val=d;
		rep(i,0,2) if (s[i]&&s[i]->val>val) val=s[i]->val,minv=s[i]->minv;

	}
}pool[N],*cur;
stack<node*> sta;
void rot(node *x) {
	node *p=x->f;bool d=x->dir();
	if (!p->isr()) p->f->setc(x,p->dir()); else x->f=p->f;
	p->setc(x->s[!d],d);x->setc(p,!d);
	p->upd();
}
void splay(node *x) {
	node *q=x;
	while (1) { sta.push(q);if (q->isr()) break; q=q->f; }
	while (!sta.empty()) sta.top()->push(),sta.pop();
	while (!x->isr()) {
		if (x->f->isr()) rot(x);
		else if (x->isr()==x->f->isr()) rot(x->f),rot(x);
		else rot(x),rot(x);
	}
	x->upd();
}
node *expose(node *x) {
	node *q=NULL;
	for (;x;x=x->f) splay(x),x->s[1]=q,(q=x)->upd();
	return q;
}
void evert(node *x) { expose(x); splay(x); x->rev^=1; x->push();}
void expose(node *x,node *y) { evert(x); expose(y); splay(x);}
void link(node *x,node *y) { evert(x); evert(y); x->setc(y,1);}
void cut(node *x,node *y) { expose(x,y); x->s[1]=y->f=NULL;}
