// (1-base) next[i] = lcp(text[1..n], text[i..n]), text[1..next[i]] = text[i..(i + next[i] - 1)]
void build(char *pattern) {
	int len = strlen(pattern + 1);
	int j = 1, k = 2;
	for (; j + 1 <= len && pattern[j] == pattern[j + 1]; j++);
	next[1] = len;
	next[2] = j - 1;
	for (int i = 3; i <= len; i++) {
		int far = k + next[k] - 1;
		if (next[i - k + 1] < far - i + 1) {
			next[i] = next[i - k + 1];
		}
		else {
			j = max(far - i + 1, 0);
			for (; i + j <= len && pattern[1 + j] == pattern[i + j]; j++);
			next[i] = j;
			k = i;
		}
	}
}
void solve(char *text, char *pattern) {
	int len = strlen(text + 1);
	int lenp = strlen(pattern + 1);
	int j = 1, k = 1;
	for (; j <= len && j <= lenp && pattern[j] == text[j]; j++);
	extend[1] = j - 1;
	for (int i = 2; i <= len; i++) {
		int far = k + extend[k] - 1;
		if (next[i - k + 1] < far - i + 1) {
			extend[i] = next[i - k + 1];
		}
		else {
			j = max(far - i + 1, 0);
			for (; i + j <= len && 1 + j <= lenp && pattern[1 + j] == text[i + j]; j++);
			extend[i] = j;
			k = i;
		}
	}
}
