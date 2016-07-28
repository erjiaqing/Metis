#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-12;
const int maxn = 1e3 + 5;

int n, q, m;
double r[maxn], c[maxn], t[maxn];
double cv, v[maxn], sv;

bool check(double tt){
	
	double cc = cv * m * tt;
	for(int i = 1; i <= n; ++i){
		if(r[i] + eps > v[i] * tt) continue;
		double dc = v[i] * tt - r[i];
		cc -= dc;
		if(cc < -eps) return false;
	}
	return true;
}

double binary(double left, double rght){
	
	int step = 0;
	for(int rep = 1; rep <= 200; ++rep){
		double mid = (left + rght) / 2.00;
		if(check(mid)) left = mid;
		else rght = mid;
	}
	return left;
}

void work(){
	
	scanf("%lf", &cv);
	sv = 0.00;
	for(int i = 1; i <= n; ++i){
		scanf("%lf%lf%lf", &c[i], &t[i], &r[i]);
		v[i] = c[i] / t[i];
		sv += v[i];
	}
	
	for(m = 0; m <= 400; ++m) if(cv * m + eps > sv) break;
	printf("%d\n", m);
	
	while(q--){
		scanf("%d", &m);
		double ans = binary(0.00, 1e5 + 1);
		if(ans > 1e5 + eps) puts("-1.000");
		else printf("%.3f\n", ans + eps);
	}
}

int main(){
	
	int t;
	for(int tt = 1; ; ++tt){
		scanf("%d%d", &n, &q);
		if(n + q == 0) break;
		printf("Case %d:\n", tt);
		work();
	}

	return 0;
}
