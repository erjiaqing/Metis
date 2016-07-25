#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const int maxn = 1e4 + 5;

int n, a[maxn], b[maxn], c[maxn];

double calc(double x){
	
	double rtn = -1000.00;
	for(int i = 1; i <= n; ++i)
		rtn = max(rtn, x * x * a[i] + x * b[i] + c[i]);
	return rtn;
}

double ans(double left, double rght){
	
	double rtn = 1000.00;
	int step = 0;
	while(left + eps < rght && ++step <= 100){
		double m1 = (left * 2.00 + rght) / 3.00;
		double m2 = (left + rght * 2.00) / 3.00;
		double cm1 = calc(m1);
		double cm2 = calc(m2);
		if(cm1 < cm2) rght = m2;
		else left = m1;
		rtn = min(cm1, cm2);
	}
	return rtn;
}

void work(){
	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]);
	printf("%.4f\n", ans(0.00, 1000.00) + eps);
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
