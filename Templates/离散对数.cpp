struct hash_table {
	static const int Mn = 100003;
	int hd[Mn], key[Mn], val[Mn], nxt[Mn], tot;
	hash_table() : tot(0) {
		memset(hd, -1, sizeof hd);
	}
	void clear() {
		memset(hd, -1, sizeof hd);
		tot = 0;
	}
	int &operator[] (const int &cur) {
		int pos = cur % Mn;
		for(int i = hd[pos]; ~i; i = nxt[i]) {
			if(key[i] == cur) {
				return val[i];
			}
		}
		nxt[tot] = hd[pos];
		hd[pos] = tot;
		key[tot] = cur;
		return val[tot++];
	} 
	bool find(const int &cur) {
		int pos = cur % Mn;
		for(int i = hd[pos]; ~i; i = nxt[i]) {
			if(key[i] == cur)
				return true;
		}
		return false;
	}
};
// base ^ res = n % mod
inline int discrete_log(int base, int n, int mod) {
	int size = int(sqrt(mod)) + 1;
	hash_table hsh;
	int val = 1;
	for (int i = 0; i < size; ++i) {
		if(hsh.find(val) == 0)
			hsh[val] = i;
		val = (long long) val * base % mod;
	}
	int inv = inverse(val, mod);
	val = 1;
	for(int i = 0; i < size; ++i) {
		if(hsh.find((long long) val * n % mod))
			return i * size + hsh[(long long)val * n % mod];
		val = (long long) inv * val % mod;
	}
	return -1;
}