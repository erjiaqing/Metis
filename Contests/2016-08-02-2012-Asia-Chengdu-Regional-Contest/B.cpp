#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double e = 2.718281828;

int n;
double p;

void work(){

	double pp = 0;
	double qq = 0;
	for(int i = 1; i <= n + 1; ++i) pp += log(p), qq += log(1.0 - p);
	double ans = 0;
	for(int m = n + 1; m <= 2 * n + 1; ++m){
		if(m > n + 1) pp += log(m - 1) - log(m - n - 1);
		if(m > n + 1) qq += log(m - 1) - log(m - n - 1);
		if(m > n + 1) pp += log(1.0 - p);
		if(m > n + 1) qq += log(p);
		ans += pow(e, pp) * (2 * n - m + 1);
		ans += pow(e, qq) * (2 * n - m + 1);
		//printf("%d : %lf\n", m, (pp + qq) * (2 * n - m + 1));
	}
	/*
	double pp = 1;
	double qq = 1;
	for(int i = 1; i <= n + 1; ++i) pp *= p, qq *= (1.0 - p);
	double ans = 0;
	for(int m = n + 1; m <= 2 * n + 1; ++m){
		if(m > n + 1) pp *= 1.0 * (m - 1) / (m - n - 1);
		if(m > n + 1) qq *= 1.0 * (m - 1) / (m - n - 1);
		if(m > n + 1) pp *= (1.0 - p);
		if(m > n + 1) qq *= p;
		ans += (pp + qq) * (2 * n - m + 1);
		//printf("%d : %lf\n", m, (pp + qq) * (2 * n - m + 1));
	}
	*/
	printf("%.10f\n", ans);
}

int main(){
	
	int cs = 0;
	while(scanf("%d%lf", &n, &p) == 2){
		printf("Case %d: ", ++cs);
		work();
	}

	return 0;
}
