#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
const int M = 1000005;

int n, m, a[N], d[N], p[N];
int tot, id[M], lst[N], nxt[M];
int Q[N];
bool mark[N];

void Add(int x, int y) {
	id[++tot] = y; nxt[tot] = lst[x]; lst[x] = tot;
}

int bfs(int cur, int d[]) {
	int l = 1, r = 0;
	memset(mark, 0, sizeof(mark));
	for (int i = 1; i <= n; i++)
		if (d[i] == 0) Q[++r] = i;
	
	int cnt = 0;
	while (l <= r) {
		int now = l;
		while (now <= r) {
			int x = Q[now];
			if (mark[x]) {
				now++, l++;
				continue;
			}
			if (a[x] == cur) {
				if (now == l) l++;
				mark[x] = 1;
				for (int i = lst[x]; i; i = nxt[i]) {
					int y = id[i];
					d[y]--;
					if (d[y] == 0) Q[++r] = y;
				}
			}
			now++;
		}
		cur = 3 - cur;
		cnt++;
	}
	
	return cnt - 1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		tot = 0; memset(lst, 0, sizeof(lst));
		memset(d, 0, sizeof(d));
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			Add(x, y);
			d[y]++;
		}
		for (int i = 1; i <= n; i++)
			p[i] = d[i];
		
		int ans = bfs(1, d);
		ans = min(ans, bfs(2, p));
		printf("%d\n", ans);
	}
	return 0;
}
