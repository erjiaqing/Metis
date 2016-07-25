#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const int N = 3600;
int d[N];
pair<int ,int> a[N];
int n, m, nn, ans, now;

int main()
{
	while (1)
	{
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) return 0;
		nn = n * n;
		for (int i = 1; i <= nn; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[i] = make_pair(x, y);
		}
		sort(a + 1, a + nn + 1);
		for (int i = 0; i < nn; i++)
			d[i + 1] = i % n;
		ans = (int)1e8;
		for (int i = 1; i <= m - n + 1; i++)
		{
			now = 0;
			for (int j = 1; j <= nn; j++)
				now += abs(a[j].second - d[j] - i);
			if (now < ans) ans = now;
		}
		printf("%d\n", ans);
	}
	return 0;
}
