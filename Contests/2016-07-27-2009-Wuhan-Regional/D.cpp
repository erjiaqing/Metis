#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const double eps = 1e-8;

int main()
{
	int cases = 0;
	int n, m, v;
	while (1)
	{	
		scanf("%d%d%d", &n, &m, &v);
		if (n == 0 && m == 0 && v == 0) break;
		double sum = 0.0;
		for (int i = 1; i <= n; i++)
		{
			double x;
			int p;
			scanf("%lf%d", &x, &p);
			sum += x * (100 - p) / 100;
		}
		cases++;
		printf("Case %d: %.2f\n", cases, sum / (double)v + eps);
		printf("\n");
	}
	return 0;
}
