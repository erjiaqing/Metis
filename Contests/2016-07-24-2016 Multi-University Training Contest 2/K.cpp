#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k, cnt;

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		k = cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			if (x % 2 == 1) k = k + 1;
			cnt += x / 2;
		}
		if (k == 0) printf("%d\n", cnt * 2);
		else printf("%d\n", cnt / k * 2 + 1);
	}
	return 0;
}
