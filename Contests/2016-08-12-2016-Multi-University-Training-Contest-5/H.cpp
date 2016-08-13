#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 100005;
const int M = 100000;
int n, a[N], mid[N], d[N];
int m, ind[N], pos[N], lst[N];
vector<int> E[N];
long long ans, sum, c[N];

struct Tree {
	int l, r, L, R, x;
} h[(int)3e6];
int tot, root[N];

void Build(int x, int l, int r) {
	h[x].l = l; h[x].r = r; h[x].x = 0;
	if (l < r) {
		int m = (l + r) / 2;
		h[x].L = ++tot; Build(tot, l, m);
		h[x].R = ++tot; Build(tot, m + 1, r);
	}
}

void build(int x, int y, int num) {
	int l = h[y].l, r = h[y].r;
	h[x].l = l; h[x].r = r;
	h[x].x = h[y].x + 1;
	if (l < r) {
		int m = (l + r) / 2;
		if (num <= m) {
			h[x].L = ++tot; build(tot, h[y].L, num);
			h[x].R = h[y].R;
		}
		else {
			h[x].L = h[y].L;
			h[x].R = ++tot; build(tot, h[y].R, num);
		}
		h[x].x = h[h[x].L].x + h[h[x].R].x;
	}
}

int find(int x, int y, int k) {
	if (h[x].l == h[x].r) return h[x].l;
	int t = h[h[y].L].x - h[h[x].L].x;
	if (t >= k) return find(h[x].L, h[y].L, k);
	else return find(h[x].R, h[y].R, k - t);
}

void modify(int x, long long k) {
	for (; x <= M; x += x & (-x))
		c[x] += k;
}

long long get_sum(int x) {
	long long res = 0;
	for (; x; x -= x & (-x))
		res += c[x];
	return res;
}

void dfs(int x) {
	ind[++m] = x;
	pos[x] = m;
	for (int i = 0; i < (int)E[x].size(); i++)
		dfs(E[x][i]);
	lst[x] = m;
}

void solve(int x) {
	modify(mid[x], d[x]);
	long long t = get_sum(M) - get_sum(a[x] - 1);
	if (sum + t > ans) ans = sum + t;
	
	for (int i = 0; i < (int)E[x].size(); i++)
		solve(E[x][i]);
	
	modify(mid[x], -d[x]);
}

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) E[i].clear();
		
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		
		for (int i = 2; i <= n; i++) {
			int x;
			scanf("%d", &x);
			E[x].push_back(i);
		}
		m = 0; dfs(1);
		
		root[0] = tot = 1;
		Build(1, 1, M);
		for (int i = 1; i <= n; i++) {
			root[i] = ++tot;
			build(tot, root[i - 1], a[ind[i]]);
		}
		
		sum = 0;
		for (int i = 1; i <= n; i++) {
			int size = lst[i] - pos[i] + 1;
			if (size == 1) {
				mid[i] = a[i];
				sum += mid[i];
				d[i] = M - mid[i];
				continue;
			}
			int mm = (size + 1) / 2;
			mid[i] = find(root[pos[i] - 1], root[lst[i]], mm);
			sum += mid[i];
			d[i] = find(root[pos[i] - 1], root[lst[i]], mm + 1) - mid[i];
		}
		
		ans = 0;
		memset(c, 0, sizeof(c));
		solve(1);
		cout << ans << endl;
	}
	return 0;
}
