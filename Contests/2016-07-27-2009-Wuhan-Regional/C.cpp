#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, D;
double ans;
int p, L, v;

int main()
{
	int Case = 0;
	while(scanf("%d%d", &n, &D) == 2 && !(n == 0 && D == 0))
	{
		++Case;
		
		ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d%d", &p, &L, &v);
			ans += 2.0 * L / (double)v;
			D -= L;
		}
		ans += (double)D;
				
		printf("Case %d: %.3f\n\n", Case, ans);
	}
	return 0;
}
