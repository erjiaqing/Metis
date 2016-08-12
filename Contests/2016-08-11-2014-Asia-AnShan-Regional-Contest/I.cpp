#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int n, t, x, y, tt, xx, yy;
double ans;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		ans = 0.0;
		scanf("%d%d%d", &t, &x, &y);
		for (int i = 2; i <= n; i++) {
			scanf("%d%d%d", &tt, &xx, &yy);
			double tmp = sqrt(1.0 * (xx - x) * (xx - x) + 1.0 * (yy - y) * (yy - y)) / (double)(tt - t);
			if (tmp > ans) ans = tmp;
			t = tt; x = xx; y = yy;
		}
		printf("%.10f\n", ans);
	}
	return 0;
}
