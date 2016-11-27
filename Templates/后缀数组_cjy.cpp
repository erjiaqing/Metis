void calsa(int n, int m) {
	for (int i = 1; i <= n; i++) Rank[i] = num[i];
	for (int i = 1; i <= m; i++) c[i] = 0;
	for (int i = 1; i <= n; i++) c[Rank[i]]++;
	for (int i = 2; i <= m; i++) c[i] += c[i - 1];
	for (int i = n; i >= 1; i--) sa[c[Rank[i]]--] = i;
	for (int k = 1; k < n; k <<= 1) {
		int t = 0, j = n - k + 1;
		for (int i = j; i <= n; i++) sb[++t] = i;
		for (int i = 1; i <= n; i++) if (sa[i] > k) sb[++t] = sa[i] - k;
		for (int i = 1; i <= m; i++) c[i] = 0;
		for (int i = 1; i <= n; i++) c[Rank[i]]++;
		for (int i = 2; i <= m; i++) c[i] += c[i - 1];
		for (int i = n; i >= 1; i--) sa[c[Rank[sb[i]]]--] = sb[i];
		a[sa[1]] = t = 1;
		for (int i = 2; i <= n; i++)
			if (Rank[sa[i]] == Rank[sa[i - 1]] && Rank[sa[i] + k] == Rank[sa[i - 1] + k])
				a[sa[i]] = t; else a[sa[i]] = ++t;
		for (int i = 1; i <= n; i++) Rank[i] = a[i];
		if (t == n) break; m = t;
	}
}
void calheight(int n) {
	int t = 0;
	for (int i = 1; i <= n; i++) {
		if (Rank[i] == 1) height[1] = t = 0;
		else {
			if (t > 0) t--;
			int j = sa[Rank[i] - 1];
			while (i + t <= n && j + t <= n && num[i + t] == num[j + t]) t++;
			height[Rank[i]] = t;
		}
	}
}
