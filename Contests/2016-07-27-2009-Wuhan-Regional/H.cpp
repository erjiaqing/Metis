#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int inf = 10000;
struct Event {
	int i, j, s;
	Event() {}
	Event(int i, int j, int s) : i(i), j(j), s(s) {}
} ;

vector<Event> h[2];
int ans, f[2][105][15][300];
int n, m, S, a[105];

int main()
{
	int cases = 0;
	while (1)
	{
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		S = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			a[i] -= 24;
			S |= (1 << (a[i] - 1));
		}
		
		int now = 0;
		h[0].clear(); h[1].clear();
		memset(f, -1, sizeof(f));
		h[now].push_back(Event(0, 0, 0));
		f[0][0][0][0] = 0;
		for (int p = 1; p <= n; p++)
		{
			for (int k = 0; k < (int)h[now].size(); k++)
			{
				int i = h[now][k].i, j = h[now][k].j, s = h[now][k].s;
				if (a[p] == j)
				{
					if (f[now ^ 1][i][j][s] == -1)
					{
						h[now ^ 1].push_back(Event(i, j, s));
						f[now ^ 1][i][j][s] = f[now][i][j][s];
					}
					if (f[now][i][j][s] < f[now ^ 1][i][j][s])
						f[now ^ 1][i][j][s] = f[now][i][j][s];
				}
				else
				{
					int ss = s | (1 << (a[p] - 1));
					if (f[now ^ 1][i][a[p]][ss] == -1)
					{
						h[now ^ 1].push_back(Event(i, a[p], ss));
						f[now ^ 1][i][a[p]][ss] = f[now][i][j][s] + 1;
					}
					if (f[now][i][j][s] + 1 < f[now ^ 1][i][a[p]][ss])
						f[now ^ 1][i][a[p]][ss] = f[now][i][j][s] + 1;
				}
				if (i < m)
				{
					if (f[now ^ 1][i + 1][j][s] == -1)
					{
						h[now ^ 1].push_back(Event(i + 1, j, s));
						f[now ^ 1][i + 1][j][s] = f[now][i][j][s];
					}
					if (f[now][i][j][s] < f[now ^ 1][i + 1][j][s])
						f[now ^ 1][i + 1][j][s] = f[now][i][j][s];
				}
			}
			
			for (int k = 0; k < (int)h[now].size(); k++)
			{
				f[now][h[now][k].i][h[now][k].j][h[now][k].s] = -1;
			}
			h[now].clear();
			now ^= 1;
		}
		
		ans = inf;
		S = __builtin_popcount(S);
		for (int i = 0; i < (int)h[now].size(); i++)
		{
			int tmp = __builtin_popcount(h[now][i].s);
			ans = min(ans, S - tmp + f[now][h[now][i].i][h[now][i].j][h[now][i].s]);
		}
		cases++; printf("Case %d: %d\n", cases, ans);
		printf("\n");
	}
	return 0;
}
