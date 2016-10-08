#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
struct Tree {
	int l, r, L, R, x;
} h[(int)3e6];
int n, m, q, a[N], b[N];
int root[N], tot;

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
	h[x].x = h[y].x + 1; //-------------------
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

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + m + 1, a[i]) - (b + 1) + 1;
	
	root[0] = tot = 1;
	Build(1, 1, m); //------------------ 
	for (int i = 1; i <= n; i++) {
		root[i] = ++tot;
		build(tot, root[i - 1], a[i]);
	}
	
	for(int i = 1; i <= q; i++) {
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", b[find(root[l - 1], root[r], k)]);
	}
	return 0;
}
