#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, sum, ans, a[50];

int main() {
	int T; scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		printf("Case #%d: ", cs);
		scanf("%d", &n);
		sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			sum += a[i];
		}
		ans = sum / 2;
		if (ans <= 1) {
			printf("%d\n", ans);
			continue;
		}
		sort(a + 1, a + n + 1);
		
		if (a[n] >= ans / 2) {
			int t = ans - ans / 2;
			if (sum - a[n] < t)
				if ((sum - a[n]) * 2 + 1 < ans)
					ans = (sum - a[n]) * 2 + 1;
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
