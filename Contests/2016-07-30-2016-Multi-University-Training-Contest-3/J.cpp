#include <cstdio>
#include <iostream>
using namespace std;

int a, v1, v2;

double sqr(double x)
{
	return x * x;
}

int main(){
	
	while(scanf("%d%d%d", &a, &v1, &v2) == 3){
		if(a == 0){
			puts("0.000000000");
			continue;
		}
		if(v1 <= v2) puts("Infinity");
		else printf("%.10f\n", 1.0 * a * v1  / (sqr(v1) - sqr(v2)));
	}
	
	return 0;
}
