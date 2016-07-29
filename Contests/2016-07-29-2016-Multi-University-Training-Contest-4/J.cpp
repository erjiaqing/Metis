#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 111111;
int c[N], n, ans, k;

void Add(int x, int p)
{
	x++;
	for (; x <= n + 5; x += x & (-x))
		c[x] += p;
}
int get(int x)
{
	int res = 0;
	x++;
	for (; x; x -= x & (-x))
		res += c[x];
	return res;
}

int main()
{
	int T, cases = 0; scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		memset(c, 0, sizeof(c));
		ans = 0; k = 0;
		Add(0, - n * 2); Add(1, n * 2);
		for (int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
				//for (int p = 0; p <= n; p++) printf("%d ", get(p)); puts("///");
			if (x == 0)
			{
				ans++;
				Add(0, 1);
				Add(k + 1, -1);
			}
			else
			{
				int l = 0, r = k;
				while (l < r)
				{
			//printf("%d %d\n", l, r);
					int m = (l + r + 1) / 2;
					if (get(m) >= x) r = m - 1;
					else l = m; 
				}
				int now = get(l);
				if (x <= now) continue;
				if (l == k)
				{
					k++;
				//printf("%d %d\n", k, x - now);
					Add(k, x);
					Add(k + 1, -x);
				}
				else
				{
					int del = x - get(l + 1);
					//printf("%d %d\n", x, get(l + 1));
					Add(l + 1, del);
					Add(l + 2, -del);
				}
			}
			//printf("%d %d\n", i, ans + k);
		}
		cases++; printf("Case #%d: %d\n", cases, ans + k);
	}
	return 0;
}
