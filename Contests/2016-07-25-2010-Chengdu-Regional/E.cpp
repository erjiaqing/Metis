#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define mp make_pair
#define fi first
#define se second

const int h[7] = {2, 1, 4, 8, 16, 32, 64};
const int dx[4] = {1, 0, 0, -1};
const int dy[4] = {0, -1, 1, 0};
const char Dir[4] = {'D', 'L', 'R', 'U'};
int a[2][8][8], n, now;
pair<int, int> s[2], t[2];
pair<pair<int, int>, pair<int, int> > Q[10000];
int pre[10000], dir[10000], l, r;
bool vis[8][8][8][8];

pair<int, int> Walk(pair<int, int> now, int d, int k)
{
	int x = now.fi, y = now.se;
	if (!(a[k][x][y] & h[d])) x += dx[d], y += dy[d];
	if (x < 1 || x > n || y < 1 || y > n || !(a[k][x][y] & h[4])) return mp(0, 0);
	return mp(x, y);
}

int bfs()
{
	while (l <= r)
	{
		pair<int, int> now1 = Q[l].fi, now2 = Q[l].se;
		if (now1 == t[0] && now2 == t[1]) return l;
		//printf("%d %d %d %d\n", now1.fi, now1.se, now2.fi, now2.se);
		for (int i = 0; i < 4; i++)
		{
			pair<int, int> nxt1 = Walk(now1, i, 0), nxt2 = Walk(now2, i, 1);
			if (nxt1.fi && nxt2.fi && !vis[nxt1.fi][nxt1.se][nxt2.fi][nxt2.se])
			{
				vis[nxt1.fi][nxt1.se][nxt2.fi][nxt2.se] = 1;
				Q[++r] = mp(nxt1, nxt2);
				pre[r] = l;
				dir[r] = i;
				if (nxt1 == t[0] && nxt2 == t[1]) return r;
			}
		}
		l++;
	}
	return 0;
}

int main()
{
	int T; scanf("%d", &T); T--;
	now = 0; n = 6;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &a[now][i][j]);
			if (a[now][i][j] & h[5]) s[now] = mp(i, j);
			if (a[now][i][j] & h[6]) t[now] = mp(i, j);  //错误点
		}
	while (T--)
	{
		now ^= 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				scanf("%d", &a[now][i][j]);
				if (a[now][i][j] & h[5]) s[now] = mp(i, j);
				if (a[now][i][j] & h[6]) t[now] = mp(i, j);  //错误点
			}
		memset(vis, 0, sizeof(vis));
		vis[s[0].fi][s[0].se][s[1].fi][s[1].se] = 1;
		l = r = 1; Q[1] = mp(s[0], s[1]);
		
		int tt = bfs();
		if (tt > 0)
		{
			int m = 0, ans[10000];
			while (tt > 1)
			{
				ans[++m] = dir[tt];
				tt = pre[tt];
			}
			for (int i = m; i >= 1; i--)
				printf("%c", Dir[ans[i]]);
			printf("\n");
		}
		else printf("-1\n");
	}
	return 0;
}
