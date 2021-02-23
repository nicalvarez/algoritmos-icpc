vi succ,pred;
vb used;
int go(vvi &e, int m) {
  int n = si(e);
  succ = vi(n,-1); pred = vi(n,-1);
  used = vb(n,false);
  for (;;) {
    vi s(n,0),t(m,0);
    queue<int> q[2];
    forn(i,n)
      if (succ[i]<0) {
        s[i] = 1;
        q[0].push(i);
      }
      else
        pred[succ[i]] = i;

    int act = 0;
    bool stop = true;
    while(!q[act].empty()) {
      while(!q[act].empty()) {
        int u = q[act].front();
        q[act].pop();
        forall(it,e[u]) {
          if (!t[*it]) {
            t[*it] = 1;
            if (!used[*it])
              stop = false;
            else {
              s[pred[*it]] = 1;
              q[!act].push(pred[*it]);
            }
            pred[*it] = u;
          }
        }
      }
      if (!stop) {
        forn(i,m) if (t[i] && !used[i]) {
            int v = i;
            while(v>=0 && (succ[pred[v]]<0 || pred[v]!=pred[succ[pred[v]]])) {
              used[v] = 1;
              t[v] = 0;
              int nextv = succ[pred[v]];
              succ[pred[v]] = v;
              v = nextv;
            }
            if (v>=0)
              used[v] = 0;
          }
        break;
      }
      act = !act;
    }
    if (stop)
      break;
  }
  int cnt = 0;
  forn(i,n) if (succ[i]>=0)  cnt++;
  return cnt;
}
