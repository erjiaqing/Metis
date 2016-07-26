#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define L x * 2
#define R x * 2 + 1

const int N = 2000005;
int s0[10005], s1[10005], n, m, t, p[10005];
int tot, num[N * 3], c[N * 3];
bool ans[N];

struct Event {
	int x, y1, y2, tp;
	Event() {}
	Event(int x, int y1, int y2, int tp) : x(x), y1(y1), y2(y2), tp(tp) {}
	friend bool operator < (Event a, Event b)
	{
		return a.x < b.x || a.x == b.x && a.tp > b.tp;
	}
} a[N];

void Add(int x, int k)
{
	for (; x <= tot; x += x & (-x))
		c[x] += k;
}

int getcnt(int x)
{
	int res = 0;
	for (; x; x -= x & (-x))
		res += c[x];
	return res;
}

int main()
{
	int T; scanf("%d", &T);
	memset(c, 0, sizeof(c));
	
	while (T--)
	{
		tot = 0;
		scanf("%d%d", &n, &m);
		int now = 0; s0[0] = s1[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &p[i]);
			s0[i] = s0[i - 1];
			s1[i] = s1[i - 1];
			if (now == 0) s0[i] += p[i];
			else s1[i] += p[i];
			now ^= 1;
		}
		t = 0;
		int mx[3], now0, now1;
		for (int l = 1; l < n; l++)
			for (int r = l + 1; r <= n; r++)
			{
				mx[0] = mx[1] = 0;
				mx[(l + 1) % 2] += p[l];
				mx[(r + 1) % 2] += p[r];
				now0 = s0[r - 1] - s0[l];
				now1 = s1[r - 1] - s1[l];
				a[++t] = Event(now0, now1, now1 + mx[1], 1);
				a[++t] = Event(now0 + mx[0], now1, now1 + mx[1], -1);
				num[++tot] = now1, num[++tot] = now1 + mx[1];
			}
		for (int i = 1; i <= m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[++t] = Event(x, y, i, 0);
			num[++tot] = y;
		}
		sort(a + 1, a + t + 1);
		
		sort(num + 1, num + tot + 1);
		tot = unique(num + 1, num + tot + 1) - (num + 1);
		for (int i = 1; i <= t; i++)
		{
			if (a[i].tp != 0)
			{
				a[i].y1 = lower_bound(num + 1, num + tot + 1, a[i].y1) - (num + 1) + 1;
				a[i].y2 = lower_bound(num + 1, num + tot + 1, a[i].y2) - (num + 1) + 1;
			}
			else a[i].y1 = lower_bound(num + 1, num + tot + 1, a[i].y1) - (num + 1) + 1;
		}
		tot++;
		
		for (int i = 1; i <= t; i++)
		{
			if (a[i].tp != 0)
			{
				Add(a[i].y1, a[i].tp); Add(a[i].y2 + 1, -a[i].tp);
			}
			else
			{
				ans[a[i].y2] = (getcnt(a[i].y1) > 0);
			}
			//for (int j = 1; j <= tot; j++) printf("%d ", getcnt(j)); puts("");
		}
		
		for (int i = 1; i <= m; i++)
			printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}
