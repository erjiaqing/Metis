#include <cstdio>
#include <iostream>
using namespace std;

const double eps = 1e-8;

const int maxn = 1e3 + 5;

int n, c[maxn];
double exp;

int main(){
	
	while(scanf("%d", &n) == 1){
		
		exp = 0.00;
		for(int i = 1; i <= n; ++i) scanf("%d", &c[i]);
		if(n == 1){
			exp = c[1];
			printf("%.10f\n", exp);
			continue;
		}
		for(int i = 1; i <= n; ++i){
			if(i == 1 || i == n) exp += double(c[i]) / 2.00;
			else exp += double(c[i]) / 3.00;
		}
		printf("%.10f\n", exp);
	}

	return 0;
}
