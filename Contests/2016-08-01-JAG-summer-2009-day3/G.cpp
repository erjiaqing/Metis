#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const int inf = 1e6;
const int N = 105;
int n, s, t;
int mark[N], len[N][N], dis[N][N];
double a[N][N];

void Gauss() {
	for (int i = 1; i <= n; i++) {
		int k = i;
		for (int j = i + 1; j <= n; j++)
			if (fabs(a[j][i]) > fabs(a[k][i])) k = j;
		if (k != i)
			for (int j = i; j <= n + 1; j++)
				swap(a[i][j], a[k][j]);
		for (int j = i + 1; j <= n; j++) {
			double t =  a[j][i] / a[i][i];
			for (int h = i; h <= n + 1; h++)
				a[j][h] -= a[i][h] * t;
		}
	}
	
	for (int i = n; i >= 1; i--) {
		for (int j = i + 1; j <= n; j++)
			a[i][n + 1] -= a[i][j] * a[j][n + 1];
		a[i][n + 1] /= a[i][i];
	}
}

int main() {
	while (true) {
		scanf("%d%d%d", &n, &s, &t);
		if (n == 0) break;
		for (int i = 1; i <= n; i++)
			scanf("%d", &mark[i]);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				scanf("%d", &len[i][j]);
				dis[i][j] = len[i][j];
				if (dis[i][j] == 0) dis[i][j] = inf;
				if (i == j) dis[i][j] = 0;
			}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

		if (dis[s][t] == inf) {
			puts("impossible");
			continue;
		}
		
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++) {
			if (i == t) {
				a[i][t] = 1;
				a[i][n + 1] = 0;
				continue;
			}
			for (int j = 1; j <= n; j++) {
				if (i == j || !len[i][j]) continue;
				if (mark[i] && len[i][j] == dis[i][t] - dis[j][t] || !mark[i]) {
					a[i][n + 1] -= len[i][j];
					a[i][j] += 1;
					a[i][i] -= 1;
				}
			}
		}
		Gauss();
		printf("%.10f\n", a[s][n + 1]);
	}
	return 0;
}
