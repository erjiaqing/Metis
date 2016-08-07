#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int M = 1e9 + 7;
int n, xx, x, m, a[50], nn, ans;

int ff(long long x, int k) {
	long long res = 1;
	for (; k; k >>= 1) {
		if ((k & 1) == 1) res = res * x % M;
		x = x * x % M;
	}
	return (int)res;
}

int get_sum(int n) {
	long long res = 0;
	res += 6LL * ff(n, 5);
	res %= M;
	res += 15LL * ff(n, 4);
	res %= M;
	res += 10LL * ff(n, 3);
	res %= M;
	res = (res - n + M) % M;
	res *= xx;
	res %= M;
	return (int)res;
}

int main() {
	int T; scanf("%d", &T);
	xx = ff(30, M - 2);
	while (T--) {
		scanf("%d", &n);
		x = n;
		m = 0;
		for (int i = 2; i * i <= n; i++) {
			if (n % i == 0) {
				a[++m] = i;
				while (n % i == 0)
					n /= i;
			}
		}
		if (n > 1) a[++m] = n;
		//cerr<<m<<endl;
		nn = 1 << m; ans = 0;
		for (int h = 0; h < nn; h++) {
			int t = 1, k = 1, tmp = h;
			for (int i = 1; i <= m; i++, tmp >>= 1)
				if ((tmp & 1) == 1) t *= a[i], k *= -1;
			int now = 1LL * ff(t, 4) * get_sum(x / t) % M;
			ans = ((ans + now * k) % M + M) % M;
			//printf("%d %d %d\n", ans, t, k);
		}
		printf("%d\n", ans);
	}
	return 0;
}
