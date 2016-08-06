#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

const int N = 10005;
int n, m;
bool a[15], vis[N];
int pre[N], num[N], ans[N];
queue<int> Q;

void bfs() {
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		for (int i = 0; i <= 9; i++)
			if (a[i]) {
				int y = (x * 10 + i) % n;
				if (!vis[y]) {
					Q.push(y);
					vis[y] = 1;
					pre[y] = x;
					num[y] = i;
				}
			}
	}
}

int main () {
	int cases = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		memset(a, 1, sizeof(a));
		for (int i = 1; i <= m; i++) {
			int x;
			scanf("%d", &x);
			a[x] = 0;
		}
		
		memset(vis, 0, sizeof(vis));
		while (!Q.empty()) Q.pop();
		for (int i = 1; i <= 9; i++) {
			int t = i % n;
			if (a[i] && !vis[t]) {
				Q.push(t);
				vis[t] = 1;
				pre[t] = -1;
				num[t] = i;
			}
		}
		bfs();
		
		cases++; printf("Case %d: ", cases);
		if (!vis[0]) {
			puts("-1");
			continue;
		}
		int p = 0, t = 0;
		while (p != -1) {
			ans[++t] = num[p];
			p = pre[p];
		}
		for (int i = t; i >= 1; i--)
			printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}
