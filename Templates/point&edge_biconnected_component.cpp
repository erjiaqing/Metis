// primitive root
// pr[1..tot] 存质数
int t[Mn],len;
inline bool judge(int cur,int x) {
	int k = x - 1;
	for(int i = 1; i <= len; ++i) {
		if(powmod(cur, k / t[i], x) == 1) {
			return false;
		}
	}
	return true;
}
inline int primitive_root(int p) {
	len = 0;
	int tmp = p - 1;
	for(int i = 1; i <= tot; ++i) {
		if(tmp % pr[i] == 0) {
			t[++len] = pr[i];
		}		
		while(tmp % pr[i] == 0)
			tmp /= pr[i];
	}
	if(tmp != 1)
		t[++len] = tmp;
	for(int i = 2;; ++i)
		if(judge(i, p)) {
			return i;
		}
}