struct fenwick {
	vt op;
	tint siz;

	// arbol para el intervalo (0,n)
	fenwick(tint n) {
		op = vt(n,0);
		siz = 0;
	}

	tint leq(tint key) {
		tint res = 0;
		for (tint i = key; i > 0; i -= i & (-i)) res += op[i];
		return res;
	}

	tint eq(tint key) {
		return leq(key) - leq(key-1);
	}

	void insert(tint key, tint ncopies = 1) {
		for (tint i = key; i < si(op); i += i & (-i)) op[i] += ncopies;
		siz += ncopies;
	}

	tint size() { return siz; }

	tint nth(tint pos) {
		if (pos < 1 || pos > siz) return -1;
		tint res = 0, mask = 1LL << (31 - __builtin_clz(si(op))), p = pos;
		while (mask) {
			if (op[res| mask] < p) {
				res |= mask;
				p -= op[res];
			}
			mask >>= 1;
		}
		return res + 1;
	}
};
