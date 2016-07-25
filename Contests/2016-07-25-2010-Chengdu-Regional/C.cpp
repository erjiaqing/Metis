#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int a[105], n, m, ans, mn;

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= m; i++)
		{
			int x;
			scanf("%d", &x);
			ans = a[1]; mn = __builtin_popcount(a[1] ^ x);
			for (int j = 2; j <= n; j++)
			{
				if (__builtin_popcount(a[j] ^ x) < mn)
				{
					ans = a[j];
					mn = __builtin_popcount(a[j] ^ x);
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
