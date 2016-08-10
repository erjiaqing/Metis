#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 55;
int n, m, f[N][N][N][N];
char mp[N][N];
bool g[N][N][N][N];
vector<pair<int, int> > Q[30];

int max4(int a, int b, int c, int d) {
	return max(max(a, b), max(c, d));
}

int main() {
	while (true) {
		scanf("%d%d", &n, &m);
		if (n + m == 0) break;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) { 
				cin >> mp[i][j];
				if (mp[i][j] >= 'a' && mp[i][j] <= 'z')
					Q[mp[i][j] - 'a' + 1].push_back(make_pair(i, j));
			} 
		
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (mp[i][j] == '#') continue;
				g[i][j][i][j] = 1;
				for (int x = i; x <= n; x++)
					for (int y = j; y <= m; y++) {
						if (mp[x][y] == '#') continue;
						if (x > i) g[i][j][x][y] |= g[i][j][x - 1][y];
						if (y > j) g[i][j][x][y] |= g[i][j][x][y - 1];
					}
			}
		if (!g[1][1][n][m]) {
			puts("-1");
			continue;
		}
		
		memset(f, 0, sizeof(f));
		for (int h = 1; h <= n + m - 2; h++) {
			for (int i = 0; i <= h; i++) {
				int j = h - i;
				for (int x = 1; x <= n - i; x++)
					for (int y = 1; y <= m - j; y++) {
						int p = x + i, q = y + j;
						if (!g[x][y][p][q]) continue;
						f[x][y][p][q] = max4(f[x + 1][y][p][q], f[x][y + 1][p][q], f[x][y][p - 1][q], f[x][y][p][q - 1]);
						if (mp[x][y] >= 'a' && mp[x][y] <= 'z' && mp[x][y] - mp[p][q] == 32)
							f[x][y][p][q] = max(f[x][y][p][q], max4(f[x + 1][y][p - 1][q], f[x + 1][y][p][q - 1], f[x][y + 1][p - 1][q], f[x][y + 1][p][q - 1]) + 1);
						if (mp[p][q] >= 'A' && mp[p][q] <= 'Z') {
							int tmp = mp[p][q] - 'A' + 1;
							for (int k = 0; k < (int)Q[tmp].size(); k++) {
								int u = Q[tmp][k].first, v = Q[tmp][k].second;
								if (g[x][y][u][v] && g[u][v][p][q])
									f[x][y][p][q] = max(f[x][y][p][q], f[x][y][u][v] + f[u][v][p][q]);
							}
						}
						//printf("%d %d %d %d %d\n", x, y, p, q, f[x][y][p][q]);
					}
			}
		}
		
		printf("%d\n", f[1][1][n][m]);
	}
	return 0;
}
