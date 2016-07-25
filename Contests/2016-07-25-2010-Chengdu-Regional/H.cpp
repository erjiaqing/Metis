#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const double eps = 1e-8;

double f[25][25][25][25][3][2];
bool vist[25][25][25][25][3][2];
double s[2][3], w[2][3];

double dfs(int a, int b, int c, int d, int e, int step){
	
	if(vist[a][b][c][d][e][step]) return f[a][b][c][d][e][step];
	vist[a][b][c][d][e][step] = true;
	
	double rtn = 0.00, p;
	int n = a + b + c + d + (e != 0);
	
	p = min(s[step][0] - w[step][0] * n, 1.00);
	if(a > 1 && p > eps) rtn = max(rtn, p * (1.00 - dfs(a - 1 + (e + 1 == 3), b + 1, c, d, (e + 1) % 3, !step)));
	p = min(s[step][1] - w[step][1] * n, 1.00);
	if(a > 1 && p > eps) rtn = max(rtn, p * (1.00 - dfs(a - 1 + (e + 1 == 3), b, c + 1, d, (e + 1) % 3, !step)));
	p = min(s[step][2] - w[step][2] * n, 1.00);
	if(c > 0 && p > eps) rtn = max(rtn, p * (1.00 - dfs(a + (e + 1 == 3), b, c - 1, d + 1, (e + 1) % 3, !step)));
	
	return f[a][b][c][d][e][step] = rtn;
}

void work(){
	
	int n;
	scanf("%d", &n);
	
	for(int i = 0; i <= 1; ++i)
		for(int j = 0; j < 3; ++j)
			scanf("%lf%lf", &s[i][j], &w[i][j]);
	memset(vist, 0, sizeof vist);
	printf("%.4f\n", dfs(n, 0, 0, 0, 0, 0));
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();
	
	return 0;
}
