#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;
const int M = 1e9 + 7;

int n, m, a[N], b[N], f[N][N];

int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= m; i++)
			scanf("%d", &b[i]);
		
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; i++) f[i][0] = 1;
		for (int i = 1; i <= m; i++) f[0][i] = 1;
		f[0][0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (a[i] == b[j]) f[i][j] = (f[i][j] + f[i - 1][j - 1]) % M;
				//printf("%d %d %d\n", i, j, f[i][j]);
				f[i][j] = (f[i][j] + f[i - 1][j]) % M;
				//printf("%d %d %d\n", i, j, f[i][j]);
				f[i][j] = (f[i][j] + f[i][j - 1]) % M;
				//printf("%d %d %d\n", i, j, f[i][j]);
				f[i][j] = (f[i][j] - f[i - 1][j - 1] + M) % M;
				//printf("%d %d %d\n", i, j, f[i][j]);
			}
		printf("%d\n", (f[n][m] - 1 + M) % M);
	}
	return 0;
}
