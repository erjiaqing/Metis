#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;

int n, m, t, a[N], b[N], d[N], ans;
long long k;
int c[N];
int tot, id[N], nxt[N], lst[N];

void Add(int x, int y) {
	id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot;
}

int get_cnt(int x) {
	int res = 0;
	for (; x; x -= x & (-x))
		res += c[x];
	return res;
}

void Modify(int x, int k) {
	for (; x <= m; x += x & (-x))
		c[x] += k;
}

void solve(int x) {
	long long t = k / b[a[x]];
	int pos;
	if (t > b[m]) pos = m;
	else {
		pos = lower_bound(b + 1, b + m + 1, t) - b;
		if (b[pos] > t) pos--;
	}
	ans += get_cnt(pos);
	
	Modify(a[x], 1);
	
	for (int i = lst[x]; i; i = nxt[i])
		solve(id[i]);
	
	Modify(a[x], -1);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%I64d", &n, &k);//------------
		tot = 0; memset(lst, 0, sizeof(lst));
		memset(d, 0, sizeof(d));
		
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(b + 1, b + n + 1);
		m = unique(b + 1, b + n + 1) - (b + 1);
		for (int i = 1; i <= n; i++)
			a[i] = lower_bound(b + 1, b + m + 1, a[i]) - (b + 1) + 1;
		
		for (int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			Add(x, y);
			d[y]++;
		}
		
		for (int i = 1; i <= n; i++)
			if (d[i] == 0) {
				t = i;
				break;
			}
			
		ans = 0;
		memset(c, 0, sizeof(c));
		solve(t);
		printf("%d\n", ans);
	}
	return 0;
}
