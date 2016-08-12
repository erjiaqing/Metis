#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

const int maxn = 5e4 + 5;
const double inf = 1e18;
const double eps = 1e-12;

int n, k;
long long x[maxn], s[maxn], s2[maxn];
double ans;

void work(){
	
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i){
		int y;
		scanf("%d", &y);
		x[i] = y;
	}
	sort(x + 1, x + 1 + n);
	for(int i = 1; i <= n; ++i) s[i] = s[i-1] + x[i];
	for(int i = 1; i <= n; ++i) s2[i] = s2[i-1] + x[i] * x[i];
	
	if(n == k){
		puts("0");
		return;
	}
	
	ans = inf;
	for(int i = n - k; i <= n; ++i){
		double xbar = 1.00 * (s[i] - s[i-n+k]) / (n - k);
		//printf("%lf\n", xbar);
		ans = min(ans, xbar * xbar * (n - k) + (s2[i] - s2[i-n+k]) - 2.00 * xbar * (s[i] - s[i-n+k]));
	}
	printf("%.12f\n", ans + eps);
}

int main(){

	int t;
	scanf("%d", &t);
	while(t--) work();
	
	return 0;
}
