void solve(int Ql, int Qr, int El, int Er) {
	if (El == Er) {
		for (int i = Ql; i <= Qr; i++)
			Q[id[i]].ans = E[El].v;
		return;
	}
	int Em = (El + Er) >> 1;
	for (int i = El; i <= Em; i++)
		modify(1, E[i].a, E[i].b, 1);
	int Qm = Ql - 1;
	for (int i = Ql; i <= Qr; i++) {
		int t = id[i];
		long long k = getcnt(1, Q[t].x, Q[t].y);
		if (k >= Q[t].k) swap(id[++Qm], id[i]);
		else Q[t].k -= k;
	}
	for (int i = El; i <= Em; i++)
		modify(1, E[i].a, E[i].b, -1);
	if (Ql <= Qm) solve(Ql, Qm, El, Em);
	if (Qm + 1 <= Qr) solve(Qm + 1, Qr, Em + 1, Er);
}
