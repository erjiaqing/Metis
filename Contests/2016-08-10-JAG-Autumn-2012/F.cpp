#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100;
int n, ans;
unsigned long long a[N], ansl, ansr;

unsigned long long Count(unsigned long long x, int k) {
	unsigned long long cnt;
	unsigned long long p = 1ULL << (k - 1);
	unsigned long long tmp = x / p / 2;
	cnt = tmp * p;
	x -= cnt * 2;
	x++;
	if (x > p) cnt += x - p;
	return cnt;
}

bool check(unsigned long long l, unsigned long long r) {
	if (l < 1 || r > 1e18) return 0;
	for (int i = 1; i <= n; i++)
		if (Count(r, i) - Count(l - 1, i) != a[i]) return 0;
	return 1;
}

void work(int k, unsigned long long l, unsigned long long r, unsigned long long len) {
	//cout << k << ' ' <<l<<' '<<r<<' '<<len <<endl;
	if (k == 0) {
		if (l >= 1 && r <= 1e18) {
			ansl = l, ansr = r;
			ans++;
		}
		return ;
	}
	if (len == 0) return ;
	
	unsigned long long m = (l + r) / 2;
	unsigned long long cnt = r - m;
	if (cnt < a[k] || len < a[k] || len > a[k] + cnt) return ;
	
	if (len == a[k]) work(k - 1, m + 1, r, len);
	else if (a[k] == 0) work(k - 1, l, m, len);
	else {
		unsigned long long p = m - len + a[k] + 1;
		unsigned long long q = m + a[k];
		//cout<<p<<' '<<q<<endl;
		if (check(p, q)) {
			ansl = p, ansr = q;
			//cout << ansl << ' ' << ansr - 1 << endl;
			ans++;
		}
	}
}

int main() {
	while (1) {
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		
		ans = 0; ansl = ansr = 0;
		unsigned long long len = a[1] * 2;
		unsigned long long nn = 0;
		for (int i = 0; i < n; i++) nn += 1ULL << i;
		if (len > 1) work(n, 0, nn, len - 1);
		if (len > 0) work(n, 0, nn, len);
		work(n, 0, nn, len + 1);
		//puts("////");
		if (ans == 0) puts("None");
		else if (ans == 1) cout << ansl << ' ' << ansr << endl;
		else puts("Many");
	}
	return 0;
}
