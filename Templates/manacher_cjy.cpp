// manacher
// 0-base
// odd s[i] len[i*2]
// even s[i],s[i+1] len[i*2+1]
void manacher(char *s) {
	int l = strlen(s);
	len[0] = 1;
	for (int i = 1, j = 0; i < n * 2 - 1; ++i) {
		int p = i / 2, q = i - p;
		int mx = (j + 1) / 2 + len[j] - 1;
		len[i] = mx < q ? 0 : min(mx - q + 1, len[j * 2 - i]);
		while (p - len[i] >= 0 && q + len[i] < l && s[p - len[i]] == s[q + len[i]]) len[i]++;
		if (q + len[i] - 1 > mx) mx = q + len[i] - 1;
	}
}
// 1-base
// only even s[i],s[i+1] len[i]
void manacher(char *s) {
	int l = strlen(s + 1);
	int mx = 0, id;
	for (int i = 1; i <= l; ++i) {
		if (mx >= i) len[i] = min(mx - i, len[id * 2 - i]); else len[i] = 0;
		for (; s[i - len[i]] == s[i + len[i] + 1]; len[i]++);
		if (i + len[i] > mx) mx = len[i] + i, id = i;
	}
}
