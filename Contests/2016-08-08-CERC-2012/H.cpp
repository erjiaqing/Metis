#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, ans, a[20];

int main() {
	int T; scanf("%d", &T);
	for (int i = 1; i <= 10; i++) a[i] = 400 * i * i;
	while (T--) {
		scanf("%d", &n);
		ans = 0;
		for (int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			int t = x * x + y * y;
			if (t > a[10]) {
				ans += 11;
				continue;
			}
			for (int j = 1; j <= 10; j++)
				if (t <= a[j]) {
					ans += j;
					break;
				}
		}
		
		printf("%d\n", n * 11 - ans);
	}
	return 0;
}
