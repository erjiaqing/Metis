#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 105;
const int maxm = 55;
const int inf = 1e9;

int n, m, a[maxn], mp[maxm][maxm], f[maxn][maxm];

void work(){
	
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", &mp[i][j]);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			f[i][j] = -inf;
	for(int j = 1; j <= m; ++j) if(a[1] == -1 || a[1] == j) f[1][j] = 0;
	for(int i = 2; i <= n; ++i)
		for(int j = 1; j <= m; ++j){
			for(int k = 1; k <= m; ++k)
				f[i][j] = max(f[i][j], f[i-1][k] + mp[k][j]);
			if(a[i] != -1 && a[i] != j) f[i][j] = -inf;
		}
	int ans = 0;
	for(int i = 1; i <= m; ++i) ans = max(ans, f[n][i]);
	
	/*for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			printf("f[%d][%d] = %d\n", i, j, f[i][j]);*/
	
	printf("%d\n", ans);
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--) work();

	return 0;
}
