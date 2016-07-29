#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10005;
int n;
long long cir = 0, a[N], b[N];

long long extended_Euclid(long long a, long long b, long long &x, long long &y) {
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

long long China_Remainder(long long a[], long long b[], int n, long long &cir) { //a[]存放余数  b[]存放两两互质的除数
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

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &a[i], &b[i]);
		printf("%lld\n", China_Remainder(a, b, n, cir));
	}
	return 0;
}
