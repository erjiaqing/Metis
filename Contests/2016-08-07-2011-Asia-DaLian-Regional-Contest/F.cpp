#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const int N = 50005;

int n, m, q, cnt[N], maxn, pos[N];
char tp[N];
int xc[N], yc[N], r[N], l[N], w[N], c[N];

struct Tree {
	int l, r, t;
} a[N * 4];

void build(int x, int l, int r) {
	a[x].l = l; a[x].r = r;
	a[x].t = 0;
	if (l == r) {
		pos[l] = x;
		if (x > maxn) maxn = x;
		return ;
	}
	int m = (l + r) / 2;
	build(x * 2, l, m);
	build(x * 2 + 1, m + 1, r);
}

void init() {
	for (int i = 1; i <= maxn; i++)
		a[i].t = 0;
}

int get_clr(int x) {
	int mx = 0;
	x = pos[x];
	while (x) {
		if (a[x].t > mx) mx = a[x].t;
		x /= 2;
	}
	return c[mx];
}

void modify(int x, int l, int r, int k) {
//printf("%d %d %d %d ... %d\n", l, r, a[x].l, a[x].r, x);
	if (a[x].l == l && a[x].r == r) {
		a[x].t = k;
		return ;
	}
	
	if (a[x].t != 0) {
		a[x * 2].t = a[x].t;
		a[x * 2 + 1].t = a[x].t;
		a[x].t = 0;
	}
	
	int m = (a[x].l + a[x].r) / 2;
	if (r <= m) modify(x * 2, l, r, k);
	else if (l >= m + 1) modify(x * 2 + 1, l, r, k);
	else {
		modify(x * 2, l, m, k);
		modify(x * 2 + 1, m + 1, r, k);
	}
}

void work(int l, int r, int c) {
	if (l < 0) l = 0;
	if (r >= m) r = m - 1;
	if (l > r) return ;
	//printf("%d %d %d\n", l, r, c);
	modify(1, l, r, c);
}

int main() {
	while (scanf("%d%d%d", &n, &m, &q) == 3) {
		for (int i = 1; i <= q; i++) {
			char s[15];
			scanf("%s", s);
			tp[i] = s[0];
			if (s[0] == 'C' || s[0] == 'D') scanf("%d%d%d%d", &xc[i], &yc[i], &r[i], &c[i]);
			else if (s[0] == 'R') scanf("%d%d%d%d%d", &xc[i], &yc[i], &l[i], &w[i], &c[i]);
			else scanf("%d%d%d%d", &xc[i], &yc[i], &w[i], &c[i]);
		}
		
		memset(cnt, 0, sizeof(cnt));
		maxn = 0; build(1, 0, m - 1);
		for (int x = 0; x < n; x++) {
			init();
			for (int i = 1; i <= q; i++) {
				if (tp[i] == 'C') {
					int k = r[i] * r[i] - (xc[i] - x)  * (xc[i] - x);
					if (k < 0) continue;
					int t = (int)sqrt(k);
					if ((t + 1) * (t + 1) <= k) t++;
					work(yc[i] - t, yc[i] + t, i);
				}
				else if (tp[i] == 'D') {
					int t = r[i] - abs(x - xc[i]);
					if (t < 0) continue;
					work(yc[i] - t, yc[i] + t, i);
				}
				else if (tp[i] == 'R') {
					if (x < xc[i] || x > xc[i] + l[i] - 1) continue;
					work(yc[i], yc[i] + w[i] - 1, i);
				}
				else {
					if (x < xc[i] || x > xc[i] + w[i] / 2) continue;
					int t = w[i] / 2 - (x - xc[i]);
					work(yc[i] - t, yc[i] + t, i);
				}
			}
			//printf("%d\n", x);
			
			for (int y = 0; y < m; y++)
				cnt[get_clr(y)]++;
		}
		
		for (int i = 1; i <= 9; i++)
			printf("%d%c", cnt[i], " \n"[i == 9]);
	}
	return 0;
}
