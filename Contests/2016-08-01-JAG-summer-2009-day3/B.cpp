#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;
int n, m, s[N], t[N], f[N][N];

int main()
{
	while (true)
	{
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++)
			scanf("%d", &t[i]);
		for (int i = n + 1; i <= 100; i++)
			t[i] = t[i - n];
		scanf("%d", &m);
		for (int i = 1; i <= 100; i++)
			s[i] = 23;
		for (int i = 1; i <= m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			s[x] = min(s[x], y);
		}
		for (int i = 1; i <= 100; i++)
			for (int j = 1; j <= 100; j++)
				f[i][j] = 1000;
		f[1][1] = 0;
		for (int i = 2; i <= 100; i++)
			for (int j = 1; j < i; j++)
			{
				f[i][1] = min(f[i][1], f[i - 1][j] + 1);
				if (s[i] >= t[j + 1])
					f[i][j + 1] = min(f[i][j + 1], f[i - 1][j]);
			}
		int ans = 1000;
		for (int i = 1; i <= 100; i++)
			ans = min(ans, f[100][i]);
		printf("%d\n", ans);
	}
	return 0;
}
