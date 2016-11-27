inline long long solve(int n, long long p) {
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			a[i][j] %= p;
	long long ans(1);
	long long sgn(1);
	for(int i = 1; i <= n; ++i) {
		for(int j = i + 1; j <= n; ++j) {
			while(a[j][i]) {
				long long t = a[i][i] / a[j][i];	
				for(int k = 1; k <= n; ++k) {
					a[i][k] = (a[i][k] - t * a[j][k]) % p;
					swap(a[i][k], a[j][k]);
				}
				sgn = -sgn;
			}
		}
		if(a[i][i] == 0)
			return 0;
		ans = ans * a[i][i] % p;
	}
	ans = ans * sgn;
	return (ans % p + p) % p;
}