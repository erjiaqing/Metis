#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

const int N = 30;
const int M = 1 << 21;
int n, m, a[N][N], h[N];
bool vis[M], ans[N];
queue<int> Q;

void solve() {
	while (!Q.empty()) Q.pop();
	Q.push(m);
	memset(vis, 0, sizeof(vis));
	vis[m] = 1;
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		int t = 0;
		for (int i = 0; i < n; i++)
			if (x & (1 << i)) h[++t] = i + 1;
		if (t == 1) {
			ans[h[1]] = 1;
			continue;
		}
		
		for (int i = 1; i <= t; i++) {
			int sum = 0;
			for (int j = 1; j <= t; j++) {
				sum += a[h[i]][h[j]];
			}
			if (sum > 0) {
				int tmp = x ^ (1 << (h[i] - 1));
				if (!vis[tmp]) {
					Q.push(tmp);
					vis[tmp] = 1;
				}
			}
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);
		m = (1 << n) - 1;
				
		memset(ans, 0, sizeof(ans));
		solve();
		int lst = 0;
		for (int i = 1; i <= n; i++)
			if (ans[i]) lst = i;
		if (lst == 0) printf("0\n");
		else {
			for (int i = 1; i <= n; i++)
				if (ans[i]) printf("%d%c", i, " \n"[i == lst]);
		}
	}
	return 0;
}
