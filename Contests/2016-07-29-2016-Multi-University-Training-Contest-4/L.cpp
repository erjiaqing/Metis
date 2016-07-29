#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n, a[N], l[N], r[N], c[N];

void Add(int x)
{
	for (; x <= n; x += x & (-x))
		c[x] += 1;
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
	int T, cases = 0; scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			l[a[i]] = i;
			r[a[i]] = i;
		}
		for (int i = 1; i <= n; i++)
			l[i] = min(l[i], i);
		memset(c, 0, sizeof(c));
		for (int i = n; i >= 1; i--)
		{
			r[a[i]] = max(r[a[i]], i + getcnt(a[i]));
			Add(a[i]);
		}
		//for (int j = 1; j <= n; j++) printf("%d ", l[j]); puts("");
		cases++; printf("Case #%d:", cases);
		for (int i = 1; i <= n; i++)
			printf(" %d", r[i] - l[i]);
		printf("\n");
	}
	return 0;
}
