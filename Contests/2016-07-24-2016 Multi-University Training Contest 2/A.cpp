#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long s1, s2;

int gcd(int a, int b)
{
	return (b == 0) ? a : gcd(b, a % b);
}

void print(long long x, int y)
{
	int tmp = gcd(y, x % y);
	cout << x / tmp << '/' << y / tmp << endl;
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		s1 = 0; s2 = 0;
		for (int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			x = abs(x);
			s1 = s1 + x;
			s2 = s2 + 1LL * x * x;
		}
		print(s2 * n - s1 * s1, n);
	}
	return 0;
}
