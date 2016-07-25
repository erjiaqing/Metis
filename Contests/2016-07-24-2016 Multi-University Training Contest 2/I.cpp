#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200;
int n, m, x[N], y[N];

int solve(int l, int r)
{
	int res = 0;
	for (int i = r; i > l; i--)
	{
		res += y[i] * (x[i] - x[i - 1]);
	}
	return res;
}

int gcd(int a, int b)
{
	return (b == 0) ? a : gcd(b, a % b);
}

void print(int x, int y)
{
	int tmp = gcd(x, y);
	printf("%d/%d\n", x / tmp, y / tmp);
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));	
		for (int i = 1; i <= m; i++)
			scanf("%d%d", &x[i], &y[i]);
		x[++m] = n + 1; y[m] = 0;
		if (x[1] == 1)
		{
			if (x[2] == 2)
			{
				int sum;
				sum = solve(2, m);
				print(y[1] + y[2], sum + y[1] + y[2]);
			}
			else
			{
				int p, q;
				int ansp = 0, ansq = 1;
				for (int i = y[1]; i >= y[2]; i--)
				{
					p = y[1] + i;
					q = solve(1, m) - y[2] + i + y[1];
					if (p * ansq > ansp * q)
						ansp = p, ansq = q;
				}
				print(ansp, ansq);
			}
		}
		else if (x[1] == 2)
		{
			int p, q;
			int ansp = 0, ansq = 1;
			x[0] = 0;
			for (int i = 100; i >= max(y[1], 1); i--)
			{
				p = i + y[1];
				q = solve(1, m) + p;
				if (p * ansq > ansp * q)
					ansp = p, ansq = q;
			}
			print(ansp, ansq);
		}
		else if (x[1] == 0 || x[1] >= 3)
		{
			int p, q;
			int ansp = 0, ansq = 1;
			x[0] = 2;
			for (int i = 100; i >= 1; i--)
				for (int j = i; j >= y[1]; j--)
				{
					p = i + j;
					q = solve(0, m) + p;
					if (p * ansq > ansp * q)
						ansp = p, ansq = q;
				}
			print(ansp, ansq);
		}
	}
	return 0;
}
