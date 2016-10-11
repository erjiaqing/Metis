long long extended_Euclid(long long a, long long b, long long &x, long long &y) { //return gcd(a, b) 
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	else {
		long long tmp = extended_Euclid(b, a % b, x, y);
		long long t = x;
		x = y;
		y = t - a / b * y;
		return tmp;
	}
}
long long China_Remainder(long long a[], long long b[], int n, long long &cir) { //a[]存放两两互质的除数  b[]存放余数
	long long x, y, ans;
	ans = 0; cir = 1;
	for (int i = 1; i <= n; i++) cir *= a[i];
	for (int i = 1; i <= n; i++) {
		long long tmp = cir / a[i];
		extended_Euclid(a[i], tmp, x, y);
		ans = (ans + y * tmp * b[i]) % cir; //可能会爆long long  用快速乘法
	}
	return (cir + ans % cir) % cir;
}
bool merge(long long &a1, long long &b1, long long a2, long long b2) { //num = b1(mod a1), num = b2(mod a2)
	long long x, y;
	long long d = extended_Euclid(a1, a2, x, y);
	long long c = b2 - b1;
	if (c % d) return false;
	long long p = a2 / d;
	x = (c / d * x % p + p) % p;
	b1 += a1 * x;
	a1 *= a2 / d;
	return true; 
}
long long China_Remainder2(long long a[], long long b[], int n) { //a[]存放除数(不一定两两互质)  b[]存放余数
	long long x, y, ans, cir;
	cir = a[1]; ans = b[1];
	for (int i = 2; i <= n; i++) {
		if (!merge(cir, ans, a[i], b[i])) return -1;
	}
	return (cir + ans % cir) % cir;
}