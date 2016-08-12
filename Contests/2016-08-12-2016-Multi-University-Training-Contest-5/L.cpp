#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 50005;
int n, m, a[N], b[N];
int c[N];
long long ls[N], lb[N], rs[N], rb[N];
long long sum1, sum2, ans;

void Add(int x) {
	for (; x <= m; x += x & (-x))
		c[x]++;
}

int get(int x) {
	int res = 0;
	for (; x; x -= x & (-x))
		res += c[x];
	return res;
}

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(b + 1, b + n + 1);
		m = unique(b + 1, b + n + 1) - (b + 1);
		for (int i = 1; i <= n; i++)
			a[i] = lower_bound(b + 1, b + m + 1, a[i]) - (b + 1) + 1;
		
		sum1 = sum2 = 0;
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; i++) {
			ls[i] = get(a[i] - 1);
			lb[i] = i - 1 - get(a[i]);
			sum1 += lb[i];
			Add(a[i]);
		}
		memset(c, 0, sizeof(c));
		for (int i = n; i >= 1; i--) {
			rs[i] = get(a[i] - 1);
			rb[i] = n - i - get(a[i]);
			sum2 += rb[i];
			Add(a[i]);
		}
		/*for (int i = 1; i <= n; i++) printf("%d ", rs[i]); puts("");
		for (int i = 1; i <= n; i++) printf("%d ", rb[i]); puts("");
		for (int i = 1; i <= n; i++) printf("%d ", lb[i]); puts("");
		for (int i = 1; i <= n; i++) printf("%d ", ls[i]); puts("");*/
		
		ans = sum1 * sum2;// cout<<ans<<endl;
		for (int i = 1; i <= n; i++)
			ans = ans - ls[i] * rs[i] - lb[i] * rb[i] - lb[i] * ls[i] - rs[i] * rb[i];
		cout << ans << endl;
	}
	return 0;
}
