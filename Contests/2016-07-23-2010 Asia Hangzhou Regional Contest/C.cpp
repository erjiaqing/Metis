#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define fi first
#define se second

const int N = 1005;
int n, m, ans;
pair<int, pair<int, int> > a[N];
int tmp[3], f[3][N][2];
bool g[N];
vector<int> vis[N];

int Id(char ch)
{
	if (ch == 'X') return 0;
	if (ch == 'Y') return 1;
	return 2;
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
		{
			char c1, c2, c;
			int p, q;
			getchar();
			scanf("%c%c%d%c%c%c%d", &c1, &c, &p, &c, &c2, &c, &q);
			tmp[0] = tmp[1] = tmp[2] = 0;
			tmp[Id(c1)] = p; tmp[Id(c2)] = q;
			a[i] = make_pair(tmp[0], make_pair(tmp[1], tmp[2]));
			//printf(".%c.%d.%c.%d.\n", c1, p, c2, q);
		}
		sort(a + 1, a + m + 1);
		ans = 0;
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; i++) vis[i].clear();
		for (int i = 1; i <= m; i++)
		{
			if (a[i] == a[i - 1]) continue;
			int p, q, t1, t2;
			int x, y, z;
			x = a[i].fi;
			y = a[i].se.fi;
			z = a[i].se.se;
			if (x < 0 || x > n || y < 0 || y > n || z < 0 || z > n) continue;
			if (x == 0) t1 = 1, t2 = 2, p = y, q = z;
			else if (y == 0) t1 = 2, t2 = 0, p = z, q = x;
			else if (z == 0) t1 = 0, t2 = 1, p = x, q = y;
			if (p == 0 || q == 0) continue;
			ans += n;
			f[t1][p][0]++; f[t2][q][1]++;
			if (x == 0) vis[y].push_back(z);
			if (a[i].fi != a[i - 1].fi) memset(g, 0, sizeof(g));
			if (y == 0) g[z] = 1;
			if (z == 0)
			{
				for (int j = 0; j < (int)vis[y].size(); j++)
					ans += g[vis[y][j]];
			}
		}
		for (int i = 0 ; i < 3; i++)
			for (int j = 1; j <= n; j++)
				ans -= f[i][j][0] * f[i][j][1];
		printf("%d\n", ans);
	}
	return 0;
}
