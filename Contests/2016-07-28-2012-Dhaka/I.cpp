#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n, m, x[100], y[100];
int f[55][55][2505];
vector<int> a[55][55];

int main() {
	int T, cases = 0; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &x[i], &y[i]);
		}
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				if (x[i] * y[j] > y[i] * x[j]) {
					int t;
					t = x[i]; x[i] = x[j]; x[j] = t;
					t = y[i]; y[i] = y[j]; y[j] = t;
				}
				
		/*memset(f, 0, sizeof(f));
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= k; j++) {
				int add = f[i - 1][j - 1] * x[i] * 2 + x[i] * y[i];
				if (s[i - 1][j - 1] + add> s[i - 1][j]) {
					s[i][j] = s[i - 1][j - 1] + add;
					f[i][j] = f[i - 1][j - 1] + y[i];
				}
				else {
					s[i][j] = s[i - 1][j];
					f[i][j] = f[i - 1][j];
				}
			}
		}*/
		memset(f, 0, sizeof(f));
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
				a[i][j].clear();
		a[0][0].push_back(0);
		for (int i = 1; i <= n; i++)
			for (int j = 0; j <= m; j++)
			{
				if (j > 0)
				{
					for (int h = 0; h < (int)a[i - 1][j - 1].size(); h++)
					{
						int k = a[i - 1][j - 1][h];
						int add = k * x[i] * 2 + x[i] * y[i];
						if (f[i][j][k + y[i]] == 0) a[i][j].push_back(k + y[i]);
						f[i][j][k + y[i]] = max(f[i][j][k + y[i]], f[i - 1][j - 1][k] + add);
					}
				}
				for (int h = 0; h < (int)a[i - 1][j].size(); h++)
				{
					int k = a[i - 1][j][h];
					if (f[i][j][k] == 0) a[i][j].push_back(k);
					f[i][j][k] = max(f[i][j][k], f[i - 1][j][k]);
				}
			}
		int ans = 0;
		for (int i = 0; i <= 2500; i++)
			ans = max(ans, f[n][m][i]);
		cases++;
		printf("Case %d: %d\n", cases, ans);
	}
	return 0;
}
